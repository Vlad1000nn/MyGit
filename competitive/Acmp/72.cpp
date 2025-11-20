#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <vector>
#include <string>
#include <cstring>
#include <random>
#include <numeric>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <utility>
#include <tuple>
#include <functional>
#include <chrono>

using namespace std;


int main()
{
	string s;
	cin >> s;
	next_permutation(s.begin(), s.end());
	cout << s;

	return 0;
}