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

int summary(vector<int>& vec, int N[11][11])
{
	int ans = { 0 };
	for (int i = 0; i < vec.size(); ++i)
	{
		ans += N[i + 1][vec[i]];
	}
	return ans;
}


int main()
{
	int n, minimum = 100000;
	cin >> n;
	int N[11][11];
	for (int i = 1; i <= n; ++i)
		for (int g = 1; g <= n; ++g)
			cin >> N[i][g];

	vector<int> vec(n);
	for (int i = 0; i < vec.size(); ++i)
		vec[i] = i + 1;
	do
	{
		int buff = summary(vec, N);
		if (buff < minimum)
			minimum = buff;
	} while (next_permutation(vec.begin(), vec.end()));

	cout << minimum;
	return 0;
}