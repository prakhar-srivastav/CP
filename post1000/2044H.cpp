#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector")
#include <bits/stdc++.h>
#include<set>
using namespace std;
#define int long long
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


void solve()
{
    int n;
    cin >> n;
    int q;
    cin >> q;

    vector<vector<int>> a(n,vector<int>(n, 0));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> a[i][j];
        }
    }

    vector<vector<int>> mat0(n, vector<int>(n, 0));
    vector<vector<int>> mat1(n, vector<int>(n, 0));
    vector<vector<int>> mat2(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            mat0[i][j] = a[i][j] + (i > 0 ? mat0[i - 1][j] : 0) + (j > 0 ? mat0[i][j - 1] : 0) - (i > 0 && j > 0 ? mat0[i - 1][j - 1] : 0);
            mat1[i][j] = a[i][j]*j + (i > 0 ? mat1[i - 1][j] : 0) + (j > 0 ? mat1[i][j - 1] : 0) - (i > 0 && j > 0 ? mat1[i - 1][j - 1] : 0);
            mat2[i][j] = a[i][j]*(i+1) + (i > 0 ? mat2[i - 1][j] : 0) + (j > 0 ? mat2[i][j - 1] : 0) - (i > 0 && j > 0 ? mat2[i - 1][j - 1] : 0);
        }
    }

    auto get_sum = [&](vector<vector<int>>& mat, int a, int b, int c, int d) -> int
    {
        return mat[c][d] - (b > 0 ? mat[c][b - 1] : 0) - (a > 0 ? mat[a - 1][d] : 0) + (a > 0 && b > 0 ? mat[a - 1][b - 1] : 0);
    };

    auto vertical_fix = [&](int a, int b, int c, int d) -> int
    {
        int ret = get_sum(mat2, a, b, c, d) - a * get_sum(mat0, a, b, c, d);
        return ret;
    };

    while(q--)
    {
        int a,b,c,d;
        cin >> a >> b >> c >> d;
        a--; b--; c--; d--;
        int ans = 0;
        ans = get_sum(mat1, a, b, c, d) - b * get_sum(mat0, a, b, c, d);
        ans += vertical_fix(a, b, c, d);
        if(a+1 <=c)
            ans += vertical_fix(a+1,b,c,d) * (d-b);
        cout << ans << " ";
    }
    cout << endl;
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    #ifndef ONLINE_JUDGE
        freopen("input.txt", "r", stdin);
        freopen("output.txt", "w", stdout);
    #endif
    int t;
    cin >> t;
    while(t--)
        solve();

}