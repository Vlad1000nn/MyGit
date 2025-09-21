#include <thread>		 // for std::thred
#include <mutex>		 // for std::mutex
#include <condition_variable> // for std::conditional_variable
#include <queue>		 // for std::queue
#include <vector>		 // for std::vector
#include <functional>	 // for std::function
#include <cstddef>		 // for std::size_t
#include <atomic>		 // for std::atomic
#include <utility>		 // for std::pair
#include <unordered_set> // for std::unordered_set

// main()
#include <iostream> // for std::cout
#include <chrono> // for std::chrono::milliseconds


// Реализация пула потоков, пока что умеет выполнять функции с сигнатурой void func();
class ThreadPool {
private:

	std::vector<std::thread> threads_;

	std::queue <std::pair<std::function<void()>, uint32_t>> tasks_;

	// из минусов постоянный рост сета, нужно добавить ручной сброс (потому что автоматический может затереть
	// необходимые для пользователя данные про завершённые таски)
	// либо после wait_all() сделать очистку(что вполне логично, таски выполнены)
	std::unordered_set<uint32_t> completed_tasks_;

	std::condition_variable q_cv_; // cv для очереди тасок
	std::condition_variable cv_wait_; // cv для ожидания выполнения тасок
	std::atomic<std::size_t> active_tasks_; // количество активных тасок

	std::mutex q_mtx_; // мьютекс на очередь тасок
	std::mutex task_mtx_; // мьютекс на ожидание выполнения тасок
	std::atomic<uint32_t> index_; // номер таски

	bool should_stop;

	void do_work()
	{
		std::pair<std::function<void()>, uint32_t> current_task;
		while (true) 
		{
			std::unique_lock<std::mutex> lock(q_mtx_);
			q_cv_.wait(lock, [this]() {return !tasks_.empty() || should_stop; }); // спим
			if (should_stop)
				break;

			current_task = tasks_.front(); // берём таску
			tasks_.pop();
			++active_tasks_;
			lock.unlock(); // разлочили

			current_task.first(); // делаем таску
			completed_tasks_.insert(current_task.second);
			--active_tasks_;
			cv_wait_.notify_all();
		}
	}

	// Сброс выполненных тасок
	void reset_tasks_()
	{
		index_ = 0;
		completed_tasks_.clear();
	}

public:

	// Конструктор с указанием количества потоков(по умолчанию значение в hardware_concurrency())
	// Либо лучше сделать по умолчанию 1, потому что hardware_concurrency() может вернуть 0
	explicit ThreadPool(std::size_t num_threads = std::thread::hardware_concurrency())
		: should_stop(false)
		, active_tasks_(0)
		, index_(0)

	{
		// создаём потоки
		std::size_t i = 0;
		for (; i < num_threads; ++i)
			threads_.emplace_back(&ThreadPool::do_work, this); 
	}

	/*
	template<typename Func, typename... Args>
	int add_task(Func&& func, Args&&... args) {

		func(std::forward<Args>(args)...);
	}
	*/

	// добавить таску(возвращается её номер)
	uint32_t add_task(std::function<void()> task)
	{
		uint32_t curr_index = index_++;
		{
			std::lock_guard<std::mutex> lock(q_mtx_);
			tasks_.emplace(std::move(task), curr_index); // добавили в очередь таску
		}
		q_cv_.notify_one(); // будим поток

		return curr_index;
	}

	// Дождаться выполнения таски с индексом index
	void wait(uint32_t index)
	{
		std::unique_lock<std::mutex> lock(task_mtx_);
		cv_wait_.wait(lock, [this, index] {
			return completed_tasks_.find(index) != completed_tasks_.end();
			});
	}

	// дождаться выполнения всех тасок
	void wait_all()
	{
		std::unique_lock<std::mutex> lock(q_mtx_);
		cv_wait_.wait(lock, [this]() {
			std::lock_guard<std::mutex> task_lock(task_mtx_);
			return tasks_.empty() && active_tasks_ == 0 
				&& completed_tasks_.size() == index_; // на всякий случай
			});
		// 	reset_tasks_();
	}

	// Возвращает true, если таска с индексом index УЖЕ выполнена (false в противном случае)
	bool completed(uint32_t index)
	{
		std::lock_guard<std::mutex> lock(task_mtx_); // во избежания UB при наличии выполняемых тасок в данный момент
		return completed_tasks_.find(index) != completed_tasks_.end();
	}

	// фактический деструктор, вызываем чтобы убить все потоки в пуле
	void clear() 
	{
		should_stop = true;
		q_cv_.notify_all();
		const std::size_t n = threads_.size();
		std::size_t i = 0;
		for (; i < n; ++i)
			if (threads_[i].joinable())
				threads_[i].join();
	}

	~ThreadPool()
	{
		clear();
	}

};

#include <vector>
#include <numeric>
#include <future>


void task()
{
	std::cout << std::this_thread::get_id() << " started" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	std::cout << std::this_thread::get_id() << " ended" << std::endl;
}



int main() {

	ThreadPool tpool(2);

	tpool.wait(tpool.add_task(task));
	tpool.add_task(task);
	tpool.add_task(task);
	tpool.add_task(task);
	tpool.add_task(task);
	tpool.add_task(task);
	tpool.add_task(task);
	task();
	task();

	tpool.wait_all();

	return 0;
}