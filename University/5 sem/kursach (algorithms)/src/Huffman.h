#pragma once

#include <vector>
#include <queue>
#include <utility>
#include <string>
#include <type_traits>
#include <tuple>


class Huffman
{
private:

	struct Node
	{
	public:
		int freq, data;
		Node* left, * right;

		Node(const int data, const int freq);

	};

	Node* root;
	int n; // Count of symbols

	// Build tree using heap, O(nlogn)
	void build(const std::vector<int>& symbols, const std::vector<int>& frequency);

	// If data is sorted we can build it with O(n)
	void build_sorted(const std::vector<int>& symbols, const std::vector<int>& frequency);

	// Help function to extract minimum from our 2 queues
	static Node* extract_min(std::queue<Node*>& q1, std::queue<Node*>& q2);

public:

	// Constructor
	Huffman(const std::vector<int>& symbols, const std::vector<int>& frequency, bool sorted = false);

	// return pairs <symbol, code>
	template<typename T>
	std::vector<std::pair<int, std::basic_string<T>>> get_code() const;

	// Destructor
	~Huffman();

};


template<typename T>
std::vector<std::pair<int, std::basic_string<T>>> Huffman::get_code() const
{
	std::basic_string<T> zero;
	std::basic_string<T> one;

	if constexpr (std::is_same<T, wchar_t>::value) {
		zero = L"0";
		one = L"1";
	} else {
		zero = "0";
		one = "1";
	}

	std::vector<std::pair<int, std::basic_string<T>>> answ;
	Node* curr = root;
	std::basic_string<T> str;
	std::queue<std::pair<Node*, std::basic_string<T>>> q;
	q.push(std::make_pair(curr, std::basic_string<T>()));
	while (!q.empty())
	{
		std::tie(curr, str) = q.front();
		q.pop();
		if (!curr)
			continue;
		if (curr->data)
			answ.push_back({ curr->data, str });
		q.push({ curr->left, str + zero });
		q.push({ curr->right, str + one });
	}

	return answ;
}
