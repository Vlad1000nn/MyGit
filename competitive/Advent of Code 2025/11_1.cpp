#include <bits/stdc++.h>

using namespace std;

#define isz(x) (int)(x).size()
#define all(x) (x).begin(), (x).end()

void dfs(std::map<std::string, std::vector<std::string>>& graph, std::vector<std::string>& order, std::map<std::string, int>& colors, const std::string& v) {
    
    if(colors[v] == 1) {
        std::cerr << "Error, graph with cycles" << endl;
        std::exit(1);
    }
    else if(colors[v] == 2) return;

    colors[v] = 1;

    for(const auto& it : graph[v]) {
        dfs(graph, order, colors, it);
    }
    colors[v] = 2;
    order.push_back(v);
}


int main() {

    const std::string startv = "you";
    const std::string endv = "out";

    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");


    std::string line;
    std::set<std::string> vertexes;

    std::map<std::string, std::vector<std::string>> graph;

    while(std::getline(fin, line)) {

        std::vector<std::string> graph_line;
        int colon = line.find(':');
        string u = line.substr(0, colon);
        vertexes.insert(u);
        
        int start = colon + 2;
        for(int i = start; i < isz(line);++i) {
            if(line[i] == ' ') {
                graph_line.push_back(line.substr(start, i - start));
                vertexes.insert(graph_line.back());
                start = i + 1;
            }
        }
        graph_line.push_back(line.substr(start, isz(line) - start));
        vertexes.insert(graph_line.back());

        graph[u] = graph_line;
    }

    std::vector<std::string> order;
    std::map<std::string, int> colors;
    
    dfs(graph, order, colors, startv);
    reverse(all(order));
    
    std::map<std::string, int> index;
    
    for(int i = 0; i < isz(order); ++i) {
        index[order[i]] = i + 1;
    }
    
    const int n = isz(vertexes);
    const int m = isz(order);
    std::vector<int64_t> dp(n + 1);
    dp[index[startv]] = 1;
    
    cout << n << endl;
    for(int i = 0; i < m; ++i) {
        for(auto& v : graph[order[i]]) {
            int v_idx = index[v];
            int order_i_idx = index[order[i]];

            if(v_idx == 0 || order_i_idx == 0) continue;
            dp[v_idx] += dp[order_i_idx];
        }
    }

    fout << dp[index[endv]];

    fin.close();
    fout.close();

    return 0;
}