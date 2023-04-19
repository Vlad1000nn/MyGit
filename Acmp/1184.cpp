#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>

using namespace std;

class SegmentTree
{
private:

    struct node {
        int value;
        int index;
    };
    vector<node> tree;
    int size;

public:

    node combine(node a, node b)
    {
        if (a.value >= b.value)
            return a;
        else if (a.value < b.value)
            return b;
    }

    //Конструктор
    SegmentTree(int _size = 1)
        : size(_size)
        , tree(_size << 2)
    { }

    //Билд дерева
    void build(const vector<int>& a)
    {
        build(a, 1, 0, size);
    }

    void build(const vector<int>& a, int v, int l, int r)
    {
        if (r - l == 1)
        {
            tree[v] = { a[l],l };
            return;
        }
        int mid = (l + r) / 2;
        build(a, 2 * v, l, mid);
        build(a, 2 * v + 1, mid, r);
        tree[v] = combine(tree[2 * v], tree[2 * v + 1]);
    }


    //Запрос максимума
    node maximum(int l, int r) {
        return maximum(1, 0, size, l, r);
    }

    node maximum(int v, int tl, int tr, int l, int r)
    {
        if (tl >= r || tr <= l)
            return { INT_MIN,-1 };

        if (tl >= l && tr <= r)
            return tree[v];
        int mid = (tr + tl) / 2;
        return combine(maximum(2 * v, tl, mid, l, r), maximum(2 * v + 1, mid, tr, l, r));
    }


    //Вывод
    void print()
    {
        cout << "size " << size << '\n';
        for (int i = 0; i < tree.size(); i++)
            cout << tree[i].value << ' ' << tree[i].index << '\n';
        cout << '\n';
    }
};


int main()
{
    cin.tie(0);
    std::ios_base::sync_with_stdio(false);
    int n, m;
    cin >> n;
    vector<int> a(n);
    SegmentTree tree(n);

    for (int& it : a)
        cin >> it;

    tree.build(a);

    cin >> m;
    while (m-- > 0)
    {
        int start, end;
        cin >> start >> end;
        --start;
        cout << tree.maximum(start, end).value << ' ' << tree.maximum(start, end).index + 1 << '\n';
    }


    return 0;
}