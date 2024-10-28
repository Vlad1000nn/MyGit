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


void solveG()
{
    // В худшем случае: 297 + 2 + 1 = 300 
	string resp = "";
	int cnt = 0;
    // Вынимаем всю очередь
	while(resp != "-1" && cnt < 297) 
    {
		cout << "get" << '\n';
		cout.flush();
		cin >> resp;
		++cnt;
	}
    // Кладём 1 и 2
	cout << "put 1" << '\n';
	cout.flush();
	cout << "put 2"  << '\n';
	cout.flush();
    // Вынимаем и смотрим, что вытащили
	cout << "get"  << '\n';
	cout.flush();
	cin >> resp;
	cout << (resp == "2" ? "stack" : "queue");
}


int main() {
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	ll t = 1;
	//cin>>t;
	while(t-->0){
		solveG();
	}
	return 0;
}