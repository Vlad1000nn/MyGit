#pragma once

#include <vector>
#include <utility>
#include <string>


template<typename T>
class CanonicalHuffman
{
private:

	std::vector<std::pair<int, std::basic_string<T>>> codes;

	static std::basic_string<T>& increment(std::basic_string<T>& str);

public:

	CanonicalHuffman(const std::vector<std::pair<int, std::basic_string<T>>>& codes);

	std::pair<std::vector<std::pair<int, int>>, std::vector<std::pair<int, std::basic_string<T>>>> solve();

};


template<typename T>
CanonicalHuffman<T>::CanonicalHuffman(const std::vector<std::pair<int, std::basic_string<T>>>& codes)
	: codes(codes)
{ }


template<typename T>
std::basic_string<T>& CanonicalHuffman<T>::increment(std::basic_string<T>& str)
{
	int index = (int)str.size() - 1;

	while (index >= 0 && str[index] == L'1')
	{
		str[index] = L'0';
		--index;
	}

	if (index == -1)
		str = L'1' + str;
	else str[index] = L'1';

	return str;
}


template<typename T>
std::pair<std::vector<std::pair<int, int>>, std::vector<std::pair<int, std::basic_string<T>>>> CanonicalHuffman<T>::solve()
{
	std::vector<std::pair<int, int>> stoi_codes;
	const int n = (int)codes.size();
	int i{};
	for (; i < n; ++i)
		stoi_codes.push_back({ codes[i].first, (int)codes[i].second.size() });


	std::vector<std::pair<int, std::basic_string<T>>> answ(n);

	std::basic_string<T> current(stoi_codes[0].second, L'0');
	answ[0] = { stoi_codes[0].first, current };
	i = 1;

	while (i < n)
	{
		if (stoi_codes[i].second == stoi_codes[i - 1].second)
			answ[i] = { stoi_codes[i].first, increment(current) };
		else
			answ[i] = { stoi_codes[i].first, increment(current) += std::basic_string<T>(stoi_codes[i].second - stoi_codes[i - 1].second, L'0') };
		++i;
	}

	return { stoi_codes, answ };
}
