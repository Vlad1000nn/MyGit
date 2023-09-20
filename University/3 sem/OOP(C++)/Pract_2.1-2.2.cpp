#include <iostream>			// for std::cin, std::cout
#include <map>				// for std::map, std::multimap
#include <set>				// for std::set
#include <functional>		// for std::function
#include "Header.h"			// for class Patient


//////////////////////////////////#2.1//////////////////////////////////////////////////////////////////////////////

// Filter
template<typename Key, typename Value>
std::map<Key, Value> filter(const std::map<Key, Value>& m, std::function<bool(Value)> f)
{
	if (!f) throw "Nullptr";

	std::map<Key, Value> ans;
	typename std::map<Key, Value>::const_iterator it = m.begin();
	while (it != m.end())
	{
		if (f(it->second)) ans.insert(*it);
		++it;
	}

	return ans;
}

// Return all keys, which has certain value
template<typename Key, typename Value>
std::vector<Key> keys_by_value(const std::map<Key, Value>& m, const Value& value)
{
	std::vector<Key> ans;
	typename std::map<Key, Value>::const_iterator it = m.begin();
	while (it != m.end())
	{
		if (it->second == value) ans.push_back(it->first);
		++it;
	}
	return ans;
}

// Return 1 key, which has certain value
template<typename Key, typename Value>
Key key_by_value(const std::map<Key, Value>& m, const Value& value)
{
	typename std::map<Key, Value>::const_iterator it = m.begin();
	while (it != m.end())
	{
		if (it->second == value) return it->first;
		++it;
	}
	return {};
}

// Return value by key
template<typename Key, typename Value>
Value value_by_key(const std::map<Key, Value>& m, const Key& key)
{
	if (!m.contains(key)) return {};		// before C++20 if(m.find(key) == m.end())
	return  m.find(key)->second;
}

// Print function for map
template<typename Key, typename Value>
void print_map(const std::map<Key, Value>& m)
{
	for (auto& it : m) std::wcout << it.first << ' ' << it.second << '\n';
}

// Return vector of unique values in map
template<typename Key, typename Value>
std::vector<Value> get_different_values(const std::map<Key, Value>& m)
{
	std::set<Value> ans;
	for (auto& it : m) ans.insert(it.second);

	return { ans.begin(),ans.end() };
}

// Overloading operator<< for map
template<typename Key, typename Value>
std::ostream& operator<<(std::ostream& out, const std::map<Key, Value>& m)
{
	print_map(m);
	return out;
}

// Overloading operator<< for map (std::wcout)
template<typename Key, typename Value>
std::wostream& operator<<(std::wostream& out, const std::map<Key, Value>& m)
{
	print_map(m);
	return out;
}

// Checking if the key is already in map
template<typename Key, typename Value>
void insert_map(std::map<Key, Value>& m, const Key& key, const Value& value)
{
	if (m.contains(key))   // Before C++20 if(m.find(key) != m.end())
		throw "Wrong_Key";
	m.insert({ key, value });
}


////////////# 2.2////////////////////////////////////////////////////////////////

// Filter
template<typename Key, typename Value>
std::multimap<Key, Value> filter(const std::multimap<Key, Value>& m, std::function<bool(Value)> f)
{
	if (!f) throw "Nullptr";

	std::multimap<Key, Value> ans;
	typename std::multimap<Key, Value>::const_iterator it = m.begin();
	while (it != m.end())
	{
		if (f(it->second)) ans.insert(*it);
		++it;
	}

	return ans;
}

// Return all keys, which has certain value
template<typename Key, typename Value>
std::vector<Key> keys_by_value(const std::multimap<Key, Value>& m, const Value& value)
{
	std::vector<Key> ans;
	typename std::multimap<Key, Value>::const_iterator it = m.begin();
	while (it != m.end())
	{
		if (it->second == value) ans.push_back(it->first);
		++it;
	}
	return ans;
}

// Return 1 key, which has certain value
template<typename Key, typename Value>
Key key_by_value(const std::multimap<Key, Value>& m, const Value& value)
{
	typename std::multimap<Key, Value>::const_iterator it = m.begin();
	while (it != m.end())
	{
		if (it->second == value) return it->first;
		++it;
	}
	return m.end();
}

// Return all elements in map, that has certain key
template<typename Key, typename Value>
std::vector<std::pair<Key, Value>> similar(const std::multimap<Key, Value>& m, const Key& key)
{
	std::vector<std::pair<Key, Value>> ans;
	for (auto& it : m) if (it.first == key) ans.push_back({ it.first, it.second });
	return ans;
}

// Return value by key
template<typename Key, typename Value>
Value value_by_key(const std::multimap<Key, Value>& m, const Key& key)
{
	if (!m.contains(key)) return {};		// before C++20 if(m.find(key) == m.end())
	return  m.find(key)->second;
}

// Print function for map
template<typename Key, typename Value>
void print_multimap(const std::multimap<Key, Value>& m)
{
	for (auto& it : m) std::wcout << it.first << ' ' << it.second << '\n';
}

// Return vector of unique values in map
template<typename Key, typename Value>
std::vector<Value> get_different_values(const std::multimap<Key, Value>& m)
{
	std::set<Value> ans;
	for (auto& it : m) ans.insert(it.second);

	return { ans.begin(),ans.end() };
}

// Overloading operator<< for map
template<typename Key, typename Value>
std::ostream& operator<<(std::ostream& out, const std::multimap<Key, Value>& m)
{
	print_map(m);
	return out;
}

// Overloading operator<< for map (std::wcout)
template<typename Key, typename Value>
std::wostream& operator<<(std::wostream& out, const std::multimap<Key, Value>& m)
{
	print_map(m);
	return out;
}

// Checking if the key is already in map
template<typename Key, typename Value>
void insert_multimap(std::multimap<Key, Value>& m, const Key& key, const Value& value)
{
	if (m.contains(key))   // Before C++20 if(m.find(key) != m.end())
		throw "Wrong_Key";
	m.insert({ key, value });
}


int main()
{
	try {
		std::vector<Patient> vec(15);
		for (auto& it : vec) fill(it);


		std::map<std::wstring, std::wstring> m;
		for (auto& it : vec) m[it.get_card_number()] = it.get_blood_type();

		for (auto& it : vec) std::wcout << it.get_blood_type() << ' ';
		std::cout << '\n';

		for (auto& it : vec)
		{
			std::wstring curr = it.get_card_number();
			std::wcout << value_by_key(m, curr) << ' ';
		}
		std::cout << '\n';

		std::wstring str = L"II";
		std::wstring str_id = L"22";
		std::wcout << key_by_value(m, str) << '\n';

		std::vector<std::wstring> values = keys_by_value(m, str);
		for (auto& it : values) std::wcout << it << ' ';
		std::cout << '\n';

		std::function<bool(std::wstring)> lambda = [](std::wstring x) { return x == L"II"; };


		std::map<std::wstring, std::wstring> m2 = filter(m, lambda);
		for (auto it : m2) std::wcout << it.first << ' ';
		std::cout << '\n';

		print_map(m2);

		std::vector<std::wstring> unique = get_different_values(m);
		for (auto& it : unique) std::wcout << it << ' ';
		std::cout << '\n';

		insert_map(m, str_id, str);
		std::wcout << m;
	}
	catch (const char exc)
	{
		std::cout << "Exc: " << exc;
	}
	catch (...)
	{
		std::cout << "Unknown error";
		std::abort();
	}


	return 0;
}
