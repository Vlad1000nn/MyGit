#pragma once

#include <map>
#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include <sstream>


template<typename T>
class CanonicalHuffmanDecoder
{
private:

	struct Node {
		Node* left, * right;
		int data;

		Node(const int data = 0);
	
	};

	std::map<std::basic_string<T>, int> codes;
	Node* root;
	int max_cnt;

	void build_tree();

	static std::basic_string<T>& increment(std::basic_string<T>& str);

	void build_table(const std::vector<std::pair<int, int>>& decode);

public:

	CanonicalHuffmanDecoder(std::basic_ifstream<T>& in);

	std::basic_string<T> solve(const std::basic_string<T>& text);

};


template<typename T>
CanonicalHuffmanDecoder<T>::CanonicalHuffmanDecoder(std::basic_ifstream<T>& in)
{
	std::vector<std::pair<int, int>> decodes;
	root = new Node();
	int symbol, len;
	std::basic_string<T> s;
	while (std::getline(in, s))
	{
		std::basic_stringstream<T> ss(s);
		ss >> symbol >> len;
		decodes.push_back({ symbol, len });
	}
	max_cnt = decodes.back().second;

	build_table(decodes);
	build_tree();
}


template<typename T>
CanonicalHuffmanDecoder<T>::Node::Node(const int data)
	: data(data)
	, left(nullptr)
	, right(nullptr)
{ }



template<typename T>
void CanonicalHuffmanDecoder<T>::build_tree()
{
	std::basic_string<T> zero;
	std::basic_string<T> one;

	if constexpr (std::is_same<T, wchar_t>::value) {
		zero = L"0";
		one = L"1";
	}
	else {
		zero = "0";
		one = "1";
	}

	const int* symbol = nullptr;
	const std::basic_string<T>* code = nullptr;
	Node* curr, * next;

	for (const std::pair<std::basic_string<T>, int>& item : codes)
	{
		code = &item.first;
		symbol = &item.second;
		curr = root;

		for (const T& iterator : *code)
		{
			next = (iterator == '1' ? curr->right : curr->left);
			if (!next)
			{
				next = new Node();
				(iterator == '1' ? curr->right : curr->left) = next;
			}
			curr = next;
		}
		curr->data = *symbol;
	}
}


template<typename T>
std::basic_string<T>& CanonicalHuffmanDecoder<T>::increment(std::basic_string<T>& str)
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
void CanonicalHuffmanDecoder<T>::build_table(const std::vector<std::pair<int, int>>& decode)
{
	std::basic_string<T> current(decode[0].second, L'0');
	codes[current] = decode[0].first;
	int i{ 1 };
	const int n = (int)decode.size();
	while (i < n)
	{
		if (decode[i].second == decode[i - 1].second)
			codes[increment(current)] = decode[i].first;
		else
			codes[increment(current) += std::basic_string<T>(decode[i].second - decode[i - 1].second, L'0')] = decode[i].first;
		++i;
	}

}


template<typename T>
std::basic_string<T> CanonicalHuffmanDecoder<T>::solve(const std::basic_string<T>& text)
{
	Node* curr = root;
	std::basic_string<T> answ;
	const int n = (int)text.size();
	int i{};

	while (i < n)
	{
		curr = (text[i] == L'0' ? curr->left : curr->right);
		if (curr->data)
		{
			answ += curr->data;
			curr = root;
		}
		++i;
	}

	return answ;
}
