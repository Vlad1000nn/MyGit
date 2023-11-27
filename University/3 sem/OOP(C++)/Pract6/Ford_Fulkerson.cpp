#include <bits/stdc++.h>

// BFS for Ford Fulcerson algo(return true if we find the path from s to t and change path, false if there's no way from s to t)
bool bfs(std::vector<std::vector<int>>& rNetwork, int s, int t, std::vector<int>& path)
{
    const int n = (int)rNetwork.size();
	std::vector<bool> visited(n);

	std::queue<int> q;
	q.push(s);

	visited[s] = 1;
	path[s] = -1;

	while (!q.empty()) 
    {
		int curr = q.front();
		q.pop();

		for (int i = 0; i < n; ++i) 
        {
			if (!visited[i] && rNetwork[curr][i] > 0) 
            {
				if (i == t) 
                {
					path[i] = curr;
					return true;
				}
				q.push(i);
				path[i] = curr;
				visited[i] = 1;
			}
		}
	}

	return false;
}

// Algorithm of Ford Fulkerson (searching max-flow form s to t)
int Ford_Fulkerson(std::vector<std::vector<int>>& graph, int s, int t)
{
    const int n = (int)graph.size();
	int ans{};

	std::vector<std::vector<int>> rNetwork = graph; 
	std::vector<int> path(n); 

    int curr_flow, i, j;
	while (bfs(rNetwork, s, t, path)) 
    {
		curr_flow = INT_MAX;
		for (i = t; i != s; i = path[i]) 
        {
			j = path[i];
			curr_flow = std::min(curr_flow, rNetwork[j][i]);
		}

		for (i = t; i != s; i = path[i])
         {
			j = path[i];
			rNetwork[j][i] -= curr_flow;
			rNetwork[i][j] += curr_flow;
		}

		ans += curr_flow;
	}

	return ans;
}


int main()
{
    std::vector<std::vector<int>> graph =
    {
    { 0, 6, 1, 9, 4, 4, 2, 3, 5 },
    { 6, 0, 2, 2, 4, 0, 5, 5, 0 },
    { 1, 2, 0, 1, 6, 9, 4, 6, 3 },
    { 9, 2, 1, 0, 1, 9, 9, 4, 3 },
    { 4, 4, 6, 1, 0, 2, 8, 3, 1 },
    { 4, 0, 9, 9, 2, 0, 9, 1, 2 },
    { 2, 5, 4, 9, 8, 9, 0, 8, 8 },
    { 3, 5, 6, 4, 3, 1, 8, 0, 9 },
    { 5, 0, 3, 3, 1, 2, 8, 9, 0 }
    };

	std::cout << "Maxflow is " << Ford_Fulkerson(graph, 0, 8);

	return 0;
}
