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



    //Вывод
    void print()
    {
        cout << "size " << size << '\n';
        for (int i = 0; i < tree.size(); i++)
            cout << tree[i] << ' ';
        cout << '\n';
    }
};