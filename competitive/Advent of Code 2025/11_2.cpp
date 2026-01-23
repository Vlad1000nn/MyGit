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

    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");


    std::string line;
    std::set<std::string> unique_vertexes;

    std::map<std::string, std::vector<std::string>> graph;

    while(std::getline(fin, line)) {

        std::vector<std::string> graph_line;
        int colon = line.find(':');
        string u = line.substr(0, colon);
        unique_vertexes.insert(u);
        
        int start = colon + 2;
        for(int i = start; i < isz(line);++i) {
            if(line[i] == ' ') {
                graph_line.push_back(line.substr(start, i - start));
                unique_vertexes.insert(graph_line.back());
                start = i + 1;
            }
        }
        graph_line.push_back(line.substr(start, isz(line) - start));
        unique_vertexes.insert(graph_line.back());

        graph[u] = graph_line;
    }

    const int n = isz(unique_vertexes);
    
    const std::vector<std::string> vertexes = {"svr", "dac", "fft", "out"};
    std::vector<std::vector<int64_t>> paths(4, std::vector<int64_t>(4));
    
    std::map<std::string, int> index;
    std::vector<std::string> order;
    std::map<std::string, int> colors;
    std::vector<int64_t> dp(n + 1);

    // [svr][dac] * [dac][fft] * [fft][out] +
    // [svr][fft] * [dac][fft] * [dac][out]

    for(std::string startv : {"svr", "dac", "fft"}) {
        order.clear();
        colors.clear();
        index.clear();
        dp.assign(n + 1, 0);

        dfs(graph, order, colors, startv);
        reverse(all(order));
     
        for(int i = 0; i < isz(order); ++i) {
            index[order[i]] = i + 1;
        }

        const int m = isz(order);
        dp[index[startv]] = 1;

        for(int i = 0; i < m; ++i) {
            for(auto& v : graph[order[i]]) {
                int v_idx = index[v];
                int order_i_idx = index[order[i]];
    
                if(v_idx == 0 || order_i_idx == 0) continue;
                dp[v_idx] += dp[order_i_idx];
            }
        }

        int u = find(all(vertexes), startv) - vertexes.begin();
        for(int v = 0; v < 4; ++v) {
            paths[u][v] = dp[index[vertexes[v]]];
        }
    }


    int64_t ans = paths[0][1] * paths[1][2] * paths[2][3] + paths[0][2] * paths[2][1] * paths[1][3];
    fout << ans;

    fin.close();
    fout.close();

    return 0;
}