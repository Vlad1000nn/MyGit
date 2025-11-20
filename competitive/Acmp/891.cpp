//#pragma GCC optimize("Ofast,unroll-loops")
//#pragma GCC target("avx,avx2,fma")
//#pragma GCC optimize("trapv")
//#include <bits/stdc++.h>

//#include <iostream>
//#include <cmath>
//#include <iomanip>
//#include <numeric>
//#include <algorithm>
//
//#include <chrono>
//#include <ctime>
//#include <random>   
//
//#include <list>
//#include <string>
//#include <vector>
//#include <bitset>
//#include <set>
//#include <queue>
//#include <deque>
//#include <map>
//#include <stack>
//#include <unordered_map>
//#include <unordered_set>

#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <cassert>
#include <algorithm>;

using namespace std;

//template<typename T>
//using PriorityQueue = priority_queue<T, vector<T>, greater<T>>;


using ll = long long;
using vll = vector<long long>;
using vvll = vector<vll>;



using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;

//namespace Random
//{
//    std::mt19937 mt{ std::random_device{}() };
//
//    int get(int min, int max)
//    {
//        std::uniform_int_distribution<> die{ min, max };
//        return die(mt);
//    }
//}
//
//
//class Timer
//{
//private:
//    using Clock = std::chrono::steady_clock;
//    using Second = std::chrono::duration<double, std::ratio<1> >;
//    std::chrono::time_point<Clock> m_beg{ Clock::now() };
//public:
//
//    void reset()
//    {
//        m_beg = Clock::now();
//    }
//
//    double elapsed() const
//    {
//        return std::chrono::duration_cast<Second>(Clock::now() - m_beg).count();
//    }
//};

//#define int ll

//ll binpow(ll a, ll n)
//{
//    if (!n) return 1;
//
//    ll res{ 1 };
//    while (n)
//    {
//        if (n & 1)
//            res *= a;
//        a *= a;
//        n >>= 1;
//    }
//    return res;
//}
//
//ll binpow(ll a, ll n, ll mod)
//{
//    if (!n) return 1;
//
//    ll res = 1 % mod;
//    while (n)
//    {
//        if (n & 1)
//        {
//            res *= a;
//            res %= mod;
//        }
//        a *= a;
//        a %= mod;
//        n >>= 1;
//        
//    }
//
//    return res % mod;
//}
//

// Перебор направлений
const int N[4][2] = {
          {-1,0}, {0, 1}, {1,0}, {0,-1}
};

const int INF = int(1e9);
const ll INFL = ll(1e18);


const char c = 39;

// 0 - Front, 1 - left, 2 - back, 3 - right, 4 - up, 5 - down
// 0 - left up, 1 - right up, 2 - left down, 3 - right down

struct rubick
{
    char k00, k01, k02, k03;
    char k10, k11, k12, k13;
    char k20, k21, k22, k23;
    char k30, k31, k32, k33;
    char k40, k41, k42, k43;
    char k50, k51, k52, k53;
    char k60, k61, k62, k63;

    //char kubik[6][4];

    rubick rotate(short index)
    {
        rubick next = *this;

        switch (index)
        {
        case 1:
        {
            next = next.front();
            break;
        }
        case 2:
        {
            next = next.front_2();
            break;
        }
        case 3:
        {
            next = next.right();
            break;
        }
        case 4:
        {
            next = next.right_2();
            break;
        }
        case 5:
        {
            next = next.left();
            break;
        }
        case 6:
        {
            next = next.left_2();
            break;
        }
        case 7:
        {
            next = next.up();
            break;
        }
        case 8:
        {
            next = next.up_2();
            break;
        }
        case 9:
        {
            next = next.down();
            break;
        }
        case 10:
        {
            next = next.down_2();
            break;
        }
        case 11:
        {
            next = next.back();
            break;
        }
        case 12:
        {
            next = next.back_2();
            break;
        }
        default: throw 1;
        }

        return next;
    }

    rubick front()
    {
        rubick next = *this;

        next.k00 = k02;
        next.k01 = k00;
        next.k02 = k03;
        next.k03 = k01;

        next.k30 = k42;
        next.k32 = k43;

        next.k42 = k13;
        next.k43 = k11;

        next.k11 = k50;
        next.k13 = k51;

        next.k50 = k32;
        next.k51 = k30;

        return next;
    }

    rubick front_2()
    {
        rubick next = (*this).front().front().front();
        return next;
    }

    rubick right()
    {
        rubick next = *this;


        next.k30 = k32;
        next.k31 = k30;
        next.k32 = k33;
        next.k33 = k31;

        next.k01 = k51;
        next.k03 = k53;

        next.k51 = k22;
        next.k53 = k20;

        next.k41 = k01;
        next.k43 = k03;

        next.k20 = k43;
        next.k22 = k41;

        return next;
    }

    rubick right_2()
    {
        rubick next = (*this).right().right().right();
        return next;
    }

    rubick left()
    {
        rubick next = *this;


        next.k10 = k12;
        next.k11 = k10;
        next.k12 = k13;
        next.k13 = k11;

        next.k40 = k23;
        next.k42 = k21;

        next.k21 = k52;
        next.k23 = k50;

        next.k50 = k00;
        next.k52 = k02;

        next.k00 = k40;
        next.k02 = k42;

        return next;
    }

    rubick left_2()
    {
        rubick next = (*this).left().left().left();
        return next;
    }

    rubick up()
    {
        rubick next = *this;



        next.k40 = k42;
        next.k41 = k40;
        next.k42 = k43;
        next.k43 = k41;

        next.k00 = k30;
        next.k01 = k31;

        next.k10 = k00;
        next.k11 = k01;

        next.k30 = k20;
        next.k31 = k21;

        next.k20 = k10;
        next.k21 = k11;

        return next;
    }

    rubick up_2()
    {
        rubick next = (*this).up().up().up();
        return next;
    }

    rubick down()
    {
        rubick next = *this;

        next.k50 = k52;
        next.k51 = k50;
        next.k52 = k53;
        next.k53 = k51;

        next.k02 = k12;
        next.k03 = k13;

        next.k32 = k02;
        next.k33 = k03;

        next.k12 = k22;
        next.k13 = k23;

        next.k22 = k32;
        next.k23 = k33;

        return next;
    }

    rubick down_2()
    {
        rubick next = (*this).down().down().down();
        return next;
    }

    rubick back()
    {
        rubick next = *this;


        next.k20 = k22;
        next.k21 = k20;
        next.k22 = k23;
        next.k23 = k21;


        next.k40 = k31;
        next.k41 = k33;

        next.k10 = k41;
        next.k12 = k40;

        next.k31 = k53;
        next.k33 = k52;

        next.k52 = k10;
        next.k53 = k12;

        return next;
    }

    rubick back_2()
    {
        rubick next = (*this).back().back().back();
        return next;
    }


    bool isSolved()
    {
        return (k00 == k01 && k00 == k02 && k00 == k03)
            && (k10 == k11 && k10 == k12 && k10 == k13)
            && (k20 == k21 && k20 == k22 && k20 == k23)
            && (k30 == k31 && k30 == k32 && k30 == k33)
            && (k40 == k41 && k40 == k42 && k40 == k43)
            && (k50 == k51 && k50 == k52 && k50 == k53);
    }

};


string getStr(short index)
{
    string ans;
    switch (index)
    {
    case 1:
    {
        ans = "F";
        break;
    }
    case 2:
    {
        ans += c;
        ans += 'F';
        break;
    }
    case 3:
    {
        ans = "R";
        break;
    }
    case 4:
    {
        ans += c;
        ans += 'R';
        break;
    }
    case 5:
    {
        ans = "L";
        break;
    }
    case 6:
    {
        ans += c;
        ans += 'L';
        break;
    }
    case 7:
    {
        ans = "U";
        break;
    }
    case 8:
    {
        ans += c;
        ans += 'U';
        break;
    }
    case 9:
    {
        ans = "D";
        break;
    }
    case 10:
    {
        ans += c;
        ans += "F";
        break;
    }
    case 11:
    {
        ans = "B";
        break;
    }
    case 12:
    {
        ans += c;
        ans += 'B';
        break;
    }
    default: throw 1;
    }

    return ans;
}

std::istream& operator>>(std::istream& in, rubick& r)
{
    in >> r.k00 >> r.k01 >> r.k10 >> r.k11 >> r.k20 >> r.k21 >> r.k30 >> r.k31 >> r.k40 >> r.k41 >> r.k50 >> r.k51;
    in >> r.k02 >> r.k03 >> r.k12 >> r.k13 >> r.k22 >> r.k23 >> r.k32 >> r.k33 >> r.k42 >> r.k43 >> r.k52 >> r.k53;

    return in;
}

bool operator<(const rubick& a, const rubick& b)
{
    if (a.k00 != b.k00) return a.k00 < b.k00;
    if (a.k01 != b.k01) return a.k01 < b.k01;
    if (a.k02 != b.k02) return a.k02 < b.k02;
    if (a.k03 != b.k03) return a.k03 < b.k03;

    if (a.k10 != b.k10) return a.k10 < b.k10;
    if (a.k11 != b.k11) return a.k11 < b.k11;
    if (a.k12 != b.k12) return a.k12 < b.k12;
    if (a.k13 != b.k13) return a.k13 < b.k13;

    if (a.k20 != b.k20) return a.k20 < b.k20;
    if (a.k21 != b.k21) return a.k21 < b.k21;
    if (a.k22 != b.k22) return a.k22 < b.k22;
    if (a.k23 != b.k23) return a.k23 < b.k23;

    if (a.k30 != b.k30) return a.k30 < b.k30;
    if (a.k31 != b.k31) return a.k31 < b.k31;
    if (a.k32 != b.k32) return a.k32 < b.k32;
    if (a.k33 != b.k33) return a.k33 < b.k33;

    if (a.k40 != b.k40) return a.k40 < b.k40;
    if (a.k41 != b.k41) return a.k41 < b.k41;
    if (a.k42 != b.k42) return a.k42 < b.k42;
    if (a.k43 != b.k43) return a.k43 < b.k43;

    if (a.k50 != b.k50) return a.k50 < b.k50;
    if (a.k51 != b.k51) return a.k51 < b.k51;
    if (a.k52 != b.k52) return a.k52 < b.k52;
    if (a.k53 != b.k53) return a.k53 < b.k53;

    return false;
}

bool operator==(const rubick& a, const rubick& b)
{
    return !(a < b) && !(b < a);
}

bool operator!=(const rubick& a, const rubick& b)
{
    return !(a == b);
}

// ����� ���� = 11
void solve()
{
    rubick start;
    cin >> start;
    if (start.isSolved())
    {
        cout << "Solved";
        return;
    }

    queue<rubick> q;
    std::map<rubick, rubick> m;
    m[start] = start;
    q.push(start);
    while (!q.empty())
    {
        assert(q.size() <= 155000);
        auto curr = q.front();
        q.pop();

        if (curr.isSolved())
        {
            assert(m.size() <= 155000);
            rubick prev;
            string ans;
            while (curr != start)
            {
                prev = m[curr];
                for (int i = 1; i <= 12; ++i)
                    if (prev.rotate(i) == curr)
                    {
                        ans = ans + getStr(i);
                        break;
                    }
                curr = prev;
            }
            reverse(ans.begin(), ans.end());
            cout << ans;
            return;
        }

        for (int i = 1; i <= 12; ++i)
        {
            if (i == 3 || i == 4 || i > 8) continue;
            rubick next = curr.rotate(i);
            if (m.find(next) == m.end()) {
                m[next] = curr;
                q.push(next);
            }
            /* if (m.count(next) == 0)
             {
                 m[next] = curr;
                 q.push(next);
             }*/
        }
    }
    throw 1;
}




int main()
{
    cin.tie(0);
    std::ios_base::sync_with_stdio(false);


    int t{ 1 };
    //cin >> t;
    while (t--)
        solve();
    return 0;
}