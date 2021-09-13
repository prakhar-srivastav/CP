template<class S,
    S(*op)(S, S),
    S(*e)()>
    struct segtree {
 
    private:
        int s, _n;
        vector<S> st;
        
        void construct(int pos, int l, int r, vector<S>& ind)
        {
 
            if (l == r)
            {
                st[pos] = ind[l];
                return;
            }
            int mid = (l + r) / 2;
            construct(pos * 2 + 1, l, mid, ind);
            construct(pos * 2 + 2, mid + 1, r, ind);
            st[pos] = op(st[pos * 2 + 1], st[pos * 2 + 2]);
        }
        
        void update(int i, int j, int l, int r, S val, int pos)
        {
            if (l > r || l > j || r < i)
                return;
 
            if (l == r)
            {
                st[pos] = val;
                return;
            }
 
 
            int mid = (l + r) / 2;
            update(i, j, l, mid, val, 2 * pos + 1);
            update(i, j, mid + 1, r, val, 2 * pos + 2);
            st[pos] = op(st[pos * 2 + 1], st[pos * 2 + 2]);
        }
        S query(int i, int j, int l, int r, int pos)
        {
            
 
            if (l > r || l > j || r < i)
                return e();
            if (i <= l && j >= r)
                return st[pos];
            int mid = (l + r) / 2;
            return  op(query(i, j, l, mid, pos * 2 + 1), query(i, j, mid + 1, r, pos * 2 + 2));
 
        }

        /*
        * bs() will function as follows:-
        * For a range (l,r)
        * we will consider following terms:
        * op(l,l), op(l,l+1), op(l,l+2).... op(l,l+r)
        * [True,True,False,False...False]
        * It will then return the index on which first false value occurs
        */
        void bs(int i, int j, int l, int r, int pos, bool(*fun)(S) ,int &ans)
        {
            assert(l >= 0 && l < _n);
            assert(r >= 0 && r < _n);
            assert(r >= l);
            
            if (l > r || l > j || r < i)
                return;
            
            if (l == r)
            {
                if (fun(st[pos]) == false)
                    ans = min(ans, r);
                return;
            }
 
            if (i<=l && j>=r)
            {
                if (fun(st[pos]) == false)
                {
                    ans = min(ans, r);
                    
                    int mid = (l + r) / 2;
                    if(fun(st[pos*2+1])==false) bs(i, j, l, mid,  2 * pos + 1,fun,ans);
                    else if(fun(st[pos*2+2])==false) bs(i, j, mid + 1, r, 2 * pos + 2,fun,ans);
                    
                }
                return;
            }
            
            
            int mid = (l + r) / 2;
            bs(i, j, l, mid, 2 * pos + 1, fun, ans);
            bs(i, j, mid + 1, r, 2 * pos + 2, fun, ans);
            
            return;
        }

        /*
        * rbs() will function as follows:-
        * For a range (l,r)
        * we will consider following terms:
        * op(l,r), op(l+1,r), op(l+3,r).... op(r,r)
        * [False,False,True,True,True]
        * It will then return the index on which last false value occurs
        */
        void rbs(int i, int j, int l, int r, int pos, bool(*fun)(S), int& ans)
        {
            assert(l >= 0 && l < _n);
            assert(r >= 0 && r < _n);
            assert(r >= l);
 
            if (l > r || l > j || r < i)
                return;
 
            if (l == r)
            {
                if (fun(st[pos]) == false)
                    ans = max(ans, l);
                return;
            }
 
            if (i <= l && j >= r)
            {
                if (fun(st[pos]) == false)
                {
                    ans = max(ans,l);
 
                    int mid = (l + r) / 2;
                    if (fun(st[pos * 2 + 2]) == false) rbs(i, j, l, mid, 2 * pos + 2, fun, ans);
                    else if(fun(st[pos * 2 + 1]) == false) rbs(i, j, mid + 1, r, 2 * pos + 1, fun, ans);
 
                }
                return;
            }
 
 
            int mid = (l + r) / 2;
            rbs(i, j, mid + 1, r, 2 * pos + 2, fun, ans);
            rbs(i, j, l, mid, 2 * pos + 1, fun, ans);
            
 
            return;
        }
    public:
        segtree() :segtree(0) {}
        segtree(int n) : segtree(vector<S>(n, e())) {}
        segtree(vector<S>& v) : _n(int(v.size())) {
            assert(_n > 0);
            int s = ceil(log2(_n));
            s = pow(2, s + 1) - 1;
            st.clear();
            st.resize(s, e());
            construct(0, 0, _n - 1, v);
        }
        void set(int i, S val)
        {
            assert(i >= 0 && i < _n);
            update(i, i, 0, _n - 1, val, 0);
        }
        
        S query(int i)
        {
            assert(i >= 0 && i < _n);
            return query(i, i, 0, _n - 1, 0);
        }
        S query(int i, int j)
        {
            assert(i >= 0 && i < _n);
            assert(i <= j && j >= 0 && j < _n);
            return query(i, j, 0, _n - 1, 0);
        }
        template<bool (*fun)(S)>int bs(int l, int r)
        {
            assert(l >= 0 && l < _n);
            assert(r >= l && r >= 0 && r < _n);
            assert(fun(e()) == true);
            int ans = r + 1;
            bs(l, r, 0, _n - 1,0 ,fun,ans);
            return ans; 
        }
        template<bool (*fun)(S)>int rbs(int l, int r)
        {
            assert(l >= 0 && l < _n);
            assert(r >= l && r >= 0 && r < _n);
            assert(fun(e()) == true);
            int ans = l-1;
            rbs(l, r, 0, _n - 1, 0, fun, ans);
            return ans;
        }
 
};
struct S
{
    ll a;
};
S op(S a, S b)
{
    return S{min(a.a,b.a)};
}
S e()
{
    return S{numeric_limits<ll>max()};
}
