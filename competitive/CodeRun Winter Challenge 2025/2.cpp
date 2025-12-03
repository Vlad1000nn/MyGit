#include <iostream>
#include <vector>

using namespace std;

int get_bit(int x, int pos) {
	return (x >> pos) & 1;
}

int main() 
{
	vector<int> a(10);
	for(int i = 0;i<10;++i)
		cin >> a[i];
	
	int best = 100, total = 0;
	for(int mask = 0; mask < (1 << 10); ++ mask) {
		int curr = 0;
		for(int i = 0;i < 10; ++i) {
			if(get_bit(mask, i)) {
				curr += a[i];
			}
		}
		int ans = abs(100 - curr);
		if(ans <= best) {
			best = ans;
			total = curr;
		} else if (ans == best && curr > total) {
			total = curr;
		}

	}

	cout << total << endl;


	return 0;
}
