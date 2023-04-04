#include <iostream>

using ll = long long;

bool solve()
{
	ll a, b, c, d;
	std::cin >> a >> b >> c >> d;

	if (a == c && b == d)
		return true;

	while (b != 0)
	{
		if (a < b)
		{
			std::swap(a, b);
			if (a == c && b == d)
				return true;
		}
		if (b == 0)
			break;
		ll countOfDivisions = a / b;
		ll a_1 = a;
		a -= countOfDivisions * b;
		ll a_2 = a;
		if (b == d && c >= a_2 && c <= a_1 && (a_1 - c) % b == 0)
			return true;
	}
	return (a == c && b == d) ? true : false;
}


int main()
{
	freopen("INPUT.TXT", "r", stdin);
	freopen("OUTPUT.TXT", "w", stdout);

	short k;
	std::cin >> k;
	for (int i = 1; i <= k; i++)
	{
		if (solve())
			std::cout << "YES\n";
		else
			std::cout << "NO\n";
	}
	fclose(stdin);
	fclose(stdout);

	return 0;
}