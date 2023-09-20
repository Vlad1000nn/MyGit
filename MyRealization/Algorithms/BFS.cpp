const int N[4][2] = {
		  {-1,0}, {0, 1}, {1,0}, {0,-1}
};

const int INF = int(1e9);

queue<int, int, int> q;
q.push({ 1,1,0 });

vvi dist(n, vi(m));



while (!q.empty())
{
	auto [row, col, currDist] = q.front();
	q.pop();

	if (field[row][col] == '#') continue;
	if (dist[row][col] <= currDist) continue;

	dist[row][col] = currDist;

	for (int i = 0; i < 4; ++i)
		q.push({ row + N[i][0], col + N[i][1], currDist + 1 });
}