#include <iostream>
#include <string>

int main()
{
    freopen("INPUT.TXT", "r", stdin);
    freopen("OUTPUT.TXT", "w", stdout);
    long long a, b, c;
    std::cin >> a >> b >> c;
    long long sum = 3 * a + 5 * b + 12 * c;
    std::cout << sum;
    fclose(stdin);
    fclose(stdout);
    return 0;
}