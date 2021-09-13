struct mcf_graph
{
private:
  int _n;
  struct edge
  {
    int to, rev;
    ll cap;
    ll cost;
  };
  vector<pair<int, int>> pos;
  vector<vector<edge>> g;
  vector<ll> H;
  vector<ll> dist;
  vector<int> pv, pe;
  vector<bool> vis;
 
  bool dijkstra(int s, int t)
  {
    pv = vector<int>(_n, -1);
    pe = vector<int>(_n, -1);
    dist = vector<ll>(_n, 1e15);
    vis = vector<bool>(_n);
    using node = pair<ll, int>;
    priority_queue<node, vector<node>, greater<node>> pq;
    pq.push({ 0,s });
    dist[s] = 0;
    while (!pq.empty())
    {
      int x = pq.top().second;
      pq.pop();
      if (vis[x])
        continue;
      vis[x] = true;
      if (x == t)
        break;
      for (int i = 0; i < (int)g[x].size(); i++)
      {
        auto e = g[x][i];
        if (vis[e.to] or e.cap == 0)
          continue;
        ll cost = e.cost + (H[x] - H[e.to]);
        if (dist[e.to] <= dist[x] + cost)
          continue;
        dist[e.to] = dist[x] + cost;
        pv[e.to] = x;
        pe[e.to] = i;
        pq.push({ dist[e.to],e.to });
      }
    }
 
    if (!vis[t]) return false;
    for (int i = 0; i < _n; i++)
    {
      if (vis[i])
      {
        H[i] +=  dist[i]-dist[t];
      }
    }
      return true;
 
  }
public:
  mcf_graph(int n) :_n(n), g(n) {}
 
  int add_edge(int f, int t, ll cap, ll cost)
  {
    int m = (int)pos.size();
    pos.push_back({ f,int(g[f].size()) });
    int _f = (int)g[f].size();
    int _t = (int)g[t].size();
    if (f == t) _t++;
    g[f].push_back(edge{ t,_t,cap,cost });
    g[t].push_back(edge{ f,_f,0,-cost });
    return m;
  }
  struct _edge {
    int from, to;
    ll cap, flow;
    ll cost;
  };
  _edge get_edge(int i)
  {
    int m = (int)pos.size();
    auto e = g[pos[i].first][pos[i].second];
    auto re = g[e.to][e.rev];
    return _edge{ pos[i].first,e.to,e.cap + re.cap,re.cap,e.cost };
  }
 
  vector<_edge> edges()
  {
    int m = (int)(pos.size());
    vector<_edge> res;
    for (int i = 0; i < m; i++)
      res.push_back(get_edge(i));
    return res;
  }
  pair<ll, ll> flow(int s, int t)
  {
    return flow(s, t, 1e15);
  }
  pair<ll, ll> flow(int s, int t, ll flow_limit)
  {
    return slope(s, t, flow_limit).back();
  }
  vector<pair<ll, ll>> slope(int s, int t)
  {
    return slope(s, t, 1e15);
  }
  vector<pair<ll, ll>>slope(int s, int t, ll flow_limit)
  {
    H = vector<ll>(_n);
    ll flow = 0;
    ll cost = 0;
    ll prev = -1;
    vector<pair<ll, ll>> res;
    res.push_back({ flow,cost });
    while (flow < flow_limit)
    {
      if (dijkstra(s, t) == false)
        break;
      ll c = flow_limit - flow;
      for (int i = t; i != s; i = pv[i])
      {
        c = min(c, g[pv[i]][pe[i]].cap);
      }
      for (int i = t; i != s; i = pv[i])
      {
        auto &e = g[pv[i]][pe[i]];
        e.cap -= c;
        auto &re = g[e.to][e.rev];
        re.cap += c;
      }
      ll _cost = -H[s];
      flow += c;
      cost += c * _cost;
      if (prev == _cost)
        res.pop_back();
      res.push_back({ flow,cost });
      prev = _cost;
 
    }
    return res;
  }
 
 
 
};