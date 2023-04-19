#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <numeric>

using namespace std;


//НОД
class SegmentTree
{
private:
    vector<long long> tree;
    int size;

public:

    //Слияние детей
    int combine(int a, int b)
    {
        return gcd(a, b);
    }

    //Конструктор
    SegmentTree(int _size)
        : size(_size)
        , tree(_size << 2)
    {  }


    //Билд дерева
    void  build(const vector<int>& a)
    {
        build(a, 1, 0, size);
    }

    void build(const vector<int>& a, int v, int l, int r)
    {
        if (r - l == 1)
        {
            tree[v] = a[l];
            return;
        }
        int mid = (l + r) / 2;
        build(a, 2 * v, l, mid);
        build(a, 2 * v + 1, mid, r);
        tree[v] = combine(tree[2 * v], tree[2 * v + 1]);
    }

    //Запрос НОД
    long long max_gcd(int l, int r) {
        return max_gcd(1, 0, size, l, r);
    }

    long long max_gcd(int v, int tl, int tr, int l, int r)
    {
        if (tl >= r || tr <= l)
            return 0;

        if (tl >= l && tr <= r)
            return tree[v];
        int mid = (tr + tl) / 2;
        return combine(max_gcd(2 * v, tl, mid, l, r), max_gcd(2 * v + 1, mid, tr, l, r));
    }

    //Обновление вершины
    void update_vertex(int pos, int value) {
        update_vertex(1, 0, size, pos, value);
    }

    void update_vertex(int v, int tl, int tr, int pos, int value) {
        if (tr - tl == 1)
            tree[v] = value;
        else {
            int mid = (tr + tl) / 2;
            if (pos < mid)
                update_vertex(v * 2, tl, mid, pos, value);
            else
                update_vertex(v * 2 + 1, mid, tr, pos, value);
            tree[v] = gcd(tree[2 * v], tree[2 * v + 1]);
        }
    }




    //Вывод
    void print()
    {
        cout << "size " << size << '\n';
        for (int i = 0; i < tree.size(); i++)
            cout << tree[i] << ' ';
        cout << '\n';
    }
};


int main()
{
    int n, m;
    cin >> n;
    vector<int> a(n);
    SegmentTree tree(n);

    for (int& it : a)
        cin >> it;

    tree.build(a);

    const char SUM = 'g', ADD = 'u';
    cin >> m;
    while (m-- > 0)
    {
        char type;
        cin >> type;
        if (SUM == type)
        {
            int start, end;
            cin >> start >> end;
            --start;
            cout << tree.max_gcd(start, end) << ' ';
        }
        else if (ADD == type) {
            int index, value;
            cin >> index >> value;
            --index;
            tree.update_vertex(index, value);
        }
    }


    return 0;
}