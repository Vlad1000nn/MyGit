#include <iostream>
#include <cmath>
#include <string>
#include <numeric>
#include <vector>
#include <algorithm>
#include <bitset>
#include <iomanip>

using namespace std;


int main()
{
    //cin.tie(0);                  
    //std::ios_base::sync_with_stdio(false);    
    int N[1001];
    int M[1001];
    int N1[1001];
    int M1[1001];
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> N[i];
        N1[i] = N[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> M[i];
        M1[i] = M[i];
    }
    sort(N, N + n);
    sort(M, M + n);
    reverse(N, N + n);

    for (int i = 0; i < n; i++)
    {
        int k = 0;
        while (N1[k] != N[i])
            k++;
        cout << k + 1 << ' ';
        N1[k] = 0;
    }
    cout << '\n';

    for (int i = 0; i < n; i++)
    {
        int k = 0;
        while (M1[k] != M[i])
            k++;
        cout << k + 1 << ' ';
        M1[k] = 0;
    }

    //for (int i = 0; i < n; i++)
    //{
    //    cout << N[i] << ' ';
    //}
    //cout << '\n';
    //for (int i = 0; i < n; i++)
    //{
    //    cout << M[i] << ' ';
    //}



    return 0;
}