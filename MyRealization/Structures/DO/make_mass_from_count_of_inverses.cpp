﻿class SegmentTree
{
private:
    vector<int> tree;
    int size;
public:

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
            tree[v] = a[l];
            return;
        }
        int mid = (l + r) / 2;
        build(a, 2 * v, l, mid);
        build(a, 2 * v + 1, mid, r);
        tree[v] = tree[2 * v] + tree[2 * v + 1];
    }


    //k-я единица c конца
    int find_k(int index)
    {
        return find_k(1, 0, size, tree[1] - index - 1);
    }

    int find_k(int v, int tl, int tr, int index)
    {
        if (tr - tl == 1)
            return tl;
        int mid = (tl + tr) >> 1;
        if (index < tree[2 * v])
        {
            return find_k(2 * v, tl, mid, index);
        }
        else
        {
            return find_k(2 * v + 1, mid, tr, index - tree[2 * v]);
        }
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
            tree[v] = tree[2 * v] + tree[2 * v + 1];
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

    //Подсчёт количства инверсий для каждого элемента перестановки
    void solve(const vector<int>& vec, vector<int>& ans)
    {
        for (int i = vec.size() - 1, g = 0; i >= 0; i--, g++)
        {
            ans[g] = find_k(vec[i]) + 1;
            update_vertex(ans[g] - 1, 0);
        }
    }


};