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
	int n;
	cin >> n;
	vector<int> vec(n);
	for (int i = 0, x; i < vec.size(); ++i)
	{
		cin >> x;
		vec[i] = x;
	}
	next_permutation(vec.begin(), vec.end());
	for (int i = 0; i < vec.size(); ++i)
		cout << vec[i] << ' ';

	return 0;
}