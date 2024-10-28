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


void solveD(){
	// A = 65
	
	ll n,k; cin>>n>>k;
	ll cnt = n /2;  // Количество ходов Боба
	std::set<int> s;   // Список букв которые можно использовать
	for(int i = 65;i< 65 + n;++i)
		s.insert(i);

	for(int i = 0;i<n;++i)
	{
        // Ход Алисы
		if(i % 2 == 0)
		{
			// <=k
			if(cnt <= k && cnt)
			{
                // Если буква не занята, то делаем так, чтобы Боб споткнулся
				if(s.count(65 + i + 1))
				{ 
				    std::cout<< char(65 + i  + 1)<<std::endl;
				    s.erase(65 + i + 1);
				} 
                // Иначе нам всё равно, будем добавлять с конца буквы, чтобы случайно не подставить Боба лишний раз
                else 
				{
					std::cout<<char(*s.rbegin())<<std::endl;
					s.erase(*s.rbegin());
				}
            }
            else 
            { // По очереди просто ходим
                std::cout<<char(*s.begin())<<std::endl;
                s.erase(*s.begin());			 
            }
		} 
        else    // Ход Боба 
        {
			--cnt;
		    char c; cin>>c;
		    s.erase((int)c);
		}
	}

}


int main() {
cin.tie(0);
ios_base::sync_with_stdio(0);
ll t = 1;
//cin>>t;
while(t-->0){
	solveD();
}
return 0;
}