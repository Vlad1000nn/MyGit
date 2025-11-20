#include <iostream>

int main()
{
    freopen("INPUT.TXT", "r", stdin);
    freopen("OUTPUT.TXT", "w", stdout);
    int a;
    std::cin >> a;
    std::cout << a;
    fclose(stdin);
    fclose(stdout);
    return 0;
}