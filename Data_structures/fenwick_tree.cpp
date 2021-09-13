template <class T> struct fenwick_tree {
   
private:
    int _n;
    vector<T> arr;

    T query(ll x)
    {
        ll ans = 0;
        for (ll i = x; i >= 0; i = (i & (i + 1)) - 1)
        {
            ans += arr[i];
        }
        return ans;
    }
public:
    fenwick_tree() : _n(0) {}
    fenwick_tree(int n) : _n(n), arr(n) {}

    void update(ll x, T val)
    {
        ll ans = 0;

        for (ll i = x; i < arr.size(); i = (i | (i + 1)))
        {
            arr[i] += (ll)(val);
        }

    }

    T query(int l, int r) {
        return query(r) - query(l-1);
    }


};
