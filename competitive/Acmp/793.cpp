clude <cmath>
#include <cstdlib>
#include <string>
#include <vector>


using namespace std;


int number_sum(int n);

bool isSimple(int x)
{
    for (int i = 2; i <= sqrt(x); i++)
    {
        if (x % i == 0)
            return false;
    }
    return true;
}

int primes_sum(int n)
{
    int sum = { 0 };
    if (!isSimple(n))
    {
        while (n != 1)
        {
            while (n % 2 == 0)
            {
                sum += 2;
                n /= 2;
            }
            for (int i = 3; i <= n; i += 2)
            {
                while (n % i == 0)
                {
                    sum += number_sum(i);
                    n /= i;
                }
            }
        }
        return sum;
    }
    else
        return n;
}

int number_sum(int n)
{
    int sum = { 0 };
    string s = to_string(n);
    for (int i = 0; i < s.size(); i++)
    {
        sum += s[i] - '0';
    }
    return sum;
}

int main()
{
    freopen("INPUT.TXT", "r", stdin);
    freopen("OUTPUT.TXT", "w", stdout);
    string str;
    vector<string> vec;
    getline(cin, str);
    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == ' ')
        {
            vec.push_back(str.substr(0, i));
            str = str.substr(i);
            i = 0;
        }
    }
    vec.push_back(str);
    for (int i = 0; i < vec.size(); i++)
    {
        int x = stoi(vec[i]);
        if (!isSimple(x))
        {
            if (primes_sum(x) == number_sum(x))
                cout << 1;
            else
                cout << 0;
        }
        else
            cout << 0;
    }

    return 0;
}