#include <iostream>     // For std::cout
#include <vector>       // For std::vector
#include <algorithm>    // For std::swap


#define isz(x) (int)x.size()
#define all(x) (x).begin(),(x).end()
#define vT std::vector<T>


// Binary max-heap
template<typename T>
class BinHeap
{
private:

    // Heap arr
    vT vec;
    // Count of the elements
    int count;


    // Child go up
    void sift_up(int v)
    {
        while (v > 1 && vec[v] > vec[v / 2])
        {
            std::swap(vec[v], vec[v / 2]);
            v /= 2;
        }
    }

    // Parent fall
    void sift_down(int v)
    {
        while (2 * v <= count)
        {
            int curr = ((2 * v + 1) <= count && vec[2 * v + 1] > vec[2 * v] ? (2 * v + 1) : (2 * v));
            if (vec[v] >= vec[curr]) break;
            std::swap(vec[v], vec[curr]);
            v = curr;
        }
    }

    // Build heap
    void build()
    {
        for (int i = count; i > 0; --i)
            sift_down(i);
    }

    // Calculate size of the vec
    int calc_size() const
    {
        int n = 1;
        while (n < 2 * count) n *= 2;
        return n;
    }

public:

    // Basic constructors
    BinHeap<T>(const vT& vec)
    {
        count = isz(vec);

        BinHeap::vec.assign(calc_size(), T{});
        std::copy(all(vec), BinHeap::vec.begin() + 1);

        build();
    }


    BinHeap<T>(int count = 0)
        : count(count)
    {
        vec.assign(calc_size(), T{});
    }

    // Get the top element
    T top() const
    {
        if (!count) throw L"EMPTY";
        return vec[1];
    }

    // Erase the root
    void pop()
    {
        if (!count) throw L"EMPTY";

        vec[1] = vec[count];
        vec[count] = T{};
        --count;
        sift_down(1);
    }

    // Get size of the heap
    int size() const
    {
        return count;
    }

    // Push new element
    void push(const T& key)
    {
        ++count;
        int n = calc_size();
        if (n != vec.size()) vec.resize(n);

        vec[count] = key;
        sift_up(count);
    }

    // Print func
    void print() const
    {
        if (!count) return;
        for (int i = 1; i <= count; ++i)
            std::cout << vec[i] << ' ';
    }

    // Destructor
    ~BinHeap<T>()
    {
        vec.clear();
    }

};


#include <vector>
#include <numeric>

int main()
{
    using namespace std;

    using vi = vector<int>;
    vi vec(10);
    std::iota(vec.begin(), vec.end(), 10);



    cout << "VEC print: ";
    for (auto& it : vec)
        cout << it << ' ';

    cout << '\n';
    BinHeap h(vec);
    //h.push(1); 
    h.push(100);
    cout << h.top() << " is top\n";
    h.pop(); cout << "We pop()\n";
    h.print();

    cout << "\nHEAPHEAP: ";

    std::make_heap(vec.begin(), vec.end());
    for (auto& it : vec) cout << it << ' ';


    return 0;
}