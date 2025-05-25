
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


vector<pair<int,int>> perform_swaps(vector<pair<int,int>> item)
{
    map<int,pair<int,int>> m;
    for(int i=0;i<si(item);i++)
        m[i] = item[i];
    set<int> cand;
    for(int i=0;i<si(item)-1;i++)
    {
        if(item[i].first == 1 and item[i+1].first == 0 and (item[i].second%2==0 or item[i+1].second%2==0))
            cand.insert(i);
    }

    while(!cand.empty())
    {
        int x = *cand.begin();
        cand.erase(x);
        vector<int> tbd;
        auto it = m.find(x);
        int i = x;
        auto next_it = next(it);
        int j = next_it->first;
        swap(m[i],m[j]);
        if(it!=m.begin())
            {
                auto prev_it = prev(it);
                tbd.pb(i);
                m[prev_it->first].second += m[i].second;
                if(prev_it != m.begin())
                    {
                        auto prev_prev_it = prev(prev_it);
                        if(cand.find(prev_prev_it->first)!=cand.end())
                            cand.erase(prev_prev_it->first);
                        if(prev_prev_it->second.second%2==0 or prev_it->second.second%2==0)
                            cand.insert(prev_prev_it->first);
                    }
            }
        if(next(next_it)!=m.end())
            {
                auto next_next_it = next(next_it);
                tbd.pb(next_next_it->first);
                m[j].second += next_next_it->second.second;
                if(next(next_next_it) != m.end())
                    {
                        auto next_next_next_it = next(next_next_it);
                        if(cand.find(next_next_it->first)!=cand.end())
                            cand.erase(next_next_it->first);
                        if(next_next_next_it->second.second%2==0 or next_it->second.second%2==0)
                            cand.insert(next_it->first);
                    }
            } 
        for(auto item : tbd)
            m.erase(item);
        
    }
    item.clear();
    for(auto itr:m)
        item.pb(itr.ss);
    return item;
}

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
    auto get_invcount = [&](string s)
    {
        long long invcount = 0;
        long long sum = 0;
        for(char ch : s)
            if(ch == '1')   sum++;
            else invcount += sum;
        return invcount;
    };
    long long invcount = get_invcount(s);

    vector<pair<int,int>> item;
    for(int i=0;i<n;)
    {
        int j = i;
        while(i<n and s[j] == s[i])
            i++;
        item.push_back({s[j]-'0',i-j});
    }
    
    item = perform_swaps(item);

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
       {
            int block_size = 0;
            int l=0;
            int r=si(item)-1;
            if(item[l].first == 0) l++;
            if(item[r].first == 1) r--;
            block_size = r-l+1;
            // cout << "blocksize : " << block_size << endl;
            cout <<  invcount/2 + block_size/8 - (block_size%8==0?1:0) + 1 << endl;
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



    int t; cin >> t; while (t--)
    solve();

}


