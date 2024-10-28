#include <iostream>
#include <bitset>
#include <set>
#include <map>
#include <queue>
#include <cmath>
#include <array>
#include <unordered_map>
#include <cassert>
#include <functional>
#include <string>

using namespace std;
using ll = long long;
using ld = long double;

using vi = vector<ll>;
using vvi = vector<vi>;

using vl = vi;
using vvl = vvi;

#define forx(i, a, b) for(ll i=a;i<b;++i)
#define forxr(i, a, b) for(ll i=a;i>b;--i)

#define isz(x) (int)(x).size()

#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()




void solveK() 
{
    // Фиксируем правую границу, бинпоиском ищем левую границу
    // Самый худший случай 64 * 25 = 1600
    // В любом случае будет потрачено намного меньше

	ll maxw; cin >> maxw;
	ll currr = maxw;
	vector<pair<ll, char>>ans;
	char resp;
	char currch;
    // Пока правая граница >= 1
	while(currr >= 1) 
    {
		cout << "? " << currr << '\n';
		cout.flush();
		cin >> currch;
		ll l = 0, r = currr, m;
        // Делаем бинпоиск по левой границе
		while(r-l>1) 
        {
			m = (r+l)/2;
			cout << "? " << m << '\n';
			cout.flush();
			cin >> resp;
			if (resp == currch) {
            // Если буква наша, то двигаем правую границу
				r = m;
			}
            // Если нет то левую
			else 
				l = m;
		}
		ans.push_back({currr, currch});
		currr = l;
	}
	sort(all(ans));
	cout << "! ";
	for(auto& x : ans) {
		cout << x.second << ' ' << x.first << ' ';
	}
	cout.flush();
}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    ll t = 1;
    //cin>>t;
    while(t-->0){
        solveK();
    }
    return 0;
}