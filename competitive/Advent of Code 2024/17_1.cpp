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

using vpii = vector<pair<int, int >>;
using vpll = vector<pair<ll, ll>>;


struct Computer
{
    ll A, B, C;


    Computer(ll _A, ll _B, ll _C)
        : A(_A)
        , B(_B)
        , C(_C)
    { }

    ll get_combo(ll operand)
    {
        switch (operand)
        {
        case 0:
        case 1:
        case 2:
        case 3:
            return operand;
        case 4:
            return A;
        case 5:
            return B;
        case 6:
            return C;
        default:
        {
            std::cerr << ">>" << operand << '\n';
            throw "Invalid combo operand";
        }
        }
    }

    void do_instruction(int instruction, ll operand, std::string& output, int& index)
    {
        switch (instruction)
        {
        case 0:
        {
            A = A / std::pow(2, get_combo(operand));
            index ++;
            break;
        }
        case 1:
        {
            B = B ^ operand;
            index ++;
            break;
        }
        case 2:
        {
            B = get_combo(operand) % 8;
            index++;
            break;
        }
        case 3:
        {
            if (A == 0)
                index ++;
            else
                index = operand;
            break;
        }
        case 4:
        {
            B = B ^ C;
            index ++;
            break;
        }
        case 5:
        {
            output += to_string(get_combo(operand) % 8) + ",";
            index ++;
            break;
        }
        case  6:
        {
            B = A / std::pow(2, get_combo(operand));
            index ++;
            break;
        }
        case 7:
        {
            C = A / std::pow(2, get_combo(operand));
            index ++;
            break;
        }
        default: {
            std::cerr << ".." << instruction << ' ' << operand << '\n';
            throw "Invalid instruction";
        }
        }
    }

};

void solve()
{
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

    Computer computer(input[0], input[1], input[2]);

    getline(fin, line);
    vpii commands;

    int index{ 9 };
    while (index < isz(line))
    {
        commands.emplace_back(line[index] - '0', line[index + 2] - '0');
        index += 4;
    }
    index = 0;
    std::string output;
    while (index < isz(commands)) 
        computer.do_instruction(commands[index].first, commands[index].second, output, index);
    
    cout << output << '\n';
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
