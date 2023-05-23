struct segment_dsu {
private:
    int _n;
    vector<int> arr;
    vector<int> rank;
    vector<int> left;
    vector<int> right;
    vector<int> val;
public:
    segment_dsu() :_n(0) {}
    segment_dsu(int n) : _n(n)
    {
        arr.clear();
        for (int i = 0; i < _n; ++i)
            arr.push_back(i);
        rank.clear();
        rank.resize(_n, 0);
        left = vector<int>(_n);
        right = vector<int>(_n);
        for (int i = 0; i < n; i++)
        {
            left[i] = i - 1;
            right[i] = i + 1;
        }
        right[_n - 1] = -1;
    }
    void set_val_array(vector<int> _val)
    {
        val = _val;
        return;
    }
    int parent(int x)
    {
        if (x == arr[x]) return x;
        return(arr[x] = parent(arr[x]));
    }

    int get_left(int i)
    {
        int _left = left[parent(i)];
        _left = (_left!=-1?parent(_left):_left);
        return _left;
    }
    int get_right(int i)
    {
        int _right = right[parent(i)];
        _right = (_right!=-1?parent(_right):_right);
        return _right;
    }
    int get_val(int i)
    {
        return val[parent(i)];
    }
    void set_val(int i, int new_val)
    {
        val[parent(i)] = new_val;
    }
    bool same(int x, int y)
    {
        return parent(x) == parent(y);
    }
    int op(int x, int y)
    {
        x = parent(x);
        y = parent(y);
        return min(val[x],val[y]);
    }
    void join(int x, int y)
    {
        x = parent(x);
        y = parent(y);
        if (same(x, y))
            return;
        int _left = get_left(x);
        int _right = get_right(y);
        int new_val = op(x, y);
        // u -> v
        int u = (rank[x] < rank[y] ? x : y);
        int v = x ^ y ^ u;
        arr[u] = v;
        rank[v] += (rank[u] == rank[v]);
        left[v] = _left;
        right[v] = _right;
        val[v] = new_val;
        return;
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
