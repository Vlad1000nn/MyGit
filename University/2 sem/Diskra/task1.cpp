#include <iostream>

using namespace std;

int gcd(int A, int B)
{
	while (B != 0)
	{
		int x = { A % B };
		A = B;
		B = x;
	}
	return (A > 0 ? A : -A);
}

int main()
{
	freopen("INPUT.TXT", "r", stdin);
	freopen("OUTPUT.TXT", "w", stdout);

	int A = {};
	int B = {};
	cin >> A >> B;
	cout << gcd(A, B);

	fclose(stdin);
	fclose(stdout);
	return 0;
}