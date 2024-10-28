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



void solve(){
	ll n;
	cin>>n;
	ll ans = 0;
	map<ll, ll> mp;
	string N = to_string(n);
	for(ll i=1;i<=n;++i){
		string s = to_string(i);

		++mp[N.size() - s.size()];
	}
	for(auto &i: mp){
		ans += (i.second + 499) / 500;
	}
	cout<<ans;
}

int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	ll t = 1;
	//cin>>t;
	while(t-->0){
		solve();
	}
	return 0;
}