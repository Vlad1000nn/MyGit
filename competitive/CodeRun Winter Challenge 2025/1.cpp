#include <iostream>
#include <cmath>

using namespace std;

int main() 
{
	int red, blue; cin >> red >> blue;

    int ans1{}, ans2{};
    for(int h = 1; h * h <= blue; ++h) {
        int w = blue / h;
        if(w * h != blue) continue;

        if(2 * (w + h + 4) - 4 == red) {
            ans1 = w + 2;
            ans2 = h + 2;
            break;
        }
    }


    cout << max(ans1, ans2) << ' ' << min(ans1, ans2) << '\n';
	return 0;
}
