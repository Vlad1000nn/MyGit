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



void solveJ() 
{
	ll n;
	cin>>n;
	vl a(n), b(n);
	for(auto &i: a)cin>>i;
	
	forx(i, 0, n){
		forx(p, 0, 33){
			if( (1ll<<p) > a[i] ){
				b[i] = (1ll<<p) - a[i] - 1;
				break;
			}
		}
	}
	
	ll ans = 0;
	forx(p, 0, 33){
		ll c = (1ll<<33)-1;
		forx(i, 0, n){
			if((a[i] >> p) & 1)
				c &= a[i];
			else c &= b[i];
		}
		ans = max(ans, c);
	}
	cout<<ans;
}

int main() 
{
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    ll t = 1;
    //cin>>t;
    while(t-->0){
        solveJ();
    }
    return 0;
}