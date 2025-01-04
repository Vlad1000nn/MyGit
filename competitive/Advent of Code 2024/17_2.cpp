#include <bits/stdc++.h>

#define isz(x) (int)x.size()
#define all(x) (x).begin(),(x).end()

using namespace std;

using ll = long long;
using vll = vector<long long>;
using vvll = vector<vll>;

using ull = unsigned long long;

using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;

int get_bit(const ll& x, ll index)
{
    return (x >> index) & 1;
}


void solve()
{
    // run on release
    
    // Решение задачи:
    // Поскольку ответ число порядка 8^16 = 2^48, то переберём сначала первые 24 бит, а потом к ним будем перебирать вторые 24 бит

    std::ifstream fin("input.txt");
    std::string line;

    vi input;

    while (getline(fin, line))
    {
        if (!isz(line))
            break;
        char reg;
        int value;
        sscanf_s(line.c_str(), "Register %c: %d", &reg, 1, &value);
        input.push_back(value);
    }
    getline(fin, line);
    line = line.substr(9) + ",";
    vpii commands;

    int index{ 0 };
    while (index < isz(line))
    {
        commands.emplace_back(line[index] - '0', line[index + 2] - '0');
        index += 4;
    }

    std::vector<ll> need;
    for (auto& it : commands)
        need.push_back(it.first), need.push_back(it.second);

    index = 0;
    ll buff;
    std::vector<ll> answ;
    answ.reserve(20);

    ll A, B, C;
    std::vector<ll> good;

    for (int mask = 0; mask < (1 << 25); ++mask) {
        answ.clear();
        A = mask;
        // Наша программа(компьютер нам не нужен, так быстрее)
        while (A)
        {
            B = (A % 8) ^ 2;
            B ^= (A >> B);
            B ^= 3;
            answ.push_back(B % 8);
            A >>= 3;
        }

        bool ok = true;
        for (int j = isz(answ) - 1, k = isz(need) - 1; j >= 0; --j, --k)
        {
            // Если суффикс не совпал, не подходит
            if (answ[j] != need[k])
            {
                ok = false;
                break;
            }
        }
        // суффикс совпадает, один из кандидатов на первые 24 бит это mask
        if (ok) 
            good.push_back(mask);
        
    }
    
    // very_good это ответ
    vector<ll> very_good;
    for (auto& it : good)
    {
        // Перебираем следующие 24 бит
        for (int mask = 0; mask < (1 << 25); ++mask)
        {
            answ.clear();
            int  mask_size = 1;
            for(int i = 0;i<22;++i)
                if (get_bit(mask, i))
                    mask_size = i + 1;
                
            A = (it << mask_size) | mask;
            ll buff = A;
            while (A)
            {
                B = (A % 8) ^ 2;
                B ^= (A >> B);
                B ^= 3;
                answ.push_back(B % 8);
                A >>= 3;
            }
            // Если вывело больше, то остановимся(иначе улетим в бесконечность)
            if (isz(answ) > isz(need))
                continue;

            bool ok = true;
            for (int j = isz(answ) - 1, k = isz(need) - 1; k >=0 && j >= 0; --j, --k)
            {
                if (answ[j] != need[k])
                {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                good.push_back(buff);
                // Если размер совпал, то это ответы
                if (isz(answ) == isz(need))
                    very_good.push_back((it << mask_size) | mask);
            }
        }
    }

    // Выбираем самый маленький ответ
    std::sort(all(very_good));
    for (auto& it : very_good)
        std::cout << it << '\n';

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
