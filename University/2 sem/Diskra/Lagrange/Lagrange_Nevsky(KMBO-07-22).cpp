#include <iostream>

using namespace std;

long long module(long long n, long long x)
{
	return (n + (x % n)) % n;
}

long long exceeded_gcd(long long a, long long b, long long& x, long long& y) {
	if (a == 0)
	{
		x = 0;
		y = 1;
		return b;
	}
	long long x1{}, y1{};
	long long ans = exceeded_gcd(b % a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return ans;
}


long long lagrange(int* X, int* Y, int n, int p, int x)
{
	long long ans = { 0 };

	for (int i = 0; i < p; i++)
	{
		long long sum_numerator{ Y[i] };
		long long sum_denominator{ 1 };

		for (int g = 0; g < p; g++)
		{
			if (X[g] != X[i])
			{
				sum_numerator *= (x - X[g]);
				sum_numerator = module(n, sum_numerator);
				sum_denominator *= (X[i] - X[g]);
				sum_denominator = module(n, sum_denominator);
			}
		}
		long long x1{}, y1{}, buff{};
		buff = exceeded_gcd(n, sum_denominator, x1, y1);
		y1 = module(n, y1);
		ans += sum_numerator * y1;
		ans %= n;
	}
	return ans % n;
}

int main()
{
	int X[10001];
	int Y[10001];
	int n, p, x;

	cin >> n >> x >> p;
	for (int i = 0; i < p; i++)
		cin >> X[i] >> Y[i];

	cout << lagrange(X, Y, n, p, x);

	return 0;
}