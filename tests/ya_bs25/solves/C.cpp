#include <bits/stdc++.h>

using namespace std;

using vi = vector<int>;

template<typename T>
std::istream& operator>>(std::istream& in, vector<T>& vec)
{
    for (auto& it : vec)
        in >> it;
    return in;
}

/*
    Посмотрим, какие числа отсутсвуют в В и в С. Эти числа необходимо удалить из А (поскольку если все есть, то нам ничего 
    и не надо убирать). Будем работать по принципу очереди: достали элемент из очереди, удалили столбец где A с этим элементом.
    Пусть мы удалили a,b,c тогда проверим, не пропали ли  b,c элементы навсегда, если да то добавляем в очередь
    В конечном итоге останется ответ(ну точнее ответ мы получим считая сколько мы удалили). 

    Насчёт повторов переживать не стоит, они автоматически пропадут(можно доказать)
*/

void solve()
{
    int n; cin >> n;
    vi A(n), B(n), C(n); cin >> A >> B >> C;
    map<int, int> B_cnt, C_cnt;
    for (auto& it : B)
        B_cnt[it]++;
    for (auto& it : C)
        C_cnt[it]++;

    map<int, int> indexes;  
    for (int i = 0; i < n; ++i)
        indexes[A[i]] = i;
    int answ{};

    queue<int> need;
    for (int i = 1; i <= n; ++i)
        if (B_cnt.find(i) == B_cnt.end() || C_cnt.find(i) == C_cnt.end())
            need.push(i);
    
    vi visit(n);
    while (!need.empty())
    {
        auto next = need.front();
        need.pop();
        int remove = indexes[next];
        if (visit[remove])
            continue;
        visit[remove] = 1;
        ++answ;
        B_cnt[B[remove]]--;
        C_cnt[C[remove]]--;
        if (B_cnt[B[remove]] == 0)
            need.push(B[remove]);

        if (C_cnt[C[remove]] == 0)
            need.push(C[remove]);

        if (B_cnt[A[remove]] == 0 || C_cnt[A[remove]] == 0)
            need.push(A[remove]);
    }

    cout << '\n'<< answ << '\n';

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
