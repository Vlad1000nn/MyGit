#include <bits/stdc++.h>

using namespace std;

#define isz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

int get_bit(int x, int n)  {
    return (x >> n) & 1;
}

constexpr long double EPS = 1e-9;

int gauss_solve(std::vector<std::vector<long double>>& A, const int n, const int m, std::vector<bool>& isBasis) {

    int rank = 0;

    for(int col = 0; col < m && rank < n; ++col) {
        int curr = rank;
        for(int i = curr; i < n; ++i) {
            if(std::abs(A[i][col]) > std::abs(A[rank][col])) {
                curr = i;
            }
        }

        if(std::abs(A[curr][col]) < EPS) {
            continue;
        }
        isBasis[col] = true;
        std::swap(A[rank], A[curr]);
        
        for(int k = m - 1; k >= col; --k) {
            A[rank][k] /= A[rank][col];
        }

        for(int i = 0; i < n; ++i) {
            if(i == rank) continue;
            long double coeff = -A[i][col];
            for(int k = col; k < m; ++k) {
                A[i][k] += coeff * A[rank][k];
            }
        }

        ++rank;
    }

    return rank;
}


int main() {
    
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    std::string line;
    std::vector<std::string> patterns;
    std::vector<std::vector<std::vector<int>>> buttons;
    std::vector<std::vector<int>> voltages;

    while(getline(fin, line)) {
        
        int sz = isz(line);
        std::vector<std::vector<int>> line_buttons;

        for(int i = 0; i < sz; ++i) {
            switch(line[i]) {
                case '[': {
                    std::string pattern;
                    ++i;
                    while(line[i] != ']') {
                        pattern.push_back(line[i] == '#' ? '1' : '0');
                        ++i;
                    }
                    patterns.emplace_back(pattern);
                    break;
                }
                case '(': {
                    ++i;
                    std::vector<int> nums;
                    std::string num_s;
                    while (line[i] != ')') {
                        if(line[i] == ',') {
                            nums.emplace_back(std::stoi(num_s));
                            num_s.clear();
                            ++i;
                            continue;
                        }
                        num_s += line[i];
                        ++i;
                    }
                    nums.emplace_back(std::stoi(num_s));
                    line_buttons.emplace_back(nums);
                    break;
                }
                case '{': {
                    ++i;
                    std::vector<int> nums;
                    std::string num_s;
                    while(line[i] != '}') {
                        if(line[i] == ',') {
                            nums.emplace_back(std::stoi(num_s));
                        
                            num_s.clear();
                            ++i;
                            continue;
                        }
                        num_s += line[i];
                        ++i;
                    }
                    nums.emplace_back(std::stoi(num_s));
                    
                    voltages.emplace_back(nums);
                    buttons.emplace_back(line_buttons);
                    break;
                }
                case ' ': {
                    break;
                }
                default: {
                    throw 1;
                }
            }
        }
    }


    int ans = 0;
    
    const int k = isz(voltages);
    for(int i = 0; i < k; ++i) {
        
        int curr_min = 1e9;
        
        const int n = isz(buttons[i]);
        const int m = isz(voltages[i]);
        
        std::vector<std::vector<long double>> A(m, std::vector<long double>(n + 1));
        std::vector<bool> isBasis(n);

        for(int r = 0; r < m; ++r) {
            for(int c = 0; c < n; ++c) {
                A[r][c] = find(all(buttons[i][c]), r) != buttons[i][c].end();
            }
            A[r].back() = voltages[i][r];
        }

        int rank = gauss_solve(A, m, n + 1, isBasis);
        int right = *max_element(all(voltages[i]));
        
        std::vector<int> free_vars;
        std::vector<int> basis_vars;
        std::vector<int> basis_rows(n, -1);

        int curr{};
        for(int c = 0;c < n; ++c) {
            if(isBasis[c]) {
                basis_vars.push_back(c);
                basis_rows[c] = curr;
                ++curr;
            } else {
                free_vars.push_back(c);
            }
        }

        std::vector<int> currs(n);

        std::function<void(int)> dfs = [&](const int idx) {

            if(idx == isz(free_vars)) {
                
                int sum = 0;
                bool ok = true;

                for(auto& it : free_vars) {
                    sum += currs[it];
                }

                for(auto& it : basis_vars) {
                    int curr_row = basis_rows[it];
                    long double b_r = A[curr_row][n];

                    for(auto& it2 : free_vars) {
                        b_r -= A[curr_row][it2] * currs[it2];
                    }

                    // x_i >= 0
                    if(b_r < -EPS) {
                        ok = false;
                        break;
                    }
                    int b_r_int = (int)(b_r + 0.5);
                    if(std::abs(b_r - b_r_int) > EPS) {
                        ok = false;
                        break;
                    }

                    currs[it] = b_r_int;
                    sum += b_r_int;
                }

                if(ok && curr_min > sum) {
                    curr_min = sum;
                }

                return;
            }
            
            int v_idx = free_vars[idx];
            for(int v = 0; v <= right; ++v) {
                currs[v_idx] = v;
                dfs(idx + 1);
            }

        };

        dfs(0);

        ans += curr_min;

    }

    fout << ans;


    fin.close();
    fout.close();

    return 0;
}