#include <iostream>
#include <string>

using namespace std;


int main()
{
    freopen("INPUT.TXT", "r", stdin);
    freopen("OUTPUT.TXT", "w", stdout);
    string str;
    cin >> str;
    if ((str[0] - '0' + str[1] - '0' + str[2] - '0') == (str[3] - '0' + str[4] - '0' + str[5] - '0'))
        cout << "YES";
    else
        cout << "NO";
    fclose(stdin);
    fclose(stdout);
    return 0;
}