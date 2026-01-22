#include <thread>
#include <iostream>
#include <vector>
#include <atomic>
#include <barrier>
#include <utility>	// for std::pair
#include <string>
#include <fstream>
#include <iomanip>

constexpr long double LOCAL_MAX_CHANGE = 1.0l;
constexpr long double LOCAL_MIN_CHANGE = -1.0l;

constexpr long double EPS = 1e-9;

// x >= y
bool ld_ge(const long double x, const long double y) {
    return !((x - y) < (-EPS));
}

// x <= y
bool ld_le(const long double x, const long double y) {
    return !((x - y) > EPS);
}

double get_cpu_time() {
	struct timespec ts;
	if (clock_gettime(CLOCK_THREAD_CPUTIME_ID, &ts) == 0) {
	    return ts.tv_sec + ts.tv_nsec * 1e-9;
	}
	return 0.0;
}

int64_t matrix_op(std::vector<long double>& matr, std::vector<double>& t_times, const int n1, const int n2, const int p) {
	const int rows_per_worker = (n1 + p - 1) / p;

	std::vector<std::thread> workers;
	workers.reserve(p);

	std::atomic<int64_t> changes_cnt = 0;
	std::barrier<> stop_point(p);

	// Thread func
	auto worker = [&](const int m) {
		double start_time = get_cpu_time();
		const int start_row = m * rows_per_worker;
		const int end_row = std::min(start_row + rows_per_worker, n1);

		std::vector<std::pair<int, long double>> changes;
		changes.reserve((end_row - start_row) * n2);

		for (int i = start_row; i < end_row; ++i) {
			for (int j = 0; j < n2; ++j) {
				int le_cnt = 0; // <= count
				int ge_cnt = 0; // >= count
				int neighbours_cnt = 0;

				for (int dx = -1; dx <= 1; ++dx) {
					for (int dy = -1; dy <= 1; ++dy) {
						if (dx == 0 && dy == 0) continue;
						const int row = i + dx;
						const int col = j + dy;
						if (row < 0 || row >= n1 || col < 0 || col >= n2) continue; // Bounds
						neighbours_cnt++;
						le_cnt += ld_le(matr[row * n2 + col], matr[i * n2 + j]);
						ge_cnt += ld_ge(matr[row * n2 + col], matr[i * n2 + j]);
					}
				}

				// Local maximum
				if (le_cnt == neighbours_cnt) {
					changes.emplace_back(n2 * i + j, LOCAL_MAX_CHANGE);
				}
				// Local minimum
				else if (ge_cnt == neighbours_cnt) {
					changes.emplace_back(n2 * i + j, LOCAL_MIN_CHANGE);
				}
			}
		}

		stop_point.arrive_and_wait();

		for (const auto& [index, value] : changes) {
			matr[index] = value;
		}

		changes_cnt.fetch_add(changes.size()); // Add changes count for current thread

		double end_time = get_cpu_time();
		t_times[m] += end_time - start_time;

		// Wait foir others
		stop_point.arrive_and_wait();
	};

	for (int i = 1; i < p; ++i) {
		workers.emplace_back(worker, i);
	}

	// Main thread doing work too
	worker(0);
	
	// Join threads
	for (auto& t : workers) {
		if (t.joinable()) {
			t.join();
		}
	}
	return changes_cnt.load();

}

/*
	Error codes:

	0 - success
	1 - invalid amount of arguments
	2 - invalid argument
	3 - cannot open file
	4 - invalid file contents
	5 - unknown error
*/


int main(int argc, char** argv) {

	if (argc != 5) {
		std::cerr << "Invalid amount of arguments." << std::endl << "Usage: " << argv[0] << " p n1 n2 filename" << std::endl;
		return 1;
	}

	int p, n1, n2;
	std::string filename;

	p = std::atoi(argv[1]);
	n1 = std::atoi(argv[2]);
	n2 = std::atoi(argv[3]);
	filename = argv[4];
	

	if (p < 1 || n1 < 1 || n2 < 1) {
		std::cerr << "Invalid argument." << std::endl << "p, n1, n2 must be positive integers" << std::endl;
		return 2;
	}

	std::vector<long double> matr(n1 * n2);
	std::ifstream fin(filename);
	if (!fin.is_open()) {
		std::cerr << "Error. Cannot open file " << filename << std::endl;
		return 3;
	}

	for (int i = 0; i < n1 * n2; ++i) {
		if (!(fin >> matr[i])) {
			std::cerr << "Invalid file contents" << std::endl;
			return 4;
		}
	}
	
	fin.close();

	try {
		std::vector<double> t_times(p);
		int64_t changes_cnt = matrix_op(matr, t_times, n1, n2, p);

        std::cout << std::fixed;
        //std::cout << std::setprecision(12);

		std::cout << "Total changes: " << changes_cnt << std::endl;

		double summary_time = 0.0;
		for (int i = 0; i < p; ++i) {
			std::cout << "Thread " << i << " time: " << t_times[i] << std::endl;
			summary_time += t_times[i];
		}

		std::cout << "Total time: " << summary_time << std::endl;

		std::cout << "--------------- MATRIX -------------------" << std::endl;

		for (int i = 0; i < n1; ++i) {
			for (int j = 0; j < n2; ++j) {
				std::cout << matr[i * n2 + j] << ' ';
			}
			std::cout << std::endl;
		}

		std::cout << "------------------------------------------" << std::endl;
	
	}
	catch (...) {
		std::cerr << "Unknown Error" << std::endl;
		return 5;
	}

	return 0;
}
