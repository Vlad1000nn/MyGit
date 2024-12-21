#pragma once

#include <map>
#include <string>
#include <fstream>
#include <istream>
#include <sstream>
#include <queue>
#include <algorithm>


template<typename T>
class HuffmanDecoder
{
private:

	struct Node
	{
	public:
		int data;
		Node* left, * right;

		Node(const int data = 0);

	};

	// Table with codes for symbols
	std::map<std::basic_string<T>, int> codes;

	Node* root;

	// We need to build our tree
	void build_tree();

public:

	// Get the input file and build table
	HuffmanDecoder(std::basic_istream<T>& in);

	std::basic_string<T> decode(const std::basic_string<T>& text)	const;

	// Destructor
	~HuffmanDecoder();

};


template<typename T>
HuffmanDecoder<T>::HuffmanDecoder(std::basic_istream<T>& in)
{
	root = new Node();
	int symbol;
	T colon;
	std::basic_string<T> s;

	while (std::getline(in, s))
	{
		std::basic_stringstream<T> ss(s);
		ss >> symbol >> colon >> s;
		codes[s] = symbol;
	}

	build_tree();
}


template<typename T>
HuffmanDecoder<T>::~HuffmanDecoder()
{
	Node* curr;
	std::queue<Node*> q;
	q.push(root);
	while (!q.empty())
	{
		curr = q.front();
		q.pop();
		if (!curr)
			continue;
		q.push(curr->left);
		q.push(curr->right);
		curr->left = curr->right = nullptr;
		delete curr;
	}
}


template<typename T>
HuffmanDecoder<T>::Node::Node(const int data)
	: data(data)
	, left(nullptr)
	, right(nullptr)
{ }


template<typename T>
std::basic_string<T> HuffmanDecoder<T>::decode(const std::basic_string<T>& text)	const
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


template<typename T>
void HuffmanDecoder<T>::build_tree()
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
	Node* curr, *next;

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
