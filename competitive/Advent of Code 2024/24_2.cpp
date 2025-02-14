

void dfs(map<string, string>& l, map<string, string>& r, map<string, string>& op, map<string, bool>& values, const string& curr)
{
    if (l[curr] == curr)
        return;

    //cout << curr << " -> " << l[curr] << '\n';
    dfs(l, r, op, values, l[curr]);
    //cout << curr << " -> " << r[curr] << '\n';
    dfs(l, r, op, values, r[curr]);


    if (op[curr][0] == 'X')
        values[curr] = values[l[curr]] ^ values[r[curr]];
    else if (op[curr][0] == 'A')
        values[curr] = values[l[curr]] & values[r[curr]];
    else if (op[curr][0] == 'O')
        values[curr] = values[l[curr]] | values[r[curr]];
    else
        cout << "DFS ERROR";
}


void check_dfs(map<string, string>& l, map<string, string>& r, map<string, string>& op, const string& curr, vector<string>& need)
{
    if (l[curr] == curr)
        return;

    check_dfs(l, r, op, l[curr], need);
    check_dfs(l, r, op, r[curr], need);

    need.push_back(l[curr]);
    need.push_back(r[curr]);
}

bool is_path(map<string, string>& l, map<string, string>& r, map<string, string>& op, const string& curr, string& need)
{
    if (l[curr] == curr)
        return 0;

    if (curr == need)
        return 1;
    return is_path(l, r, op, l[curr], need) || is_path(l, r, op, r[curr], need);
}


void solve()
{
    std::ifstream fin("input.txt");
    std::string line;

    // У нас есть дерево, круто
    std::map<std::string, bool> vertex_value;
    char str1[3];
    char str2[3];
    char str3[3];
    char str4[3];
    bitset<64> answ_x = 0, answ_y = 0;

    // Будем строить дерево снизу вверх, рекурсивно
    std::map<std::string, std::string> l, r, op;


    while (getline(fin, line))
    {
        if (!isz(line))
            break;
        int x;
        sscanf_s(line.c_str(), "%3s: %d", &str1, 4, &x);
        vertex_value[str1] = x;
        l[str1] = str1;
    }

    for (auto& [key, val] : vertex_value)
    {
        if (key[0] == 'x')
            answ_x[stoi(key.substr(1, 2))] = val;
        if (key[0] == 'y')
            answ_y[stoi(key.substr(1, 2))] = val;

    }

    while (getline(fin, line))
    {
        sscanf_s(line.c_str(), "%3s %3s %3s -> %3s", &str1, 4, &str2, 4, &str3, 4, &str4, 4);
        l[str4] = str1;
        r[str4] = str3;
        op[str4] = str2;
    }

    // Выяснили проблему, поставив единичку только в 1 бит
   // 11 12
   // 17 18
   // 26 27
   // 39 40

   // Теперь будем перебирать все пары, а потом все пары вершин
    const vector<int> need_to_fix = { 11,12,17,18,26,27,39,40 };
    vector<vector<string>> vertexes_to_swap(isz(need_to_fix));
    int index{};
    for (auto& [key, val] : l)
    {
        if (index >= 8 || (key[0] != 'z' || stoi(key.substr(1, 2)) != need_to_fix[index]))
            continue;

        check_dfs(l, r, op, key, vertexes_to_swap[index]);

        ++index;
    }

    map<string, string> l_change, r_change, op_change;
    map<string, bool> vertex_value_change;
    string buff; // 
    bitset<64> answ_change = 0;

    /* 11-12
        bng gjc
        bng dnj
        fsw gjc
        fsw dnj
        qjj gjc
        qjj dnj
        jdm gjc
        jdm dnj
    */

    /* 17-18
        pqv rqq
        pqv vfq
        pqv wmp
        ffg vfq
        ffg wmp
    */

    /* 26-27
        
    */

    /* 39-40
        
    */


    for (auto& change1 : vertexes_to_swap[6])
    {
        l_change.clear();
        r_change.clear();
        op_change.clear();
        vertex_value_change.clear();

        l_change = l;
        r_change = r;
        op_change = op;
        vertex_value_change = vertex_value;

        for(auto& change2 : vertexes_to_swap[7])
        {
            if (l[change1] == change1 || l[change2] == change2)
                continue;
            if (is_path(l_change, r_change, op_change, change2, change1) || is_path(l_change, r_change, op_change, change1, change2))
                continue;
            
            //cout << "NEW:" << change1 << ' ' << change2 << '\n';
            swap(l_change[change1], l_change[change2]);
            swap(r_change[change1], r_change[change2]);
            swap(op_change[change1], op_change[change2]);

            answ_change = 0;
            for (auto& [key, val] : l_change)
            {
                if (key[0] != 'z')
                    continue;

                dfs(l_change, r_change, op_change, vertex_value_change, key);
                answ_change[stoi(key.substr(1, 2))] = vertex_value_change[key];
            }
            if (answ_change == answ_x)
            {
                std::cout << change1 << ' ' << change2 << '\n';
            } 
        }
    }


    bitset<64> answ = 0;
    for (auto& [key, val] : l)
    {
        if (key[0] != 'z')
            continue;

        dfs(l, r, op, vertex_value, key);
        answ[stoi(key.substr(1, 2))] = vertex_value[key];
    }

    cout << answ.to_ullong() << '\n';
    cout << answ << '\n';
}