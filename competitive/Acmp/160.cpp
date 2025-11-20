
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
	int n, ans{ 1 };
	cin >> n;

	vector<int> vec(n + 1);
	vec[0] = 0;

	for (int i = 1; i < vec.size(); ++i)
		cin >> vec[i];

	for (int i = 1; i < vec.size(); ++i)
	{
		if (vec[i] == 0)
			continue;
		int buff = vec[i], temp, k = 1;
		while (buff != i)
		{
			temp = buff;
			k++;
			buff = vec[buff];
			vec[temp] = 0;
		}
		ans = lcm(k, ans);
	}
	cout << ans;
	return 0;
}

