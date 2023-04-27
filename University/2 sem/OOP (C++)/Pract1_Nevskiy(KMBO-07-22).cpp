#include <iostream>
#include <cmath>


using namespace std;


class Polynomial
{
private:
	double a0_p;			//Коэффициент при c
	double a1_p;			//Коэффициент при x
	double a2_p;			//Коэффициент при x^2
public:

	double root(double a = 1, double b = 0, double c = 0)		//Поиск max по модулю корня
	{
		double D = { b * b - 4 * a * c };
		if (D < 0)
			return nan;
		double x1 = { (-b + sqrt(D)) / (2 * a) };
		double x2 = { (-b - sqrt(D)) / (2 * a) };

		return (abs(x1) > abs(x2)) ? x1 : x2;
	}


	//Конструктор инициализации многочлена
	Polynomial(double a2, double a1, double a0)
	{
		a0_p = a0;
		a1_p = a1;
		a2_p = a2;
	}

	//Конструктор присвоение многочлену значения другого многочлена
	Polynomial(Polynomial& P)
	{
		a0_p=P.a0_p;
		a1_p=P.a1_p;
		a2_p=P.a2_p;
	}

	// Геттеры
	double get_a0()
	{
		return a0_p;
	}
	double get_a1()
	{
		return a1_p;
	}
	double get_a2()
	{
		return a2_p;
	}

	// Сеттеры
	void set_a0(double a0)
	{
		a0_p = a0;
	}
	void set_a1(double a1)
	{
		a1_p = a1;
	}
	void set_a2(double a2)
	{
		a2_p = a2;
	}

	//Перегрузка унарного + , нахождение max по модулю корня
	double operator+()
	{
			return root(a2_p, a1_p, a0_p);
	}

	//Операция сложения двух многочленов
	Polynomial operator+(Polynomial P)
	{
		Polynomial Res;
		Res.a0_p = a0_p + P.a0_p;
		Res.a1_p = a1_p + P.a1_p;
		Res.a2_p = a2_p + P.a2_p;
		return Res;
	}

	//Операция сложения многочлена и числа
	Polynomial operator+(int c)
	{
		Polynomial Res;
		Res.a0_p = a0_p + c;
		Res.a1_p = a1_p;
		Res.a2_p = a2_p;
		return Res;
	}

	//Операция умножения многочлена на число
	Polynomial operator*(int k)
	{
		Polynomial Res;
		Res.a0_p = k * a0_p;
		Res.a1_p = k * a1_p;
		Res.a2_p = k * a2_p;
		return Res;
	}



	// Деструктор
	~Polynomial()
	{
		;
		//cout << "\nDestructor is working";
	}

	//Вывод многочлена
	void print()
	{
		cout << a2_p << "x^2 + " << a1_p << "x + " << a0_p;
	}

};

int main()
{
	Polynomial P1{ 1,2,3 };
	P1.print();

	cout << '\n';

	Polynomial P2;
	P2.print();

	cout << '\n';

	Polynomial P3;
	P3.set_a2(4);
	P3.set_a1(15);
	P3.set_a0(6);
	P3.print();

	double x = P3.get_a0();
	cout << "\nFree P3 koef is " << x << '\n';

	Polynomial P4 = P1 + P3;
	P4.print();

	cout << '\n';

	P3 = P3 + 2;
	P3.print();

	cout << '\n';

	P4 = P4 * 9;
	P4.print();

	double root = {+P3};
	if (!isnan(root))
		cout << '\n' << root;
	else
		cout << "No roots\n";

	return 0;
}