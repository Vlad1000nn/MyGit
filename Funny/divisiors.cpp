#include <iostream>
#include <locale.h>

using namespace std;

void null_mass(int x[])
{
	for (int i = 0; i < 100000; i++)
	{
		x[i] = 0;
	}
}

void output(int N[])
{
	for (int i = 1; i < 100000;i++)
	{
		if (N[i] != 0)
			cout << N[i] << ' ';
	}
}

void find_divisiors(int x,int N[])
{
	for (int i = 1; i <= x; i++)
	{
		if (x % i == 0)
			N[i] = i;
	}
}


int main()
{
	int Div[100000];
	null_mass(Div);
	setlocale(LC_ALL, "rus");
	int x = {};
	cout << "Введите число:";
	cin >> x;
	cout << "Делители числа:";
	find_divisiors(x,Div);
	output(Div);


return 0;

}