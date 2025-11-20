//nclude "BigInt.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <array>
#include <cstring>
#include <tuple>
#include <ctime>
 
using namespace std;
 
using ll = long long;
 
using uint = unsigned int;
using ull = unsigned long long;
using ul = unsigned long;
using ushort = unsigned short;
using uchar = unsigned char;
 
// BigInt вЂ” С†РµР»РѕРµ С‡РёСЃР»Рѕ Р±РµР· РѕРіСЂР°РЅРёС‡РµРЅРёР№
//
// Р РµР°Р»РёР·РѕРІР°РЅ РЅР° РІРµРєС‚РѕСЂРµ СЃ РѕР±СЂР°С‚РЅРѕР№ Р·Р°РїРёСЃСЊСЋ С†РёС„СЂ
//
// РЎС‡РёС‚Р°РµРј, С‡С‚Рѕ С‡РёСЃР»Рѕ 0 РёРјРµРµС‚ Р·РЅР°Рє +
//
// BigInt РїРѕ СѓРјРѕР»С‡Р°РЅРёСЋ СЂР°РІРµРЅ 0
//
//
 
 
// РџРµСЂРµРіСЂСѓР·РєР° РґР»СЏ РІСЃРµС… С‚РёРїРѕРІ СЂРµР°Р»РёР·РѕРІР°РЅР° РЅР° РѕСЃРЅРѕРІРµ Р±Р°Р·С‹ РґР»СЏ long long(РІСЃС‘ СЃРІРѕРґРёС‚СЃСЏ Рє РІС‹Р·РѕРІСѓ РёРјРµРЅРЅРѕ РјРµС‚РѕРґРѕРІ СЃ long long  СЃ РєР°СЃС‚РѕРІР°РЅРёРµРј)
 
constexpr int len_f_naivniy = 128;      // РљРѕР»РёС‡РµСЃС‚РІРѕ С†РёС„СЂ, С‡С‚РѕР±С‹ РІС‹Р±СЂР°С‚СЊ СѓРјРЅРѕР¶РµРЅРёРµ РЅР°РёРІРЅС‹Рј РѕР±СЂР°Р·РѕРј РёР»Рё РљР°СЂР°С†СѓР±С‹
constexpr int base = 10;                // Р‘Р°Р·Р° РІ РєР°Р¶РґРѕРј СЌР»РµРјРµРЅС‚Рµ РІРµРєС‚РѕСЂР°
 
class BigInt
{
private:
 
    // Р’РµРєС‚РѕСЂ С†РёС„СЂ РЅР°С€РµРіРѕ С‡РёСЃР»Р°
    std::vector<int> digits;
    // Р—РЅР°Рє С‡РёСЃР»Р° (0 +,
    //             1 -) 
    bool sign;
    // РЈРґР°Р»РµРЅРёРµ Р»РёРґРёСЂСѓСЋС‰РёС… РЅСѓР»РµР№ РёР· *this
    void remove_lead_zeros();
    // РЈРґР°Р»РµРЅРёРµ Р»РёРґРёСЂСѓСЋС‰РёС… РЅСѓР»РµР№ РёР· BigInt
    void remove_lead_zeros(std::vector<int>& _digits) const;
 
    ////////////////////////РЎР›РћР–Р•РќРР•/////////////////////////////////
 
        // РЎР»РѕР¶РµРЅРёРµ РІРµРєС‚РѕСЂРѕРІ С†РёС„СЂ РґРІСѓС… BigInt (a >= b) 
    std::vector<int> addition(const std::vector<int>& a, const std::vector<int>& b) const;
 
    //////////////////////Р’Р«Р§РРўРђРќРР•///////////////////////////////
 
            // РЎРІРµРґРµРЅРёРµ РґРІСѓС… РІРµРєС‚РѕСЂРѕРІ Рє 1 РґР»РёРЅРµ
    void normalization(std::vector<int>& a, std::vector<int>& b)    const;
 
    // Р Р°Р·РЅРѕСЃС‚СЊ РІРµРєС‚РѕСЂРѕРІ С†РёС„СЂ РґРІСѓС… BigInt (Р° >= b)
    std::vector<int> subtraction(std::vector<int> a, std::vector<int> b)    const;
 
    //////////////////////РЈРњРќРћР–Р•РќРР•///////////////////////////////////
 
        // РЈРјРЅРѕР¶РµРЅРёРµ РІРµРєС‚РѕСЂРѕРІ С†РёС„СЂ
    std::vector<int> multiplication(std::vector<int> a, std::vector<int> b) const;
 
    // Р”РѕРІРѕРґРёРј СЂР°Р·РјРµСЂ РІРµРєС‚РѕСЂР° РґРѕ Р±Р»РёР¶Р°Р№С€РµР№ СЃС‚РµРїРµРЅРё РґРІРѕР№РєРё
    void normalize_vec_to_2n(std::vector<int>& a, long long n) const;
 
    // РђР»РіРѕСЂРёС‚Рј СѓРјРЅРѕР¶РµРЅРёСЏ РљР°СЂР°С†СѓР±Р° ( O( n ^ log2(3) ) )
    std::vector<int> karacuba_multiplication(const std::vector<int>& a, const std::vector<int>& b)  const;
 
    // Р‘Р°Р·РѕРІРѕРµ СѓРјРЅРѕР¶РµРЅРёРµ Р·Р° O(n^2), РґР»СЏ С‡РёСЃРµР» РґР»РёРЅС‹ <128 (С‚.Рє. Сѓ СЌС‚РѕРіРѕ Р°Р»РіРѕСЂРёС‚РјР° РјРµРЅСЊС€Рµ РєРѕРЅСЃС‚Р°РЅС‚Р°)
    std::vector<int> naivniy_multiplication(const std::vector<int>& a, const std::vector<int>& b)       const;
 
    // Р”РµР»Р°РµРј РІСЃРµ РїРµСЂРµРЅРѕСЃС‹ Рё СѓР±РёСЂР°РµРј РІРµРґСѓС‰РёРµ РЅСѓР»Рё
    void carries(std::vector<int>& res) const;
    //////////////////Р”Р•Р›Р•РќРР•////////////////////////////////////////
 
    // Р”РµР»РµРЅРёРµ BigInt РЅР° 2
    BigInt div_by_2(BigInt& a)  const;
 
    ///////////////////////////////////////////////////////
 
        // Р’РµРєС‚РѕСЂ Р° РјРµРЅСЊС€Рµ => 1, РІРµРєС‚РѕСЂ b РјРµРЅСЊС€Рµ => 2, a = b => 0
    int vec_compare(const std::vector<int>& a, const std::vector<int>& b) const;
 
public:
 
    // РљРѕРЅСЃС‚СЂСѓРєС‚РѕСЂ РїРѕ СѓРјРѕР»С‡Р°РЅРёСЋ
    BigInt();
 
    // РљРѕРЅСЃС‚СЂСѓРєС‚РѕСЂС‹, РїСЂРёРЅРёРјР°СЋС‰РёРµ С†РµР»С‹Рµ С‡РёСЃР»Р°
    BigInt(long long number);
 
    BigInt(ull number);
 
    BigInt(long number);
 
    BigInt(ul number);
 
    BigInt(int number);
 
    BigInt(uint number);
 
    BigInt(short number);
 
    BigInt(ushort number);
 
 
    // РљРѕРЅСЃС‚СЂСѓРєС‚РѕСЂ, РїСЂРёРЅРёРјР°СЋС‰РёР№ СЃС‚СЂРѕРєСѓ
    BigInt(const std::string& s);
 
    // РљРѕРЅСЃС‚СЂСѓРєС‚РѕСЂ, РїСЂРёРЅРёРјР°СЋС‰РёР№ РІРµРєС‚РѕСЂ С†РёС„СЂ
    BigInt(const std::vector<int>& vec, bool _sign = false);
 
    // РљРѕРЅСЃС‚СЂСѓРєС‚РѕСЂ РєРѕРїРёР№
    BigInt(const BigInt& bigInt);
 
    // РљРѕРЅСЃС‚СЂСѓРєС‚РѕСЂ, РїСЂРёРЅРёРјР°СЋС‰РёР№ РЎ-СЃС‚СЂРѕРєСѓ
    BigInt(const char* str);
 
    // РљРѕРЅСЃС‚СЂСѓРєС‚РѕСЂ, РїСЂРёРЅРёРјР°СЋС‰РёР№ СЃРёРјРІРѕР»(С†РёС„СЂСѓ)
    BigInt(const char& c);
 
    // РЎРјРµРЅР° Р·РЅР°РєР° Сѓ С‡РёСЃР»Р° (СѓРЅР°СЂРЅС‹Р№ РјРёРЅСѓСЃ)
    BigInt operator-() const;
 
    // РћРїРµСЂР°С‚РѕСЂ РїСЂРёСЃРІР°РёРІР°РЅРёСЏ BigInt
    BigInt& operator=(const BigInt& a);
 
    // РћРїРµСЂР°С‚РѕСЂ СЂР°РІРµРЅСЃС‚РІР°
    bool operator==(const BigInt& a)  const;
 
    bool operator!=(const BigInt& a)  const;
 
    BigInt operator!()  const;
 
    // РџРµСЂРµРіСЂСѓР·РєР° РѕРїРµСЂР°С‚РѕСЂР° СЃР»РѕР¶РµРЅРёСЏ РґРІСѓС… BigInt
    BigInt operator+(const BigInt& a) const;
 
    // РћРїРµСЂР°С‚РѕСЂ РІС‹С‡РёС‚Р°РЅРёСЏ РґРІСѓС… BigInt
    BigInt operator-(const BigInt a)  const;
 
    // РћРїРµСЂР°С‚РѕСЂ СѓРјРЅРѕР¶РµРЅРёСЏ РґРІСѓС… BigInt
    BigInt operator*(const BigInt& a) const;
 
    // РћРїРµСЂР°С‚РѕСЂ РґРµР»РµРЅРёСЏ РґРІСѓС… BigInt
    BigInt operator/(const BigInt& a) const;
 
    BigInt operator%(const BigInt& a) const;
 
    // РџРµСЂРµРіСЂСѓР·РєР° РѕРїРµСЂР°С‚РѕСЂР° СѓРјРЅРѕР¶РµРЅРёСЏ BigInt РЅР° С†РµР»РѕРµ С‡РёСЃР»Рѕ СЃРїСЂР°РІР°
    BigInt operator*(const long long x) const;
 
    BigInt operator*(const ull x)       const;
 
    BigInt operator*(const long x)      const;
 
    BigInt operator*(const ul x)        const;
 
    BigInt operator*(const int x)       const;
 
    BigInt operator*(const uint x)      const;
 
    BigInt operator*(const short x)     const;
 
    BigInt operator*(const ushort x)    const;
 
 
 
 
    // РЎС‚СЂРѕРіРёР№ РѕРїРµСЂР°С‚РѕСЂ Р±РѕР»СЊС€Рµ РґР»СЏ РґРІСѓС… BigInt
    bool operator>(const BigInt& a) const;
 
    // РќРµС‚СЂРѕРіРёР№ РѕРїРµСЂР°С‚РѕСЂ Р±РѕР»СЊС€Рµ РґР»СЏ РґРІСѓС… BigInt
    bool operator>=(const BigInt& a) const;
 
    // РЎС‚СЂРѕРіРёР№ РѕРїРµСЂР°С‚РѕСЂ РјРµРЅСЊС€Рµ РґР»СЏ РґРІСѓС… BigInt
    bool operator<(const BigInt& a) const;
 
    // РќРµСЃС‚СЂРѕРіРёР№ РѕРїРµСЂР°С‚РѕСЂ РјРµРЅСЊС€Рµ РґР»СЏ РґРІСѓС… BigInt
    bool operator<=(const BigInt& a) const;
 
    // Р’С‹РІРѕРґ ( _reverse = 0 вЂ” РѕР±С‹С‡РЅРѕРµ С‡РёСЃР»Рѕ, -reverse = 1 вЂ” РїРµСЂРµРІС‘СЂРЅСѓС‚РѕРµ)
    void print(bool _reverse = 0)   const;
 
    BigInt make_abs() const;
 
    BigInt square(const int n = 2) const;
 
    BigInt power(const BigInt& n)   const;
 
    BigInt& operator*=(const BigInt& a);
 
    ull to_ull()        const;
 
    long long to_ll()   const;
 
    ul to_ul()          const;
 
    long to_long()      const;
 
    uint to_uint()      const;
 
    int to_int()        const;
 
    ushort to_ushort()  const;
 
    short to_short()    const;
 
 
 
    // РђСЂРёС„РјРµС‚РёС‡РµСЃРєРёРµ РѕРїРµСЂР°С‚РѕСЂС‹ СЃР»РµРІР°
 
    // РЈРјРЅРѕР¶РµРЅРёРµ BigInt РЅР° С†РµР»РѕРµ С‡РёСЃР»Рѕ СЃР»РµРІР°
    friend BigInt operator*(const long long x, const BigInt& b);
 
    // РЎР»РѕР¶РµРЅРёРµ BigInt СЃ С†РµР»С‹Рј С‡РёСЃР»РѕРј СЃР»РµРІР°
    friend BigInt operator+(const long long x, const BigInt& b);
 
    // Р’С‹С‡РёС‚Р°РЅРёРµ РёР· С†РµР»РѕРіРѕ С‡РёСЃР»Р° BigInt
    friend BigInt operator-(const long long x, const BigInt& b);
 
    // Р”РµР»РµРЅРёРµ С†РµР»РѕРіРѕ С‡РёСЃР»Р° РЅР° BigInt
    friend BigInt operator/(const long long x, const BigInt& b);
 
    friend BigInt factorial(const long long n);
};
 
//BigInt factorial(const long long n);
 
// РЈРґР°Р»РµРЅРёРµ Р»РёРґРёСЂСѓСЋС‰РёС… РЅСѓР»РµР№ РёР· *this
void BigInt::remove_lead_zeros()
{
    int index = static_cast<int>(digits.size()) - 1;
    while (!digits[index])
        digits.erase(digits.begin() + index);
}
 
// РЈРґР°Р»РµРЅРёРµ Р»РёРґРёСЂСѓСЋС‰РёС… РЅСѓР»РµР№ РёР· BigInt
void BigInt::remove_lead_zeros(std::vector<int>& _digits) const
{
    int index = static_cast<int>(_digits.size()) - 1;
    while (!_digits[index] && index > 0)
        --index;
 
    _digits.resize(index + 1);
 
    if (!_digits.size()) _digits.push_back(0);
}
 
////////////////////////РЎР›РћР–Р•РќРР•/////////////////////////////////
 
// РЎР»РѕР¶РµРЅРёРµ РІРµРєС‚РѕСЂРѕРІ С†РёС„СЂ РґРІСѓС… BigInt (a >= b) 
std::vector<int> BigInt::addition(const std::vector<int>& a, const std::vector<int>& b) const
{
    // if a == b, a + b = 2 * a
 
    std::vector<int> res;
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
 
//////////////////////Р’Р«Р§РРўРђРќРР•///////////////////////////////
 
// РЎРІРµРґРµРЅРёРµ РґРІСѓС… РІРµРєС‚РѕСЂРѕРІ Рє 1 РґР»РёРЅРµ
void BigInt::normalization(std::vector<int>& a, std::vector<int>& b)    const
{
    int count1{};
    while (static_cast<int>(b.size()) + count1 < a.size()) ++count1;
    b.resize(b.size() + count1);
}
 
// Р Р°Р·РЅРѕСЃС‚СЊ РІРµРєС‚РѕСЂРѕРІ С†РёС„СЂ РґРІСѓС… BigInt (Р° >= b)
std::vector<int> BigInt::subtraction(std::vector<int> a, std::vector<int> b)    const
{
    normalization(a, b);
 
    std::vector<int> res(a.size());
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
 
//////////////////////РЈРњРќРћР–Р•РќРР•///////////////////////////////////
 
// РЈРјРЅРѕР¶РµРЅРёРµ РІРµРєС‚РѕСЂРѕРІ С†РёС„СЂ
std::vector<int> BigInt::multiplication(std::vector<int> a, std::vector<int> b) const
{
    long long n = std::max(static_cast<int>(a.size()), static_cast<int>(b.size()));
    normalize_vec_to_2n(a, n);
    normalize_vec_to_2n(b, n);
 
    std::vector<int> res;
 
    res = karacuba_multiplication(a, b);
    carries(res);
 
    return res;
}
 
// Р”РѕРІРѕРґРёРј СЂР°Р·РјРµСЂ РІРµРєС‚РѕСЂР° РґРѕ Р±Р»РёР¶Р°Р№С€РµР№ СЃС‚РµРїРµРЅРё РґРІРѕР№РєРё
void BigInt::normalize_vec_to_2n(std::vector<int>& a, long long n) const
{
    while (n & (n - 1))     ++n;
 
    a.resize(n);
}
 
// РђР»РіРѕСЂРёС‚Рј СѓРјРЅРѕР¶РµРЅРёСЏ РљР°СЂР°С†СѓР±Р° ( O( n ^ log2(3) ) )
std::vector<int> BigInt::karacuba_multiplication(const std::vector<int>& a, const std::vector<int>& b)  const
{
    auto len = a.size();
    std::vector<int> res(2 * len);
 
    if (len <= len_f_naivniy)   return naivniy_multiplication(a, b);
 
 
    auto k = len / 2;
 
    std::vector<int> a_right{ a.begin(),a.begin() + k };
    std::vector<int> a_left{ a.begin() + k,a.end() };
    std::vector<int> b_right{ b.begin(),b.begin() + k };
    std::vector<int> b_left{ b.begin() + k,b.end() };
 
    std::vector<int> P1 = karacuba_multiplication(a_left, b_left);
    std::vector<int> P2 = karacuba_multiplication(a_right, b_right);
 
    std::vector<int> a_lr(k);
    std::vector<int> b_lr(k);
 
    for (int i = 0; i < k; ++i)
    {
        a_lr[i] = a_left[i] + a_right[i];
        b_lr[i] = b_left[i] + b_right[i];
    }
 
    std::vector<int> P3 = karacuba_multiplication(a_lr, b_lr);
 
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
 
// Р‘Р°Р·РѕРІРѕРµ СѓРјРЅРѕР¶РµРЅРёРµ Р·Р° O(n^2), РґР»СЏ С‡РёСЃРµР» РґР»РёРЅС‹ <128 (С‚.Рє. Сѓ СЌС‚РѕРіРѕ Р°Р»РіРѕСЂРёС‚РјР° РјРµРЅСЊС€Рµ РєРѕРЅСЃС‚Р°РЅС‚Р°)
std::vector<int> BigInt::naivniy_multiplication(const std::vector<int>& a, const std::vector<int>& b)       const
{
    std::vector<int> res(2 * a.size());
 
    for (int i = 0; i < static_cast<int>(a.size()); ++i)
    {
        for (int g = 0; g < static_cast<int>(a.size()); ++g)
        {
            res[i + g] += a[i] * b[g];
        }
    }
 
    return res;
}
 
// Р”РµР»Р°РµРј РІСЃРµ РїРµСЂРµРЅРѕСЃС‹ Рё СѓР±РёСЂР°РµРј РІРµРґСѓС‰РёРµ РЅСѓР»Рё
void BigInt::carries(std::vector<int>& res)     const
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
 
//////////////////Р”Р•Р›Р•РќРР•////////////////////////////////////////
 
// Р”РµР»РµРЅРёРµ BigInt РЅР° 2
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
 
// Р’РµРєС‚РѕСЂ Р° РјРµРЅСЊС€Рµ => 1, РІРµРєС‚РѕСЂ b РјРµРЅСЊС€Рµ => 2, a = b => 0
int BigInt::vec_compare(const std::vector<int>& a, const std::vector<int>& b) const
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
 
// РљРѕРЅСЃС‚СЂСѓРєС‚РѕСЂ РїРѕ СѓРјРѕР»С‡Р°РЅРёСЋ
BigInt::BigInt()
    : digits(1, 0)
    , sign()
{ }
 
// РљРѕРЅСЃС‚СЂСѓРєС‚РѕСЂС‹, РїСЂРёРЅРёРјР°СЋС‰РёРµ С†РµР»С‹Рµ С‡РёСЃР»Р°
BigInt::BigInt(long long number)
{
    sign = (number < 0);
    number = abs(number);   // РќР° РІСЃСЏРєРёР№ СЃР»СѓС‡Р°Р№, РјРѕР¶РЅРѕ СѓР±СЂР°С‚СЊ
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
 
 
// РљРѕРЅСЃС‚СЂСѓРєС‚РѕСЂ, РїСЂРёРЅРёРјР°СЋС‰РёР№ СЃС‚СЂРѕРєСѓ
BigInt::BigInt(const std::string& s)
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
 
// РљРѕРЅСЃС‚СЂСѓРєС‚РѕСЂ, РїСЂРёРЅРёРјР°СЋС‰РёР№ РІРµРєС‚РѕСЂ С†РёС„СЂ
BigInt::BigInt(const std::vector<int>& vec, bool _sign)
    : digits(vec)
    , sign(_sign)
{ }
 
// РљРѕРЅСЃС‚СЂСѓРєС‚РѕСЂ РєРѕРїРёР№
BigInt::BigInt(const BigInt& bigInt)
    : digits(bigInt.digits)
    , sign(bigInt.sign)
{}
 
// РљРѕРЅСЃС‚СЂСѓРєС‚РѕСЂ, РїСЂРёРЅРёРјР°СЋС‰РёР№ РЎ-СЃС‚СЂРѕРєСѓ
BigInt::BigInt(const char* str)
{
    // (str == nullptr) throw null_ptr();   // Р”РѕР±Р°РІРёС‚СЊ Р°СЂРіСѓРјРµРЅС‚, РЅР°Р·РІР°РЅРёРµ С„СѓРЅРєС†РёРё, С‡С‚РѕР±С‹ РїСЂРѕС‰Рµ Р±С‹Р»Рѕ РѕС‚Р»РѕРІРёС‚СЊ РѕС€РёР±РєСѓ
 
    if (strlen(str))
    {
        for (long long i = strlen(str) - 1; i > 0; --i)
        {
            if (str[i] > 47 && str[i] < 58)
                digits.push_back(str[i] - '0');
            //se throw invalid_value();     //////////////////////// РњРћР–РќРћ РџР•Р Р•Р”РђР’РђРўР¬ РЎРРњР’РћР› Р Р“РћР’РћР РРўР¬ Р§РўРћ Р­РўРћ РќР• Р§РРЎР›Рћ
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
 
// РљРѕРЅСЃС‚СЂСѓРєС‚РѕСЂ, РїСЂРёРЅРёРјР°СЋС‰РёР№ СЃРёРјРІРѕР»(С†РёС„СЂСѓ)
BigInt::BigInt(const char& c)
{
    if (c > 47 && c < 58)
    {
        digits.push_back(c - '0');
        sign = 0;
    }
    //se throw invalid_value();
}
 
 
 
// РџСЂРµРѕР±СЂР°Р·РѕРІР°С‚СЊ BigInt РІ С†РµР»РѕРµ С‡РёСЃР»Рѕ
ull BigInt::to_ull()    const
{
    //if (this->sign) throw math_error();
    return static_cast<ull>(to_ll());
}
 
long long BigInt::to_ll()   const
{
    //if (this->digits.size() > 18) throw math_error();
    std::string s;
    for (int i = 0; i < static_cast<int>(this->digits.size()); ++i)
        s.push_back(this->digits[i] + '0');
    std::reverse(s.begin(), s.end());
    if (this->sign) s = '-' + s;
    return std::stoll(s);
}
 
ul BigInt::to_ul()  const
{
    //if (this->sign) throw math_error();
    return static_cast<ul>(to_long());
}
 
long BigInt::to_long()  const
{
    return static_cast<long>(to_ll());
}
 
uint BigInt::to_uint()  const
{
    //if (this->sign) throw math_error();
    return static_cast<uint>(to_int());
 
}
 
int BigInt::to_int()    const
{
    ///if (this->digits.size() > 9) throw math_error();
    std::string s;
    for (int i = 0; i < static_cast<int>(this->digits.size()); ++i)
        s.push_back(this->digits[i]);
    std::reverse(s.begin(), s.end());
    if (this->sign) s = '-' + s;
    return std::stoi(s);
}
 
ushort BigInt::to_ushort()  const
{
    //if (this->sign) throw math_error();
    return static_cast<ushort>(to_short());
 
}
 
short BigInt::to_short()    const
{
    //if (this->digits.size() > 6) throw math_error();
    return static_cast<short>(to_int());
}
 
 
 
// РџРѕРїСЂРѕР±РѕРІР°С‚СЊ СЃР»РѕРјР°С‚СЊ СЃ РїРѕРјРѕС‰СЊСЋ РІРІРѕРґР° РІСЃСЏРєРѕРіРѕ РіРѕРІРЅР° РІ РєР°С‡РµСЃС‚РІРµ Р°СЂРіСѓРјРµРЅС‚РѕРІ//////////////////////////////
 
// РЎРјРµРЅР° Р·РЅР°РєР° Сѓ С‡РёСЃР»Р° (СѓРЅР°СЂРЅС‹Р№ РјРёРЅСѓСЃ)
BigInt BigInt::operator-()  const
{
    return { this->digits, !this->sign };
}
 
// РћРїРµСЂР°С‚РѕСЂ РїСЂРёСЃРІР°РёРІР°РЅРёСЏ BigInt
BigInt& BigInt::operator=(const BigInt& a)
{
    if (&a == this) return *this;
 
    this->digits = a.digits;
    this->sign = a.sign;
    return *this;
}
 
// РћРїРµСЂР°С‚РѕСЂ РѕС‚СЂРёС†Р°РЅРёСЏ
BigInt BigInt::operator!() const
{
    return{ digits, !sign };
}
 
// РћРїРµСЂР°С‚РѕСЂ СЂР°РІРµРЅСЃС‚РІР° BigInt
bool BigInt::operator==(const BigInt& a)    const
{
    return (this->sign == a.sign) && (vec_compare(this->digits, a.digits) == 0);
}
 
// РћРїРµСЂР°С‚РѕСЂ РЅРµ СЂР°РІРЅРѕ BigInt
bool BigInt::operator!=(const BigInt& a)    const
{
    return !((*this) == a);
}
 
// РџРµСЂРµРіСЂСѓР·РєР° РѕРїРµСЂР°С‚РѕСЂР° СЃР»РѕР¶РµРЅРёСЏ РґРІСѓС… BigInt
BigInt BigInt::operator+(const BigInt& a)   const
{
    std::vector<int> res;
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
 
// РћРїРµСЂР°С‚РѕСЂ РІС‹С‡РёС‚Р°РЅРёСЏ РґРІСѓС… BigInt
BigInt BigInt::operator-(const BigInt a)    const
{
    if (*this == a) return { 0 };
 
    std::vector<int> res;
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
 
// РћРїРµСЂР°С‚РѕСЂ СѓРјРЅРѕР¶РµРЅРёСЏ РґРІСѓС… BigInt
BigInt BigInt::operator*(const BigInt& a)   const
{
    std::vector<int> res;
    bool res_sign{ static_cast<bool>(this->sign ^ a.sign) };
 
    res = multiplication(this->digits, a.digits);
 
    return { res, res_sign };
}
 
 
// РџРµСЂРµРіСЂСѓР·РєР° РѕРїРµСЂР°С‚РѕСЂР° СѓРјРЅРѕР¶РµРЅРёСЏ BigInt РЅР° С†РµР»РѕРµ С‡РёСЃР»Рѕ СЃРїСЂР°РІР°
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
 
 
 
// РћРїРµСЂР°С‚РѕСЂ РґРµР»РµРЅРёСЏ РґРІСѓС… BigInt
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
    if (ans != 0)
        ans.sign = this->sign ^ a.sign;
    return ans;
}
 
// РћРїРµСЂР°С‚РѕСЂ РІР·СЏС‚РёСЏ РѕСЃС‚Р°С‚РєР° РїСЂРё РґРµР»РµРЅРёРё РЅР° BigInt
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
 
//// Р’Р·СЏС‚РёРµ РєРѕСЂРЅСЏ РёР· BigInt
BigInt BigInt::square(const int n) const
{
    //////if (n < 2) throw math_error();
 
    BigInt l{}, r{ BigInt{10}.power(static_cast<int>(this->digits.size() + 2) / 2) }, mid, ans{ 0 }, sum, current;
    while (l <= r)
    {
        sum = r + l;
        mid = div_by_2(sum);
        current = mid.power(n);
        if (current < (*this))
        {
            ans = mid;
            l = mid + 1;
        }
        else if (current > (*this))
            r = mid - 1;
        else return mid;
    }
 
    return ans;
}
 
//BigInt BigInt::square(const int n) const
//{
//  if (n < 2) throw math_error();
//  unsigned int t;
//  BigInt ans{ BigInt{10}.power(static_cast<int>(this->digits.size() + 1) / 2) }, next{ ans - 1 };
//
//  while (next < ans)
//  {
//      ans = next;
//      next = (ans + (*this) / ans) / 2;
//  }
//  return ans;
//}
 
// Р’РѕР·РІРµРґРµРЅРёРµ РІ С†РµР»СѓСЋ СЃС‚РµРїРµРЅСЊ BigInt
BigInt BigInt::power(const BigInt& n)   const
{
    //if (n < 0) throw math_error();        // РЈ РЅР°СЃ BigInt Р° РЅРµ BigDouble
 
    BigInt ans{ 1 }, val{ (*this) }, k{ n };
 
    while (k > 0)
    {
        if (k % 2 == 0)
        {
            k = k / 2;
            val *= val;
        }
        else
        {
            k = k - 1;
            ans *= val;
        }
    }
 
    return ans;
}
 
BigInt& BigInt::operator*=(const BigInt& a)
{
    (*this) = (*this) * a;
    return *this;
}
 
// РЎС‚СЂРѕРіРёР№ РѕРїРµСЂР°С‚РѕСЂ Р±РѕР»СЊС€Рµ РґР»СЏ РґРІСѓС… BigInt
bool BigInt::operator>(const BigInt& a)     const
{
    // Р•СЃР»Рё Р·РЅР°РєРё СЂР°РІРЅС‹ РґРІР° СЃР»СѓС‡Р°СЏ
    if ((this->sign && a.sign) || (!(this->sign) && !a.sign))
    {
        return (vec_compare(this->digits, a.digits) == 2);
    }
    else if (this->sign && !a.sign) return false;
    else return true;
 
}
 
// РќРµС‚СЂРѕРіРёР№ РѕРїРµСЂР°С‚РѕСЂ Р±РѕР»СЊС€Рµ РґР»СЏ РґРІСѓС… BigInt
bool BigInt::operator>=(const BigInt& a)    const
{
    if ((this->sign && a.sign) || (!(this->sign) && !a.sign))
    {
        return (vec_compare(this->digits, a.digits) != 1);
    }
    else if (this->sign && !a.sign) return false;
    else return true;
 
}
 
// РЎС‚СЂРѕРіРёР№ РѕРїРµСЂР°С‚РѕСЂ РјРµРЅСЊС€Рµ РґР»СЏ РґРІСѓС… BigInt
bool BigInt::operator<(const BigInt& a)     const
{
    if ((this->sign && a.sign) || (!(this->sign) && !a.sign))
        return (vec_compare(this->digits, a.digits)) == 1;
    else if (this->sign && !a.sign) return true;
    else return false;
}
 
// РќРµСЃС‚СЂРѕРіРёР№ РѕРїРµСЂР°С‚РѕСЂ РјРµРЅСЊС€Рµ РґР»СЏ РґРІСѓС… BigInt
bool BigInt::operator<=(const BigInt& a)    const
{
    if ((this->sign && a.sign) || (!(this->sign) && !a.sign))
        return (vec_compare(this->digits, a.digits)) != 2;
    else if (this->sign && !a.sign) return true;
    else return false;
}
 
// Р’С‹РІРѕРґ ( _reverse = 0 вЂ” РѕР±С‹С‡РЅРѕРµ С‡РёСЃР»Рѕ, _reverse = 1 вЂ” РїРµСЂРµРІС‘СЂРЅСѓС‚РѕРµ)
void BigInt::print(bool _reverse)           const
{
    if (!_reverse)
    {
        if (sign) std::cout << '-';
        for (int i = static_cast<int>(digits.size() - 1); i >= 0; --i)
            std::cout << digits[i];
    }
    else
    {
        for (int i = 0; i < static_cast<int>(digits.size()); ++i)
            std::cout << digits[i];
        if (sign) std::cout << '-';
    }
}
 
// Р’Р·СЏС‚РёРµ РјРѕРґСѓР»СЏ РѕС‚ С‡РёСЃР»Р°
BigInt BigInt::make_abs()   const
{
    return { this->digits,0 };
}
 
// РџРµСЂРµРіСЂСѓР·РєР° РѕРїРµСЂР°С‚РѕСЂРѕРІ РІРІРѕРґР°/РІС‹РІРѕРґР°
// Р»РёР±Рѕ 2 РѕС‚РґРµР»СЊРЅС‹С… Р»РёР±Рѕ РїСЂРѕРІРµСЂРєСѓ РЅР° РІРІРѕРґ/РІС‹РІРѕРґ РёР· С„Р°Р№Р»Р°!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// 
// РЎС‚Р°РЅРґР°СЂС‚РЅС‹Р№ РІС‹РІРѕРґ
std::ostream& operator<<(std::ostream& out, const BigInt& a)
{
    a.print();
    return out;
}
 
// РЎС‚Р°РЅРґР°СЂС‚РЅС‹Р№ РІРІРѕРґ
std::istream& operator>>(std::istream& in, BigInt& a)
{
    std::string s;
    in >> s;
    a = s;
    return in;
}
 
 
 
// РџРµСЂРµРіСЂСѓР·РєР° Р°СЂРёС„РјРµС‚РёС‡РµСЃРєРёС… РѕРїРµСЂР°С‚РѕСЂРѕРІ СЃР»РµРІР°
 
 
// РџРµСЂРµРіСЂСѓР·РєР° РѕРїРµСЂР°С‚РѕСЂР° СѓРјРЅРѕР¶РµРЅРёСЏ BigInt РЅР° С†РµР»РѕРµ С‡РёСЃР»Рѕ СЃР»РµРІР°
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
 
 
 
// РџРµСЂРµРіСЂСѓР·РєР° РѕРїРµСЂР°С‚РѕСЂР° РІС‹С‡РёС‚Р°РЅРёСЏ РёР· С†РµР»РѕРіРѕ С‡РёСЃР»Р° BigInt
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
 
 
 
// РџРµСЂРµРіСЂСѓР·РєР° РѕРїРµСЂР°С‚РѕСЂР° РґРµР»РµРЅРёСЏ С†РµР»РѕРіРѕ С‡РёСЃР»Р° РЅР° BigInt
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
 
 
 
// РџРµСЂРµРіСЂСѓР·РєР° РѕРїРµСЂР°С‚РѕСЂР° СЃР»РѕР¶РµРЅРёСЏ BigInt СЃ С†РµР»С‹Рј С‡РёСЃР»РѕРј СЃР»РµРІР°
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
 
 
 
// РџРµСЂРµРіСЂСѓР·РєР° РѕРїРµСЂР°С‚РѕСЂР° РѕС‚СЃС‚Р°С‚РєР° С†РµР»РѕРіРѕ С‡РёСЃР»Р° РЅР° BigInt
BigInt operator%(const long long x, const BigInt& b)
{
    return BigInt{ x } % b;
}
 
BigInt operator%(const ull x, const BigInt& a)
{
    return static_cast<long long>(x) % a;
}
 
BigInt operator%(const long  x, const BigInt& a)
{
    return static_cast<long long>(x) % a;
}
 
BigInt operator%(const ul x, const BigInt& a)
{
    return static_cast<long long>(x) % a;
}
 
BigInt operator%(const int x, const BigInt& a)
{
    return static_cast<long long>(x) % a;
}
 
BigInt operator%(const uint  x, const BigInt& a)
{
    return static_cast<long long>(x) % a;
}
 
BigInt operator%(const short x, const BigInt& a)
{
    return static_cast<long long>(x) % a;
}
 
BigInt operator%(const ushort x, const BigInt& a)
{
    return static_cast<long long>(x) % a;
}
 
 
 
 
 
void solve()
{
    int k, n; cin >> k >> n;
    BigInt dp[301]{};
 
    dp[0] = 1;
    dp[1] = 1;
    for (int i = 2; i <= k; ++i)
        dp[i] = dp[i - 1] * 2;
 
    for (int i = k + 1; i <= n; ++i)
    {
        dp[i] = dp[i - 1] * 2 - dp[i - 1 - k];
    }
     
    dp[n].print();
}
 
 
 
int main()
{
    int t{ 1 };
    //cin >> t;
    while (t-- > 0)
    {
        solve();
    }
    return 0;
}