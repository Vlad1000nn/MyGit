#include <iostream>		// for std::cin, std::cout
#include <functional>	// for std::function
#include <list>			// for std::list
#include <string_view>	// for std::string_view
#include <string>		// for std::string
#include <algorithm>	// for std::find
#include <random>		// for std::mt19937

// All consonants
const std::string_view consonants = "BCDFGHJKLMNPQRSTVWXYZbcdfghjklmnpqrstvwxyz";

// Checking for a consonant
bool isConsonant(const char c)
{
	return std::find(consonants.begin(), consonants.end(), c) != consonants.end();
}

// Filter std::list<T> by predicate f
template<typename T>
std::list<T> filter(const std::list<T>& lst, std::function<bool(const char)>  f = isConsonant)
{
	if (!f) throw "Nullptr";
	std::list<T> ans;
	typename std::list<T>::const_iterator it = lst.begin();
	while (it != lst.end()) {
		if (f(*it))
			ans.push_front((*it)); ++it;
	}

	return ans;
}

// Function, that prints std::list<T>
template<typename T>
void print_list(const std::list<T>& lst)
{
	std::cout << "List: ";
	typename std::list<T>::const_iterator it = lst.begin();
	while (it != lst.end()) {
		std::cout << *it << ' '; ++it;
	}
	std::cout << '\n';
}

// Overloading of operator<<
template<typename T>
std::ostream& operator<<(std::ostream& out, const std::list<T>& lst)
{
	print_list(lst);
	return out;
}

// Pop the element in random place of std::list<T>
template<typename T>
void pop(std::list<T>& lst, typename std::list<T>::const_iterator it)
{
	if (lst.size())
		lst.erase(it);
}

// Pop the specified element from the std::list<T>
template<typename T>
void pop(std::list<T>& lst, const T& data)
{
	typename std::list<T>::const_iterator it = lst.begin();
	while (it != lst.end() && (*it) != data) ++it;
	if (it != lst.end()) lst.erase(it);
}

// Push the specified element to the std::list<T>
template<typename T>
void push(std::list<T>& lst, const T& data)
{
	typename std::list<T>::const_iterator it = lst.begin();
	while (it != lst.end() && (*it) <= data) ++it;
	lst.insert(it, data);
}

// Below is the implementation of the class and its substitution in std::list<T>
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// namespace for generating random numbers
namespace Random
{
	std::mt19937 mt{ std::random_device{}() };

	int get(const int min, const int max)
	{
		std::uniform_int_distribution<> die{ min, max };
		return die(mt);
	}
}

// Class to fill std::list<T>
class Patient
{
private:
	std::string first_name;
	std::string last_name;
	std::string birthday;
	std::string phone_number;
	std::string address;
	std::string card_number;
	std::string blood_type;

public:

	Patient(const std::string _first_name, const std::string _last_name, const std::string _birthday, const std::string _phone_number,
		const std::string _address, const std::string _card_number, const std::string _blood_type)
		: first_name(_first_name)
		, last_name(_last_name)
		, birthday(_birthday)
		, phone_number(_phone_number)
		, address(_address)
		, card_number(_card_number)
		, blood_type(_blood_type)
	{ }

	Patient() = default;

	const std::string first_names[5]
	{
		"Alex", "Mark","Kate", "Andrew","Max"
	};

	const std::string last_names[5]
	{
		"Koch", "Chang","Fischer", "Chase","Preston"
	};

	std::string make_birthday(const int k1, const int k2, const int k3) const
	{
		std::string ans{ std::to_string(k1) };
		ans += '/'; ans += std::to_string(k2); ans += '/'; ans += std::to_string(k3);
		return ans;
	}

	std::string make_blood(const int k) const
	{
		switch (k)
		{
		case 1: return "I";
		case 2: return "II";
		case 3: return "III";
		case 4: return "IV";
		}
	}

	void fill()
	{
		int k1{ Random::get(0,4) }, k2{ Random::get(0,4) }, k3_1{ Random::get(1,28) }, k3_2{ Random::get(1,12) }, k3_3{ Random::get(1950,2023) },
			k4{ Random::get(10,99) }, k5{ Random::get(1,1000) }, k6{ Random::get(1,4) };

		first_name = first_names[k1];
		last_name = last_names[k2];
		birthday = make_birthday(k3_1, k3_2, k3_3);
		phone_number = "+101 (22) 343-35-" + std::to_string(k4);
		address = "Random street, number of house isn't mind)";
		card_number = std::to_string(k5);
		blood_type = make_blood(k6);
	}

	bool operator<(const Patient& a) const
	{
		return (card_number > a.card_number) || (card_number != a.card_number && blood_type > a.blood_type) ||
			(card_number != a.card_number && blood_type != a.blood_type && last_name < a.last_name) ||
			(card_number != a.card_number && blood_type != a.blood_type && last_name != a.last_name && first_name < a.first_name);
	}

	bool operator>(const Patient& a) const
	{
		return !(*this < a);
	}

	bool operator==(const Patient& a) const
	{
		return !(*this > a) && !(a > *this);
	}

	bool operator>=(const Patient& a) const
	{
		return !(*this < a);
	}

	bool operator<=(const Patient& a) const
	{
		return !(*this > a);
	}

	bool operator!=(const Patient& a) const
	{
		return !(*this == a);
	}

	void print() const
	{
		std::cout << "First name:\t" << first_name << "\nLast name:\t" << last_name << "\nBirthday:\t" << birthday << "\nPhone number:"
			"\t" << phone_number << "\nAddress:\t" << address << "\nCard number:\t" << card_number << "\nBlood type:\t" << blood_type << '\n';
	}

	friend std::ostream& operator<<(std::ostream& out, const Patient& a)
	{
		a.print();
		return out;
	}

	~Patient() = default;
};


int main()
{
	try
	{
		Patient a, b, c, d;
		a.fill(); b.fill(), c.fill(), d.fill();
		std::list<Patient> lst;
		push(lst, a); push(lst, b); push(lst, c); push(lst, d);
		std::list<Patient>::const_iterator it = lst.begin();
		pop(lst, it); it = lst.begin(); pop(lst, it); it = lst.begin(); pop(lst, it); it = lst.begin(); pop(lst, it);
		it = lst.begin(); pop(lst, a);
		std::cout << lst;
	}
	catch (std::string exc)
	{
		std::cout << "Find " << exc;
	}
	catch (...)
	{
		std::cout << "Unknown Error";
		std::abort();
	}

	return 0;
}