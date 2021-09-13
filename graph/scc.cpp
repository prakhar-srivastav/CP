struct scc_graph {


private:
	int _n;
	vector<int> vis, low, time, ids;
	int now_time, group_num;
	vector<vector<int> > g;


	void dfs(int v)
	{
		low[v] = time[v] = now_time++;
		vis.push_back(v);
		for (auto x : g[v])
		{
			if (time[x] == -1)
			{
				dfs(x);
				low[v] = min(low[v], low[x]);
			}
			else low[v] = min(low[v], time[x]);
		}

		if (low[v] == time[v])
		{
			while (1)
			{
				int u = vis.back();
				vis.pop_back();
				time[u] = _n;
				ids[u] = group_num;
				if (v == u) break;
			}
			group_num++;
		}

	}

public:
	scc_graph(int n) : _n(n), g(n) {}
	scc_graph(vector<vector<int>>& graph) : _n(int(graph.size())), g(int(graph.size()))
	{
		for (int i = 0; i < g.size(); i++)
		{
			g[i] = graph[i];
		}
	}



	int num_vertices()
	{
		return _n;
	}
	void add_edge(int from, int to)
	{
		g[from].push_back(to);
	}

	pair<int, vector<int> > scc_ids()
	{

		now_time = 0, group_num = 0;
		vis.clear();
		ids.clear();
		time.clear();
		low.clear();
		vis.reserve(_n);
		time.resize(_n, -1);
		low.resize(_n);
		ids.resize(_n);
		for (int i = 0; i < _n; ++i)
		{
			if (time[i] == -1)
			{
				dfs(i);
			}
		}

		for (auto& x : ids)
		{
			x = group_num - x - 1;
		}
		return { group_num,ids };
	};

	vector<vector<int>> scc()
	{
		auto ids = scc_ids();
		int group_num = ids.first;
		vector<vector<int>> groups(group_num, vector<int>{});
		for (int i = 0; i < _n; ++i)
		{
			groups[ids.second[i]].push_back(i);
		}
		return groups;
	}

	pair< vector<set<int>> , vector<vector<int>> > condensed_graph()
	{
		auto temp = scc();
		vector<set<int>> new_g((int)(temp.size()));
		unordered_map<int,int>m;
		for (int i = 0; i < temp.size(); i++)
		{
			for (ll j = 0; j < temp[i].size(); j++)
			{
				m[temp[i][j]] = i;
			}
		}
		for (int i = 0; i < g.size(); i++)
		{
			for (int j = 0; j < g[i].size(); j++)
			{
				if (m[i] == m[g[i][j]]) continue;
				new_g[m[i]].insert(m[g[i][j]]);
			}
		}
		return { new_g,temp };
	}

};
