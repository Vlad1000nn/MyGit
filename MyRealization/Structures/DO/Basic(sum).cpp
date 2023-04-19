//Моё дерево отрезков
class SegmentTree
{
private:
    vector<long long> tree;
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


    //Запрос суммы
    long long rsq(int l, int r) {
        return rsq(1, 0, size, l, r);
    }

    long long rsq(int v, int tl, int tr, int l, int r)
    {
        if (tl >= r || tr <= l)
            return 0;

        if (tl >= l && tr <= r)
            return tree[v];
        int mid = (tr + tl) / 2;
        return rsq(2 * v, tl, mid, l, r) + rsq(2 * v + 1, mid, tr, l, r);
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
};