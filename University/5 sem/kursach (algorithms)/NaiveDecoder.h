#pragma once

#include <vector>
#include <utility>
#include <boost/dynamic_bitset.hpp>
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <stdexcept>

// Decoder of naive solution
template<typename T>
class NaiveDecoder
{
private:

	std::vector<std::pair<T, boost::dynamic_bitset<>>> decode;
	int code_size;

	const T get_symbol(boost::dynamic_bitset<> bits)	const;

public:

	// Constructor
	NaiveDecoder(std::basic_ifstream<T>& in);

	std::basic_string<T> decode_text(const std::basic_string<T>& text)	const;

};


template<typename T>
NaiveDecoder<T>::NaiveDecoder(std::basic_ifstream<T>& in)
{
	std::basic_string<T> s;
	int symbol;  T colon; std::basic_string<T> word;
	while (getline(in, s))
	{
		std::basic_stringstream<T> ss(s);
		ss >> symbol >> colon >> word;
		boost::dynamic_bitset<> bits(word);
		decode.push_back({ T(symbol), bits });
	}

	//for (auto& it : decode)
		//std::wcout << it.first << L" : " << it.second << L'\n';

	code_size = (int)decode[0].second.size();

}


template<typename T>
std::basic_string<T> NaiveDecoder<T>::decode_text(const std::basic_string<T>& text)	const
{
	const int n = (int)text.size();
	std::basic_string<T> answ;
	std::basic_string<T> current;
	int index{};
	for (; index < n; index += code_size)
	{
		current = text.substr(index, code_size);
		const boost::dynamic_bitset<> bits(current);
		answ += get_symbol(bits);
	}

	return answ;
}


template<typename T>
const T NaiveDecoder<T>::get_symbol(boost::dynamic_bitset<> bits)	const
{
	for (const std::pair<T, boost::dynamic_bitset<>>& it : decode)
	{
		if (it.second == bits)
			return it.first;
	}
	throw std::runtime_error("Unknown code");
}

