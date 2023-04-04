#include <iostream>
#include <string>

int main()
{
    freopen("INPUT.TXT", "r", stdin);
    freopen("OUTPUT.TXT", "w", stdout);
    int n;
    std::cin >> n;
    std::cout << n << 9 << 9 - n;
    fclose(stdin);
    fclose(stdout);
    return 0;
}