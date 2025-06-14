#include <judypp/judypp.hpp>

#include <iostream>
#include <cassert>
#include <vector>
#include <forward_list>
#include <list>
#include <initializer_list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <deque>
#include <array>
#include <stack>
#include <memory>
#include <utility>
#include <algorithm>
#include <numeric>


void judy1_test()
{
//*******************************CONTAINERS*************************************//

    std::vector<int> vec1 = {1, 2, 3};
    std::vector<int> vec2 = {100, 200, 300 ,400};

    std::set<int16_t> s1 = {23, 33, 32, 3};
    std::set<int16_t> s2 = {10, 20, 30};

    std::map<Word_t, Word_t> mp1 = {{1, 10}, {2, 100}, {3, 1000}};
    std::map<int, int> mp2 = {{2000, 1}, {2001, 2}, {20002, 3} };

    std::array<long long, 3> arr1 = {10000000000, 100000000000, 1000000000000};
    std::array<long long, 3> arr2 = {11111111, 22222222, 33333333};

    std::list<int8_t> lst1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::list<int8_t> lst2 = {11, 12, 13, 14, 15, 16, 17, 18, 19, 20};

    std::deque<unsigned char> deq1 = {100, 200};
    std::deque<unsigned char> deq2 = {0, 0, 1, 2, 3};

    std::forward_list<char32_t> flst1 = {1, 2, 3, 10};
    std::forward_list<char32_t> flst2 = {2, 2, 2, 2, 2};

    std::multiset<int> ms1 = {-2, -2, -1, 0, 1, 2};
    std::multiset<int> ms2 = {10};

    std::unordered_set<intmax_t> us1 = {-1, 200, -2};
    std::unordered_set<intmax_t> us2 = {-10000, -1233425234, 134213413}; 

    std::unordered_multiset<uintmax_t> ums1 = {10, 120, 10, 10, 120};
    std::unordered_multiset<uintmax_t> ums2 = {1, 2, 2, 1, 3, 4, 5, 6, 5, 4 };

    std::priority_queue<std::size_t> pq1; for(auto it : {0, 1, 2, 3, 2}) pq1.push(it);
    std::priority_queue<std::size_t> pq2; for(auto it : {12930, 213123, 213123, 213}) pq2.push(it);

    std::queue<bool> q1; for(auto it : {1, 0, 0, 2, 3}) q1.push(it);
    std::queue<bool> q2; for(auto it : {0, 10}) q2.push(it);

    std::stack<signed char> st1; for(auto it : {1, 2, 3}) s1.insert(it);
    std::stack<signed char> st2; for(auto it : {0}) s2.insert(it);

    std::string str1 = "Hello";
    std::string str2 = ", World!\n";

    std::wstring wstr1 = L"окак";
    std::wstring wstr2 = L"привет";

    std::bitset<32> bits1 = 10;
    std::bitset<100> bits2; bits2[10] = bits2[20] = 10;


//*********************************JUDY 1***************************************//
    std::cout << "=========== JUDY 1 TESTS ===========" << std::endl;

std::cout<< std::endl << "\t=== CONSTRUCTOR TESTS ===" << std::endl;

// Базовый конструктор
std::cout<< "Basic constructor: ";

    judy::Judy1 j1;
    judy::Judy1 j1_1{};
    
    assert(j1.size() == j1_1.size() && j1.size() == 0);
    assert(j1.empty() && j1_1.empty());
    assert(j1[1] == j1[2] && j1[1] == 0);

    judy::Judy1* pj1_2 = new judy::Judy1();
    judy::Judy1* pj1_3 = new judy::Judy1;

    assert(pj1_2->size() == pj1_3->size() && pj1_2->size() == 0);
    assert(pj1_2->empty() && pj1_3->empty());
    assert((*pj1_2)[1] == (*pj1_2)[2] && (*pj1_2)[1] == 0);

    delete pj1_2;
    delete pj1_3;

    std::unique_ptr<judy::Judy1> pj1_4 = std::make_unique<judy::Judy1>();
    assert(pj1_4->size() == 0);
    
    std::cout << "PASSED" << std::endl;

// Конструктор для контейнеров с value_type = is_integral
std::cout << "container<integral> constructors: ";

    // std::vector
    judy::Judy1 j2(vec1);
    judy::Judy1 j2_1(vec2);

    for(auto val : vec1) assert(j2[val]);
    for(auto val : vec2) assert(j2_1[val]);

    // std::set
    judy::Judy1 j2_2(s1);
    judy::Judy1 j2_3(s2);

    for(auto val : s1) assert(j2_2[val]);
    for(auto val : s2) assert(j2_3[val]);

    // std::array
    judy::Judy1 j2_4(arr1);
    judy::Judy1 j2_5(arr2);

    for(auto val : arr1) assert(j2_4[val]);
    for(auto val : arr2) assert(j2_5[val]);

    // std::list
    judy::Judy1 j2_6(lst1);
    judy::Judy1 j2_7(lst2);

    for(auto val : lst1) assert(j2_6[val]);
    for(auto val : lst2) assert(j2_7[val]);

    // std::deque
    judy::Judy1 j2_8(deq1);
    judy::Judy1 j2_9(deq2);

    for(auto val : deq1) assert(j2_8[val]);
    for(auto val : deq2) assert(j2_9[val]);

    // std::forward_list
    judy::Judy1 j2_10(flst1);
    judy::Judy1 j2_11(flst2);

    for(auto val : flst1) assert(j2_10[val]);
    for(auto val : flst2) assert(j2_11[val]);

    // std::multiset
    judy::Judy1 j2_12(ms1);
    judy::Judy1 j2_13(ms2);

    for(auto val : ms1) assert(j2_12[val]);
    for(auto val : ms2) assert(j2_13[val]);

    // std::unordered_set
    judy::Judy1 j2_14(us1);
    judy::Judy1 j2_15(us2);

    for(auto val : us1) assert(j2_14[val]);
    for(auto val : us2) assert(j2_15[val]);
    
    // std::unordered_multiset
    judy::Judy1 j2_16(ums1);
    judy::Judy1 j2_17(ums2);

    for(auto val : ums1) assert(j2_16[val]);
    for(auto val : ums2) assert(j2_17[val]);

    judy::Judy1 j2_18(str1);
    judy::Judy1 j2_19(str2);

    for(auto val : str1) assert(j2_18[val]);
    for(auto val : str2) assert(j2_19[val]);
    
    // std::wstring
    judy::Judy1 j2_20(wstr1);
    judy::Judy1 j2_21(wstr2);

    for(auto val : wstr1)assert(j2_20[val]);
    for(auto val : wstr2) assert(j2_21[val]);

    std::cout << "PASSED" << std::endl;

// Конструктор для списка инициализации
std::cout << "initializer_list constructor: ";

    judy::Judy1 j3_1 = {};
    judy::Judy1 j3_2 = {1, 2, 3, 2, 5};

    assert(j3_1.size() == 0);
    for(auto val : {1, 2, 3, 2, 5})
        assert(j3_2[val]);

    std::cout << "PASSED" << std::endl;

// Конструктор для std::bitset<Nb>
std::cout << "std::bitset<Nb> constructor: ";

    judy::Judy1 j4_1(bits1);
    judy::Judy1 j4_2(bits2);

    for(int i = 0; i < 32; ++i) assert(bits1[i] == j4_1[i]);
    
    for(int i = 0; i < 100; ++i) assert(bits2[i] == j4_2[i]);

    std::cout << "PASSED" << std::endl;

// Конструктор копирования
std::cout << "copy constructor: ";

    judy::Judy1 j5_1(j4_1);
    assert(j5_1 == j4_1);

    judy::Judy1 j5_2(judy::Judy1{1, 2, 3});
    for(auto val : {1, 2, 3}) assert(j5_2[val]);

    std::cout << "PASSED" << std::endl;

// нужно ещё конструктор перемещения

// Оператор =
std::cout << "oprtator= : ";
    
    judy::Judy1 j6_1 = j5_1;
    assert(j6_1 == j5_1);

    std::cout << "PASSED" << std::endl;

// нужно ещё оператор = move

std::cout << "\t=== CONSTRUCTOR TESTS ENDED ===" << std::endl;


std::cout<< std::endl << "\t=== CONTAINER FUNCS TESTS ===" << std::endl;

// size()
std::cout << "size() func: ";

    for(auto sz : {1, 10, 100, 1000, 10000, 100000})
    {
        std::vector<int> vec(sz);
        std::iota(vec.begin(), vec.end(), 1);
        judy::Judy1 j7_1(vec);
        judy::Judy1 j7_2;

        for(int i = 1;i <= sz; ++i)
            j7_2[i] = 1;

        assert(j7_1.size() == sz);
        assert(j7_2.size() == sz);
    }

    std::cout << "PASSED" << std::endl;

// clear()
std::cout << "clear() func: ";

    j6_1.clear(); j5_1.clear();
    j4_1.clear(); j4_2.clear();

    assert(j6_1.size() == 0);
    assert(j5_1.size() == 0);
    assert(j4_1.size() == 0);
    assert(j4_2.size() == 0);

    std::cout << "PASSED" << std::endl;

// empty()
std::cout << "empty() func: ";

    assert(j5_1.empty() == true);
    assert(j3_2.empty() == false);

    std::cout << "PASSED" << std::endl;

// swap()
std::cout << "swap() func: ";

    judy::Judy1 j8_1 = j3_1;
    judy::Judy1 j8_2 = j3_2;
    j8_1.swap(j8_2);
    assert(j8_1 == j3_2 && j8_2 == j3_1);

    std::cout << "PASSED" << std::endl;

// count()
std::cout << "count() func: ";

    for(auto [key,val] : j3_2)
        assert(j3_2.count(key));
    
    std::cout << "PASSED" << std::endl;

// contains()
std::cout << "contains() func: ";

    for(auto [key, val] : j3_2)
        assert(j3_2.contains(key) == true);

    std::cout << "PASSED" << std::endl;

// set_debug_mode()
std::cout << "set_debug_mode() func: ";

    judy::Judy1::set_debug_mode(true);
    {
        judy::Judy1 j9_1;
    }
    judy::Judy1::set_debug_mode(false);
    {
        judy::Judy1 j9_2;
    }

    std::cout << "PASSED" << std::endl;

std::cout<< "\t=== CONTAINER FUNCS TESTS ENDED ===" << std::endl;

std::cout<< std::endl << "\t=== JUDY MACRO FUNCS TESTS ===" << std::endl;

// set()
std::cout << "set() : ";

    judy::Judy1 j10_1;
    std::initializer_list<int> init_list1 = {10, 100, 20, 30, 40, 22, 15, 21, 23};
    for(auto it : init_list1) j10_1.set(it);
    for(auto it : init_list1) assert(j10_1[it]);

    std::cout << "PASSED" << std::endl;

// unset()
std::cout << "unset() : ";

    for(auto it : init_list1) j10_1.unset(it);
    for(auto it : init_list1) assert(j10_1[it] == 0);

    std::cout << "PASSED" << std::endl;

// test()
std::cout << "test() : ";

    j10_1.clear(); for(auto it : init_list1) j10_1.set(it);
    for(auto it : init_list1) assert(j10_1.test(it));

    std::cout << "PASSED" << std::endl;

// count()
std::cout << "count() : ";

    assert(j10_1.count(0, -1) == 9);
    assert(j10_1.count(10, 10) == 1);
    assert(j10_1.count(1,1) == 0);
    assert(j10_1.count(10, 22) == 5);

    std::cout << "PASSED" << std::endl;

// ncount()
std::cout << "ncount() : ";

    assert(j10_1.ncount(2).value() == 15);
    assert(j10_1.ncount(1).value() == 10);
    assert(j10_1.ncount(100) == std::nullopt);

    std::cout << "PASSED" << std::endl;

// memused()
std::cout << "memused() : ";

    assert(j10_1.memused() != 0);
    j10_1.clear();
    assert(j10_1.memused() == 0);

    std::cout << "PASSED" << std::endl;

// first()
std::cout << "first() : ";

    for(auto it : init_list1) j10_1.set(it);
    assert(j10_1.first(0).value() == 10);
    assert(j10_1.first(10000) == std::nullopt);
    assert(j10_1.first(11).value() == 15);

    std::cout << "PASSED" << std::endl;

// next()
std::cout << "next() : ";

    assert(j10_1.next(10).value() == 15);
    assert(j10_1.next(10000) == std::nullopt);
    assert(j10_1.next(11).value() == 15);
    
    std::cout << "PASSED" << std::endl;

// last()
std::cout << "last() : ";

    assert(j10_1.last(10).value() == 10);
    assert(j10_1.last(9) == std::nullopt);
    assert(j10_1.last(11).value() == 10);

    std::cout << "PASSED" << std::endl;

// prev()
std::cout << "prev() : ";

    assert(j10_1.prev(11).value() == 10);
    assert(j10_1.prev(10) == std::nullopt);
    assert(j10_1.prev(20).value() == 15);

    std::cout << "PASSED" << std::endl;

// first_empty()
std::cout << "first_empty() : ";

    j10_1.set(-1);
    assert(j10_1.first_empty(10).value() == 11);
    assert(j10_1.first_empty(-1) == std::nullopt);
    assert(j10_1.first_empty(11).value() == 11);

    std::cout << "PASSED" << std::endl;

// next_empty()
std::cout << "next_empty() : ";

    assert(j10_1.next_empty(10).value() == 11);
    assert(j10_1.next_empty(-2) == std::nullopt);
    assert(j10_1.next_empty(11).value() == 12);

    std::cout << "PASSED" << std::endl;

// last_empty()
std::cout << "last_empty() : ";

    j10_1.set(0);
    assert(j10_1.last_empty(10).value() == 9);
    assert(j10_1.last_empty(0) == std::nullopt);
    assert(j10_1.last_empty(11).value() == 11);

    std::cout << "PASSED" << std::endl;

// prev_empty()
std::cout << "prev_empty() : ";

    assert(j10_1.prev_empty(10).value() == 9);
    assert(j10_1.prev_empty(1) == std::nullopt);
    assert(j10_1.prev_empty(11).value() == 9);

    std::cout << "PASSED" << std::endl;

std::cout<< "\t=== JUDY MACRO FUNCS TESTS ENDED ===" << std::endl;

// operator[]
std::cout << std::endl <<  "operator[] : ";

    assert(j10_1[0] == 1);
    assert(j10_1[1] == 0);
    assert(j10_1[10] == j10_1[15]);
    assert(j10_1[2] == j10_1[3]);

    j10_1[3] = 1;
    assert(j10_1[3] == 1);

    j10_1[3] = 0;
    assert(j10_1[3] == 0);

    std::cout << "PASSED" << std::endl;

// judy1_it consturctor
std::cout << "judy1_it constructor : ";

    judy::Judy1 j11_1(j10_1.begin(), j10_1.end());
    assert(j10_1 == j11_1);
    assert(j11_1[3] == 0);
    assert(j11_1[0] == 1);

    std::cout << "PASSED" << std::endl;

// container_it constructor
std::cout << "container_it constructor : ";

    // std::vector
    judy::Judy1 j11_2(vec1.begin(), vec1.begin() + 2);
    assert(j11_2[1] == 1); assert(j11_2[2] == 1); assert(j11_2[3] == 0);

    // std::list
    std::list<int8_t>::const_iterator lst1_it = lst1.begin();
    for(int i = 0; i < 5; ++i) ++lst1_it;

    judy::Judy1 j11_3(lst1.cbegin(), lst1_it);
    for(int i = 1; i <= 5; ++i) assert(j11_3[i] == 1);
    assert(j11_3[6] == 0);

    // и т.д. в общем

    std::cout << "PASSED" << std::endl;

// iterators
std::cout << "iterators : ";

    j11_2[3] = 1;
    // begin(), cbegin()
    judy::Judy1::iterator j11_2_it1 = j11_2.begin();
    judy::Judy1::const_iterator j11_2_it2 = j11_2.begin();
    assert(j11_2_it2 == j11_2.cbegin());

    assert(j11_2_it1 != j10_1.begin());
    assert(j11_2_it2 != j10_1.cbegin());

    assert(j11_2_it1->first == 1 && j11_2_it1->second == 1);
    assert(j11_2_it2->first == 1 && j11_2_it2->second == 1);
    
    // iterator operator++, const_iterator operator++
    ++j11_2_it1; ++j11_2_it2;
    assert(j11_2_it1->first == 2 && j11_2_it1->second == 1);
    assert(j11_2_it2->first == 2 && j11_2_it2->second == 1);

    ++j11_2_it1; j11_2_it2++;
    ++j11_2_it1; j11_2_it2++;

    // end(), cend()

    assert(j11_2_it1 == j11_2.end());
    assert(j11_2_it2 == j11_2.cend());

    assert(j11_2_it1 != j10_1.end());
    assert(j11_2_it2 != j10_1.cend());

    // iterator operator--, const_iterator operator--
    --j11_2_it1; --j11_2_it2;
    j11_2_it1--; j11_2_it2--;

    assert(j11_2_it1->first == 2 && j11_2_it1->second == 1);
    assert(j11_2_it2->first == 2 && j11_2_it2->second == 1);

    // rbegin(), crbegin()
    judy::Judy1::reverse_iterator j11_2_rit1 = j11_2.rbegin();
    judy::Judy1::const_reverse_iterator j11_2_rit2 = j11_2.rbegin();
    assert(j11_2_rit2 == j11_2.crbegin());

    assert(j11_2_rit1 != j10_1.rbegin());
    assert(j11_2_rit2 != j10_1.crbegin());

    assert(j11_2_rit1->first == 3 && j11_2_rit1->second == 1);
    assert(j11_2_rit2->first == 3 && j11_2_rit2->second == 1);

    // reverse_iterator operator++, const_reverse_iterator operator++
    ++j11_2_rit1; j11_2_rit1++;
    ++j11_2_rit2; j11_2_rit2++;
    
    assert(j11_2_rit1->first == 1 && j11_2_rit1->second == 1);
    assert(j11_2_rit2->first == 1 && j11_2_rit2->second == 1);
    
    ++j11_2_rit1; j11_2_rit2++;

    // rend(), crend()

    assert(j11_2_rit1 == j11_2.rend());
    assert(j11_2_rit2 == j11_2.crend());
    
    assert(j11_2_rit1 != j10_1.rend());
    assert(j11_2_rit2 != j10_1.crend());

    // reverse_iterator operator--, const_reverse_iterator operator--
    --j11_2_rit1; j11_2_rit1--;
    --j11_2_rit2; j11_2_rit2--;

    assert(j11_2_rit1->first == 2 && j11_2_rit1->second == 1);
    assert(j11_2_rit2->first == 2 && j11_2_rit2->second == 1);
    
    for(auto it : j11_2) assert(it.second == 1);                        
    for(const auto& it : j11_2) assert(it.second == 1);             
    for(auto [key, val] : j11_2) assert(val== 1);  
    for(const auto& [key, val] : j11_2) assert(val == 1); 

    std::cout << "PASSED" << std::endl;

// stl-like
std::cout<< std::endl << "\t=== STL-LIKE FUNCS TESTS ===" << std::endl;

// lower_bound
std::cout << "lower_bound() : ";

    judy::Judy1::iterator lb_it1 = j11_2.lower_bound(1);
    assert(lb_it1->first == 1);
    judy::Judy1::const_iterator lb_it2 = j11_2.lower_bound(1);
    assert(lb_it1->first == 1);
    
    lb_it1 = j11_2.lower_bound(5);
    assert(lb_it1 == j11_2.end());

    lb_it2 = j11_2.lower_bound(5);
    assert(lb_it2 == j11_2.cend());

    std::cout << "PASSED" << std::endl;

// upper_bound
std::cout << "upper_bound() : ";

    lb_it1 = j11_2.upper_bound(1);
    assert(lb_it1->first == 2);
    lb_it2 = j11_2.upper_bound(1);
    assert(lb_it1->first == 2);
    
    lb_it1 = j11_2.upper_bound(3);
    assert(lb_it1 == j11_2.end());

    lb_it2 = j11_2.upper_bound(3);
    assert(lb_it2 == j11_2.cend());

    std::cout << "PASSED" << std::endl;

// equal_range
std::cout << "equal_range() : ";

    std::pair<judy::Judy1::iterator, judy::Judy1::iterator> lb_it3 = j11_2.equal_range(1);
    assert(lb_it3.first->first == 1 && lb_it3.second->first == 2);
    std::pair<judy::Judy1::const_iterator, judy::Judy1::const_iterator> lb_it4 = j11_2.equal_range(1);
    assert(lb_it4.first->first == 1 && lb_it4.second->first == 2);

    lb_it3 = j11_2.equal_range(3);
    assert(lb_it3.first->first == 3 && lb_it3.second == j11_2.end());
    lb_it4 = j11_2.equal_range(3);
    assert(lb_it4.first->first == 3 && lb_it4.second == j11_2.cend());
    
    std::cout << "PASSED" << std::endl;

// find
std::cout << "find() : ";

    judy::Judy1::iterator find_it1 = j11_2.find(2);
    assert(find_it1->first == 2);
    judy::Judy1::const_iterator find_it2 = j11_2.find(2);
    assert(find_it2->first == 2);

    find_it1 = j11_2.find(5);
    find_it2 = j11_2.find(5);
    assert(find_it1 == j11_2.end());
    assert(find_it2 == j11_2.cend());

    std::cout << "PASSED" << std::endl;

// erase
std::cout << "erase() : ";

    find_it1 = j11_2.find(2);
    j11_2.erase(find_it1);
    assert(j11_2[2] == 0);

    find_it2 = j11_2.find(1);
    j11_2.erase(find_it2);
    assert(j11_2[1] == 0);

    std::size_t erase_int1 = j11_2.erase(3);
    assert(erase_int1 == 1);

    for(auto val : {1,2,3}) j11_2[val] = 1;
    j11_2.erase(j11_2.begin(), j11_2.end());
    assert(j11_2.size() == 0);
    
    for(auto val : {1,2,3}) j11_2[val] = 1;
    j11_2.erase(j11_2.cbegin(), j11_2.cend());
    assert(j11_2.size() == 0);

    std::cout << "PASSED" << std::endl;

std::cout<< "\t=== STL-LIKE FUNCS TESTS ENDED ===" << std::endl;

// class funcs
std::cout<< std::endl << "\t=== CLASS FUNCS TESTS ===" << std::endl;

// operator==
std::cout << std::endl << "operator== : ";

    judy::Judy1 j12_1, j12_2;
    for(auto val : {1, 10, -2, 30, 29}) j12_1[val] = j12_2[val] = 1;
    assert(j12_1 == j12_2);
    
    std::cout << "PASSED" << std::endl;

// operator !=
std::cout << "operator!= : ";
    
    j12_1[0] = 1;
    assert(j12_1 != j12_2);

    std::cout << "PASSED" << std::endl;

// operator|
std::cout << "operator| : ";

    // 01011
    // 10001
    judy::Judy1 j13_1, j13_2; 
    for(auto val : {0, 1, 3}) j13_1[val] = 1;
    for(auto val : {0, 4}) j13_2[val] = 1;
    judy::Judy1 j13_3 = j13_1 | j13_2;
    for(auto val : {0, 1, 3, 4}) assert(j13_3[val]);
    assert(j13_3.size() == 4);

    std::cout << "PASSED" << std::endl;

// operator&
std::cout << "operator& : ";

    j13_3 = j13_1 & j13_2;
    assert(j13_3.size() == 1 && j13_3[0] == 1);

    std::cout << "PASSED" << std::endl;

// operator-
std::cout << "operator- : ";

    j13_3 = j13_1 - j13_2;
    for(auto val : {1, 3}) assert(j13_3[val]);
    assert(j13_3.size() == 2);

    std::cout << "PASSED" << std::endl;

// operator^
std::cout << "operator^ : ";
    //11010
    j13_3 = j13_1 ^ j13_2;
    for(auto val : {1, 3, 4}) assert(j13_3[val]);
    assert(j13_3.size() == 3);

    std::cout << "PASSED" << std::endl;

// operator|=
std::cout << "operator|= : ";

    j13_3 = j13_1;
    j13_3 |= j13_2;
    for(auto val : {0, 1, 3, 4}) assert(j13_3[val]);
    assert(j13_3.size() == 4);

    std::cout << "PASSED" << std::endl;

// operator&=
std::cout << "operator&= : ";

    j13_3 = j13_1;
    j13_3 &= j13_2;
    assert(j13_3.size() == 1 && j13_3[0] == 1);

    std::cout << "PASSED" << std::endl;

// operator-=
std::cout << "operator-= : ";

    j13_3 = j13_1;
    j13_3 -= j13_2;
    for(auto val : {1, 3}) assert(j13_3[val]);
    assert(j13_3.size() == 2);

    std::cout << "PASSED" << std::endl;

// operator^=
std::cout << "operator^= : ";
    
    j13_3 = j13_1;
    j13_3 ^= j13_2;
    for(auto val : {1, 3, 4}) assert(j13_3[val]);
    assert(j13_3.size() == 3);

    std::cout << "PASSED" << std::endl;

std::cout << "\t=== CLASS FUNCS TESTS ENDED ===" << std::endl;

// namespace judy funcs

// swap(Judy1, Judy1)
std::cout << std::endl << "judy::swap(Judy1, Judy1) : ";

    j13_3 = j13_1;
    judy::swap(j13_1, j13_2);
    assert(j13_3 == j13_2);
    
    std::cout << "PASSED" << std::endl;

}

void judyl_test()
{
//*******************************CONTAINERS*************************************//
    std::initializer_list<std::pair<Word_t, Word_t>> init_lst1 = {{1, 2}, {3, 2}, {5, 6}};
    
    std::vector<int> vec1 = {2, 3, 4, 5}; // {0, 2}, {1, 3}, {2, 4}, {3, 5}
    std::vector<int> vec2 = {1}; // {0, 1}

    std::set<unsigned long long> s1 = {1, 10, 20}; // {0, 1}, {1, 10}, {2, 20}
    std::set<long long> s2 = {-2, -10, -100}; // {0, -100}, {1, -10}, {2, -2}

    std::array<int_fast32_t, 4> arr1 = {-1, 12, 13, -1}; // {0, -1}, {1, 12}, {2, 13}, {3, -1}
    std::array<uint_fast32_t, 4> arr2 = {0, 0, 0, 0}; // {0, 0}, {1, 0}, {2, 0}, {3, 0}

    std::list<char> lst1 = {0, 12, 1}; // {0, 0}, {1, 12}, {2, 1}
    std::list<char> lst2 = {0, 0, 1, 1}; // {0, 0}, {1, 0}, {2, 1}, {3, 1}

    std::forward_list<bool> flst1 = {1, 1, 1, 0, 1}; // {0, 1}, {1, 1}, {2, 1}, {3, 0}, {4, 1}
    std::forward_list<bool> flst2 = {1};

    std::multiset<long> ms1 = {1, 1, 2, -1}; // {0, -1}, {1, 1}, {2, 1}, {3, 2}
    std::multiset<unsigned long> ms2 = {10, 2, 100}; // {0, 2}, {1, 10}, {2, 100}

    std::unordered_set<int8_t> us1 = {1, 2, 1}; // not safe (нет гарантированного порядка обхода)
    std::unordered_set<int8_t> us2 = {1, 3};    // not safe

    std::unordered_multiset<int> ums1 = {1, 2, 1};  // not safe
    std::unordered_multiset<int> ums2 = {1, 3};     // not safe

    std::string str1 = "Hello"; // {0, 'H'}, {1, 'e'}, {2, 'l'}, {3, 'l'}, {4, 'o'}
    std::string str2 = ", World!\n"; // {0, ','}, {1, ' '}, {2, 'W'}, {3, 'o'}, {4, 'r'}, {5, 'l'}, {6, 'd'}, {7, '!'}, {8, '\n'}

    std::wstring wstr1 = L"окак"; // {0, L'о'}, {1, L'к'}, {2, L'а'}, {3, L'к'}
    std::wstring wstr2 = L"привет"; // {0, L'п'}, {1, L'р'}, {2, L'и'}, {3, L'в'}, {4, 'е'}, {5, 'т'}

    std::map<unsigned int, unsigned int> mp1 = {{2, 20}, {3, 1}};
    std::map<int, int> mp2 = {{1, 100}, {-1, 200}, {2, 300}};

    std::multimap<int, int> mmp1 = {{1, 20}, {2, 30}, {1, 2}};
    
    std::vector<std::pair<int,int>> vecp1 = {{0, 1}, {1, 1}, {2, 2}};

//*********************************JUDY L***************************************//
    std::cout << std::endl << "=========== JUDY L TESTS ===========" << std::endl;

std::cout<< std::endl << "\t=== CONSTRUCTOR TESTS ===" << std::endl;

// Базовый конструктор
std::cout<< "Basic constructor: ";

    judy::JudyL jl1;
    judy::JudyL jl1_1{};
    
    assert(jl1.size() == jl1_1.size() && jl1.size() == 0);
    assert(jl1.empty() && jl1_1.empty());

    judy::Judy1* pjl1_2 = new judy::Judy1();
    judy::Judy1* pjl1_3 = new judy::Judy1;

    assert(pjl1_2->size() == pjl1_3->size() && pjl1_2->size() == 0);
    assert(pjl1_2->empty() && pjl1_3->empty());
    
    delete pjl1_2;
    delete pjl1_3;

    std::unique_ptr<judy::Judy1> pjl1_4 = std::make_unique<judy::Judy1>();
    assert(pjl1_4->size() == 0);
    
    std::cout << "PASSED" << std::endl;
  
// Конструктор для списка инициализации
std::cout << "initializer_list constructor: ";

    judy::JudyL jl2_1 = {};
    judy::JudyL jl2_2 = {{1, 2}, {3, 2}, {5, 6}};


    assert(jl2_1.size() == 0);
    for(auto val : init_lst1)
        assert(jl2_2[val.first] == val.second);
    assert(jl2_2.size() == init_lst1.size());        

    std::cout << "PASSED" << std::endl;

// Конструктор для контейнеров с value_type = is_integral
std::cout << "container<integral> constructors: ";

    std::size_t i;

    // std::vector
    judy::JudyL jl3(vec1);
    judy::JudyL jl3_1(vec2);

    for(i = 0; i < vec1.size(); ++i) assert(jl3[i] == vec1[i]);
    for(i = 0; i < vec2.size(); ++i) assert(jl3_1[i] == vec2[i]);

    // std::set
    judy::JudyL jl3_2(s1);
    judy::JudyL jl3_3(s2);
    i = 0;
    for(auto val : s1) assert(jl3_2[i] == val), ++i;
    i = 0;
    for(auto val : s2) assert(jl3_3[i] == val), ++i;

    // std::array
    judy::JudyL jl3_4(arr1);
    judy::JudyL jl3_5(arr2);

    i = 0;
    for(auto val : arr1) assert(jl3_4[i] == val), ++i;
    i = 0;
    for(auto val : arr2) assert(jl3_5[i] == val), ++i;

    // std::list
    judy::JudyL jl3_6(lst1);
    judy::JudyL jl3_7(lst2);

    i = 0;
    for(auto val : lst1) assert(jl3_6[i] == val), ++i;
    i = 0;
    for(auto val : lst2) assert(jl3_7[i] == val), ++i;

    // std::forward_list
    judy::JudyL jl3_10(flst1);
    judy::JudyL jl3_11(flst2);

    i = 0;
    for(auto val : flst1) assert(jl3_10[i] == val), ++i;
    i = 0;
    for(auto val : flst2) assert(jl3_11[i] == val), ++i;

    // std::multiset
    judy::JudyL jl3_12(ms1);
    judy::JudyL jl3_13(ms2);

    i = 0;
    for(auto val : ms1) assert(jl3_12[i] == val), ++i;
    i = 0;
    for(auto val : ms2) assert(jl3_13[i] == val), ++i;

    // std::unordered_set
    judy::JudyL jl3_14(us1);
    judy::JudyL jl3_15(us2);

    i = 0;
    for(auto val : us1) assert(jl3_14[i] == val), ++i;
    i = 0;
    for(auto val : us2) assert(jl3_15[i] == val), ++i;
    
    // std::unordered_multiset
    judy::JudyL jl3_16(ums1);
    judy::JudyL jl3_17(ums2);

    i = 0;
    for(auto val : ums1) assert(jl3_16[i] == val), ++i;
    i = 0;
    for(auto val : ums2) assert(jl3_17[i] == val), ++i;

    // std::string
    judy::JudyL jl3_18(str1);
    judy::JudyL jl3_19(str2);

    i = 0;
    for(auto val : str1) assert(jl3_18[i] == val), ++i;
    i = 0;
    for(auto val : str2) assert(jl3_19[i] == val), ++i;
    
    // std::wstring
    judy::JudyL jl3_20(wstr1);
    judy::JudyL jl3_21(wstr2);

    i = 0;
    for(auto val : wstr1) assert(jl3_20[i] == val), ++i;
    i = 0;
    for(auto val : wstr2) assert(jl3_21[i] == val), ++i;

    std::cout << "PASSED" << std::endl;

// Конструктор для итераторов для контейнеров пар
std::cout << "iterator<pair> constructors: ";

    std::map<int, int>::const_iterator mp2_it1 = mp2.begin(); ++mp2_it1; ++mp2_it1; 
    judy::JudyL jl4_1(mp1.begin(), mp1.end());
    judy::JudyL jl4_2(mp2.cbegin(), mp2_it1);

    for(auto [key, val] : mp1) assert(jl4_1[key] == val);
    for(auto it = mp2.begin(); it != mp2_it1; ++it) assert(jl4_2[it->first] == it->second);

    judy::JudyL jl4_3(mmp1.begin(), mmp1.end());
    judy::JudyL jl4_4(vecp1.begin(), vecp1.end());

    assert(jl4_3[1] == 20 && jl4_3[2] == 30);
    for(auto [key, val] : vecp1) assert(jl4_4[key] == val);

    std::cout << "PASSED" << std::endl;

// Конструктор копирования
std::cout << "copy constructor: ";

    judy::JudyL jl4_5(jl4_1);
    assert(jl4_5 == jl4_1);

    judy::JudyL jl4_6(judy::JudyL{ {1, 1}, {2, 1}, {3, 1}});
    for(auto val : {1, 2, 3}) assert(jl4_6[val] == 1);

    std::cout << "PASSED" << std::endl;

// Оператор =
std::cout << "oprtator= : ";
    
    judy::JudyL jl4_7 = jl4_5;
    assert(jl4_7 == jl4_5);

    std::cout << "PASSED" << std::endl;

std::cout << "\t=== CONSTRUCTOR TESTS ENDED ===" << std::endl;


std::cout << std::endl << "\t=== JUDY MACROS FUNCS TESTS ===" << std::endl;

// insert()
std::cout << "insert() func: ";

    judy::JudyL jl5_1;
    jl5_1.insert(0); jl5_1.insert(-1);
    assert(jl5_1.get(0)); assert(jl5_1.get(-1));

    std::cout << "PASSED" << std::endl;

// get()
std::cout << "get() func : ";
    
    assert(jl5_1.get(0) && jl5_1.get(-1));
    assert(!jl5_1.get(2));

    std::cout << "PASSED" << std::endl;

// del()
std::cout << "del() func : ";
    
    assert(jl5_1.del(0));
    assert(!jl5_1.del(0));
    assert(!jl5_1.get(0));

    std::cout << "PASSED" << std::endl;

// count()
std::cout << "count() func : ";

    assert(jl5_1.count(0, -1) == 1);
    assert(jl5_1.count(0, 0) == 0);
    assert(jl5_1.count(-1, -1) == 1);

    std::cout << "PASSED" << std::endl;

// ncount()
std::cout << "ncount() func : ";

    std::pair<PWord_t, Word_t> ans1 = jl5_1.ncount(1);
    assert(ans1.first && ans1.second == -1);
    ans1 = jl5_1.ncount(2);
    assert(!ans1.first);

    std::cout << "PASSED" << std::endl;

// memused()
std::cout << "memused() func : ";

    assert(jl5_1.memused() != 0);
    jl5_1.clear();
    assert(jl5_1.memused() == 0);

    std::cout << "PASSED" << std::endl;

// first()
std::cout << "first() func : ";

    jl5_1[1] = jl5_1[2] = jl5_1[10] = 2;

    ans1 = jl5_1.first(0);
    assert(ans1.first && ans1.second == 1);
    ans1 = jl5_1.first(11);
    assert(!ans1.first);

    std::cout << "PASSED" << std::endl;

// next()
std::cout << "next() func : ";

    ans1 = jl5_1.next(1);
    assert(ans1.first && ans1.second == 2);
    ans1 = jl5_1.next(10);
    assert(!ans1.first);

    std::cout << "PASSED" << std::endl;

// last()
std::cout << "last() func : ";

    ans1 = jl5_1.last(1);
    assert(ans1.first && ans1.second == 1);
    ans1 = jl5_1.last(0);
    assert(!ans1.first);

    std::cout << "PASSED" << std::endl;

// prev()
std::cout << "prev() func : ";

    ans1 = jl5_1.prev(10);
    assert(ans1.first && ans1.second == 2);
    ans1 = jl5_1.prev(1);
    assert(!ans1.first);

    std::cout << "PASSED" << std::endl;

// first_empty()
std::cout << "first_empty() func : ";

    jl5_1.del(1); jl5_1.del(2); jl5_1[0] = 2;
    jl5_1[-1] = 2;

    std::optional<Word_t> ans2 = jl5_1.first_empty(0);
    assert(ans2 != std::nullopt && ans2.value() == 1);
    ans2 = jl5_1.first_empty(-1);
    assert(ans2 == std::nullopt);

    std::cout << "PASSED" << std::endl;

// next_empty()
std::cout << "next_empty() func : ";


    ans2 = jl5_1.next_empty(1);
    assert(ans2 != std::nullopt && ans2.value() == 2);
    ans2 = jl5_1.next_empty(-2);
    assert(ans2 == std::nullopt);

    std::cout << "PASSED" << std::endl;

// last_empty()
std::cout << "last_empty() func : ";

    ans2 = jl5_1.last_empty(1);
    assert(ans2 != std::nullopt && ans2.value() == 1);
    ans2 = jl5_1.last_empty(0);
    assert(ans2 == std::nullopt);

    std::cout << "PASSED" << std::endl;

// prev_empty()
std::cout << "prev_empty() func : ";

    ans2 = jl5_1.prev_empty(2);
    assert(ans2 != std::nullopt && ans2.value() == 1);
    ans2 = jl5_1.prev_empty(1);
    assert(ans2 == std::nullopt);

    std::cout << "PASSED" << std::endl;

std::cout << "\t=== JUDY MACROS FUNCS TESTS ENDED ===" << std::endl;


std::cout << std::endl << "\t=== CONTAINER FUNCS TESTS ===" << std::endl;

// size()
std::cout << "size() func: ";

    judy::JudyL jl6_1;
    assert(jl6_1.size() == 0);
    jl6_1.insert(0); jl6_1.insert(1); jl6_1.insert(2);
    assert(jl6_1.size() == 3);
    jl6_1.del(0);
    assert(jl6_1.size() == 2);

    std::cout << "PASSED" << std::endl;

// empty()
std::cout << "empty() func : ";

    judy::JudyL jl6_2;
    assert(jl6_2.empty());
    jl6_2.insert(0);
    assert(!jl6_2.empty());

    std::cout << "PASSED" << std::endl;

// clear()
std::cout << "clear() func : ";

    jl6_2.clear();
    assert(jl6_2.size() == 0);

    std::cout << "PASSED" << std::endl;

// swap()
std::cout << "swap() func : ";

    judy::JudyL jl6_3(jl6_1);
    jl6_1.swap(jl6_2);
    assert(jl6_3 == jl6_2);
    jl6_2.swap(jl6_1);
    assert(jl6_3 == jl6_1);

// count()
std::cout << "count() func : ";

    assert(jl6_1.count(1) == 1);
    assert(jl6_1.count(4) == 0);

    std::cout << "PASSED" << std::endl;

// contains()
std::cout << "contains() func : ";

    assert(jl6_1.contains(1) == true);
    assert(jl6_1.contains(4) == false);

    std::cout << "PASSED" << std::endl;

// set_debug_mode()
std::cout << "set_debug_mode() func : ";

    judy::JudyL::set_debug_mode(true);
    {
        judy::JudyL jl7_1;
    }
    judy::JudyL::set_debug_mode(false);
    {
        judy::JudyL jl7_2;
    }

    std::cout << "PASSED" << std::endl;

std::cout<< "\t=== CONTAINER FUNCS TESTS ENDED ===" << std::endl;


// operator[]
std::cout << "operator[] : ";

    PWord_t pv1;

    judy::JudyL jl8_1;
    pv1 = jl8_1.insert(0); *pv1 = 2; pv1 = jl8_1.insert(2); *pv1 = 2; pv1 = jl8_1.insert(5); *pv1 = 5; pv1 = jl8_1.insert(10); *pv1 = 10;
    

    assert(jl8_1[0] == 2);
    assert(jl8_1[5] == 5);
    assert(jl8_1[11] == jl8_1[15]);
    assert(jl8_1[2] == jl8_1[0]);

    jl8_1[3] = 1;
    assert(jl8_1[3] == 1);

    jl8_1[3] = 0;
    assert(jl8_1[3] == 0);

    std::cout << "PASSED" << std::endl;

// at()
std::cout << "at() : ";

    assert(jl8_1.at(3) == 0);
    assert(jl8_1.at(5) == 5);

    const judy::JudyL jl8_2 = {{1, 1}, {10, 2}, {100, 3}};
    assert(jl8_2.at(1) == 1);
    assert(jl8_2.at(100) == 3);

    std::cout << "PASSED" << std::endl;

// iterators
std::cout << "iterators : ";

    judy::JudyL jl8_3(jl8_2);

    // begin(), cbegin()
    judy::JudyL::iterator jl8_1_it1 = jl8_1.begin();
    judy::JudyL::const_iterator jl8_1_it2 = jl8_1.begin();
    assert(jl8_1_it2 == jl8_1.cbegin());

    assert(jl8_1_it1 != jl8_3.begin());
    assert(jl8_1_it2 != jl8_3.cbegin());

    assert(jl8_1_it1->first == 0 && jl8_1_it1->second == 2);
    assert(jl8_1_it2->first == 0 && jl8_1_it2->second == 2);
    
    // iterator operator++, const_iterator operator++
    ++jl8_1_it1; ++jl8_1_it2;
    assert(jl8_1_it1->first == 2 && jl8_1_it1->second == 2);
    assert(jl8_1_it2->first == 2 && jl8_1_it2->second == 2);

    for(i = 0; i < 6; ++i) ++jl8_1_it1, jl8_1_it2++;

    // end(), cend()

    assert(jl8_1_it1 == jl8_1.end());
    assert(jl8_1_it2 == jl8_1.cend());

    assert(jl8_1_it1 != jl8_3.end());
    assert(jl8_1_it2 != jl8_3.cend());

    // iterator operator--, const_iterator operator--
    --jl8_1_it1; --jl8_1_it2;
    jl8_1_it1--; jl8_1_it2--;

    assert(jl8_1_it1->first == 11 && jl8_1_it1->second == 0);
    assert(jl8_1_it2->first == 11 && jl8_1_it2->second == 0);

    // rbegin(), crbegin()
    judy::JudyL::reverse_iterator jl8_1_rit1 = jl8_1.rbegin();
    judy::JudyL::const_reverse_iterator jl8_1_rit2 = jl8_1.rbegin();
    assert(jl8_1_rit2 == jl8_1.crbegin());

    assert(jl8_1_rit1 != jl8_3.rbegin());
    assert(jl8_1_rit2 != jl8_3.crbegin());

    assert(jl8_1_rit1->first == 15 && jl8_1_rit1->second == 0);
    assert(jl8_1_rit2->first == 15 && jl8_1_rit2->second == 0);

    // reverse_iterator operator++, const_reverse_iterator operator++
    ++jl8_1_rit1; jl8_1_rit1++;
    ++jl8_1_rit2; jl8_1_rit2++;
    
    assert(jl8_1_rit1->first == 10 && jl8_1_rit1->second == 10);
    assert(jl8_1_rit2->first == 10 && jl8_1_rit2->second == 10);
    
    for(i = 0; i < 5; ++i) ++jl8_1_rit1, jl8_1_rit2++;

    // rend(), crend()

    assert(jl8_1_rit1 == jl8_1.rend());
    assert(jl8_1_rit2 == jl8_1.crend());
    
    assert(jl8_1_rit1 != jl8_3.rend());
    assert(jl8_1_rit2 != jl8_3.crend());

    // reverse_iterator operator--, const_reverse_iterator operator--
    --jl8_1_rit1; jl8_1_rit1--;
    --jl8_1_rit2; jl8_1_rit2--;

    assert(jl8_1_rit1->first == 2 && jl8_1_rit1->second == 2);
    assert(jl8_1_rit2->first == 2 && jl8_1_rit2->second == 2);
    
    std::map<int, int> vals = { {0, 2}, {2, 2}, {3, 0}, {5, 5}, {10, 10}, {11, 0}, {15, 0}};

    for(auto it : jl8_1) assert(vals[it.first] == it.second);                        
    for(const auto& it : jl8_1) assert(vals[it.first] == it.second);             
    for(auto [key, val] : jl8_1) assert(vals[key] == val);  
    for(const auto& [key, val] : jl8_1) assert(vals[key] == val); 

    std::cout << "PASSED" << std::endl;

// stl-like
std::cout<< std::endl << "\t=== STL-LIKE FUNCS TESTS ===" << std::endl;

// lower_bound
std::cout << "lower_bound() : ";

    judy::JudyL::iterator lb_it1 = jl8_1.lower_bound(2);
    assert(lb_it1->first == 2);
    judy::JudyL::const_iterator lb_it2 = jl8_1.lower_bound(2);
    assert(lb_it1->first == 2);
    
    lb_it1 = jl8_1.lower_bound(16);
    assert(lb_it1 == jl8_1.end());

    lb_it2 = jl8_1.lower_bound(16);
    assert(lb_it2 == jl8_1.cend());

    std::cout << "PASSED" << std::endl;

// upper_bound
std::cout << "upper_bound() : ";

    lb_it1 = jl8_1.upper_bound(2);
    assert(lb_it1->first == 3);
    lb_it2 = jl8_1.upper_bound(2);
    assert(lb_it1->first == 3);
    
    lb_it1 = jl8_1.upper_bound(15);
    assert(lb_it1 == jl8_1.end());

    lb_it2 = jl8_1.upper_bound(15);
    assert(lb_it2 == jl8_1.cend());

    std::cout << "PASSED" << std::endl;

// equal_range
std::cout << "equal_range() : ";

    std::pair<judy::JudyL::iterator, judy::JudyL::iterator> lb_it3 = jl8_1.equal_range(2);
    assert(lb_it3.first->first == 2 && lb_it3.first->second == 2 && lb_it3.second->first == 3 && lb_it3.second->second == 0);
    std::pair<judy::JudyL::const_iterator, judy::JudyL::const_iterator> lb_it4 = jl8_1.equal_range(2);
    assert(lb_it4.first->first == 2 && lb_it4.first->second == 2 && lb_it4.second->first == 3 && lb_it4.second->second == 0);

    lb_it3 = jl8_1.equal_range(15);
    assert(lb_it3.first->first == 15 && lb_it3.first->second == 0 && lb_it3.second == jl8_1.end());
    lb_it4 = jl8_1.equal_range(15);
    assert(lb_it4.first->first == 15 && lb_it4.first->second == 0 && lb_it4.second == jl8_1.cend());
    
    std::cout << "PASSED" << std::endl;

// find
std::cout << "find() : ";

    judy::JudyL::iterator find_it1 = jl8_1.find(2);
    assert(find_it1->first == 2 && find_it1->second == 2);
    judy::JudyL::const_iterator find_it2 = jl8_1.find(2);
    assert(find_it2->first == 2 && find_it2->second == 2);

    find_it1 = jl8_1.find(4);
    find_it2 = jl8_1.find(4);
    assert(find_it1 == jl8_1.end());
    assert(find_it2 == jl8_1.cend());

    std::cout << "PASSED" << std::endl;

// erase
std::cout << "erase() : ";

    find_it1 = jl8_1.find(2);
    jl8_1.erase(find_it1);
    assert(!jl8_1.get(2));

    find_it2 = jl8_1.find(0);
    jl8_1.erase(find_it2);
    assert(!jl8_1.get(0));

    std::size_t erase_int1 = jl8_1.erase(3);
    assert(erase_int1 == 1);

    jl8_1.erase(jl8_1.begin(), jl8_1.end());
    assert(jl8_1.size() == 0);
    
    for(auto [key, val] : vals) jl8_1[key] = val;
    jl8_1.erase(jl8_1.cbegin(), jl8_1.cend());
    assert(jl8_1.size() == 0);

    std::cout << "PASSED" << std::endl;

// merge
std::cout << "merge() : ";

    judy::JudyL jl9_1 = {{1, 10}, {2, 20}};
    judy::JudyL jl9_2 = {{3, 30}, {4, 40}};

    jl9_1.merge(jl9_2);
    assert(jl9_1.size() == 4 && jl9_2.size() == 0);

    judy::JudyL jl9_3 = {{10, 100}, {30, 300}, {50, 500}};
    judy::JudyL jl9_4 = {{20, 200}, {30, 999}, {40, 400}}; 

    jl9_3.merge(jl9_4);

    assert(jl9_3.size() == 5 && jl9_4.size() == 1 && jl9_4[30] == 999);

    judy::JudyL jl9_5 = {{1, 1}};
    judy::JudyL jl9_6; 

    jl9_5.merge(jl9_6);
    
    assert(jl9_5.size() == 1 && jl9_5[1] == 1 && jl9_6.size() == 0);

    judy::JudyL jl9_7; 
    judy::JudyL jl9_8 = {{100, 101}, {200, 201}};

    jl9_7.merge(jl9_8);

    assert(jl9_7.size() == 2 && jl9_8.size() == 0);

    std::cout << "PASSED" << std::endl;

std::cout<< "\t=== STL-LIKE FUNCS TESTS ENDED ===" << std::endl;

// swap(JudyL, JudyL)
std::cout << std::endl << "judy::swap(JudyL, JudyL) : ";

    jl9_3 = jl9_1;
    judy::swap(jl9_1, jl9_2);
    assert(jl9_3 == jl9_2);
    
    std::cout << "PASSED" << std::endl;

}

// Протестируем на валидность работу всех методов (не стресс)
int main(int argc, char** argv) {

    judy1_test();
    judyl_test();

    std::cout << std::endl << "ALL TESTS PASSED" << std::endl;

    return 0;
}
