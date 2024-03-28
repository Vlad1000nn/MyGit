#include <bits/stdc++.h>
 
 
 
#define isz(x) (int)x.size()
#define all(x) (x).begin(),(x).end()
 
using namespace std;
 
 
using ll = long long;
using vll = vector<long long>;
using vvll = vector<vll>;
 
using vi = vector<int>;
using vvi = vector<vi>;
 
 
 
 
template<typename T>
std::istream& operator>>(std::istream& in, vector<T>& vec)
{
    for (auto& it : vec)
        in >> it;
    return in;
}
 
// Overload vector output
template<typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& vec)
{
    for (auto& it : vec)
        out << it << ' ';
 
    return out;
}
 
 
 
//#define int ll
 
 
void solve()
{
    int n; cin >> n;
    vector<tuple<int, int, int>> time_vec(n);
    for (auto& it : time_vec)
        scanf("%d:%d:%d", &get<0>(it), &get<1>(it), &get<2>(it)), get<0>(it)--;
 
    vll vec(n);
    for (int i = 0; i < n; ++i)
        vec[i] = get<0>(time_vec[i]) * 3600 + get<1>(time_vec[i]) * 60 + get < 2>(time_vec[i]);
 
 
    sort(all(vec));
    // РџСЂРµС„РёРєСЃС‹, РїРѕС„РёРі
    vll pref(n + 1);
    for (int i = 1; i <= n; ++i)
        pref[i] = vec[i - 1];
 
    for (int i = 1; i <= n; ++i)
        pref[i] += pref[i - 1];
 
    // Р’РѕС‚ С‚СѓС‚ СЃС‡РёС‚Р°СЋ РѕС‚РІРµС‚ РґР»СЏ РєР°Р¶РґРѕРіРѕ a[i]
    vll answ(n);
    for (int i = 0; i < n; ++i)
        answ[i] = i * vec[i] - pref[i] + (n - i - 1) * (12LL * 3600 + vec[i]) - (pref[n] - pref[i + 1]);
 
    // РќСѓ Рё Р±РµСЂС‘Рј РјРёРЅРёРјСѓРј РІ answ Рё Р±РµСЂС‘Рј Р·РЅР°С‡РµРЅРёРµ РїРѕРґ СЌС‚Рё С‡Р°СЃС‹
    ll answer = vec[min_element(all(answ)) - answ.begin()];
    int hh = answer / 3600; 
    answer %= 3600;
    int mm = answer / 60;
    answer %= 60;
    int ss = answer;
    printf("%d:%02d:%02d", hh + 1, mm, ss);
}
 
int main()
{
 
        solve();
    return 0;
}