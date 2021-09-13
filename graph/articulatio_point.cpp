struct articulation_point
{
private:
	vector<vector<int>> g; 
	vector<int> low, time;
	vector<bool> vis; 
	int timer;
	int _n;
	void dfs(int v, int p, vector<bool> &arr)
	{
		vis[v] = true;
		time[v] = low[v] = timer++; 
		int c = 0;
		for (auto x : g[v])
		{
			if (x == p) continue;
			if (vis[x] == true)
			{
				low[v] = min(low[v], time[x]);
			}
			else
			{
				dfs(x, v,arr); 
				low[v] = min(low[v], low[x]); 
				if (low[x] >= time[v] && p!= -1)
					arr[v] = true;
				++c; 
			}
		}
		if (p == -1 && c > 1)
			arr[v] = true;
	}
public:

	articulation_point(vector<vector<int>>& graph) : _n(int(graph.size())), g(int(graph.size())) {
		
		for (int i = 0; i < _n; ++i)
		{
			g[i] = graph[i]; 
		}
	}

	vector<bool> answer()
	{
		vector<bool> arr(_n,false); 
		timer = 0; 
		vis.clear();
		vis.resize(_n, false);
		time.clear();
		time.resize(_n, -1);
		low.clear();
		low.resize(_n, -1); 
		for (int i = 0; i < _n; ++i)
		{
			if (!vis[i])
				dfs(i,-1,arr); 
		}
		return arr; 
	}

};
