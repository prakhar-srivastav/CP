
/* Dont forget to add scc template */ 
struct two_sat
{
private:
	int _n;
	vector<bool> ans;
	scc_graph scc;


public:
	two_sat() : _n(0), scc(0) {}
	two_sat(int n) : _n(n), ans(n), scc(2 * n) {}

	void add_clause(int i, bool f, int j, bool g)
	{
		assert(i >= 0 && i < _n);
		assert(j >= 0 && j <= _n);
		scc.add_edge(2 * i + (f ? 0 : 1), 2 * j + (g ? 1 : 0));
		scc.add_edge(2 * j + (g ? 0 : 1), 2 * i + (f ? 1 : 0));
	}

	bool satisfiable()
	{
		auto id = scc.scc_ids().second;
		for (int i = 0; i < _n; ++i)
		{
			if (id[2 * i] == id[2 * i + 1]) return false;
			ans[i] = id[2 * i] < id[2 * i + 1];

		}
		return true;
	}
	vector<bool> answer()
	{
		return ans;
	}
};
