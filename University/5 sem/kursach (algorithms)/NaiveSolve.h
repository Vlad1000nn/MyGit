#pragma once
#include <boost/dynamic_bitset.hpp>
#include <string>
#include <vector>
#include <set>
#include <cmath>
#include <algorithm>
#include <utility>

// Naive solve (static length of codes)
template<typename T>
class NaiveSolve
{
private:

	std::basic_string<T> code;	  // output
	std::basic_string<T> text;	  // input
	std::vector<int> symbols;	  // symbols
	std::vector<std::basic_string<T> >encode;	// codes for symbols
	
	// Make a set of symbols
	void get_all_symbols();

	// Make encode for each symbol
	void make_encodes();

	// Cast boost::dynamimc_bitset<> to std::basic_string<T>
	static std::basic_string<T> bitsetToBasicString(const boost::dynamic_bitset<>& bitset);

public:

	NaiveSolve(const std::basic_string<T>& input);
	
	std::basic_string<T> solve();
	
	std::pair<std::vector<int>, std::vector<std::basic_string<T>>>  getDecoder()	const;

};


template<typename T>
NaiveSolve<T>::NaiveSolve(const std::basic_string<T>& input)
	: text(input)
{
	get_all_symbols();
	make_encodes();
}


template<typename T>
void NaiveSolve<T>::get_all_symbols()
{
	std::set<int> unique;
	for (T& it : text)
		unique.insert((int)it);
	symbols = std::vector<int>(unique.begin(), unique.end());
}


template<typename T>
std::pair<std::vector<int>, std::vector<std::basic_string<T>>> NaiveSolve<T>::getDecoder() const
{
	return std::make_pair(symbols, encode);
}


template<typename T>
std::basic_string<T> NaiveSolve<T>::solve()
{
	for (const T& it : text)
		code += encode[std::lower_bound(symbols.begin(), symbols.end(), it) - symbols.begin()];

	return code;
}


template <typename T>
std::basic_string<T> NaiveSolve<T>::bitsetToBasicString(const boost::dynamic_bitset<>& bitset) {
	std::basic_string<T> result;
	for (size_t i = 0; i < bitset.size(); ++i) 
		result += static_cast<T>(bitset[i] ? '1' : '0');
	
	return result;
}


template<typename T>
void NaiveSolve<T>::make_encodes()
{
	const int count = (int)symbols.size();
	const int bit_count = (int)std::ceil(std::log2((int)symbols.size()));
	encode.resize(count);

	int i{};
	for (; i < count; ++i) 
		encode[i] = bitsetToBasicString(boost::dynamic_bitset<>(bit_count, i));

}