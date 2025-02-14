#include <bits/stdc++.h>

#define isz(x) (int)x.size()
#define all(x) (x).begin(),(x).end()

using namespace std;

using ll = long long;

struct Pad
{
    vector<int> x_arr;
    bool is_key;

    Pad(const vector<int>& input_arr, bool _is_key)
        : x_arr(input_arr)
        , is_key(_is_key)
    {  }

};

bool try_to_fit(const Pad& lock, const Pad& key)
{
    const int n = isz(lock.x_arr);
    for (int i = 0; i < n; ++i)
        if (key.x_arr[i] + lock.x_arr[i] > 5) 
            return false;

    return true;
}

void solve()
{
    std::ifstream fin("input.txt");
    std::string line; 
    
    const int height = 7;
    const int width = 5;

    vector<int> x_arr(width);
    vector<Pad> keys, locks;
    vector<string> current_pad(height, std::string(width, '.'));
    int index{};

    while (getline(fin, line))
    {
        if (!isz(line))
        {
            index = 0;
           
            bool is_key = current_pad[0][0] == '.';
            
            x_arr.assign(width, 0);
            for (int i = 1; i < height - 1; ++i)
                for (int j = 0; j < width; ++j)
                    x_arr[j] += (current_pad[i][j] == '#');

            if (is_key)
                keys.emplace_back(x_arr, is_key);
            else
                locks.emplace_back(x_arr, is_key);
            continue;
        }

        current_pad[index] = line;

        ++index;
    }
    // ВАЖНО: При вводе добавить ещё пустую стркоу в конце


    int answ{};

    for(auto& lock : locks)
        for (auto& key : keys)
            if (try_to_fit(lock, key)) 
                ++answ;

    std::cout << answ << '\n';

}


int32_t main()
{
    cin.tie(0);
    std::ios_base::sync_with_stdio(false);

    int32_t t{ 1 };

    while (t--)
        solve();

    return 0;
}
