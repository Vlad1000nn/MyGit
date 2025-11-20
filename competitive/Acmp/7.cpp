#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <string_view>
#include <cstring>
#include <cstdio>


using namespace std;

int compare(int* N1, int* N2)
{
    if (N1[0] > N2[0])  return -1;
    if (N2[0] > N1[0]) return 1;
    for (int i = 1; i <= N1[0]; i++)
    {
        //cout << "IM HERE";
        if (N1[i] > N2[i]) return -1;
        if (N2[i] > N1[i]) return 1;

    }
    //  cout << "Hello";
    return 0;

}

void read(int* N, string s)
{
    for (int i = 1; i <= s.size(); i++)
    {
        N[i] = s[i - 1] - '0';
    }
}


int main()
{
    int N1[102];
    int N2[102];
    int N3[102];

    string s1, s2, s3;
    cin >> s1 >> s2 >> s3;

    N1[0] = s1.size();
    N2[0] = s2.size();
    N3[0] = s3.size();

    //cout << N1[0] << ' ' << N2[0] << ' ' << N3[0] << '\n';

    read(N1, s1);
    read(N2, s2);
    read(N3, s3);

    string ans;

    switch (compare(N1, N2))
    {
    case 0:
    {
        //cout << "N1=N2\n";
        switch (compare(N1, N3))
        {
        case 1:
        case 0:
            ans = s3; break;
        case -1: ans = s1; break;
        default:  cout << "Smth wrong\n"; break;
        }
        break;
    }

    case 1:
    {
        //cout << "N1<N2\n";
        switch (compare(N2, N3))
        {
        case 0:
        case -1:
            ans = s2; break;
        case 1: ans = s3; break;
        default:  cout << "Smth wrong\n"; break;
        }
        break;
    }

    case -1:
    {
        //  cout << "N1>N2\n";
        switch (compare(N1, N3))
        {
        case 1:
        case 0:
            ans = s3; break;
        case -1: ans = s1; break;
        default:  cout << "Smth wrong\n"; break;
        }
        break;
    }
    default: cout << "Smth wrong\n"; break;


    }
    cout << ans;




    return 0;
}