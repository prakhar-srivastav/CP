
vector<vector<ll>> g;
bool is_bipartite(ll x)
{
    vector<ll> colour(n);
    queue<ll> q;
    bool check = true;
    q.push(x);
    colour[x] = 1;
    while (!q.empty())
    {
        auto u = q.front();
        q.pop();

        for (auto a : g[u])
        {
            if (colour[a]!=0)
            {
                if (colour[a] == colour[u])
                {
                    check = false;
                    return check;
                }
               
            }
            else 
            {
            	q.push(a);
            	colour[a] = 3 - colour[u];
            }
        }
    }
    // if it is bipartite then colour array represent one of the possible distribution of vertices on two sides of bipartite graph
    return check;
}
