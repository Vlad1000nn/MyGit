#include <iostream>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <vector>
#include <string>
#include <iomanip>
#include <utility>
#include <cstdio>


using namespace std;



int main()
{
    cin.tie(0);                  //Отключает связку cin к cout
    std::ios_base::sync_with_stdio(false);    //Отключает синхронизацию cout/cin и print/scanf

    int n;
    cin >> n;
    vector<pair<int, int>> vec;
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        vec.push_back(make_pair(x, i));
    }

    sort(vec.begin(), vec.end());

    int min_s = abs(vec[1].first - vec[0].first);
    int first_index = vec[0].second + 1;
    int second_index = vec[1].second + 1;

    for (int i = 0; i < vec.size() - 1; i++)
    {
        if (abs(vec[i + 1].first - vec[i].first) < min_s)
        {
            min_s = abs(vec[i + 1].first - vec[i].first);
            first_index = vec[i].second + 1;
            second_index = vec[i + 1].second + 1;
        }
    }
    cout << min_s << '\n' << first_index << ' ' << second_index;

    return 0;
}