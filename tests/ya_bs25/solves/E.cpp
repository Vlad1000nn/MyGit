#include <bits/stdc++.h>

#define isz(x) (int)x.size()

using namespace std;

using ll = long long;

template<typename T>
std::istream& operator>>(std::istream& in, vector<T>& vec)
{
    for (auto& it : vec)
        in >> it;
    return in;
}

struct Node
{
    int symbol;
    ll cnt;
    map<int, Node*> child;

    Node(int symbol = 0)
        : symbol(symbol)
        , cnt (0)
    {  }

    Node* add(int symbol) {
        if (child.find(symbol) == child.end())
            child[symbol] = new Node(symbol);
        return child[symbol];
    }

};

ll get_tree(const string& pattern, Node* root)
{
    Node* curr = root;
    ll answ{};
    for (auto& symb : pattern)
    {
        if (curr->child.find(symb) != curr->child.end()) {
            curr = curr->child[symb];
            answ += curr->cnt;
        }
        else
            break;
    }
    return answ;
}

void build_tree(const vector<string>& input, Node* root, map<string, ll>& precalc)
{
    int before{1};
    for (auto& it : input)
    {
        Node* curr = root;
        precalc[it] = get_tree(it, root) + isz(it) + before;
        for (auto& symb : it)
        {
            curr = curr->add(symb);
            curr->cnt++;
        }
        before++;
    }
}

void print_tree(Node* node, const string& prefix = "") {
    if (!node) return;

    cout << prefix << ' '<<char(node->symbol) << " = " << node->cnt << '\n';
    for (auto& it : node->child)
        print_tree(it.second, prefix + "->" + char(it.first));
}

/*
    Давайте разобьём входные слова s на 2 категории: 1) Уже есть в БД 2) Нет в БД
    Для решения задачи напишем структуру-дерево. Каждая вершина -> символ. Проход по дереву = собрать префикс
    Так же в каждой вершине храним число, количество слов, у которых префикс как у прохода до текущей вершины. Например:
    abc ab b построит такое дерево:
    root -> a (2)
    root -> b (1)
    root -> a -> b (2)
    root -> a -> b -> c(1)

    Как будем давать ответ? Будем проходить по дереву и прибавлять все count в вершинах. Итоговый ответ + N
    Например, слово abcd:
    2 + 2 + 1 + 3 = 8. Дейстивтельно, 4 шага для abc, 3 шага для ab, 1 шаг для b

    Что делать со словами, которые уже в БД? В процессе построения дерева сразу предпосчитаем(т.е. перед добавлением
    слова в дерево) сколько нужно для того, чтобы дать им ответ (храним в map), и ответ даём как map[s]

*/

void solve()
{
    int n, q; cin >> n;
    vector<string> input(n); cin >> input;
    map<string, ll> precalc;
    Node root(' ');
    build_tree(input, &root, precalc);
    //print_tree(&root);

    cin >> q;
    while (q--)
    {
        string s; cin >> s;
        if (precalc.find(s) != precalc.end())
            cout << precalc[s] << '\n';
        else 
            cout << get_tree(s, &root) + n << '\n';
    }

}


int32_t main()
{
    cin.tie(0);
    std::ios_base::sync_with_stdio(false);

    int32_t t{ 1};

    while (t--) {
        solve();
    }

    return 0;
}
