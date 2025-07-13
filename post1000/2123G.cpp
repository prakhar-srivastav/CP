
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

int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

void solve()
{
    int n, m, q;
    cin >> n>> m >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    vector<vector<int>> query_data;
    map<int, int> topg;
    for(int i=0;i<q;i++)
    {
        int t;
        cin >> t;
        vector<int> data{t};
        if(t==1)
            {
                int x,y;
                cin >> x >> y;
                data.push_back(x);
                data.push_back(y);
            }
        else
            {
                int x;
                cin >> x;
                x = gcd(x, m);
                data.push_back(x);
                topg[x]=0;
            }
        query_data.push_back(data);
    }
    for(auto& item : topg)
    {
        int x = item.first;
        // cout << x << " ";
        for(int i=0;i<n-1;i++)
        {
            if(a[i] % x > a[i+1] % x)
            {
                item.second++;
            }
        }
        // cout << item.first << " " << item.second << endl;
    }
    // cout << endl;
    // auto print = [](const vector<int>& item)
    // {
    //     for(auto& x : item)
    //         cout << x << " ";
    //     cout << endl;
    // };
   
    for(auto& item : query_data)
    {

        if(item[0]==1)
        {
            int x = item[1] - 1;
            int y = item[2];
            for(auto& topg_item : topg)
            {
                if(x > 0 and a[x-1] % topg_item.first > a[x] % topg_item.first)
                    {
                        topg_item.second--;
                    }
                if(x < n -1 and a[x] % topg_item.first > a[x+1] % topg_item.first)
                    {
                        topg_item.second--;
                    }
                
                if(x > 0 and a[x-1] % topg_item.first > y % topg_item.first)
                    {
                        topg_item.second++;
                    }
                if(x < n -1 and y % topg_item.first > a[x+1] % topg_item.first)
                    {
                        topg_item.second++;
                    }
                // cout << topg_item.first << " " << topg_item.second << endl;
            }
            a[x] = y;
        }
        else
        {
            int x = item[1];
            int level = m/x;
            int cur = topg[x];
            cout << (cur<level?"YES":"NO")<< endl;
        }
    }
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