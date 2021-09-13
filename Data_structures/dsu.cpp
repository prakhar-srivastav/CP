struct dsu {
private:
	int _n;
	vector<int> arr;
	vector<int> rank;
public:
	dsu() :_n(0) {}
	dsu(int n) : _n(n)
	{
		arr.clear();
		for (int i = 0; i < _n; ++i)
			arr.push_back(i);
		rank.clear();
		rank.resize(_n,0);
	}
	int parent(int x)
	{
		if (x == arr[x]) return x;
		return(arr[x] = parent(arr[x]));
	}
	bool same(int x, int y)
	{
		return parent(x) == parent(y);
	}
	
	void join(int x, int y)
	{
		x = parent(x);
		y = parent(y);
		if (rank[x] < rank[y])
		{
			arr[x] = y;
			rank[y] += 1;
		}
		else if (rank[x] > rank[y])
		{
			arr[y] = x;
			rank[x] += 1;
		}
		else
		{
			arr[x] = y;
			rank[y] += 1;
		}
	}
	vector<vector<int>> groups()
	{
		
		int x = 0; 
		vector<int> temp(_n, -1);
		for (int i = 0; i < _n; i++)
		{
			int a = parent(i);
			if (temp[a] == -1)
				temp[a] = x++;
			
		}
		vector<vector<int>> res(x, vector<int>{});
		for (int i = 0; i < _n; i++)
		{
			
			res[temp[parent(i)]].push_back(i);
		}
		return res;
	}
};