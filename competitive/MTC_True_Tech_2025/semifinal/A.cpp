#include <iostream>
#include <string>
#include <algorithm>
#include <map>

#define all(x) (x).begin(), (x).end()
using namespace std;

int digit_sum(int x) {
    int ans = 0;
    while(x) {
        ans += x % 10;
        x /= 10;
    }
    return ans;
}

int main() {
    int t; cin >> t;
    while(t--) {
        string s; cin >> s;
        if(s.size() == 1)
        {
            cout << 0 << '\n';
            continue;
        }

        int m_cnt = count(all(s), 'M');
        int t_cnt = count(all(s), 'T');
        int c_cnt = count(all(s), 'C');

        map<int,int> mp;

        for(int i = 0; i <=9;++i) {
            if(i == 0 && s[0] == 'M')  continue;
            for(int j = 0; j <=9; ++j) {
                if(j == 0 && s[0] == 'T')  continue;
                for(int k = 0;k<=9;++k) {
                    if(k == 0 && s[0] == 'C')  continue;

                    int curr = m_cnt * i + t_cnt * j + c_cnt * k;
                    while(true) {
                        if(curr == digit_sum(curr))
                            break;
                        curr = digit_sum(curr);
                    }
                    mp[curr]++;

                }
            }
        }

        if(mp.size() == 1)
            cout << 1 << '\n';
        else
            cout << 0 << '\n';
    }
    return 0;
}