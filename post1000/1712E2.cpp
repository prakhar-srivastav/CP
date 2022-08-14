
#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector")
#include <bits/stdc++.h>
#include<set>
using namespace std;
#define ll long long
#define endl '\n'
#define endl2(j,x) (j==x-1?"\n":"")
#define pb push_back
#define ff first
#define ss second




#define si(x) int(x.size())
#define sum_all(a)     ( accumulate ((a).begin(), (a).end(), 0ll))
#define mine(a)    (*min_element((a).begin(), (a).end()))
#define maxe(a)    (*max_element((a).begin(), (a).end()))
#define mini(a)    ( min_element((a).begin(), (a).end()) - (a).begin())
#define maxi(a)    ( max_element((a).begin(), (a).end()) - (a).begin())

int gcd(int a, int b)
{
    return (a == 0 ? b : gcd(b % a, a));
}
int gcd(int a, int b, int c)
{
    return gcd(a, gcd(b, c));
}
const int N = 2 * 1e5 + 1;
vector<int> range[N];
vector<int> query[N];
vector<int> ind[N];
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
        return query(r) - query(l - 1);
    }


};



void  preprocess()
{

    int n = 2 * 1e5;
    int l = 1, r = n;

   
    for (int i = 1; i <= r; i++)
        for (int j = i + 1; j <= r; j++)
        {
            if (1ll * i * j > r)
            {
                break;
            }
            else
            {
                if (gcd(i, j) > 1) continue;
                for (int k = i * j; k <= min(r, n); k += (i * j))
                {
                    if (k > j)
                    {
                        for (int mul = 1; mul <= n; mul++)
                        {
                            if (mul * k > r) break;
                            if (mul * i >= l)
                                range[mul * k].push_back(mul * i);
                        }
                    }
                }
            }
        }

    vector<pair<int, int>> adhocRange({ pair<int,int>{3,6},pair<int,int>{6,15} });
    for (auto x : adhocRange)
    {
        int i = x.ff;
        int k = x.ss;

        for (int mul = 1; mul <= n; mul++)
        {
            if (mul * k > r) break;
            if (mul * i >= l)
                range[mul * k].push_back(mul * i);
        }
    }

}
void solve()
{
    auto cnk = [&](int n, int k)
    {
        ll x = 1;
        ll y = 1;
        for (ll j = 1; j <= k; j++)
        {
            y *= j;
            x *= (n - j + 1);
        }
        return x / y;
    };

   preprocess();

    int q;
    cin >> q;

   
    for (int i = 0; i < q; i++)
    {
        int l, r;
        cin >> l >> r;
        query[r].push_back(l);
        ind[r].push_back(i);
    }

    vector<vector<int>> right(2 * 1e5 + 1);

   

    fenwick_tree<int> f(N);
    vector<ll> ans(q);
    for (int r = 1; r <= 2 * 1e5; r++)
    {
        for (auto l : range[r])
        {
            f.update(l, 1);
        }
        for (int ii=0;ii<si(query[r]);ii++)
        {
            int l = query[r][ii];
            int i = ind[r][ii];
            ans[i] = cnk(r - l + 1, 3) - f.query(l, r);
        }

    }

    for (auto a : ans)
        cout << a << '\n';
    return;
}


signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);


    solve();

}
