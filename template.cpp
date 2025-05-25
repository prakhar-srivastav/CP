
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

#include<set>
using namespace std;
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


void solve()
{
 
    int n;
    cin>>n;
    string s;
    cin >> s;
    long long ans=0;
    for(int i=0;i<n;i++)
    {
       if(s[i] == 'P')
            s[i] = '1';
        else 
            s[i] = '0';
    }
    if(s == string(n,'0') or s == string(n,'1'))
        {
            cout << 0 << endl;
            return;
        }
    long long invcount = 0;
    long long sum = 0;
    for(char ch : s)
        if(ch == '1')   sum++;
        else invcount += sum;
    
    vector<pair<int,int>> item; 
    for(int i=0;i<n;)
    {
        int j = i;
        while(j<n and s[i] == s[j])
            i++;
        item.pb({s[j]-'0',i-j});
    }
    while(true)
    {
        auto norm = [&](vector<pair<int,int>> x)
        {
            vector<pair<int,int>> nx;
            for(auto item : x)
                {
                    if(nx.empty())
                        nx.pb(item);
                    else if(nx.back().first == item.first)
                        nx[si(nx)-1].second += item.second;
                    else
                        nx.pb(item);
                }
            return nx;
        };
        bool ok = false;
        for(int i=0;i<si(item)-1;i++)
            {
                if(item[i].first == 1 and (item[i].second%2==0 or item[i+1].second%2==0))
                    {
                        swap(item[i],item[i+1]);
                        ok =  true;
                        break;
                    }
            }
        if(!ok)
            break;
        item = norm(item);
    }
    auto already_sorted = [&](vector<pair<int,int>> item) -> bool
        {
            for(int i=1;i<si(item);i++)
                {
                    if(item[i].first == 0 and item[i-1].first == 1)
                        return false;
                };
            return true;
        };
    if(already_sorted(item))
        cout << invcount/2 << endl;
    else
        cout << invcount/2 + 1  << endl;

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

