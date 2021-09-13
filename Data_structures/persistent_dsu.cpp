struct PDSU
{
  vector<int> p, s;
 
  vector<pair<int,pair<int,int>>> op;
  PDSU(int n)
  {
    p = vector<int>(n);
    s = vector<int>(n);
    for (int i = 0; i < n; i++)
      p[i] = i;
    for (int i = 0; i < n; i++)
      s[i] = 1;
 
  }
  int root(int a)
  {
    if (p[a] == a) return a;
    return root(p[a]);
  }
  bool same(int a, int b)
  {
    return root(a) == root(b);
  }
  void join(int a, int b)
  {
    a = root(a);
    b = root(b);
    if (a == b) return;
    if (s[b] > s[a])
    {
      swap(a, b);
    }
     op.pb({ a,{b,s[a]} });
    s[a] += s[b];
    p[b] = a;
   
  }
  void undo()
  {
    auto temp = op.back();
    op.pop_back();
    p[temp.ss.ff] = temp.ss.ff;
    s[temp.ff] = temp.ss.ss;
  }
  int snapshot()
  {
    return si(op);
  }
 
  void roll_back(int i)
  {
    while (si(op) > i) undo();
  }
 
};