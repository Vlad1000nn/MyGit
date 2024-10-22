#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <vector>
#include <string>
#include <boost/dynamic_bitset.hpp>
#include <queue>
#include <numeric>
#include <map>


/*
#include <chrono>
class Timer
{
private:
	using Clock = std::chrono::steady_clock;
	using Second = std::chrono::duration<double, std::ratio<1> >;
	std::chrono::time_point<Clock> m_beg{ Clock::now() };
public:

	void reset()
	{
		m_beg = Clock::now();
	}

	double elapsed() const
	{
		return std::chrono::duration_cast<Second>(Clock::now() - m_beg).count();
	}
};
*/



// Naive solve (static length of codes)
class NaiveSolve 
{
private:

	boost::dynamic_bitset<> code; // output
	std::string text;			  // input
	std::vector<int> symbols;	  // symbols
	std::vector<boost::dynamic_bitset<>> encode;	// codes for symbols


	// Make a set of symbols
	void get_all_symbols()
	{
		std::set<int> unique;
		for (char& it : text)
			unique.insert((int)it);
		symbols = std::vector<int>(unique.begin(), unique.end());
	}


	void make_encodes()
	{
		const int count = (int)symbols.size();
		const int bit_count = (int)std::ceil(std::log2((int)symbols.size()));
		encode.resize(count);

		int i{};
		for (; i < count; ++i)
			encode[i] = boost::dynamic_bitset<>(bit_count, i);
	}


public:

	NaiveSolve(const std::string& input)
		: text(input)
	{
		get_all_symbols();
		make_encodes();
	}


	boost::dynamic_bitset<> solve()
	{
		boost::dynamic_bitset<> buff;
		for (const char& it : text)
		{
			buff = encode[std::lower_bound(symbols.begin(), symbols.end(), it) - symbols.begin()];
			code.resize((int)code.size() + (int)buff.size());
			code <<= (int)buff.size();
			buff.resize((int)code.size());
			code |= buff;
		}

		return code;
	}


	std::pair<std::vector<int>, std::vector<boost::dynamic_bitset<>>> getDecoder()	const
	{
		return make_pair(symbols, encode);
	}

	
};


// Decoder of naive solution
class NaiveDecoder
{
private:

	std::vector<std::pair<char, boost::dynamic_bitset<>>> decode;
	int code_size;


	const char get_symbol(boost::dynamic_bitset<> bits)	const
	{
		for (const std::pair<char, boost::dynamic_bitset<>>& it : decode)
		{
			if (it.second == bits)
				return it.first;
		}
		throw std::runtime_error("Unknown code");
	}


public:

	// Constructor
	NaiveDecoder(std::ifstream& in)
	{
		std::string s;
		int symbol;  char colon; std::string word;
		while (getline(in, s))
		{
			std::stringstream ss(s);
			ss >> symbol >> colon >> word;
			boost::dynamic_bitset<> bits(word);
			decode.push_back({ char(symbol), bits });
		}

		for (auto& it : decode)
			std::cout << it.first << " : " << it.second << '\n';

		code_size = (int)decode[0].second.size();

	}


	std::string decode_text(const std::string& text)	const
	{
		const int n = (int)text.size();
		std::string answ;
		std::string current;
		int index{};
		for (; index < n; index += code_size)
		{
			current = text.substr(index, code_size);
			const boost::dynamic_bitset<> bits(current);
			answ += get_symbol(bits);
		}

		return answ;
	}

};


class Huffman 
{
private:

	struct Node 
	{
	public:
		int freq, data;
		Node* left, *right;

		Node(const int data, const int freq)
			: data(data)
			, freq(freq)
			, left(nullptr)
			, right(nullptr)
		{ }
	};

	Node* root;

	// Build tree using heap, O(nlogn)
	void build(const std::vector<int>& symbols, const std::vector<int>& frequency)
	{
		const int n = (int)symbols.size();
		std::vector<Node*> minHeap;
		auto node_compare = [&minHeap](const Node* x, const Node* y) { return x->freq > y->freq; };
		int i{};
		Node* left, *right, *top;
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

	// If data is sorted we can build it with O(n)
	void build_sorted(const std::vector<int>& symbols, const std::vector<int>& frequency)
	{
		const int n = (int)symbols.size();
		std::queue<Node*> q1, q2;
		int i{};
		Node* left, *right, *top;
		for(; i < n; ++i)
			q1.push(new Node(symbols[i], frequency[i]));
	
		while ((int)q1.size() + (int)q2.size() > 1)
		{
			left = extarct_min(q1, q2);
			right = extarct_min(q1, q2);

			top = new Node(0, left->freq + right->freq);
			top->left = left;
			top->right = right;
			q2.push(top);
		}
		root = ((int)q1.size() ? q1.front() : q2.front());
	}

	// Help function to extract minimum from our 2 queues
	static Node* extarct_min(std::queue<Node*>& q1, std::queue<Node*>& q2)
	{
		Node* answ;
		if (!(int)q2.size())
		{
			answ = q1.front();
			q1.pop();
		} else {
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


public:

	// Constructor
	Huffman(const std::vector<int>& symbols, const std::vector<int>& frequency, bool sorted = false)
	{
		sorted && std::is_sorted(frequency.begin(), frequency.end()) ? build_sorted(symbols, frequency) : build(symbols, frequency);
	}

	// return pairs <symbol, code>
	std::vector<std::pair<int, std::string>> get_code()	const
	{
		std::vector<std::pair<int, std::string>> answ;
		Node* curr = root;
		std::string str;
		std::queue<std::pair<Node*, std::string>> q;
		q.push({ curr, "" });
		while (!q.empty())
		{
			std::tie(curr, str) = q.front();
			q.pop();
			if (!curr)
				continue;
			if (curr->data)
				answ.push_back({ curr->data, str });
			q.push({ curr->left, str + "0" });
			q.push({ curr->right, str + "1" });
		}

		return answ;
	}

	// Destructor
	~Huffman()
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

};



class HuffmanDecoder
{
private:

	struct Node 
	{
	public:
		int data;
		Node* left, *right;

		Node(const int data = 0)
			: data(data)
			, left(nullptr)
			, right(nullptr)
		{ }

	};

	// Table with codes for symbols
	std::map<std::string, int> codes;
	// max depth of the tree
	int max_cnt;

	Node* root;

	// We need to build our tree(bcs we want easily decode our messages)
	void build_tree(Node* curr, const int n, const std::string& s)
	{
		if (codes[s])
			curr->data = codes[s];

		if (n < max_cnt) {
			curr->left = new Node();
			curr->right = new Node();

			build_tree(curr->left, n + 1, s + "0");
			build_tree(curr->right, n + 1, s + "1");
		}
	}


public:


	// Get the input file and build table
	HuffmanDecoder(std::ifstream& in)
		: max_cnt(0)
	{
		root = new Node();
		int symbol;
		char colon;
		std::string s;
		while (getline(in, s))
		{
			std::stringstream ss(s);
			ss >> symbol >> colon >> s;
			codes[s] = symbol;
			max_cnt = std::max(max_cnt, (int)s.size());
		}

		build_tree(root, 0, "");
	}


	std::string decode(const std::string& text)	const
	{
		Node* curr = root;
		std::string answ;
		const int n = (int)text.size();
		int i{};

		while (i < n)
		{
			curr = (text[i] == '0' ? curr->left : curr->right);
			if (curr->data)
			{
				answ += curr->data;
				curr = root;
			}
			++i;
		}

		return answ;
	}

	// Destructor
	~HuffmanDecoder()
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
};


std::string& increment(std::string& str)
{
	int index = (int)str.size() - 1;

	while (index >= 0 && str[index] == '1')
	{
		str[index] = '0';
		--index;
	}

	if (index == -1)
		str = '1' + str;
	else str[index] = '1';

	return str;
}

std::pair<std::vector<std::pair<int,int>>, std::vector<std::pair<int, std::string>>> canonical_huffman(const std::vector<std::pair<int, std::string>>& codes)
{
	std::vector<std::pair<int, int>> stoi_codes;
	const int n = (int)codes.size();
	int i{};
	for (; i < n; ++i)
		stoi_codes.push_back({ codes[i].first, (int)codes[i].second.size() });


	std::vector<std::pair<int, std::string>> answ(n);

	std::string current(stoi_codes[0].second, '0');
	answ[0] = { stoi_codes[0].first, current };
	i = 1;

	while (i < n)
	{
		if (stoi_codes[i].second == stoi_codes[i - 1].second)
			answ[i] = { stoi_codes[i].first, increment(current) };
		else
			answ[i] = { stoi_codes[i].first, increment(current) += std::string(stoi_codes[i].second - stoi_codes[i - 1].second, '0') };
		++i;
	}
	// a 2
	// b 3
	// c 3
	// 00
	// 010
	// 011
	std::cout << "ANSW:\n";
	for (auto& it : answ)
		std::cout << it.first << " : " << it.second << '\n';

	return {stoi_codes, answ};
}



class CanonicalHuffmanDecoder
{
private:

	struct Node {
		Node* left, *right;
		int data;
		Node(const int data = 0)
			: data(data)
			, left(nullptr)
			, right(nullptr)
		{ }
	};

	std::map<std::string, int> codes;
	Node* root;
	int max_cnt;


	void build_tree(Node* curr, const int n, const std::string& s)
	{
		if (codes[s])
			curr->data = codes[s];

		if (n < max_cnt) {
			curr->left = new Node();
			curr->right = new Node();

			build_tree(curr->left, n + 1, s + "0");
			build_tree(curr->right, n + 1, s + "1");
		}
	}


	static std::string& increment(std::string& str)
	{
		int index = (int)str.size() - 1;
		
		while (index >= 0 && str[index] == '1')
		{
			str[index] = '0';
			--index;
		}

		if (index == -1)
			str = '1' + str;
		else str[index] = '1';
		
		return str;
	}


	void build_table(const std::vector<std::pair<int, int>>& decode)
	{
		std::string current(decode[0].second, '0');
		codes[current] = decode[0].first;
		int i{1};
		const int n = (int)decode.size();
		while (i < n)
		{
			if (decode[i].second == decode[i - 1].second)
				codes[increment(current)] = decode[i].first;
			else
				codes[increment(current) += std::string(decode[i].second - decode[i - 1].second, '0')] = decode[i].first;
			++i;
		}

		std::cout << "Table:\n";
		for (auto& it : codes)
			std::cout << it.first << " : " << it.second << '\n';
	}


public:

	CanonicalHuffmanDecoder(std::ifstream& in)
	{
		std::vector<std::pair<int, int>> decodes;
		root = new Node();
		int symbol, len;
		std::string s;
		while (getline(in, s))
		{
			std::stringstream ss(s);
			ss >> symbol >> len;
			decodes.push_back({ symbol, len });
		}
		max_cnt = decodes.back().second;

		build_table(decodes);
		build_tree(root, 0, "");
	}


	std::string solve(const std::string& text)
	{
		Node* curr = root;
		std::string answ;
		const int n = (int)text.size();
		int i{};

		while (i < n)
		{
			curr = (text[i] == '0' ? curr->left : curr->right);
			if (curr->data)
			{
				answ += curr->data;
				curr = root;
			}
			++i;
		}

		return answ;
	}


};


// tests 1-3
void tests()
{

	std::ifstream test_input("test1.txt");			// test 1
	std::ofstream test_output("test1_answ.txt");

	//std::ifstream test_input("test2.txt");			// test 2
	//std::ofstream test_output("test2_answ.txt");

	//std::ifstream test_input("test3.txt");			// test 3
	//std::ofstream test_output("test3_answ.txt");

	int cnt; test_input >> cnt;
	std::vector<int> arr;
	std::vector<int> freq;
	int buff; test_input >> buff;
	arr.push_back(1);
	freq.push_back(buff);

	for (int i = 1; i < cnt; ++i)
	{
		arr.push_back(arr[i - 1] + 1);	// In tests we don't have current symbols, so i just use numbers 1, 2, .., n
		test_input >> buff;
		freq.push_back(buff);
	}
	Huffman huffmanTree(arr, freq);

	std::vector<std::pair<int, std::string>> code = huffmanTree.get_code();
	for (auto& [symbol, encode] : code)
		test_output << symbol << " : " << encode << '\n';	// result of the test in the answ.txt

	long double average{};	// let's calculate average length of message by symbol
	long long summary = std::accumulate(freq.begin(), freq.end(), 0ll);

	for (auto& [symbol, encode] : code)
	{
		int index = std::lower_bound(arr.begin(), arr.end(), symbol) - arr.begin();
		average += (long double)encode.size() * freq[index] / summary;
	}
	std::cout << std::fixed << "avg len: " << average << '\n';

	/*
	Difference in average len:
	test1: 3.154696 vs 4  ~ -21%
	test2: 3.668163 vs 4  ~ -8%
	test3: 9.709104 vs 13 ~ -25%
	*/

	test_input.close();
	test_output.close();

}


// Sample test
void baftest()
{
	std::ofstream huffman_out("huffman_decoder.txt");
	std::vector<int> arr = { 'a',	'b',	'c',	'd',	'e',	'f' };
	std::vector<int> freq = { 5,	9,		12,		13,		16,		45 };

	Huffman huffmanTree(arr, freq, true);

	std::vector<std::pair<int, std::string>> code = huffmanTree.get_code();
	for (auto& [symbol, encode] : code)						// write table to huffman_decoder.txt
		huffman_out << symbol << " : " << encode << '\n';

	huffman_out.close();

	std::ifstream huffman_decode("huffman_decoder.txt");	// let's decode message with table
	HuffmanDecoder huffmanDecoder(huffman_decode);

	std::string s = "110111000110111000";	// this is message

	std::string answ = huffmanDecoder.decode(s);	// time to decode!
	std::cout << "decode message:" << answ << '\n';

	huffman_decode.close();
}


// Naive solve test
void naive()
{
	std::ifstream in("input.txt");
	std::ofstream out("output.txt");
	std::stringstream ss; ss << in.rdbuf();

	std::string s;
	s = ss.str();
	std::cout << s << '\n';	// Input text

	NaiveSolve solve(s);
	boost::dynamic_bitset<> answ = solve.solve();
	out << answ; // write encode message to output.txt

	in.close();
	out.close();

	std::ofstream decode_out("decoder.txt");	// Read table with symbols
	std::pair<std::vector<int>, std::vector<boost::dynamic_bitset<>>> decoder = solve.getDecoder();
	const int n = (int)decoder.first.size();
	for (int i = 0; i < n; ++i)
		decode_out << decoder.first[i] << " : " << decoder.second[i] << "\n";
	
	decode_out.close();


	std::ifstream decode_input("decoder.txt");
	std::ifstream text_input("output.txt");		// message with naive encoding
	getline(text_input, s);

	NaiveDecoder decoder_2(decode_input); // let's decode it
	std::string decode_text = decoder_2.decode_text(s);
	std::cout << decode_text;

	decode_input.close();
	text_input.close();

}


void canonical_test()
{
	std::ofstream huffman_out("huffman_decoder.txt");
	std::vector<int> arr = { 'a',	'b',	'c',	'd',	'e',	'f' };
	std::vector<int> freq = { 5,	9,		12,		13,		16,		45 };

	Huffman huffmanTree(arr, freq, true);

	std::vector<std::pair<int, std::string>> code = huffmanTree.get_code();
	std::vector<std::pair<int, std::string>> decode_pairs;
	std::pair<std::vector<std::pair<int,int>>, std::vector<std::pair<int,std::string>>> canon_out = canonical_huffman(code);
	decode_pairs = canon_out.second;


	for (auto& [symbol, encode] : decode_pairs)						// write table to huffman_decoder.txt
		huffman_out << symbol << " : " << encode << '\n';

	huffman_out.close();

	std::ofstream canon_test("canonical_test.txt");
	for (auto& [symbol, encode] : canon_out.first)
		canon_test << symbol << ' ' << encode << '\n';
	canon_test.close();


	std::ifstream input("canonical_test.txt");

	CanonicalHuffmanDecoder canonical_decoder(input);
	std::string s = "111111100111111100";	// this is message
	std::string answ = canonical_decoder.solve(s);
	std::cout << answ;

}


int main()
{

	//tests();
	//baftest();
	//naive();
	canonical_test();

	return  0;
}