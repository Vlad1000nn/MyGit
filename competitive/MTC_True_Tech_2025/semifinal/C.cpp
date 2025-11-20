#include <iostream>
#include <string>
#include <numeric>
#include <algorithm>

using namespace std;

int main() {
    int t; cin >> t;
    while(t--) {

        long long p,q; cin >> p>>q;
        long long numerator = 180;
        numerator /= __gcd(numerator, p);
        numerator *= q;
        numerator -= 1;

        cout << numerator << '\n';

    }

    return 0;
}