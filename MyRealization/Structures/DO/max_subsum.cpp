//Сумма на максимальном подотрезке
class SegmentTree
{
private:
    struct node
    {
        long long seg, pref, suf, sum;
    };
    vector<node> tree;
    int size;
public:
    node merge(node a, node b)
    {
        return {
            max(max(a.seg,b.seg),a.suf + b.pref),
            max(a.pref,a.sum + b.pref),
            max(b.suf,b.sum + a.suf),
            a.sum + b.sum };
    }

    node one_element(int x)
    {
        return  {
            max(x,0),
            max(x,0),
            max(x,0),
            x
        };
    }

    const node ZERO = { 0,0,0,0 };

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
            tree[v] = one_element(a[l]);
            return;
        }
        int mid = (l + r) / 2;
        build(a, 2 * v, l, mid);
        build(a, 2 * v + 1, mid, r);
        tree[v] = merge(tree[2 * v], tree[2 * v + 1]);
    }


    //Обновление вершины
    void update_vertex(int pos, int value) {
        update_vertex(1, 0, size, pos, value);
    }

    void update_vertex(int v, int tl, int tr, int pos, int value) {
        if (tr - tl == 1)
            tree[v] = one_element(value);
        else {
            int mid = (tr + tl) / 2;
            if (pos < mid)
                update_vertex(v * 2, tl, mid, pos, value);
            else
                update_vertex(v * 2 + 1, mid, tr, pos, value);
            tree[v] = merge(tree[2 * v], tree[2 * v + 1]);
        }
    }

    //Ответ
    long long get_seg()
    {
        return tree[1].seg;
    }

    //Вывод
    void print()
    {
        cout << "size " << size << '\n';
        for (int i = 0; i < tree.size(); i++)
            cout << tree[i].sum << ' ';
        cout << '\n';
    }
};