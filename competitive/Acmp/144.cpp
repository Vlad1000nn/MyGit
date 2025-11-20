#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <utility>
#include <string_view>
#include <bitset>
#include <set>
#include <cstring>
#include <map>

using namespace std;

#include <exception>
//Исключения
class Exception : public std::exception
{

};

//Неудачное выделение памяти
class bad_allocs : public Exception
{

};

//Передача нулевого указателя
class null_ptr : public Exception
{

};

// Передача недопустимых значений
class invalid_value : public Exception
{

};

constexpr int len_f_naivniy = 128;		// Количество цифр, чтобы выбрать умножение наивным образом или Карацубой


// Реализация
class BigInt
{
private:

	// Вектор цифр нашего числа
	vector<int> digits;

	// Знак числа (0 +,
	//			   1 -) 
	bool sign;


	////////////////////////СЛОЖЕНИЕ/////////////////////////////////

		// Сложение векторов цифр двух BigInt (a >= b) 
	vector<int> addition(const vector<int>& a, const vector<int>& b)	const
	{
		// if a == b, a + b = 2 * a

		vector<int> res;
		int carry{}, range{ abs(static_cast<int>(a.size()) - static_cast<int>(b.size())) };
		for (int i = 0; i < b.size(); ++i)
		{
			int sum_i = a[i] + b[i];
			res.push_back((sum_i + carry) % 10);
			if (sum_i + carry > 9) carry = (sum_i + carry) / 10;
		}
		if (range)
		{
			for (int i = static_cast<int>(b.size()); i < static_cast<int>(a.size()); ++i)
			{
				int sum_i = a[i] + carry;
				res.push_back((sum_i) % 10);
				if (sum_i > 9)	carry = sum_i / 10;
			}
		}
		if (carry)	res.push_back(carry);

		return res;
	}


	//////////////////////ВЫЧИТАНИЕ///////////////////////////////



		// Разность векторов цифр двух BigInt (а >= b)
	vector<int> subtraction(const vector<int>& a, const vector<int>& b)	const
	{
		if (a == b)	return{ 1,0 };

		vector<int> res;



		return res;
	}


	//////////////////////УМНОЖЕНИЕ///////////////////////////////////


		// Умножение векторов цифр
	vector<int> multiplication(vector<int> a, vector<int> b)	const
	{
		long long n = max(static_cast<int>(a.size()), static_cast<int>(b.size()));
		normalize_vec_to_2n(a, n);
		normalize_vec_to_2n(b, n);

		vector<int> res;

		res = karacuba_multiplication(a, b);
		carries(res);

		return res;
	}

	// Доводим размер вектора до ближайшей степени двойки
	void normalize_vec_to_2n(vector<int>& a, long long n) const
	{
		while (n & (n - 1))		++n;

		a.resize(n);
	}

	// Алгоритм умножения Карацуба ( O( n ^ log2(3) ) )
	vector<int> karacuba_multiplication(const vector<int>& a, const vector<int>& b)	const
	{
		auto len = a.size();
		vector<int> res(2 * len);

		if (len <= len_f_naivniy)	return naivniy_multiplication(a, b);

		auto k = len / 2;

		vector<int> a_right{ a.begin(),a.begin() + k };
		vector<int> a_left{ a.begin() + k,a.end() };
		vector<int> b_right{ b.begin(),b.begin() + k };
		vector<int> b_left{ b.begin() + k,b.end() };

		vector<int> P1 = karacuba_multiplication(a_left, b_left);
		vector<int> P2 = karacuba_multiplication(a_right, b_right);

		vector<int> a_lr(k);
		vector<int> b_lr(k);

		for (int i = 0; i < k; ++i)
		{
			a_lr[i] = a_left[i] + a_right[i];
			b_lr[i] = b_left[i] + b_right[i];
		}

		vector<int> P3 = karacuba_multiplication(a_lr, b_lr);

		for (auto i = 0; i < len; ++i)
			P3[i] -= P2[i] + P1[i];

		for (auto i = 0; i < k; ++i)
			res[i] = P2[i];

		for (auto i = len; i < 2 * len; ++i)
			res[i] = P1[i - len];

		for (auto i = k; i < len + k; ++i)
			res[i] += P3[i - k];

		return res;
	}

	// Базовое умножение за O(n^2), для чисел длины <128 (т.к. у этого алгоритма меньше константа)
	vector<int> naivniy_multiplication(const vector<int>& a, const vector<int>& b)		const
	{
		vector<int> res(2 * a.size());

		for (int i = 0; i < static_cast<int>(a.size()); ++i)
		{
			for (int g = 0; g < static_cast<int>(a.size()); ++g)
			{
				res[i + g] += a[i] * b[g];
			}
		}

		return res;
	}


	// Делаем все переносы и убираем ведущие нули
	void carries(vector<int>& res)		const
	{
		for (auto i = 0; i < res.size() - 1; ++i) {
			res[i + 1] += res[i] / 10;
			res[i] %= 10;
		}

		int index = static_cast<int>(res.size()) - 1;
		while (!res[index] && index > 0)
		{
			res.erase(res.begin() + index);
			--index;
		}
	}

	//////////////////ДЕЛЕНИЕ////////////////////////////////////////




	///////////////////////////////////////////////////////




		// Вектор а меньше => 1, вектор b меньше => 2, a = b => 0
	int vec_compare(const vector<int>& a, const vector<int>& b) const
	{
		if (a.size() < b.size()) return 1;
		else if (a.size() > b.size()) return 2;
		else return 0;
	}



public:

	// Конструктор по умолчанию
	BigInt()
		: digits(1, 0)
		, sign()
	{ }

	// Конструктор, принимающий целое число 
	BigInt(long long number)
	{
		sign = (number < 0);
		number = abs(number);	// На всякий случай, можно убрать
		while (number)
		{
			digits.push_back(number % 10);
			number /= 10;
		}
	}

	// Конструктор, принимающий строку
	BigInt(const string& s)
	{
		if (s.size())
		{
			for (long long i = static_cast<long long>(s.size()) - 1; i > 0; --i)
				digits.push_back(s[i] - '0');
			sign = (s[0] == '-');
			if (!sign) digits.push_back(s[0] - '0');
		}
		else
		{
			sign = 0;
			digits.push_back(0);
		}
	}

	// Конструктор, принимающий вектор цифр
	BigInt(const vector<int>& vec, bool _sign = false)
		: digits(vec)
		, sign(_sign)
	{ }

	// Конструктор копий
	BigInt(const BigInt& bigInt)
		: digits(bigInt.digits)
		, sign(bigInt.sign)
	{}

	// Конструктор, принимающий С-строку
	BigInt(const char* str)
	{
		//if (str == nullptr) throw null_ptr();	// Добавить аргумент, название функции, чтобы проще было отловить ошибку

		if (strlen(str))
		{
			for (long long i = strlen(str) - 1; i > 0; --i)
				digits.push_back(str[i] - '0');
			sign = (str[0] == '-');
			if (!sign) digits.push_back(str[0] - '0');
		}
		else
		{
			sign = 0;
			digits.push_back(0);
		}
	}

	// Конструктор, принимающий символ(цифру)
	BigInt(const char& c)
	{
		if (c > 47 && c < 58)
		{
			digits.push_back(c - '0');
			sign = 0;
		}
		//else throw invalid_value();
	}

	// Попробовать сломать с помощью ввода всякого говна в качестве аргументов

	// Смена знака у числа (унарный минус)
	void operator-()
	{
		sign = !sign;
	}


	// Оператор присваивания BigInt
	BigInt& operator=(const BigInt& a)
	{
		if (&a == this) return *this;

		this->digits = a.digits;
		this->sign = a.sign;
		return *this;
	}


	// Оператор равенства
	bool operator==(const BigInt& a) const
	{
		return (this->sign == a.sign) && (vec_compare(this->digits, a.digits) == 0);
	}


	// Перегрузка оператора сложения двух BigInt
	BigInt operator+(const BigInt& a)		const
	{
		vector<int> res;
		bool res_sign{};
		if (!(this->sign))
		{
			if (!a.sign)	// (+,+)	a + b
			{
				if ((*this) > a)	res = addition(this->digits, a.digits);
				else				res = addition(a.digits, this->digits);
			}
			else     // (+,-)	a + (-b)	a - b
			{
				if ((*this) > a)
					res = subtraction(this->digits, a.digits);
				else
				{
					res = subtraction(a.digits, this->digits);
					res_sign = 1;
				}
			}
		}
		else
		{
			if (!a.sign)	// (-,+)	(-a) - b	-(a + b)
			{
				if ((*this) > a)	res = addition(this->digits, a.digits);
				else				res = addition(a.digits, this->digits);
				res_sign = 1;
			}
			else	// (-,-)	(-a) - (-b)		b - a
			{
				if (a > (*this))
					res = subtraction(a.digits, this->digits);
				else
				{
					res = subtraction(this->digits, a.digits);
					res_sign = 1;
				}
			}
		}

		return { res, res_sign };
	}

	// Оператор умножения двух BigInt
	BigInt operator*(const BigInt& a)
	{
		vector<int> res;
		bool res_sign{ static_cast<bool>(this->sign ^ a.sign) };

		res = multiplication(this->digits, a.digits);

		return { res, res_sign };
	}



	// Оператор больше для двух BigInt
	bool operator>(const BigInt& a) const
	{
		if ((this->sign && a.sign) || (!(this->sign) && !a.sign))
		{
			return (vec_compare(this->digits, a.digits) == 2);
		}
		else if (this->sign && !a.sign) return false;
		else return true;

	}




	// Убираем лидирующие нули
	void delete_zeros()
	{
		int i = 0;
		while (!digits[i]) ++i;
		digits.erase(digits.begin(), digits.begin() + i);
	}



	// Вывод ( _reverse = 0 — обычное число, -reverse = 1 — перевёрнутое)
	void print(bool _reverse = 0)	const
	{
		if (!_reverse)
		{
			if (sign) cout << '-';
			for (int i = static_cast<int>(digits.size() - 1); i >= 0; --i)
				cout << digits[i];
		}
		else
		{
			for (int i = 0; i < static_cast<int>(digits.size()); ++i)
				cout << digits[i];
			if (sign) cout << '-';
		}
	}

};


int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	string a, b;
	cin >> a >> b;
	BigInt A = a;
	BigInt B = b;
	(A * B).print();


	return 0;
}