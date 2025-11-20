#include <iostream>


using namespace std;



int main()
{
    freopen("INPUT.TXT", "r", stdin);
    freopen("OUTPUT.TXT", "w", stdout);

    int N[101];
    int n, maximum;
    int sum = { 0 };
    maximum = -1;
    int max_prev = 0;
    int max_new = 0;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> N[i];
    }

    while (max_new != n - 1)
    {
        for (int i = max_prev; i < n; i++)
        {
            if (N[i] > maximum)
            {
                maximum = N[i];
                max_new = i;
            }
            else if (N[i] == maximum)
                max_new = i;
        }
        sum += maximum * (max_new - max_prev + 1);
        maximum = -1;
        max_prev = max_new + 1;

    }
    if (n == 1)
        cout << N[0];
    else
        cout << sum;

    return 0;
}