#include "Huffman.h"

#include <algorithm>
#include <tuple>


Huffman::Huffman(const std::vector<int>& symbols, const std::vector<int>& frequency, bool sorted)
{
	sorted && std::is_sorted(frequency.begin(), frequency.end()) ? build_sorted(symbols, frequency) : build(symbols, frequency);
}


Huffman::~Huffman()
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


Huffman::Node::Node(const int data, const int freq)
	: data(data)
	, freq(freq)
	, left(nullptr)
	, right(nullptr)
{ }


void Huffman::build(const std::vector<int>& symbols, const std::vector<int>& frequency)
{
	const int n = (int)symbols.size();
	std::vector<Node*> minHeap;
	auto node_compare = [&minHeap](const Node* x, const Node* y) { return x->freq > y->freq; };
	int i{};
	Node* left, * right, * top;
	for (; i < n; ++i)
		minHeap.push_back(new Node(symbols[i], frequency[i]));

	std::make_heap(minHeap.begin(), minHeap.end(), node_compare);

	while ((int)minHeap.size() > 1)
	{
		std::pop_heap(minHeap.begin(), minHeap.end(), node_compare);
		left = minHeap.back();
		minHeap.pop_back();

		std::pop_heap(minHeap.begin(), minHeap.end(), node_compare);
		right = minHeap.back();
		minHeap.pop_back();

		top = new Node(0, left->freq + right->freq);
		top->left = left;
		top->right = right;

		minHeap.push_back(top);
		std::push_heap(minHeap.begin(), minHeap.end(), node_compare);
	}

	root = minHeap[0];
}


void Huffman::build_sorted(const std::vector<int>& symbols, const std::vector<int>& frequency)
{
	const int n = (int)symbols.size();
	std::queue<Node*> q1, q2;
	int i{};
	Node* left, * right, * top;
	for (; i < n; ++i)
		q1.push(new Node(symbols[i], frequency[i]));

	while ((int)q1.size() + (int)q2.size() > 1)
	{
		left = extract_min(q1, q2);
		right = extract_min(q1, q2);

		top = new Node(0, left->freq + right->freq);
		top->left = left;
		top->right = right;
		q2.push(top);
	}
	root = ((int)q1.size() ? q1.front() : q2.front());
}


Huffman::Node* Huffman::extract_min(std::queue<Node*>& q1, std::queue<Node*>& q2)
{
	Node* answ;
	if (!(int)q2.size())
	{
		answ = q1.front();
		q1.pop();
	}
	else {
		if (!(int)q1.size())
		{
			answ = q2.front();
			q2.pop();
		}
		else {
			answ = std::min(q1.front()->freq, q2.front()->freq) == q1.front()->freq ? q1.front() : q2.front();
			answ == q1.front() ? q1.pop() : q2.pop();
		}
	}
	return answ;
}
