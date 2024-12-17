#include <bits/stdc++.h>

#define isz(x) (int)x.size()
#define all(x) (x).begin(),(x).end()

using namespace std;

using ll = long long;
using vll = vector<long long>;
using vvll = vector<vll>;

using ull = unsigned long long;


using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;


template<typename T>
std::istream& operator>>(std::istream& in, vector<T>& vec)
{
    for (auto& it : vec)
        in >> it;
    return in;
}

// Overload vector output
template<typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& vec)
{
    for (auto& it : vec)
        out << it << ' ';

    return out;
}


////////////////////////////////////////////////////////////////////////////////////

using vpii = vector<pair<int, int >>;
using vpll = vector<pair<ll, ll>>;

struct BigInt
{
	// +, -, *, /, %, <, <<
	std::vector<int> digits;
	int sign;
	int base;

	BigInt()
		: digits(1)
		, sign(0)
		, base(10)
	{
	}

	BigInt(const std::vector<int>& vec, const int k = 0)
		: digits(vec)
		, sign(k)
		, base(10)
	{
	}

	BigInt(const std::string& s)
		: base(10)
	{
		const int n = (int)s.size();
		sign = s[0] == '-';
		int i = (sign ? 1 : 0), j{ n - 1 - sign };
		digits.resize(j + 1);
		for (; i < n; --j, ++i)
			digits[j] = s[i] - '0';
	}

	BigInt(int k)
		: base(10)
	{
		sign = (k < 0);
		k = abs(k);
		while (k) {
			digits.push_back(k % base);
			k /= base;
		}
		if (!(int)digits.size())
			digits.push_back(0);
	}


	bool isZero()	const
	{
		return !digits[(int)digits.size() - 1];
	}


	bool operator<(const BigInt& val)	const
	{
		const int n = (int)digits.size();
		const int m = (int)val.digits.size();
		if (n != m)
			return n < m;
		else {
			if (sign != val.sign)
				return !sign;
			int i{ n - 1 };
			for (; i >= 0; --i)
			{
				const int& a = digits[i];
				const int& b = val.digits[i];
				if (a != b)
					return a < b;
			}
			return false;
		}
	}

	static void remove_lead_zeros(std::vector<int>& vec)
	{
		int i = (int)vec.size() - 1;
		while (i > 0 && !vec[i])
			--i;
		vec.resize(i + 1);
	}

	BigInt operator-()	const
	{
		return { digits, 1 - sign };
	}

	BigInt operator+(const BigInt& val)	const
	{
		const std::vector<int>* a = &digits;
		const std::vector<int>* b = &val.digits;
		std::vector<int> res;
		int res_sign{ sign };

		if ((sign + val.sign % 2) & 1)
		{
			const bool less = vec_cmp(*a, *b);
			if (less)
				std::swap(a, b);

			res = subtraction(*a, *b);
			res_sign = (less == sign ? 0 : 1);
		}
		else
			res = addition(*a, *b);

		return BigInt{ res, res_sign };
	}

	static bool vec_cmp(const std::vector<int>& a, const std::vector<int>& b)
	{
		const int n = (int)a.size();
		const int m = (int)b.size();
		if (n != m)
			return n < m;
		else {
			int i{ n - 1 };
			for (; i >= 0; --i)
				if (a[i] != b[i])
					return a[i] < b[i];
		}
		return false;
	}

	BigInt operator-(const BigInt& val)	const
	{
		const std::vector<int>* a = &digits;
		const std::vector<int>* b = &val.digits;
		std::vector<int> res;
		int res_sign{ sign };

		if ((sign + val.sign % 2) & 1)
			res = addition(*a, *b);
		else
		{
			const bool less = vec_cmp(*a, *b);
			if (less)
				std::swap(a, b);

			res = subtraction(*a, *b);
			res_sign = (less == sign ? 0 : 1);
		}
		return BigInt{ res, res_sign };
	}

	BigInt operator*(const BigInt& val)	const
	{
		std::vector<int> a = digits;
		std::vector<int> b = val.digits;

		const int res_sign = ((sign + val.sign % 2) & 1);
		const int n = std::max((int)a.size(), (int)b.size());
		allign(a, n);
		allign(b, n);
		std::vector<int> res(2 * n + 1);

		int i{}, j{};
		for (; i < n; ++i)
			for (j = 0; j < n; ++j)
				res[i + j] += a[i] * b[j];

		for (i = 0; i < 2 * n; ++i)
		{
			res[i + 1] += res[i] / base;
			res[i] %= base;
		}
		remove_lead_zeros(res);
		return BigInt{ res, res_sign };
	}



	std::vector<int> addition(const std::vector<int>& first, const std::vector<int>& second)	const
	{
		std::vector<int> a{ first };
		std::vector<int> b{ second };

		const int n = std::max((int)a.size(), (int)b.size());
		allign(a, n);
		allign(b, n);

		std::vector<int> res(n + 1);

		int i{}, carry{};
		for (; i < n; ++i)
		{
			res[i] = a[i] + b[i] + carry;
			carry = (res[i] >= base);
			res[i] %= base;
		}
		res[n] = carry;

		remove_lead_zeros(res);
		return res;
	}

	std::vector<int> subtraction(const std::vector<int>& first, const std::vector<int>& second)	const
	{
		std::vector<int> a = first;
		std::vector<int> b = second;

		const int n = std::max((int)a.size(), (int)b.size());
		allign(a, n + 1);
		allign(b, n + 1);
		std::vector<int> res(n + 1);
		int i{};
		for (; i < n; ++i)
		{
			res[i] = a[i] - b[i];
			a[i + 1] -= (res[i] < 0);
			res[i] = (res[i] + base) % base;
		}
		remove_lead_zeros(res);
		return res;
	}

	static void allign(std::vector<int>& vec, int k)
	{
		assert(k >= (int)vec.size());
		vec.resize(k);
	}


	friend std::ostream& operator<<(std::ostream& out, const BigInt& val)
	{
		if (val.isZero())
			out << "0";
		else {
			const std::vector<int>& a = val.digits;
			const int n = (int)a.size();
			out << (val.sign ? "-" : "");
			int i{ n - 1 };
			for (; i >= 0; --i)
				out << a[i];
		}
		return out;
	}

	BigInt operator / (const int val) const {
		return int_div(val).first;
	}

	int operator%(const int val)	const
	{
		return int_div(val).second;
	}

	std::pair<BigInt, int> int_div(const int x)	const
	{
		if (!x)
			throw std::runtime_error("division by zero");
		const int n = (int)digits.size();
		BigInt res{ };
		res.sign = sign;
		allign(res.digits, n);
		std::vector<int>& vec = res.digits;

		long long i{ n - 1 }, curr, carry{};
		for (; i >= 0; --i)
		{
			curr = 1LL * carry * base + digits[i];
			carry = curr % x;
			vec[i] = curr / x;
		}
		remove_lead_zeros(vec);
		return { res,carry };
	}

	int get_len()	const
	{
		return isz(digits);
	}

	std::string to_string()	const
	{
		std::string out = "";
		if (isZero())
			out = "0";
		else {
			const std::vector<int>& a = digits;
			const int n = (int)a.size();
			out = out + (sign ? "-" : "");
			int i{ n - 1 };
			for (; i >= 0; --i)
				out = out + std::to_string(a[i]);
		}
		return out;
	}

};

ll calculate(BigInt a, int step)
{
	ll answ{};
	if (step == 25) 
		return 1;
	
	if (a.isZero())
		answ += calculate(1, step + 1);
	else if (a.get_len() % 2 == 0)
	{
		std::string curr, left, right;
		curr = a.to_string();
		left = curr.substr(0, isz(curr) / 2);
		int i = isz(curr) / 2;
		while (i < isz(curr) - 1 && curr[i] == '0')
			++i;
		right = curr.substr(i);
		answ += calculate(left, step + 1) + calculate(right, step + 1);
	}
	else 
		answ += calculate(a * 2024, step + 1);


	return answ;
}


void solve()
{
	std::ifstream fin("input.txt");
	std::string line;
	ll answ{};
	while (fin >> line)
	{
		BigInt a(line);
		answ += calculate(a, 0);
	}
	std::cout << answ << '\n';
}


int32_t main()
{
    cin.tie(0);
    std::ios_base::sync_with_stdio(false);

    int32_t t{ 1 };

    while (t--)
        solve();

    return 0;
}
