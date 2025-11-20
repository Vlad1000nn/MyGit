#include <iostream>

int main()
{
    freopen("INPUT.TXT", "r", stdin);
    freopen("OUTPUT.TXT", "w", stdout);
    int a, b, sum;
    std::cin >> a >> b;
    std::cout << b - 1 << ' ' << a - 1;
    fclose(stdin);
    fclose(stdout);
    return 0;
}