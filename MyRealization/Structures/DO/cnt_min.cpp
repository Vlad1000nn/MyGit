class SegmentTree
{
private:

    struct node {
        int mins;
        int count;
    };

    vector<node> tree;
    int size;
public:

    const node ZERO = { INT_MAX,0 };

    //Слияние детей
    node combine(node a, node b)
    {
        if (a.mins < b.mins)
            return a;
        else if (a.mins > b.mins)
            return b;
        else
            return{ a.mins, a.count + b.count };
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
            tree[v] = { a[l],1 };
            return;
        }
        int mid = (l + r) / 2;
        build(a, 2 * v, l, mid);
        build(a, 2 * v + 1, mid, r);
        tree[v] = combine(tree[2 * v], tree[2 * v + 1]);
    }

    //Подсчёт количества минимумов
    node minimum_count(int l, int r) {
        return minimum_count(1, 0, size, l, r);
    }

    node minimum_count(int v, int tl, int tr, int l, int r)
    {
        if (tl >= r || tr <= l)
            return ZERO;

        if (tl >= l && tr <= r)
            return tree[v];
        int mid = (tr + tl) / 2;
        return combine(minimum_count(2 * v, tl, mid, l, r), minimum_count(2 * v + 1, mid, tr, l, r));
    }


    //Обновление вершины
    void update_vertex(int pos, int value) {
        update_vertex(1, 0, size, pos, value);
    }

    void update_vertex(int v, int tl, int tr, int pos, int value) {
        if (tr - tl == 1)
            tree[v] = { value,1 };
        else {
            int mid = (tr + tl) / 2;
            if (pos < mid)
                update_vertex(v * 2, tl, mid, pos, value);
            else
                update_vertex(v * 2 + 1, mid, tr, pos, value);
            tree[v] = combine(tree[2 * v], tree[2 * v + 1]);
        }
    }

    //Вывод
    void print()
    {
        cout << "size " << size << '\n';
        for (int i = 0; i < tree.size(); i++)
            cout << tree[i].mins << ' ' << tree[i].count << '\n';
        cout << '\n';
    }
};

