template< class Cap, class Cost> struct mcf_graph {
private:
    int _n;
    struct _edge
    {
        int  to, rev;
        Cap  cap;
        Cost cost;
    };
    vector<pair<int, int> >pos;
    vector<vector<_edge> > g;
    vector<Cost> h;
    vector<Cost> dist;
    vector<int> pv, pe;
    vector<bool> vis;


    // normalizing nodes weights in case of negative edges 
    //References :Geeks for Geeks: Johnson's Algorithm
    void norm(int s, int t)
    {
        h.resize(_n, numeric_limits<Cost>::max());
        h[s] = 0;
        int ch = 1;
        int it = _n;
        while (ch-- && it--)
        {
            for (int i = 0; i < _n; i++)
            {
                if (h[i] == numeric_limits<Cost>::max()) continue;
                for (auto e : g[i])
                {

                    if (e.cap == 0) continue;
                    if (h[i] + e.cost < h[e.to])
                    {
                        h[e.to] = h[i] + e.cost;
                        ch = 1;
                    }
                }
            }
            assert(it >= 0); // negative cost cycle
        }
        for (int i = 0; i < _n; i++)h[i] -= h[t];

    }


    //dijkstra algorithm
    bool dijkstra(int s, int t)
    {
       
        pv.clear();
        pe.clear();
        vis.clear();
        dist.clear();
        dist.resize(_n, numeric_limits<Cost>::max());
        pv.resize(_n, -1);
        pe.resize(_n, -1);
        vis.resize(_n, false);


        priority_queue<pair<Cost, int>, vector<pair<Cost, int>>, greater<pair<Cost, int>> > pq;
        pq.push({ 0,s });
        dist[s] = 0;
        while (!pq.empty())
        {
            int x = pq.top().second;
            pq.pop();
            if (vis[x]) continue;
            vis[x] = true;
            if (x == t)
                break;
            for (int i = 0; i<int(g[x].size()); ++i)
            {
                auto e = g[x][i];
                if (vis[e.to] || e.cap == 0)
                    continue;
                Cost cost = e.cost + h[x] - h[e.to];
                if (dist[e.to] <= dist[x] + cost)
                    continue;
                dist[e.to] = dist[x] + cost;
                pv[e.to] = x;
                pe[e.to] = i;
                pq.push({ dist[e.to],e.to });
            }
        }
        if (vis[t] == false)
            return false;
        //update weights
        for (int i = 0; i < _n; ++i)
        {
            if (!vis[i]) continue;
            h[i] -= dist[t] - dist[i];
        }
        return true;

    }



public:
    mcf_graph() {}
    mcf_graph(int n) : _n(n), g(n) {}

    int add_edge(int from, int to, Cap cap, Cost cost)
    {
        assert(from >= 0 && from < _n);
        assert(to >= 0 && to < _n);
        int m = int(pos.size());
        pos.push_back({ from,int(g[from].size()) });
        int from_id = int(g[from].size());
        int to_id = int(g[to].size());
        if (from == to) to_id++;
        g[from].push_back(_edge{to,to_id,cap,cost });
        g[to].push_back(_edge{ from, from_id, 0, -cost });
        return m;
    }
    struct edge
    {
        int from, to;
        Cap cap, flow;
        Cost cost;
    };
    edge get_edge(int i) {
        int m = int(pos.size());
        assert(0 <= i && i < m);
        auto _e = g[pos[i].first][pos[i].second];
        auto _re = g[_e.to][_e.rev];
        return edge{
            pos[i].first, _e.to, _e.cap + _re.cap, _re.cap, _e.cost,
        };
    }
    vector<edge> edges()
    {
        int m = int(pos.size());
        vector<edge> result(m);
        for (int i = 0; i < m; ++i)
            result[i] = get_edge(i);
        return result;
    }
    pair<Cap, Cost> flow(int s, int t, bool neg = false)
    {
        return flow(s, t, numeric_limits<Cap>::max(), neg);
    }
    pair<Cap, Cost> flow(int s, int t, Cap flow_limit, bool neg = false)
    {
        return slope(s, t, flow_limit, neg).back();
    }
    vector<pair<Cap, Cost>> slope(int s, int t, bool neg = false)
    {
        return slope(s, t, numeric_limits<Cap>::max(), neg);
    }
    vector<pair<Cap, Cost>> slope(int s, int t, Cap flow_limit, bool neg = false)
    {
        assert(s >= 0 && s < _n);
        assert(t >= 0 && t < _n);
        assert(s != t);
        h.clear();
        if (!neg)
            h.resize(_n, 0);
        else norm(s,t);
        Cap flow = 0;
        Cost cost = 0, prev = -1;
        vector<pair<Cap, Cost>> result;
        result.push_back({ flow,cost });
        while (flow < flow_limit)
        {
            if (dijkstra(s, t) == false)
                break;
            Cap c = flow_limit - flow;
            for (int i = t; i != s; i = pv[i])
            {
                c = min(c, g[pv[i]][pe[i]].cap);
            }
            for (int i = t; i != s; i = pv[i])
            {
                auto& e = g[pv[i]][pe[i]];
                e.cap -= c;
                g[e.to][e.rev].cap += c;
            }
            Cost d = -h[s];
            flow += c;
            cost += c * d;
            if (prev == d)
                result.pop_back();
            result.push_back({ flow,cost });
            prev = d;
        }
        return result;
    }
};
.