

//#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector")
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
    return ( a == 0 ? b : gcd(b % a, a) );
}
int gcd(int a, int b, int c)
{
    return gcd(a, gcd(b, c));
}
void solve()
{
    int n = 2 * 1e5;
    
    int l, r;
    cin >> l >> r;
    ll badTriplets = 0; 
    
    vector<pair<int, int>> range;
    for(int i=1;i<=r;i++)
        for (int j = i + 1; j <= r; j++)
            {
                if (1ll * i * j > r )
                {
                    break;
                }
            else
            {
                if(gcd(i,j,i*j)>1)
                    continue;
                for (int k = i * j; k <= min(r,n); k += (i * j))
                {
                    if(k>j)
                        {
                            for(int mul =1 ;mul<=n;mul++)
                            {
                                if(mul*k>r) break;
                                if(mul*i>=l)
                                range.pb({mul*i,mul*k});
                            }
                        }
                }
            }
            }
     
    vector<pair<int, int>> adhocRange({ pair<int,int>{3,6},pair<int,int>{6,15}});
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


    for (auto x : adhocRange)
    {
        int i = x.ff;
        int k = x.ss;

        for(int mul =1 ;mul<=n;mul++)
        {
            if(mul*k>r) break;
            if(mul*i>=l)
            range.pb({mul*i,mul*k});
        }
    }
    ll tot = cnk(r - l + 1, 3);
    // cout << tot  << endl;
    cout << tot - si(range) << endl;
    
}


signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif

    int t; cin >> t; while (t--)
        solve();

}

