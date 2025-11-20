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

bool check(vector<int>& vec, int k)
{
	for (int i = 0; i < vec.size() - 1; ++i)
		if (abs(vec[i + 1] - vec[i]) > k)
			return false;
	return true;
}


int main()
{
	int n, k, ans{ 0 };
	cin >> n >> k;
	vector<int> vec(n);
	for (int i = 0; i < vec.size(); ++i)
		vec[i] = i + 1;
	do
	{
		if (check(vec, k))
			++ans;
	} while (next_permutation(vec.begin(), vec.end()));
	cout << ans;
	return 0;
}