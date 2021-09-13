// longest path using toposort in dg.If the graph contains a cycle then it returns -1.
ll longest_path_dg(vector<vector<ll>>& g)
{
    int n = int(g.size());
    vector<int> ind(n, 0);
    vector<bool> vis(n, false);
    for (auto v : g)
    {
        for (auto x : v)
        {
            ind[x]++;
        }
    }

    queue<int> q;// use priority_queue for lexicographically smallest sorting
    for (int i = 0; i < n; ++i)
    {
        if (ind[i] == 0) q.push({i});
    }
   
    bool check = true;
    vector<ll> dis(n);
    ll ans = 0; 
    while (!q.empty())
    {
        auto x = q.front(); 
        
        q.pop();
        n--;
        if (vis[x])
        {
            check = false;
            break;
        }
        vis[x] = true;
        for (auto a : g[x])
        {
            ind[a]--;
            dis[a] = max(dis[a], dis[x] + 1);
            if (ind[a] == 0) q.push(a);
        }

    }
    if (n != 0) check = false;
    if (check == false) return -1;
    return maxe(dis);
}

