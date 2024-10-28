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


void solveB(){
	ll abc=0, ab=0, bc=0;
	set<ll> a, b, c;
	ll k, n;
	cin>>n>>k;
	for(ll i=0, m;i<n;++i){
		cin>>m;
		a.insert(m);
	}
	for(ll i=0, m;i<n;++i){
		cin>>m;
		b.insert(m);
	}
	for(ll i=0, m;i<n;++i){
		cin>>m;
		c.insert(m);
	}

	for(auto &i: b){
		if(a.count(i)){
			if(c.count(i)){
				++abc;
			}else ++ ab;
		}else if(c.count(i)) ++bc;
	}

	ll ans = 0;
	while(abc*k > 0 ){
		--abc; -- k;
		++ans;
	}
	ans += min(k, ab+bc) * 2;
	k -= min(k, ab+bc);
	ans += k * 3;
	cout<<ans;
}


int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    ll t = 1;
    //cin>>t;
    while(t-->0){
        solveB();
    }
    return 0;
}