#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>



// 1

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
			if (!visited[i] && rNetwork[curr][i] > 0)
			{
				path[i] = curr;
				if (i == t)
					return true;

				q.push(i);
				visited[i] = 1;
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


// 2


// Function to check, can we add new vertex to cycle or not
bool check(int v, const std::vector<std::vector<int>>& graph, std::vector<int>& path, int pos)
{

	if (!graph[path[pos - 1]][v])
		return false;

	for (int i = 0; i < pos; ++i)
		if (path[i] == v)
			return false;

	return true;
}


// Recursive help-function to calculate Hamiltonian Cycle
bool hamiltonian(std::vector<std::vector<int>>& graph, std::vector<int>& path, int pos)
{
	const int n = (int)graph.size();

	if (pos == n)
		return (graph[path[pos - 1]][path[0]] == 1 ? true : false);


	for (int v = 1; v < n; ++v)
		if (check(v, graph, path, pos))
		{
			path[pos] = v;

			if (hamiltonian(graph, path, pos + 1))
				return true;

			path[pos] = -1;
		}

	return false;
}


// Return vector of vertexes in cycle
std::vector<int> hamiltonianCycle(std::vector<std::vector<int>>& graph)
{
	std::vector<int> path((int)graph.size(), -1);

	path[0] = 0;

	return (hamiltonian(graph, path, 1) ? path : std::vector<int>{});
}



// 3

// Function to color graph
std::vector<int> coloring(const std::vector<std::vector<int>>& graph)
{
	const int n = (int)graph.size();
	std::vector<int> ans(n, -1);
	std::vector<bool> colors;

	ans[0] = 0;

	for (int i = 1; i < n; ++i)
	{
		colors.assign(n, true);

		for (int j = 0; j < n; ++j)
		{
			if (graph[i][j] && ans[j] != -1)
				colors[ans[j]] = false;
		}

		int first_avaliable{};
		for (first_avaliable = 0; first_avaliable < n; ++first_avaliable)
			if (colors[first_avaliable]) break;


		ans[i] = first_avaliable;
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

	// 1
	std::cout << "Maxflow is " << Ford_Fulkerson(graph, 0, 8) << "\n\n";

	// 2
	std::vector<int> path = hamiltonianCycle(graph);

	if (!(int)path.size())
		std::cout << "Hamilton cycle is not exist!";
	else std::cout << "Hamilton cycle : ";

	for (auto& it : path)
		std::cout << it << ' ';

	std::cout << "\n\n";

	// 3
	std::vector<int> colors = coloring(graph);

	std::cout << "Vertex colors:" << std::endl;
	for (int i = 0; i < colors.size(); ++i)
		std::cout << "Vertex " << i + 1 << " --->  Color " << colors[i] << std::endl;


	return 0;
}