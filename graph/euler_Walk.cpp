vector<int> eulerwalk(vector<vector<pair<int, int>>>& g, int m, int src = 0)
{
	int n = int(g.size());
	vector<int> deg(n), its(n), vis(m), res;
	stack<int> s;
	s.push(src);
	deg[src]++; // to allow for euler path as well  
	while (!s.empty())
	{
		int x = s.top();
		int& i = its[x];
		if (i == int(g[x].size()))
		{
			res.push_back(x);
			s.pop();
			continue;
		}
		int a, b;
		tie(a, b) = g[x][i++];

		if (vis[b] == 0)
		{
			vis[b] = 1;
			deg[x]--;
			deg[a]++;
			s.push(a);
		}
	}

	for (auto x : deg)
	{
		if (x < 0 || res.size() != m + 1) return {}; 

	}
	reverse(res.begin(), res.end()); 
	return res;
	}