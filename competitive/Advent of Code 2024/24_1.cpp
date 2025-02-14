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


void dfs(map<string, string>& l, map<string, string>& r, map<string, string>& op, map<string, bool>& values, const string& curr)
{
    if (l[curr] == curr)
        return;

    dfs(l, r, op, values, l[curr]);
    dfs(l, r, op, values, r[curr]);

    if (op[curr][0] == 'X')
        values[curr] = values[l[curr]] ^ values[r[curr]];
    else if (op[curr][0] == 'A')
        values[curr] = values[l[curr]] & values[r[curr]];
    else if (op[curr][0] == 'O')
        values[curr] = values[l[curr]] | values[r[curr]];
    else
        cout << "DFS ERROR";
}

void solve()
{
    std::ifstream fin("input.txt");
    std::string line; 
    
    // У нас есть дерево, круто
    std::map<std::string, bool> vertex_value;
    char str1[3];
    char str2[3];
    char str3[3];
    char str4[3];
    
    // Будем строить дерево снизу вверх, рекурсивно
    std::map<std::string, std::string> l, r, op;


    while (getline(fin, line))
    {
        if (!isz(line))
            break;
        int x;
        sscanf_s(line.c_str(), "%3s: %d", &str1, 4, &x);
        vertex_value[str1] = x;
        l[str1] = str1;
    }


    while (getline(fin, line))
    {
        sscanf_s(line.c_str(), "%3s %3s %3s -> %3s", &str1, 4, &str2, 4, &str3, 4, &str4, 4);
        l[str4] = str1;
        r[str4] = str3;
        op[str4] = str2;
    }
    
    bitset<64> answ = 0;
    for (auto& [key, val] : l)
    {
        if (key[0] != 'z')
            continue;

        dfs(l, r, op, vertex_value , key);
        answ[stoi(key.substr(1, 2))] = vertex_value[key];
    }

    cout << answ.to_ullong() << '\n';
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
