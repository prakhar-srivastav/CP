
//#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector")

#ifndef STDC_PLUS_PLUS_H
#define STDC_PLUS_PLUS_H

// Standard I/O
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cstdio>

// Containers
#include <vector>
#include <list>
#include <deque>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <array>

// Strings
#include <string>
#include <cstring>

// Algorithms
#include <algorithm>
#include <numeric>
#include <functional>
#include <iterator>

// Math
#include <cmath>
#include <climits>
#include <cfloat>
#include <cstdlib>
#include <random>

// Utilities
#include <utility>
#include <tuple>
#include <bitset>
#include <chrono>

// C standard library
#include <cassert>
#include <ctime>

using namespace std;

#endif

#define ll long long
#define endl '\n'
#define pb push_back
#define ff first
#define ss second




#define si(x) int(x.size())
#define sum_all(a)     ( accumulate ((a).begin(), (a).end(), 0ll))
#define mine(a)    (*min_element((a).begin(), (a).end()))
#define maxe(a)    (*max_element((a).begin(), (a).end()))
#define mini(a)    ( min_element((a).begin(), (a).end()) - (a).begin())
#define maxi(a)    ( max_element((a).begin(), (a).end()) - (a).begin())

#define PII pair<int,int>
#define NO 0
#define YES 1

const int mod = 998244353;
const int MAXSCORE = 20;
int n;
int dp[104][104][12][12];
int add(int a, int b)
{
    a += b;
    if(a >= mod) a -= mod;
    return a;
}

int mul(int a, int b)
{
    return (a * 1LL * b) % mod;
}

vector<vector<int>> binom(104, vector<int>(104, 0));
void init()
{
        for (int i = 0; i <= 103; ++i) {
        binom[i][0] = 1;
        for (int j = 1; j <= i; ++j) {
            binom[i][j] = add(binom[i-1][j-1], binom[i-1][j]);
        }
    }
}

int calcdp(int l, int r, int ls, int rs, vector<int> &s)
{
        int ans = 0;
        auto make_change = [&](int x) -> int
        {
            if(x == MAXSCORE) return MAXSCORE;
            return x - 1;
        };
        auto isok = [&](int x) -> bool
        {
            return (x == 0 or x == MAXSCORE);
        };
        if(l > r)
        {
            if(isok(ls) and isok(rs))
                return 1;
            return 0;
        }
        if(dp[l][r][ls][rs] != -1) return dp[l][r][ls][rs];
        for(int i=l;i<=r;i++)
        {
            int side = (i-l<=r-i)?0:1;
            if(l==0 and r!=n-1) side = 1;
            if(l!=0 and r==n-1) side = 0;
            int left = i-l;
            int right = r-i;
            int binomvalue = binom[left+right][left];
            if(s[i] == MAXSCORE)
                {
                    if(side == 0 and ls > 0)
                        {
                            ans = add(ans, mul(mul(calcdp(l,i-1,make_change(ls),s[i],s), calcdp(i+1,r,s[i],rs,s)), binomvalue));
                        }
                    if(side == 1 and rs > 0)
                        {
                            ans = add(ans, mul(mul(calcdp(l,i-1,ls,s[i],s), calcdp(i+1,r,s[i],make_change(rs),s)), binomvalue));
                        }
                }
            else
                {
                   for(int scoreleft =0;scoreleft<=s[i];scoreleft++)
                   {
                       int scoreright = s[i]-scoreleft;
                       if(side == 0 and ls > 0)
                        {
                            ans = add(ans, mul(mul(calcdp(l,i-1,make_change(ls),scoreleft,s), calcdp(i+1,r,scoreright,rs,s)), binomvalue));
                        }
                       if(side == 1 and rs > 0)
                        ans = add(ans, mul(mul(calcdp(l,i-1,ls,scoreleft,s), calcdp(i+1,r,scoreright,make_change(rs),s)), binomvalue)); 
                   }
                }
        }
        dp[l][r][ls][rs] = ans;
        return ans;
    }




void solve()
{   
    cin >> n;
    vector<int> s(n);
    for(int i=0;i<n;i++)
        cin >> s[i];
    if(maxe(s) >= MAXSCORE)
    {
        cout << 0 << endl;
        return;
    }
    for(int i=0;i<n;i++)
        {
            if(s[i] == -1)
                s[i] = MAXSCORE;
        }
    for(int i=0;i<=n;i++)
        for(int j=0;j<=n;j++)
            for(int k=0;k<=MAXSCORE;k++)
                for(int l=0;l<=MAXSCORE;l++)
                    dp[i][j][k][l] = -1;
    cout << calcdp(0,n-1,MAXSCORE, MAXSCORE, s) << endl;
}


signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif

    init();

    int t; cin >> t; while (t--)
    solve();

}


