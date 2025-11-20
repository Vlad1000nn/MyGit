#include <iostream>

int main()
{
    freopen("INPUT.TXT", "r", stdin);
    freopen("OUTPUT.TXT", "w", stdout);
    int a, b;
    std::cin >> a >> b;
    std::cout << a + b;
    fclose(stdin);
    fclose(stdout);
    return 0;
}