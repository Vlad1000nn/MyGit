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




void solveI(){
	ll n;
	cin>>n;
	priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> b;
	
	forx(i, 0, 10)b.push({0, i});

	vector<string> s(n, "*****");

	function <void(ll, ll, ll)> go = [&](ll l, ll r, ll ind){
		if(ind == 5 || r <= l)return;
		vector<ll> vals(10, (r-l) / 10);
		ll cn = (r-l) % 10;
		vector<pair<ll, ll>> stack;
		while(cn-->0){
			stack.push_back(b.top());
			b.pop();
		}

		for(auto &i: stack){
			++i.first;
			b.push(i);
			++vals[i.second];
		}

		ll sum=0;
		for(ll i=0;i<10;++i){
			forx(j, l+sum, l+sum+vals[i]){
				s[j][ind] = '0' + i;
			}
			go(l+sum, l+sum+vals[i], ind+1);
			sum += vals[i];
		}
	}; 
	go(0, n, 0);
	for(auto &i: s)cout<<i<<'\n';

}


int main() 
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    ll t = 1;
    //cin>>t;
    while(t-->0){
        solveI();
    }
    return 0;
}