struct mf_graph
{
 private:
 int _n;
 struct edge
 {
 	int u,id_u;
 	int v,id_v;
 	ll cap;
 };
 vector<edge> edges;
 vector<vector<int>> g;
 vector<bool> vis; 
 ll min(ll a,ll b)
 {
 	if(a>b)swap(a,b);
 	return a;
 }
 public:
 
 mf_graph(int n) : _n(n)
 {
 	g=vector<vector<int>>(n);
 	edges.clear();
 }	
 void add_edge(int from ,int to, ll cap)
 {
 	
 	int id_to= si(g[to]);
 	int id_from = si(g[from]);
 	g[from].pb(si(edges));
 	edges.pb({from,id_from,to,id_to,cap});
 	g[to].pb(si(edges));
 	edges.pb({to,id_to,from,id_from,0});
 	
 }	
 
/*
path s->1->3->t
better way : s-> i of where 1 is -> i of where 3 is -> i of where t is
*/
 
void bfs(int s,int t,vector<int> &level)
{
 fill(level.begin(),level.end(),-1);
 level[s]=0;
 queue<int> q; 
 q.push(s);
 while(!q.empty())
 {
 	int v=q.front();
 	q.pop();
 	for(auto i: g[v])
 	{
 		auto e=edges[i];
 		if(e.cap==0 or level[e.v]>=0) continue;
 		level[e.v]=level[v]+1;
 		if(e.v==t) return; 
 		q.push(e.v);
 
 	}
 }
}
 
ll dfs(int s,int t ,ll up,vector<int> &level,vector<int> &iter)
{
	if(s==t) return up;
	ll res=0;
	int level_t=level[t];
	for(int &i=iter[t];i<si(g[t]);i++)
	{
		auto &e= edges[g[t][i]];
		int from =e.u,to=e.v;
		int to_id = e.id_v;
		auto &e2= edges[g[to][to_id]];
		if(level[to]>=level_t or e2.cap==0) continue;
		ll d=dfs(s,to,min(e2.cap,up-res),level,iter);
		if(d<=0)
			continue;
        e2.cap-=d;
        e.cap+=d;
        res+=d;
        if(res==up) break;
	}
	return res;
 
}
 ll flow(int s,int t,ll flow_limit= 1e13)
 {
 	vector<int> level(_n),iter(_n);
 	ll flow=0;
 
 	while(flow<=flow_limit)
 	{
 		bfs(s,t,level);
 		if(level[t]==-1) break;
 		fill(iter.begin(),iter.end(),0);
 		flow+= dfs(s,t,flow_limit,level,iter);
 	}
 	return flow;
 
 
 
 }
 
};