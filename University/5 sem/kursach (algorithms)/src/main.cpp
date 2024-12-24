#define _SILENCE_ALL_CXX17_DEPRECATION_WARNINGS

#include "Tests.h"
#include <chrono>
#include <iostream>
#include <string>


#include "Huffman.h"
#include "HuffmanDecoder.h"
#include "Timer.h"


#include <sstream>
#include <fstream>
#include <codecvt>
#include <memory> // for std::unique_ptr


std::wstring readFile(const std::string& filename)
{
	std::wifstream wif(filename);
	wif.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
	std::wstringstream wss;
	wss << wif.rdbuf();
	return wss.str();
}


void war_and_peace_huffman_encode(const std::string& filename)
{
	Timer t;

	std::unique_ptr<Timer> t_read = std::make_unique<Timer>();

	std::wstring text = readFile(filename);
	std::wofstream out("test/huffman/war_and_peace_codes.txt");
	out.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
	std::cout << "Read huffman encoding time: " << t_read->elapsed() << '\n';
	t_read.reset(); // Run destructor
	
	std::unique_ptr<Timer> t_prebuild = std::make_unique<Timer>();
	
	// get freq
	std::map<wchar_t, int> mp;
	std::vector<int> symb, freq;
	for (auto& it : text)
		mp[it]++;

	for (auto& [key, val] : mp)
	{
		symb.push_back(key);
		freq.push_back(val);
	}
	std::cout << "Prebuild huffman encoding time: " << t_prebuild->elapsed() << '\n';
	t_prebuild.reset();

	std::unique_ptr<Timer> t_build = std::make_unique<Timer>();
	// Build Huffman
	Huffman huffman_tree(symb, freq);
	std::cout << "Build huffman encoding time: " << t_build->elapsed() << '\n';
	t_build.reset();

	std::unique_ptr<Timer> t_out = std::make_unique<Timer>();
	std::vector<std::pair<int, std::wstring>> code = huffman_tree.get_code<wchar_t>();

	std::map<int, std::wstring> codes(code.begin(), code.end());
	for (auto& [symb, str] : code)
		out << symb << L": " << str << L'\n';

	out.close();
	std::cout << "Out huffman encoding time: " << t_out->elapsed() << '\n';
	t_out.reset();

	// Try to encode with the table
	std::wofstream encode_message("test/huffman/war_and_peace_encode.txt");
	out.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));

	std::unique_ptr<Timer> t_encode = std::make_unique<Timer>();

	for (auto& it : text)
		encode_message << codes[it];
	std::cout << "Encode huffman encoding time: " << t_encode->elapsed() << '\n';
	out.close();
	std::cout << "Full Encoding time: " << t.elapsed() << '\n';

	long double average{};	// let's calculate average length of message by symbol
	long long summary = std::accumulate(freq.begin(), freq.end(), 0ll);

	for (auto& [symbol, encode] : code)
	{
		int index = std::lower_bound(symb.begin(), symb.end(), symbol) - symb.begin();
		average += (long double)encode.size() * freq[index] / summary;
	}
	std::cout << std::fixed << "avg len: " << average << '\n';
}


void war_and_peace_huffman_decode()
{
	Timer t;
	
	std::unique_ptr<Timer> t_read = std::make_unique<Timer>();

	std::string filename = "test/huffman/war_and_peace_encode.txt";
	std::wstring text = readFile(filename);
	std::wifstream in("test/huffman/war_and_peace_codes.txt");
	in.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
	std::cout << "Read huffman decoding time: " << t_read->elapsed() << '\n';
	t_read.reset();

	std::unique_ptr<Timer> t_build = std::make_unique<Timer>();
	HuffmanDecoder<wchar_t> huffman_decoder(in);
	std::cout << "Build huffman decoding time: " << t_build->elapsed() << '\n';
	t_build.reset();

	in.close();

	std::wofstream out("test/huffman/war_and_peace_decode.txt");
	out.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));

	std::unique_ptr<Timer> t_decode = std::make_unique<Timer>();
	std::wstring total = huffman_decoder.decode(text);
	std::cout << "Decode huffman decoding time: " << t_decode->elapsed() << '\n';

	out << total;
	out.close();

	std::cout << "Full huffman decoding time: " << t.elapsed() << '\n';
}


void war_and_peace_naive_encode(const std::string& filename)
{
	Timer t;

	std::unique_ptr<Timer> t_read = std::make_unique<Timer>();

	std::wstring text = readFile(filename);
	std::wofstream out("test/naive/war_and_peace_codes.txt");
	out.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
	std::cout << "Read naive encoding time: " << t_read->elapsed() << '\n';
	t_read.reset(); // Run destructor

	std::unique_ptr<Timer> t_build = std::make_unique<Timer>();
	// Build Naive
	NaiveSolve<wchar_t> naive_solve(text);
	std::cout << "Build naive encoding time: " << t_build->elapsed() << '\n';
	t_build.reset(); // Run desctructor

	std::unique_ptr<Timer> t_solve = std::make_unique<Timer>();
	std::wstring answ = naive_solve.solve();
	std::cout << "Solve naive encoding time: " << t_solve->elapsed() << '\n';
	t_solve.reset(); // Run destructor

	std::unique_ptr<Timer> t_out = std::make_unique<Timer>();
	std::pair<std::vector<int>, std::vector<std::wstring>> code = naive_solve.getDecoder();
	std::vector<int> symbols = code.first;
	std::vector<std::wstring> encodes = code.second;
	
	const int n = (int)symbols.size();
	std::map<int, std::wstring> codes;
	int i{};
	for (; i < n; ++i)
		codes[symbols[i]] = encodes[i];

	for (auto& [symb, str] : codes)
		out << symb << L": " << str << L'\n';

	out.close();
	std::cout << "Out naive encoding time: " << t_out->elapsed() << '\n';
	t_out.reset(); // Run destructor
	

	// Try to encode with the table
	std::wofstream encode_message("test/naive/war_and_peace_encode.txt");
	out.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));

	std::unique_ptr<Timer> t_encode = std::make_unique<Timer>();
	encode_message << answ;
	std::cout << "Encode naive encoding time: " << t_encode->elapsed() << '\n';

	out.close();

	std::cout << "Full naive encoding time: " << t.elapsed() << '\n';

	// get freq
	std::map<wchar_t, int> mp;
	for (auto& it : text)
		mp[it]++;

	long double average_len = 0.0l;
	long long summary = 0;
	for (auto& [key, val] : mp)
		summary += val;

	for (auto& [key, val] : codes)
		average_len += (long double)val.size() * mp[key] / summary;
	std::cout << std::fixed << "avg len: " << average_len << '\n';
}


void war_and_peace_naive_decode()
{
	Timer t;

	std::unique_ptr<Timer> t_read = std::make_unique<Timer>();

	std::string filename = "test/naive/war_and_peace_encode.txt";
	std::wstring text = readFile(filename);
	std::wifstream in("test/naive/war_and_peace_codes.txt");
	in.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
	std::cout << "Read naive decoding: " << t_read->elapsed() << '\n';
	t_read.reset(); // Run destructor

	std::unique_ptr<Timer> t_build = std::make_unique<Timer>();
	NaiveDecoder<wchar_t> huffman_decoder(in);
	std::cout << "Build naive decoding: " << t_build->elapsed() << '\n';
	t_build.reset(); // Run destructor
	in.close();

	std::wofstream out("test/naive/war_and_peace_decode.txt");
	out.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
	
	std::unique_ptr<Timer> t_solve = std::make_unique<Timer>();
	std::wstring total = huffman_decoder.decode_text(text);
	std::cout << "Solve naive decoding: " << t_solve->elapsed() << '\n';
	t_solve.reset(); // Run destructor
	
	std::unique_ptr<Timer> t_out = std::make_unique<Timer>();
	out << total;
	out.close();
	std::cout << "Out naive decoding: " << t_out->elapsed() << '\n';
	t_out.reset(); // Run destructor

	std::cout << "Full naive decoding time: " << t.elapsed() << '\n';
}


void war_and_peace_canonical_encode(const std::string& filename)
{
	std::wstring text = readFile(filename);
	std::wofstream out("test/canonical/war_and_peace_codes.txt");
	out.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));

	Timer t;
	// get freq
	std::map<wchar_t, int> mp;
	std::vector<int> symb, freq;
	for (auto& it : text)
		mp[it]++;

	for (auto& [key, val] : mp)
	{
		symb.push_back(key);
		freq.push_back(val);
	}

	// Build Huffman
	Huffman huffman_tree(symb, freq);
	std::vector<std::pair<int, std::wstring>> code = huffman_tree.get_code<wchar_t>();

	CanonicalHuffman canonical_huffman(code);
	std::pair<std::vector<std::pair<int, int>>, std::vector<std::pair<int, std::wstring>>> canon_out = canonical_huffman.solve();
	std::vector<std::pair<int, int>> codes = canon_out.first;
	std::vector<std::pair<int, std::wstring>>& canon_out_sec = canon_out.second;

	std::map<int, std::wstring> str_codes(canon_out_sec.begin(), canon_out_sec.end());


	for (auto& [symb, code] : codes)
		out << symb << " " << code << '\n';

	out.close();

	// Try to encode with the table
	std::wofstream encode_message("test/canonical/war_and_peace_encode.txt");
	out.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
	for (auto& it : text)
		encode_message << str_codes[it];

	out.close();

	std::cout << "Encoding time: " << t.elapsed() << '\n';
}


void war_and_peace_canonical_decode()
{
	Timer t;
	
	std::string filename = "test/canonical/war_and_peace_encode.txt";
	std::wstring text = readFile(filename);
	std::wifstream in("test/canonical/war_and_peace_codes.txt");
	in.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));

	CanonicalHuffmanDecoder<wchar_t> canonical_huffman_decoder(in);
	in.close();

	std::wofstream out("test/canonical/war_and_peace_decode.txt");
	out.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
	std::wstring total = canonical_huffman_decoder.solve(text);
	out << total;
	out.close();

	std::cout << "Full canonical decoding time: " << t.elapsed() << '\n';
}


void check_similarity(const std::string& filename1, const std::string& filename2)
{
	std::wstring text1 = readFile(filename1);
	std::wstring text2 = readFile(filename2);
	// Проверим что исходное сообщение совпдает с декодированным сообщением

	if (text1 == text2)
		std::cout << "SIMILAR\n";
	else
		std::cout << "NO SIMILAR\n";
}

void fixed_war_and_peace_huffman_encode()
{
	Timer t;

	std::unique_ptr<Timer> t_read = std::make_unique<Timer>();

	std::wstring text = readFile("test/fixed_war_and_peace.txt");
	std::wofstream out("test/huffman/fixed_war_and_peace_codes.txt");
	out.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
	std::cout << "Read huffman encoding time: " << t_read->elapsed() << '\n';
	t_read.reset(); // Run destructor

	std::unique_ptr<Timer> t_prebuild = std::make_unique<Timer>();

	// get freq
	std::map<wchar_t, int> mp;
	for (auto& it : text)
		mp[it]++;

	std::vector<int> symb = { 32,1086,1077,1072,1080,1090,1085,1089,1088,1074,1083,1082,
		1084,1076,1087,1091,1103,1099,1100,1075,1079,46,44,1073,1095,1081,1054,1093,10,
		1078,1045,1040,1096,1048,1058,1102,1053,1057,1094,1056,1042,1051,1097,1050,1052,
		1101,33,63,1044,1055,1059,1092,1071,59,58,1067,1068,1043,1047,1041,1063,1049,
		1061,45,8212,40,41,91,93,123,125,171,187,39,34,1046,1064,1070,8230,1062,
		1098,1065,1069,1060,1105,1066,1025 };

	std::vector<int> freq = { 100,99,98,97,96,95,94,93,92,91,90,89,88,87,86,85,84,83,82,
		81,80,79,78,77,76,75,74,73,72,71,70,69,68,67,66,65,64,63,62,61,60,59,58,57,56,
		55,54,53,52,51,50,49,48,47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,
		29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14 };


	std::cout << "Prebuild huffman encoding time: " << t_prebuild->elapsed() << '\n';
	t_prebuild.reset();

	std::unique_ptr<Timer> t_build = std::make_unique<Timer>();
	// Build Huffman
	Huffman huffman_tree(symb, freq);
	std::cout << "Build huffman encoding time: " << t_build->elapsed() << '\n';
	t_build.reset();

	std::unique_ptr<Timer> t_out = std::make_unique<Timer>();
	std::vector<std::pair<int, std::wstring>> code = huffman_tree.get_code<wchar_t>();

	std::map<int, std::wstring> codes(code.begin(), code.end());
	for (auto& [symb, str] : code)
		out << symb << L": " << str << L'\n';

	out.close();
	std::cout << "Out huffman encoding time: " << t_out->elapsed() << '\n';
	t_out.reset();

	// Try to encode with the table
	std::wofstream encode_message("test/huffman/fixed_war_and_peace_encode.txt");
	out.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));

	std::unique_ptr<Timer> t_encode = std::make_unique<Timer>();

	for (auto& it : text)
		encode_message << codes[it];
	std::cout << "Encode huffman encoding time: " << t_encode->elapsed() << '\n';
	out.close();
	std::cout << "Full Encoding time: " << t.elapsed() << '\n';

	long double average_len = 0.0l;
	long long summary = 0;
	for (auto& [key, val] : mp)
		summary += val;

	for (auto& [key, val] : codes)
		average_len += (long double)val.size() * mp[key] / summary;
	std::cout << std::fixed << "avg len: " << average_len << '\n';
}

void fixed_war_and_peace_huffman_decode()
{
	Timer t;

	std::unique_ptr<Timer> t_read = std::make_unique<Timer>();

	std::string filename = "test/huffman/fixed_war_and_peace_encode.txt";
	std::wstring text = readFile(filename);
	std::wifstream in("test/huffman/fixed_war_and_peace_codes.txt");
	in.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
	std::cout << "Read huffman decoding time: " << t_read->elapsed() << '\n';
	t_read.reset();

	std::unique_ptr<Timer> t_build = std::make_unique<Timer>();
	HuffmanDecoder<wchar_t> huffman_decoder(in);
	std::cout << "Build huffman decoding time: " << t_build->elapsed() << '\n';
	t_build.reset();

	in.close();

	std::wofstream out("test/huffman/fixed_war_and_peace_decode.txt");
	out.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));

	std::unique_ptr<Timer> t_decode = std::make_unique<Timer>();
	std::wstring total = huffman_decoder.decode(text);
	std::cout << "Decode huffman decoding time: " << t_decode->elapsed() << '\n';

	out << total;
	out.close();

	std::cout << "Full huffman decoding time: " << t.elapsed() << '\n';
}


void fixed_war_and_peace_naive_encode()
{
	Timer t;
	
	std::unique_ptr<Timer> t_read = std::make_unique<Timer>();
	
	std::string filename("test/fixed_war_and_peace.txt");
	std::wstring text = readFile(filename);
	std::wofstream out("test/naive/fixed_war_and_peace_codes.txt");
	out.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
	std::cout << "Read naive encoding time: " << t_read->elapsed() << '\n';
	t_read.reset(); // Run destructor


	// get freq
	std::map<wchar_t, int> mp;
	for (auto& it : text)
		mp[it]++;

	std::unique_ptr<Timer> t_build = std::make_unique<Timer>();
	// Build Naive
	NaiveSolve<wchar_t> naive_solve(text);
	std::cout << "Build naive encoding time: " << t_build->elapsed() << '\n';
	t_build.reset(); // Run desctructor

	std::unique_ptr<Timer> t_solve = std::make_unique<Timer>();
	std::wstring answ = naive_solve.solve();
	std::cout << "Solve naive encoding time: " << t_solve->elapsed() << '\n';
	t_solve.reset(); // Run destructor

	std::unique_ptr<Timer> t_out = std::make_unique<Timer>();
	std::pair<std::vector<int>, std::vector<std::wstring>> code = naive_solve.getDecoder();
	std::vector<int> symbols = code.first;
	std::vector<std::wstring> encodes = code.second;

	const int n = (int)symbols.size();
	std::map<int, std::wstring> codes;
	int i{};
	for (; i < n; ++i)
		codes[symbols[i]] = encodes[i];

	for (auto& [symb, str] : codes)
		out << symb << L": " << str << L'\n';

	out.close();
	std::cout << "Out naive encoding time: " << t_out->elapsed() << '\n';
	t_out.reset(); // Run destructor


	// Try to encode with the table
	std::wofstream encode_message("test/naive/fixed_war_and_peace_encode.txt");
	out.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));

	std::unique_ptr<Timer> t_encode = std::make_unique<Timer>();
	encode_message << answ;
	std::cout << "Encode naive encoding time: " << t_encode->elapsed() << '\n';

	out.close();

	std::cout << "Full naive encoding time: " << t.elapsed() << '\n';

	long double average_len = 0.0l;
	long long summary = 0;
	for (auto& [key, val] : mp)
		summary += val;

	for (auto& [key, val] : codes)
		average_len += (long double)val.size() * mp[key] / summary;
	std::cout << std::fixed << "avg len: " << average_len << '\n';
}


void fixed_war_and_peace_naive_decode()
{
	Timer t;

	std::unique_ptr<Timer> t_read = std::make_unique<Timer>();

	std::string filename = "test/naive/fixed_war_and_peace_encode.txt";
	std::wstring text = readFile(filename);
	std::wifstream in("test/naive/fixed_war_and_peace_codes.txt");
	in.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
	std::cout << "Read naive decoding: " << t_read->elapsed() << '\n';
	t_read.reset(); // Run destructor

	std::unique_ptr<Timer> t_build = std::make_unique<Timer>();
	NaiveDecoder<wchar_t> huffman_decoder(in);
	std::cout << "Build naive decoding: " << t_build->elapsed() << '\n';
	t_build.reset(); // Run destructor
	in.close();

	std::wofstream out("test/naive/fixed_war_and_peace_decode.txt");
	out.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));

	std::unique_ptr<Timer> t_solve = std::make_unique<Timer>();
	std::wstring total = huffman_decoder.decode_text(text);
	std::cout << "Solve naive decoding: " << t_solve->elapsed() << '\n';
	t_solve.reset(); // Run destructor 

	std::unique_ptr<Timer> t_out = std::make_unique<Timer>();
	out << total;
	out.close();
	std::cout << "Out naive decoding: " << t_out->elapsed() << '\n';
	t_out.reset(); // Run destructor

	std::cout << "Full naive decoding time: " << t.elapsed() << '\n';
}


int main()
{
	std::cin.tie(0);
	std::ios_base::sync_with_stdio(false);

	std::vector<std::string> test_inputs = { "test/test1.txt", "test/test2.txt", "test/test3.txt" };
	std::vector<std::string> test_outputs = { "test/test1_answ.txt", "test/test2_answ.txt", "test/test3_answ.txt" };

	Tests<wchar_t> tests(test_inputs, test_outputs);
	tests.do_all_tests();

	int32_t t{ 5 };
	std::string filename = "test/war_and_peace.txt";

	if (t == 1) {
		war_and_peace_huffman_encode(filename);
		war_and_peace_huffman_decode();
		check_similarity(filename, "test/huffman/war_and_peace_decode.txt");
	}
	else if (t == 2)
	{
		war_and_peace_naive_encode(filename);
		war_and_peace_naive_decode();
		check_similarity(filename, "test/naive/war_and_peace_decode.txt");
	}
	else if (t == 3)
	{
		war_and_peace_canonical_encode(filename);
		war_and_peace_canonical_decode();
		check_similarity(filename, "test/canonical/war_and_peace_decode.txt");
	}
	else if (t == 4)
	{
		fixed_war_and_peace_huffman_encode();
		fixed_war_and_peace_huffman_decode();
		check_similarity("test/fixed_war_and_peace.txt", "test/huffman/fixed_war_and_peace_decode.txt");
	}
	else if (t == 5)
	{
		fixed_war_and_peace_naive_encode();
		fixed_war_and_peace_naive_decode();
		check_similarity("test/fixed_war_and_peace.txt", "test/naive/fixed_war_and_peace_decode.txt");
	}

	return  0;
}
