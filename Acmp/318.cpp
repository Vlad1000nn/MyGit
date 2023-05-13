#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstring>
#include <random>
#include <numeric>
#include <cmath>
#include <bitset>
#include <algorithm>
#include <iomanip>
#include <utility>
#include <tuple>
#include <functional>
#include <chrono>

using namespace std;


int main()
{
	int x;
	cin >> x;
	string s = bitset<32>(x).to_string();
	next_permutation(s.begin(), s.end());
	bitset<32> bits(s);
	cout << bits.to_ulong();
	return 0;
}