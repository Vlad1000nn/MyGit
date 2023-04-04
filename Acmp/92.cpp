#include <iostream>

int main()
{
    freopen("INPUT.TXT", "r", stdin);
    freopen("OUTPUT.TXT", "w", stdout);
    int sum;
    std::cin >> sum;
    std::cout << sum / 6 << ' ' << 2 * sum / 3 << ' ' << sum / 6;
    fclose(stdin);
    fclose(stdout);
    return 0;
}