#include<vector>
#include<iostream>
#include<unordered_map>
#include<set>
#include<assert.h>
#include<algorithm>
#include<queue>
using namespace std;
 
 
 
vector<int> topo_sort(vector<vector<int>> &g)
{
 
	int n = (int)(g.size());
	vector<int> ind(n);
	for (int i = 0; i<int(g.size()); i++)
		for (auto v : g[i]) ind[v]++;
	queue<int> q;
	for (int i = 0; i < n; i++)
		if (ind[i] == 0) q.push(i);
	vector<int> res;
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		res.push_back(u);
		for (auto v : g[u])
		{
			ind[v]--;
			if (ind[v] == 0)
				q.push(v);
		}
	}
	return res;
}
 
 
 
struct scc
{
private:
	vector<vector<int>> g, tg;
	int _n, _t;
	vector<pair<int, int>> _out;
	vector<vector<int>> comp;
	vector<bool> vis;
	vector<int> cur;
public:
 
	void dfs(int r)
	{
		vis[r] = true;
		_t++;
		for (auto c : g[r])
		{
			if (vis[c])
				continue;
			dfs(c);
		}
		_out[r].first = _t++;
 
	}
	void dfs2(int r)
	{
		vis[r] = true;
		cur.push_back(r);
 
		for (auto c : tg[r])
		{
			if (vis[c])
				continue;
			dfs2(c);
		}
 
	}
	scc(vector<vector<int>> &G) :g(G)
	{
		_n = (int)(g.size());
		_t = 0;
		_out = vector<pair<int, int>>(_n);
		for (int i = 0; i < _n; i++) _out[i].second = i;
		vector<pair<int, int>> ed;
		vis = vector<bool>(_n);
		tg = vector<vector<int>>(_n);
		for (int i = 0; i < _n; i++)
			for (auto v : g[i]) ed.push_back({ v,i });
		for (auto e : ed)
			tg[e.first].push_back(e.second);
 
		for (int i = 0; i < _n; i++)
		{
			if (vis[i]) continue;
			dfs(i);
		}
		sort(_out.begin(), _out.end());
		reverse(_out.begin(), _out.end());
		vis = vector<bool>(_n);
		for (int i = 0; i < _n; i++)
		{
			int u = _out[i].second;
			if (vis[u])
				continue;
			cur.clear();
			dfs2(u);
			comp.push_back(cur);
		}
 
	}
 
	pair<vector<vector<int>>, vector<int>> scc_graph()
	{
		int N = (int)(comp.size());
		vector<vector<int>> _g(N);
		vector<int> id(_n);
		for (int i = 0; i < (int)(comp.size()); i++)
		{
			for (int j = 0; j < (int)(comp[i].size()); j++)
			{
				id[comp[i][j]] = i;
			}
		}
		for (int i = 0; i < _n; i++)
			for (auto v : g[i])
			{
				if (id[i] != id[v]) _g[id[i]].push_back(id[v]);
			}
		return { _g,id };
	}
};
 
 
 
struct two_sat
{
private:
	int _n;
	vector<vector<int>> g;
public:
	two_sat(int n) : _n(n), g(vector<vector<int>>(n*2)) {}
 
	
 
	void add_clause(int i, int ti, int j, int tj)
	{
		int a = i, b = j;
		if (ti) a += _n;
		if (!tj) b += _n;
		g[a].push_back(b);
		if (i == j and ti == tj) return;
		a = i, b = j;
		if (tj) b += _n;
		if (!ti) a += _n;
		g[b].push_back(a);
	}
	
	void at_most_one(vector<pair<int,int>> &a)
	{
		
		if ((int)a.size() <= 1) return; 
		int __n = (int)(g.size());
		g.resize(__n + (int)(a.size()) * 2);
		int _y = __n;
		int _z = __n + (int)(a.size());
		for (int i = 1; i < (int)a.size(); i++)
		{
			int y1 = i-1 + _y;
			int y2 = i + _y;
			g[y2].push_back(y1);
		}
		for (int i = 0; i < (int)a.size(); i++)
		{
			int y1 = i + _y;
			int x1;
			if (a[i].second == 2)
				x1 = a[i].first + _n;
			else
				x1 = a[i].first;
 
			g[y1].push_back(x1);
		}
		for (int i = 1; i < (int)a.size(); i++)
		{
			int y1 = i-1 + _y;
			int x1;
			if (a[i].second == 2)
				x1 = a[i].first;
			else
				x1 = a[i].first+_n;
			g[x1].push_back(y1);
		}
		for (int i = 1; i < (int)a.size(); i++)
		{
			int z1 = i-1 + _z;
			int z2 = i + _z;
			g[z1].push_back(z2);
		}
		for (int i = 0; i < (int)a.size(); i++)
		{
			int z1 = i + _z;
			int x1;
			if (a[i].second == 2)
				x1 = a[i].first + _n;
			else
				x1 = a[i].first;
			g[z1].push_back(x1);
		}
		for (int i = 1; i < (int)a.size(); i++)
		{
			int z1 = i + _z;
			int x1;
			if (a[i-1].second == 2)
				x1 = a[i - 1].first;
			else
				x1 = a[i-1].first + _n;
			g[x1].push_back(z1);
		}
	}
	pair<bool, vector<bool>> run()
	{
		scc S(g);
		auto info = S.scc_graph();
		auto _g = info.first;
		auto id = info.second;
		vector<bool> res(_n);
		for (int i = 0; i < _n; i++)
			if (id[i] == id[i + _n])
				return { false,res };
 
		auto sorted = topo_sort(_g);
		vector<int> _inv(int(_g.size()));
 
		assert(sorted.size() == _g.size());
		for (int i = 0; i < (int)_g.size(); i++)
			_inv[sorted[i]] = i;
 
		for (int i = 0; i < _n; i++)
		{
			if (_inv[i] < _inv[i + _n]) res[i] = false;
			else res[i] = true;
		}
		return { true,res };
 
	}
 
 
};
