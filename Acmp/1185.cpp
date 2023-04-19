#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>

using namespace std;

class SegmentTree
{
private:
    vector<int> tree;
    int size;
public:

    //�����������
    SegmentTree(int _size = 1)
        : size(_size)
        , tree(_size << 2)
    { }

    //���� ������
    void build(const vector<int>& a)
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
        tree[v] = max(tree[2 * v], tree[2 * v + 1]);
    }


    //������ ��������
    int maximum(int l, int r) {
        return maximum(1, 0, size, l, r);
    }

    int maximum(int v, int tl, int tr, int l, int r)
    {
        if (tl >= r || tr <= l)
            return INT_MIN;

        if (tl >= l && tr <= r)
            return tree[v];
        int mid = (tr + tl) / 2;
        return max(maximum(2 * v, tl, mid, l, r), maximum(2 * v + 1, mid, tr, l, r));
    }


    //���������� �������
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
            tree[v] = max(tree[2 * v], tree[2 * v + 1]);
        }
    }

    //�����
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

    const char SUM = 'm', ADD = 'u';
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
            cout << tree.maximum(start, end) << ' ';
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