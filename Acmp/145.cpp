#include <iostream>
#include <vector>
#include <string>
#include <cstring>


using namespace std;

using uint = unsigned int;
using ull = unsigned long long;
using ul = unsigned long;
using ushort = unsigned short;
using uchar = unsigned char;

// BigInt — целое число без ограничений
//
// � еализован на векторе с обратной записью цифр
//
// Считаем, что число 0 имеет знак +
//
// BigInt по умолчанию равен 0
//
//



// Перегрузка для всех типов реализована на основе базы для long long(всё сводится к вызову именно методов с long long  с кастованием)

constexpr int len_f_naivniy = 128;      // Количество цифр, чтобы выбрать умножение наивным образом или Карацубы
constexpr int base = 10;                // База в каждом элементе вектора

class BigInt
{
private:

    // Вектор цифр нашего числа
    vector<int> digits;
    // Знак числа (0 +,
    //             1 -) 
    bool sign;
    // Удаление лидирующих нулей из *this
    void remove_lead_zeros();
    // Удаление лидирующих нулей из BigInt
    void remove_lead_zeros(vector<int>& _digits) const;

    ////////////////////////СЛОЖЕНИЕ/////////////////////////////////

        // Сложение векторов цифр двух BigInt (a >= b) 
    vector<int> addition(const vector<int>& a, const vector<int>& b)    const;

    //////////////////////ВЫЧИТАНИЕ///////////////////////////////

            // Сведение двух векторов к 1 длине
    void normalization(vector<int>& a, vector<int>& b)  const;

    // � азность векторов цифр двух BigInt (а >= b)
    vector<int> subtraction(vector<int> a, vector<int> b)   const;

    //////////////////////УМНОЖЕНИЕ///////////////////////////////////

        // Умножение векторов цифр
    vector<int> multiplication(vector<int> a, vector<int> b)    const;

    // Доводим размер вектора до ближайшей степени двойки
    void normalize_vec_to_2n(vector<int>& a, long long n) const;

    // Алгоритм умножения Карацуба ( O( n ^ log2(3) ) )
    vector<int> karacuba_multiplication(const vector<int>& a, const vector<int>& b) const;

    // Базовое умножение за O(n^2), для чисел длины <128 (т.к. у этого алгоритма меньше константа)
    vector<int> naivniy_multiplication(const vector<int>& a, const vector<int>& b)      const;

    // Делаем все переносы и убираем ведущие нули
    void carries(vector<int>& res)  const;
    //////////////////ДЕЛЕНИЕ////////////////////////////////////////

    // Деление BigInt на 2
    BigInt div_by_2(BigInt& a)  const;

    ///////////////////////////////////////////////////////

        // Вектор а меньше => 1, вектор b меньше => 2, a = b => 0
    int vec_compare(const vector<int>& a, const vector<int>& b) const;

public:

    // Конструктор по умолчанию
    BigInt();

    // Конструкторы, принимающие целые числа
    BigInt(long long number);

    BigInt(ull number);

    BigInt(long number);

    BigInt(ul number);

    BigInt(int number);

    BigInt(uint number);

    BigInt(short number);

    BigInt(ushort number);


    // Конструктор, принимающий строку
    BigInt(const string& s);

    // Конструктор, принимающий вектор цифр
    BigInt(const vector<int>& vec, bool _sign = false);

    // Конструктор копий
    BigInt(const BigInt& bigInt);

    // Конструктор, принимающий С-строку
    BigInt(const char* str);

    // Конструктор, принимающий символ(цифру)
    BigInt(const char& c);

    // Смена знака у числа (унарный минус)
    BigInt operator-() const;

    // Оператор присваивания BigInt
    BigInt& operator=(const BigInt& a);

    // Оператор равенства
    bool operator==(const BigInt& a)  const;

    // Перегрузка оператора сложения двух BigInt
    BigInt operator+(const BigInt& a) const;

    // Оператор вычитания двух BigInt
    BigInt operator-(const BigInt a)  const;

    // Оператор умножения двух BigInt
    BigInt operator*(const BigInt& a) const;

    // Оператор деления двух BigInt
    BigInt operator/(const BigInt& a) const;

    BigInt operator%(const BigInt& a) const;

    // Перегрузка оператора умножения BigInt на целое число справа
    BigInt operator*(const long long x) const;

    BigInt operator*(const ull x)       const;

    BigInt operator*(const long x)      const;

    BigInt operator*(const ul x)        const;

    BigInt operator*(const int x)       const;

    BigInt operator*(const uint x)      const;

    BigInt operator*(const short x)     const;

    BigInt operator*(const ushort x)    const;



    // Строгий оператор больше для двух BigInt
    bool operator>(const BigInt& a) const;

    // Нетрогий оператор больше для двух BigInt
    bool operator>=(const BigInt& a) const;

    // Строгий оператор меньше для двух BigInt
    bool operator<(const BigInt& a) const;

    // Нестрогий оператор меньше для двух BigInt
    bool operator<=(const BigInt& a) const;

    // Вывод ( _reverse = 0 — обычное число, -reverse = 1 — перевёрнутое)
    void print(bool _reverse = 0)   const;

    BigInt make_abs() const;

    // Арифметические операторы слева

    // Умножение BigInt на целое число слева
    friend BigInt operator*(const long long x, const BigInt& b);

    // Сложение BigInt с целым числом слева
    friend BigInt operator+(const long long x, const BigInt& b);

    // Вычитание из целого числа BigInt
    friend BigInt operator-(const long long x, const BigInt& b);

    // Деление целого числа на BigInt
    friend BigInt operator/(const long long x, const BigInt& b);
};



// Удаление лидирующих нулей из *this
void BigInt::remove_lead_zeros()
{
    int index = static_cast<int>(digits.size()) - 1;
    while (!digits[index])
        digits.erase(digits.begin() + index);
}

// Удаление лидирующих нулей из BigInt
void BigInt::remove_lead_zeros(vector<int>& _digits) const
{
    int index = static_cast<int>(_digits.size()) - 1;
    while (!_digits[index] && index > 0)
        --index;

    _digits.resize(index + 1);

    if (!_digits.size()) _digits.push_back(0);
}

////////////////////////СЛОЖЕНИЕ/////////////////////////////////

// Сложение векторов цифр двух BigInt (a >= b) 
vector<int> BigInt::addition(const vector<int>& a, const vector<int>& b)    const
{
    // if a == b, a + b = 2 * a

    vector<int> res;
    int carry{}, range{ abs(static_cast<int>(a.size()) - static_cast<int>(b.size())) }, sum_i;

    for (int i = 0; i < b.size(); ++i)
    {
        sum_i = a[i] + b[i];
        res.push_back((sum_i + carry) % base);
        carry = (sum_i + carry) / base;
    }
    if (range)
    {
        for (int i = static_cast<int>(b.size()); i < static_cast<int>(a.size()); ++i)
        {
            sum_i = a[i] + carry;
            res.push_back((sum_i) % base);
            carry = sum_i / base;
        }
    }
    if (carry)  res.push_back(carry);

    return res;
}

//////////////////////ВЫЧИТАНИЕ///////////////////////////////

// Сведение двух векторов к 1 длине
void BigInt::normalization(vector<int>& a, vector<int>& b)  const
{
    int count1{};
    while (static_cast<int>(b.size()) + count1 < a.size()) ++count1;
    b.resize(b.size() + count1);
}

// � азность векторов цифр двух BigInt (а >= b)
vector<int> BigInt::subtraction(vector<int> a, vector<int> b)   const
{
    normalization(a, b);

    vector<int> res(a.size());
    int length = static_cast<int>(a.size());

    for (int i = 0, x; i < length; ++i)
    {
        x = a[i] - b[i];
        if (x < 0)
        {
            x += base;
            a[i + 1] -= 1;
        }
        res[i] = x;
    }
    remove_lead_zeros(res);
    return res;
}

//////////////////////УМНОЖЕНИЕ///////////////////////////////////

// Умножение векторов цифр
vector<int> BigInt::multiplication(vector<int> a, vector<int> b)    const
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
void BigInt::normalize_vec_to_2n(vector<int>& a, long long n) const
{
    while (n & (n - 1))     ++n;

    a.resize(n);
}

// Алгоритм умножения Карацуба ( O( n ^ log2(3) ) )
vector<int> BigInt::karacuba_multiplication(const vector<int>& a, const vector<int>& b) const
{
    auto len = a.size();
    vector<int> res(2 * len);

    if (len <= len_f_naivniy)   return naivniy_multiplication(a, b);


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
    {
        P3[i] -= (P2[i] + P1[i]);
        res[i] = P2[i];
    }


    for (auto i = len; i < 2 * len; ++i)
        res[i] = P1[i - len];

    for (auto i = k; i < len + k; ++i)
        res[i] += P3[i - k];

    return res;
}

// Базовое умножение за O(n^2), для чисел длины <128 (т.к. у этого алгоритма меньше константа)
vector<int> BigInt::naivniy_multiplication(const vector<int>& a, const vector<int>& b)      const
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
void BigInt::carries(vector<int>& res)      const
{
    if (res.size() == 1)
    {
        if (res[0] > 9)
        {
            res.push_back(res[0] / base);
            res[0] %= base;
        }
    }
    else
        for (auto i = 0; i < res.size() - 1; ++i)
        {
            res[i + 1] += res[i] / base;
            res[i] %= base;
        }

    remove_lead_zeros(res);
}

//////////////////ДЕЛЕНИЕ////////////////////////////////////////

// Деление BigInt на 2
BigInt BigInt::div_by_2(BigInt& a) const
{
    long long length = static_cast<long long>(a.digits.size());
    bool carry = {};
    for (long long i = length - 1; i >= 0; --i)
    {
        a.digits[i] += base * carry;
        carry = a.digits[i] % 2 == 1;
        a.digits[i] /= 2;
    }
    remove_lead_zeros(a.digits);
    return a;
}

///////////////////////////////////////////////////////

// Вектор а меньше => 1, вектор b меньше => 2, a = b => 0
int BigInt::vec_compare(const vector<int>& a, const vector<int>& b) const
{
    if (a.size() < b.size()) return 1;
    else if (a.size() > b.size()) return 2;
    else
    {
        int length = static_cast<int>(a.size());
        for (int i = length - 1; i >= 0; --i)
            if (a[i] != b[i])
            {
                if (a[i] > b[i])
                    return 2;
                else return 1;
            }

        return 0;
    }
}

// Конструктор по умолчанию
BigInt::BigInt()
    : digits(1, 0)
    , sign()
{ }

// Конструкторы, принимающие целые числа
BigInt::BigInt(long long number)
{
    sign = (number < 0);
    number = abs(number);   // На всякий случай, можно убрать
    while (number)
    {
        digits.push_back(number % base);
        number /= base;
    }
    if (!digits.size())
        digits.push_back(0);
}

BigInt::BigInt(ull  number) : BigInt(static_cast<long long>(number))
{ }

BigInt::BigInt(long number) : BigInt(static_cast<long long>(number))
{ }

BigInt::BigInt(ul number) : BigInt(static_cast<long long>(number))
{ }

BigInt::BigInt(int number) : BigInt(static_cast<long long>(number))
{ }

BigInt::BigInt(uint number) : BigInt(static_cast<long long>(number))
{ }

BigInt::BigInt(short number) : BigInt(static_cast<long long>(number))
{ }

BigInt::BigInt(ushort number) : BigInt(static_cast<long long>(number))
{ }


// Конструктор, принимающий строку
BigInt::BigInt(const string& s)
{
    if (s.size())
    {
        for (long long i = static_cast<long long>(s.size()) - 1; i > 0; --i)
        {
            if (s[i] > 47 && s[i] < 58)
                digits.push_back(s[i] - '0');
            //else throw invalid_value();
        }
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
BigInt::BigInt(const vector<int>& vec, bool _sign)
    : digits(vec)
    , sign(_sign)
{ }

// Конструктор копий
BigInt::BigInt(const BigInt& bigInt)
    : digits(bigInt.digits)
    , sign(bigInt.sign)
{}

// Конструктор, принимающий С-строку
BigInt::BigInt(const char* str)
{
    //if (str == nullptr) throw null_ptr(); // Добавить аргумент, название функции, чтобы проще было отловить ошибку

    if (strlen(str))
    {
        for (long long i = strlen(str) - 1; i > 0; --i)
        {
            if (str[i] > 47 && str[i] < 58)
                digits.push_back(str[i] - '0');
            //  else throw invalid_value();     //////////////////////// МОЖНО ПЕ� ЕДАВАТЬ СИМВОЛ И ГОВО� ИТЬ ЧТО ЭТО НЕ ЧИСЛО
        }
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
BigInt::BigInt(const char& c)
{
    if (c > 47 && c < 58)
    {
        digits.push_back(c - '0');
        sign = 0;
    }
    //else throw invalid_value();
}

// Попробовать сломать с помощью ввода всякого говна в качестве аргументов//////////////////////////////

// Смена знака у числа (унарный минус)
BigInt BigInt::operator-()  const
{
    return { this->digits, !this->sign };
}

// Оператор присваивания BigInt
BigInt& BigInt::operator=(const BigInt& a)
{
    if (&a == this) return *this;

    this->digits = a.digits;
    this->sign = a.sign;
    return *this;
}

// Оператор равенства
bool BigInt::operator==(const BigInt& a)    const
{
    return (this->sign == a.sign) && (vec_compare(this->digits, a.digits) == 0);
}


// Перегрузка оператора сложения двух BigInt
BigInt BigInt::operator+(const BigInt& a)   const
{
    vector<int> res;
    bool res_sign{};
    if (!(this->sign))
    {
        if (!a.sign)    // (+,+)    a + b
        {
            if ((*this) > a)    res = addition(this->digits, a.digits);
            else                res = addition(a.digits, this->digits);
        }
        else     // (+,-)   a + (-b)    a - b
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
        if (!a.sign)    // (-,+)    (-a) - b    -(a + b)
        {
            if ((*this) > a)    res = addition(this->digits, a.digits);
            else                res = addition(a.digits, this->digits);
            res_sign = 1;
        }
        else    // (-,-)    (-a) - (-b)     b - a
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

// Оператор вычитания двух BigInt
BigInt BigInt::operator-(const BigInt a)    const
{
    if (*this == a) return { 0 };

    vector<int> res;
    bool res_sign{};
    if (!this->sign)
    {
        if (!a.sign)
        {

            if ((*this) > a)
                res = subtraction(this->digits, a.digits);
            else
            {
                res = subtraction(a.digits, this->digits);
                res_sign = 1;
            }
        }
        else
            res = addition(this->digits, a.digits);
    }
    else
    {
        if (!a.sign)
        {
            res = addition(this->digits, a.digits);
            res_sign = 1;
        }
        else
        {
            if ((*this) > a)
                res = subtraction(a.digits, this->digits);
            else
            {
                subtraction(this->digits, a.digits);
                res_sign = 1;
            }
        }
    }
    return { res, res_sign };
}

// Оператор умножения двух BigInt
BigInt BigInt::operator*(const BigInt& a)   const
{
    vector<int> res;
    bool res_sign{ static_cast<bool>(this->sign ^ a.sign) };

    res = multiplication(this->digits, a.digits);

    return { res, res_sign };
}


// Перегрузка оператора умножения BigInt на целое число справа
BigInt BigInt::operator*(const long long x) const
{
    return (*this) * BigInt { x };
}

BigInt BigInt::operator*(const ull x)       const
{
    return ((*this) * static_cast<long long>(x));
}

BigInt BigInt::operator*(const long x)      const
{
    return ((*this) * static_cast<long long>(x));
}

BigInt BigInt::operator*(const ul x)        const
{
    return ((*this) * static_cast<long long>(x));
}

BigInt BigInt::operator*(const int x)       const
{
    return ((*this) * static_cast<long long>(x));
}

BigInt BigInt::operator*(const uint x)      const
{
    return ((*this) * static_cast<long long>(x));
}

BigInt BigInt::operator*(const short x)     const
{
    return ((*this) * static_cast<long long>(x));
}

BigInt BigInt::operator*(const ushort x)    const
{
    return ((*this) * static_cast<long long>(x));
}



// Оператор деления двух BigInt

//  СТОП Я ЗАБЫЛ П� О ЗНАК И ЕЩЁ ЭТУ ФУНКЦИЮ МОЖНО ЮЗАТЬ ДЛЯ ДЕЛЕНИЯ С ОСТАТКОМ (*THIS - ANSWER ОСТАТОК) 
BigInt BigInt::operator/(const BigInt& a)   const
{
    //if (a == 0)   throw math_error();
    if ((*this) == 0) return 0;

    BigInt l{}, r{ (*this) }, mid, ans{ 0 }, sum, current;
    while (l <= r)
    {
        sum = r + l;
        mid = div_by_2(sum);
        current = a * mid;
        if (current < (*this))
        {
            ans = mid;
            l = mid + 1;
        }
        else if (current > (*this))
            r = mid - 1;
        else return mid;
    }
    if (!(ans == 0))
        ans.sign = this->sign ^ a.sign;
    return ans;
}

// Оператор взятия остатка при делении на BigInt
BigInt BigInt::operator%(const BigInt& a)   const
{
    //if (a.sign) throw math_error();

    if (this->sign)
    {
        BigInt temp = ((*this).make_abs() - (a * ((*this).make_abs() / a)));
        if (temp == 0) return 0;
        else
            return a - temp;
    }

    return (*this) - (a * ((*this) / a));
}

// Строгий оператор больше для двух BigInt
bool BigInt::operator>(const BigInt& a)     const
{
    // Если знаки равны два случая
    if ((this->sign && a.sign) || (!(this->sign) && !a.sign))
    {
        return (vec_compare(this->digits, a.digits) == 2);
    }
    else if (this->sign && !a.sign) return false;
    else return true;

}

// Нетрогий оператор больше для двух BigInt
bool BigInt::operator>=(const BigInt& a)    const
{
    if ((this->sign && a.sign) || (!(this->sign) && !a.sign))
    {
        return (vec_compare(this->digits, a.digits) != 1);
    }
    else if (this->sign && !a.sign) return false;
    else return true;

}

// Строгий оператор меньше для двух BigInt
bool BigInt::operator<(const BigInt& a)     const
{
    if ((this->sign && a.sign) || (!(this->sign) && !a.sign))
        return (vec_compare(this->digits, a.digits)) == 1;
    else if (this->sign && !a.sign) return true;
    else return false;
}

// Нестрогий оператор меньше для двух BigInt
bool BigInt::operator<=(const BigInt& a)    const
{
    if ((this->sign && a.sign) || (!(this->sign) && !a.sign))
        return (vec_compare(this->digits, a.digits)) != 2;
    else if (this->sign && !a.sign) return true;
    else return false;
}

// Вывод ( _reverse = 0 — обычное число, _reverse = 1 — перевёрнутое)
void BigInt::print(bool _reverse)           const
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

// Взятие модуля от числа
BigInt BigInt::make_abs()   const
{
    return { this->digits,0 };
}

// Перегрузка операторов ввода/вывода
// либо 2 отдельных либо проверку на ввод/вывод из файла!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// 
// Стандартный вывод
ostream& operator<<(ostream& out, const BigInt& a)
{
    a.print();
    return out;
}

// Стандартный ввод
istream& operator>>(istream& in, BigInt& a)
{
    string s;
    in >> s;
    a = s;
    return in;
}



// Перегрузка арифметических операторов слева


// Перегрузка оператора умножения BigInt на целое число слева
BigInt operator*(const long long x, const BigInt& b)
{
    return BigInt{ x } *b;
}

BigInt operator*(const ull x, const BigInt& a)
{
    return (static_cast<long long>(x) * a);
}

BigInt operator*(const long x, const BigInt& a)
{
    return (static_cast<long long>(x) * a);
}

BigInt operator*(const ul x, const BigInt& a)
{
    return (static_cast<long long>(x) * a);
}

BigInt operator*(const int x, const BigInt& a)
{
    return (static_cast<long long>(x) * a);
}

BigInt operator*(const uint x, const BigInt& a)
{
    return (static_cast<long long>(x) * a);
}

BigInt operator*(const short x, const BigInt& a)
{
    return (static_cast<long long>(x) * a);
}

BigInt operator*(const ushort x, const BigInt& a)
{
    return (static_cast<long long>(x) * a);
}



// Перегрузка оператора вычитания из целого числа BigInt
BigInt operator-(const long long x, const BigInt& b)
{
    return BigInt{ x } - b;
}

BigInt operator-(const ull x, const BigInt& a)
{
    return (static_cast<long long>(x) - a);
}

BigInt operator-(const long x, const BigInt& a)
{
    return (static_cast<long long>(x) - a);
}

BigInt operator-(const ul x, const BigInt& a)
{
    return (static_cast<long long>(x) - a);
}

BigInt operator-(const int x, const BigInt& a)
{
    return (static_cast<long long>(x) - a);
}

BigInt operator-(const uint x, const BigInt& a)
{
    return (static_cast<long long>(x) - a);
}

BigInt operator-(const short x, const BigInt& a)
{
    return (static_cast<long long>(x) - a);
}

BigInt operator-(const ushort x, const BigInt& a)
{
    return (static_cast<long long>(x) - a);
}



// Перегрузка оператора деления целого числа на BigInt
BigInt operator/(const long long x, const BigInt& b)
{
    return BigInt{ x } / b;
}

BigInt operator/(const ull x, const BigInt& a)
{
    return (static_cast<long long>(x) / a);
}

BigInt operator/(const long x, const BigInt& a)
{
    return (static_cast<long long>(x) / a);
}

BigInt operator/(const ul x, const BigInt& a)
{
    return (static_cast<long long>(x) / a);
}

BigInt operator/(const int x, const BigInt& a)
{
    return (static_cast<long long>(x) / a);
}

BigInt operator/(const uint x, const BigInt& a)
{
    return (static_cast<long long>(x) / a);
}

BigInt operator/(const short x, const BigInt& a)
{
    return (static_cast<long long>(x) / a);
}

BigInt operator/(const ushort x, const BigInt& a)
{
    return (static_cast<long long>(x) / a);
}



// Перегрузка оператора сложения BigInt с целым числом слева
BigInt operator+(const long long x, const BigInt& b)
{
    return BigInt{ x } + b;
}

BigInt operator+(const ull  x, const BigInt& a)
{
    return (static_cast<long long>(x) + a);
}

BigInt operator+(const long x, const BigInt& a)
{
    return (static_cast<long long>(x) + a);
}

BigInt operator+(const ul x, const BigInt& a)
{
    return (static_cast<long long>(x) + a);
}

BigInt operator+(const int x, const BigInt& a)
{
    return (static_cast<long long>(x) + a);
}

BigInt operator+(const uint x, const BigInt& a)
{
    return (static_cast<long long>(x) + a);
}

BigInt operator+(const short x, const BigInt& a)
{
    return (static_cast<long long>(x) * a);
}

BigInt operator+(const ushort x, const BigInt& a)
{
    return (static_cast<long long>(x) * a);
}

int main()
{
    BigInt a, b;
    cin >> a >> b;
    cout << a / b;
}