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

struct DSU{
	vl root;
	DSU(ll n): root(n + 1){
		forx(i, 1, n + 1)
			root[i] = i;
	}
	ll get_root(ll u) {
		if (u == root[u])
			return u;
		return root[u] = get_root(root[u]);
	}
	void unite(ll u, ll v) {
		u =	get_root(u);
		v = get_root(v);
		root[v] = u;
	}
};

ll gcd(ll a, ll b) {
	if (b == 0)
		return a;
	else 
		return gcd(b, a % b);
}

void solveH(){
	ll n, k;
	cin >> n >> k;
	ll u, v;
	DSU dsu(n);
	for(ll i = 0; i < k; ++i) {
		cin >> u >> v;
		dsu.unite(u, v);
	}
	map<ll, ll>cnt;
	for(ll i = 1; i <= n; ++i) {
		++cnt[dsu.get_root(i)];
	}
	ll okpair = 0;
	for(auto& x : cnt) {
		okpair += x.second * (x.second - 1);
	}
	ll allpair = n*(n-1);
	cout << okpair / gcd(max(okpair, allpair), min(okpair, allpair)) << ' ' << allpair / gcd(max(okpair, allpair), min(okpair, allpair));
}

int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    ll t = 1;
    //cin>>t;
    while(t-->0){
        solveH();
    }
    return 0;
}