#pragma once

#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <numeric>

#include "Huffman.h"
#include "HuffmanDecoder.h"

#include "CanonicalHuffman.h"
#include "CanonicalHuffmanDecoder.h"

#include "NaiveSolve.h"
#include "NaiveDecoder.h"
#include "Timer.h"


template<typename T>
class Tests
{
private:

	std::vector<std::basic_ifstream<T>> test_inputs;
	std::vector<std::basic_ofstream<T>> test_outputs;

	// hello world. this is test text for encoding.

	const std::vector<int> arr = { L' ', L'e', L't', L'o', L'i', L'n', L's', L'h', L'r', L'd', L'l', L'c', L'w', L'f', L'g', L'x', L'.' };

	const std::vector<int> freq = {17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	const std::basic_string<T> message = L"101001000000000111101110001111110010000000111010100110011010111010110111110101101100101010110010110010101101011001011100001111100101101011001101111110001111011001101001101010";
	const std::basic_string<T> canonical_message = L"100100101100110110101011101110110000110011111111100100001001110010100101100101001000000110100000100000011111111000010111001101100001000110111111011010111110010111111101111110";

	void do_test(std::basic_ifstream<T>& in, std::basic_ofstream<T>& out);

	// Sample test
	void huffman_test();

	void canonical_test();

	// Naive solve test
	void naive_test();


public:

	Tests(const std::vector<std::string>& test_inputs, const std::vector<std::string>& test_outputs);

	void do_all_tests();

	~Tests();

};


template<typename T>
Tests<T>::Tests(const std::vector<std::string>& test_inputs, const std::vector<std::string>& test_outputs)
{
	const int n = (int)test_inputs.size();
	int i{};
	for (; i < n; ++i)
	{
		Tests::test_inputs.emplace_back(test_inputs[i].c_str());
		Tests::test_outputs.emplace_back(test_outputs[i].c_str());
	}
}


template<typename T>
void Tests<T>::do_test(std::basic_ifstream<T>& in, std::basic_ofstream<T>& out)
{
	Timer t;

	int cnt; in >> cnt;
	std::vector<int> arr;
	std::vector<int> freq;
	int buff; in >> buff;
	arr.push_back(1);
	freq.push_back(buff);

	for (int i = 1; i < cnt; ++i)
	{
		arr.push_back(arr[i - 1] + 1);	// In tests we don't have current symbols, so i just use numbers 1, 2, .., n
		in >> buff;
		freq.push_back(buff);
	}
	Huffman huffmanTree(arr, freq);

	out << "Time:" << std::fixed << t.elapsed() << '\n';
	std::vector<std::pair<int, std::basic_string<T>>> code = huffmanTree.get_code<T>();


	long double average{};	// let's calculate average length of message by symbol
	long long summary = std::accumulate(freq.begin(), freq.end(), 0ll);

	for (auto& [symbol, encode] : code)
	{
		int index = std::lower_bound(arr.begin(), arr.end(), symbol) - arr.begin();
		average += (long double)encode.size() * freq[index] / summary;
	}
	out << std::fixed << "avg len: " << average << '\n';

	for (auto& [symbol, encode] : code)
		out << symbol << "\t:\t" << encode << '\n';	// result of the test in the answ.txt
}


template<typename T>
void Tests<T>::huffman_test()
{
	std::basic_ofstream<T> huffman_out("test/huffman_decoder.txt");
	Huffman huffmanTree(arr, freq, true);

	std::vector<std::pair<int, std::basic_string<T>>> code = huffmanTree.get_code<T>();
	for (auto& [symbol, encode] : code)
		huffman_out << symbol << " : " << encode << '\n';

	huffman_out.close();
	std::wcout << message << '\n';

	std::basic_ifstream<T> huffman_decode("test/huffman_decoder.txt");
	HuffmanDecoder<T> huffmanDecoder(huffman_decode);

	std::basic_string<T> answ = huffmanDecoder.decode(message);
	std::wcout << "decode message:" << answ << '\n';

	huffman_decode.close();
}


template<typename T>
void Tests<T>::canonical_test()
{
	std::wcout << canonical_message << '\n';
	std::basic_ofstream<T> huffman_out("test/huffman_decoder.txt");
	Huffman huffmanTree(arr, freq, true);

	std::vector<std::pair<int, std::basic_string<T>>> code = huffmanTree.get_code<T>();
	std::vector<std::pair<int, std::basic_string<T>>> decode_pairs;

	CanonicalHuffman<T> canonical_huffman(code);
	std::pair<std::vector<std::pair<int, int>>, std::vector<std::pair<int, std::basic_string<T>>>> canon_out = canonical_huffman.solve();
	decode_pairs = canon_out.second;


	for (auto& [symbol, encode] : decode_pairs)
		huffman_out << symbol << " : " << encode << '\n';

	huffman_out.close();

	std::basic_ofstream<T> canon_test("test/canonical_test.txt");
	for (auto& [symbol, encode] : canon_out.first)
		canon_test << symbol << ' ' << encode << '\n';
	canon_test.close();
	for (auto& [symbol, encode] : canon_out.second)
		std::wcout << symbol << ":" << encode << '\n';

	std::basic_ifstream<T> input("test/canonical_test.txt");

	CanonicalHuffmanDecoder<T> canonical_decoder(input);
	std::basic_string<T> answ = canonical_decoder.solve(canonical_message);
	std::wcout << answ;
}


template<typename T>
void Tests<T>::naive_test()
{
	std::basic_ifstream<T> in("test/input.txt");
	std::basic_ofstream<T> out("test/output.txt");
	std::basic_stringstream<T> ss; ss << in.rdbuf();

	std::basic_string<T> s;
	s = ss.str();
	std::wcout << s << '\n';

	NaiveSolve<T> solve(s);
	std::wstring answ = solve.solve();
	out << answ;

	in.close();
	out.close();

	std::basic_ofstream<T> decode_out("test/decoder.txt");
	std::pair<std::vector<int>, std::vector<std::wstring>> decoder = solve.getDecoder();
	const int n = (int)decoder.first.size();
	for (int i = 0; i < n; ++i)
		decode_out << decoder.first[i] << " : " << decoder.second[i] << "\n";

	decode_out.close();

	std::basic_ifstream<T> decode_input("test/decoder.txt");
	std::basic_ifstream<T> text_input("test/output.txt");

	std::getline(text_input, s);

	NaiveDecoder<T> decoder_2(decode_input);
	std::basic_string<T> decode_text = decoder_2.decode_text(s);
	std::wcout << decode_text;

	decode_input.close();
	text_input.close();
}


template<typename T>
void Tests<T>::do_all_tests()
{
	std::wcout << L"input message:hello world. this is test text for encoding.\n";
	naive_test();
	//huffman_test();

	const int n = (int)test_inputs.size();
	int i{};
	for (; i < n; ++i)
		do_test(test_inputs[i], test_outputs[i]);

	//canonical_test();
}


template<typename T>
Tests<T>::~Tests()
{
	const int n = (int)test_inputs.size();
	int i{};
	for (; i < n; ++i)
	{
		test_inputs[i].close();
		test_outputs[i].close();
	}
}
