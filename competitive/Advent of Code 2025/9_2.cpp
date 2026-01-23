#include <bits/stdc++.h>

using namespace std;

#define isz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()


void bfs(std::vector<std::vector<char>>& field, int sx, int sy, char symb) {
    const int nx = isz(field);
    const int ny = isz(field[0]);
    std::queue<std::pair<int, int>> q;
    q.push(make_pair(sx, sy));

    while(!q.empty()) {
        auto [row, col] = q.front();
        q.pop();
        if(row < 0 || col < 0 || row >= nx || col >= ny) continue;
        if(field[row][col] != '.') continue;
        field[row][col] = symb;
        for(int dx = -1; dx <= 1; ++dx) {
            for(int dy = -1; dy <= 1; ++dy) {
                if(std::abs(dx + dy) != 1) continue;
                q.push(make_pair(row + dx, col + dy));
            }
        }
    }
}

struct PrefSum2D {
public:

    int n, m;

    std::vector<std::vector<int64_t>> pref;

    PrefSum2D(const std::vector<std::vector<char>>& field) {
        n = isz(field);
        m = isz(field[0]);
        pref.assign(n + 1, std::vector<int64_t>(m + 1, 0ll));
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                pref[i + 1][j + 1] = (field[i][j] == 'X') + pref[i][j + 1] + pref[i + 1][j] - pref[i][j];
            }
        }
    }

    int64_t get(int r1, int c1, int r2, int c2) const
    {
        if(r1 > r2) {
            std::swap(r1, r2);
        }        

        if(c1 > c2) {
            std::swap(c1, c2);
        }

        return pref[r2 + 1][c2 + 1] - pref[r1][c2 + 1] - pref[r2 + 1][c1] + pref[r1][c1];
    }

};

int main() {

    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    std::string line;

    std::vector<std::pair<int64_t, int64_t>> red_tails;    

    while(getline(fin, line)) {
        int comma = line.find(',');

        int64_t col = std::stoll(line.substr(0, comma)); 
        int64_t row = std::stoll(line.substr(comma + 1, isz(line) - comma - 1));
        
        red_tails.emplace_back(row, col);
    }
    const int n = isz(red_tails);

    std::vector<int64_t> xs(n), ys(n);
    for(int i = 0; i < n; ++i){
        xs[i] = red_tails[i].first;
        ys[i] = red_tails[i].second;
    }

    sort(all(xs));
    sort(all(ys));

    auto last_x = std::unique(all(xs));
    xs.erase(last_x, xs.end());

    auto last_y = std::unique(all(ys));
    ys.erase(last_y, ys.end());

    const int nx = isz(xs);
    const int ny = isz(ys);

    auto get_index = [](const std::vector<int64_t>& vec, const int64_t val) {
        return lower_bound(all(vec), val) - vec.begin() + 1; //  1-индексация
    };

    std::vector<std::vector<char>> field(nx + 2, std::vector<char>(ny + 2, '.'));

    for(int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        
        int dx = !(get_index(xs, red_tails[i].first) == get_index(xs, red_tails[j].first));
        int dy = !(get_index(ys, red_tails[i].second) == get_index(ys, red_tails[j].second));

        dx *= (red_tails[i].first < red_tails[j].first ? 1 : -1);
        dy *= (red_tails[i].second < red_tails[j].second ? 1 : -1);

        int row = get_index(xs, red_tails[i].first);
        int col = get_index(ys, red_tails[i].second);

        while(row != get_index(xs, red_tails[j].first) || col != get_index(ys, red_tails[j].second)) {
            field[row][col] = 'X';

            row += dx;
            col += dy;
        }
        field[row][col] = 'X';
    }

    // Заменили внешнюю часть на -
    bfs(field, 0, 0, '-');

    while(true) {
        int sx = -1, sy = -1;
        for(int i = 0; i < nx + 2; ++i) {
            for(int j = 0; j < ny + 2; ++j) {
                if(field[i][j] == '.') {
                    sx = i;
                    sy = j;
                    break;
                }
            }
        }

        // Заменили внутреннюю часть фигуры на X
        if(!(sx == -1 && sy == -1)) {
            bfs(field, sx, sy, 'X');
        } else {
            break;
        }
    }

    // Строим 2-мерные префикс суммы

    PrefSum2D pref(field);

    int64_t max_val = -1;

    for(int i = 0; i < n; ++i) {
        for(int j = i + 1; j < n; ++j) {
            int64_t height = std::abs(red_tails[i].first - red_tails[j].first) + 1;
            int64_t width  = std::abs(red_tails[i].second - red_tails[j].second) + 1; 
 
            int64_t curr_square = height * width;
            // Добавляем площадь на преф-суммах. Если совпала - обновляем

            int row_i = get_index(xs, red_tails[i].first);
            int row_j = get_index(xs, red_tails[j].first);
            
            int col_i = get_index(ys, red_tails[i].second);
            int col_j = get_index(ys, red_tails[j].second);

            int64_t cnt = pref.get(row_i, col_i, row_j, col_j);
            int64_t need = 1ll * (std::abs(row_i - row_j) + 1) * (std::abs(col_i - col_j) + 1); 

            if(cnt == need) {
                max_val = std::max(max_val, curr_square);
            }
        }
    }

    fout << max_val;

    return 0;
}