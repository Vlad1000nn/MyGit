#include <iostream>
#include <numeric>
#include <cmath>

using namespace std;


int main()
{
	freopen("INPUT.TXT", "r", stdin);
	freopen("OUTPUT.TXT", "w", stdout);

	int x1 = {};
	int y1 = {};
	int x2 = {};
	int y2 = {};
	cin >> x1 >> y1 >> x2 >> y2;
	cout << gcd(abs(x2 - x1), abs(y2 - y1)) + 1;

	fclose(stdin);
	fclose(stdout);

	return 0;
}