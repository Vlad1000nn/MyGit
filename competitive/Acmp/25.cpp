#include <iostream>
#include <string>

int main()
{
    freopen("INPUT.TXT", "r", stdin);
    freopen("OUTPUT.TXT", "w", stdout);
    int a, b;
    std::cin >> a >> b;
    if (a > b)
        std::cout << '>';
    else if (a < b)
        std::cout << '<';
    else
        std::cout << '=';
    fclose(stdin);
    fclose(stdout);
    return 0;
}