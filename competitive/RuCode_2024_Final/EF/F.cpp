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


// Функция, которая открывает видимые ячейки, если мы смотрим с помощью фигуры field[i][j]
void openField(vector<string>& field, vector<string>& fieldAns,  int i, int j, int type, bool isBlack)
{
    // Ходы коня
	int konb [8][2] ={
		{-2, -1},
		{-2, 1},
		{-1, 2},
		{1,2},
		{2, 1},
		{2,-1},
		{-1,-2},
		{1,-2}
	};

    // Ходы остальных фигур(в удобном порядке)
	int N[8][2] = {
		{-1, 0},
		{0, 1},
		{1, 0},
		{0,-1},
		{1, 1},
		{-1, -1},
		{-1, 1},
		{1,-1}
	};

	fieldAns[i][j] = type + (isBlack ? 97 : 65); // Включаем текущую клетку
	switch(type)
	{
	case 1: // Ладья
	{
		for(int ind = 4;ind<8;++ind)
		{
			int dx = N[ind][0];
			int dy = N[ind][1];

			int currX{i + dx}, currY{j + dy};
			while(currX >= 0 && currX < 8 && currY >=0 && currY < 8)
			{
				char current = field[currX][currY];
				if(current == '.')
					fieldAns[currX][currY] = current;
				else {
                    // Врезались в какую-то фигуру
					fieldAns[currX][currY] = current;
					break;
				}
				currX += dx; currY += dy;
			}
		}
		
		break;
	}
	case 10:	// Король
	{
		for(int ind = 0;ind<8;++ind)
		{
			int dx = N[ind][0];
			int dy = N[ind][1];

			int currX{i + dx}, currY{j + dy};
			int cnt{};
			while(currX >= 0 && currX < 8 && currY >=0 && currY < 8 && cnt < 1)
			{
				char current = field[currX][currY];
				if(current == '.')
					fieldAns[currX][currY] = current;
				else {
                    // Врезались в какую-то фигуру
					fieldAns[currX][currY] = current;
					break;
				}
				currX += dx; currY += dy;
				++cnt;
			}
		}

		
		break;
	}
	case 13:	// Конь
	{
		int currX {i}, currY{j};
		for(int ind = 0;ind<8;++ind)
		{
			int dx = konb[ind][0];
			int dy = konb[ind][1];
			int newX = currX + dx;
			int newY = currY + dy;
			if(newX >= 0 && newY >=0 && newX < 8 && newY < 8)
				fieldAns[newX][newY] = field[newX][newY];
		}
		
		break;
	}
	case 15:	// пешка
	{
		int currX {i}, currY{j};
		int dx = (isBlack ? -1 : 1);
		for(int dy = -1;dy<=1;++dy)
		{
			int newX = currX + dx;
			int newY = currY + dy;
			if(newX >= 0 && newY >=0 && newX < 8 && newY < 8)
				fieldAns[newX][newY] = field[newX][newY];
		}
		
		break;
	}
	case 16:	// ферзь
	{
		for(int ind = 0;ind<8;++ind)
		{
			int dx = N[ind][0];
			int dy = N[ind][1];

			int currX{i + dx}, currY{j + dy};
			while(currX >= 0 && currX < 8 && currY >=0 && currY < 8)
			{
				char current = field[currX][currY];
				if(current == '.')
					fieldAns[currX][currY] = current;
				else {
                    // Врезались в какую-то фигуру
					fieldAns[currX][currY] = current;
					break;
				}
				currX += dx; currY += dy;
			}
		}
		
		break;
	}
	case 17:	// слон
	{
		for(int ind = 0;ind<4;++ind)
		{
			int dx = N[ind][0];
			int dy = N[ind][1];

			int currX{i + dx}, currY{j + dy};
			while(currX >= 0 && currX < 8 && currY >=0 && currY < 8)
			{
				char current = field[currX][currY];
				if(current == '.')
					fieldAns[currX][currY] = current;
				else {
                    // Врезались в какую-то фигуру
					fieldAns[currX][currY] = current;
					break;
				}
				currX += dx; currY += dy;
			}
		}
		break;
	}
	default:
		throw "Unknown type";
	}

}


void solveF()
{
	// R слон 17, N конь 13, B ладья 1, K король 10, Q ферзь 16, p пешка 15
	// строчные белые, заглавные чёрные

	string buff = "????????";
	const int n = 8;
	vector<string> field(n);
	vector<string> BlackAns(n, buff), WhiteAns(n, buff);
	for(auto& it : field)
		cin>>it;

	bool isBlack {}; 

	for(int i = 0;i<n;++i)
		for(int j = 0;j<n;++j)
		{
			char curr = field[i][j];
			if(curr == '.')
				continue;
			curr -= ((isBlack = (curr >= 97)) ? 'a' : 'A');
			
			openField(field, isBlack ? BlackAns : WhiteAns, i, j, (int)curr, isBlack);			
		}

	for(auto& it : BlackAns)
		cout<<it<<'\n';
	cout<<'\n';
	for(auto& it : WhiteAns)
		cout<<it<<'\n';

}


int main() {
    cin.tie(0);
    ios_base::sync_with_stdio(0);
    ll t = 1;
    //cin>>t;
    while(t-->0){
        solveF();
    }
    return 0;
}