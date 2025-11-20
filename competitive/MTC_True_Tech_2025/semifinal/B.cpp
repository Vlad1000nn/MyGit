#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <map>

#define all(x) (x).begin(), (x).end()
#define isz(x) (x).size()

using namespace std;

int main() {
    
    int t; cin >> t;
    while(t--) {
        int n; cin >> n;
        map<int, int> starts, ends;
        for(int i = 0, x;i<n;++i)
        {
            cin >> x;
            if(x < 0)
                ends[abs(x)]++;
            else
            starts[x]++;
        }

        int ans = 0;

        auto it1 = starts.begin();
        auto it2 = ends.begin();

        while(it1 != starts.end() && it2 != ends.end()) {

            if(it1->first > it2->first) break;
            int duration = it2->first - it1->first;
            while(it1->second > 0 && it2->second > 0) {
                ans += duration;
                it1->second--;
                it2->second--;
            }
            if(it1->second == 0)
                ++it1;
            if(it2->second == 0)
                ++it2;
        }

        if(it1 != starts.end() || it2 != ends.end())
            ans = -1;

        cout << ans << '\n';
    }
    return 0;
}