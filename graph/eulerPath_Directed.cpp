class Solution {
public:
    
    vector<vector<int>> g;
    vector<int> indegree, outdegree;
    vector<int> path; 
    
    bool verifyEulerianPath()
    {
        int s=0,e=0;
        for(int i=0;i<g.size();i++)
        {
            if(abs(outdegree[i]-indegree[i])>1) return false;
            else if (outdegree[i]-indegree[i]==1)
                s++;
            else if (indegree[i]-outdegree[i]==1)
                e++;
            
            
        }
        return (s==0 and e==0) or (s==1 and e==1);
    }
    int findStartNode()
    {
        int s = 0 ;
        for(int i=0;i<g.size();i++)
        {
            if(outdegree[i]-indegree[i]==1) return i;
            if(outdegree[i]>0) s=i; 
        }
        return s ;
    }
    
    void dfs(int root)
    {
        while(outdegree[root]!=0)
        {
            int next_root = g[root][--outdegree[root]];
            dfs(next_root);
        }
        path.push_back(root);
        return ;
    }
    
    
    vector<vector<int>> validArrangement(vector<vector<int>>& pairs) {
      
       map<int,int> dict,rdict;
       int n =0 ; 
       for(auto p : pairs)
       {
           for(auto v: p)
           {
               if(dict.find(v) == dict.end())
               {
                   dict[v]=n++;
                   rdict[n-1]=v;
               }
               
           }
       }
        vector<vector<int>> res; 
        g= vector<vector<int>>(n);
        indegree=vector<int>(n);
        outdegree=vector<int>(n);
        for(auto p : pairs)
        {
            g[dict[p[0]]].push_back(dict[p[1]]);
            outdegree[dict[p[0]]]++;
            indegree[dict[p[1]]]++;
        }
        
        // code for euler paths begin :
        // g -> adjacency list, outdegree and indegree
         
         if(verifyEulerianPath()) 
         {
              path.clear();
              dfs(findStartNode()); 
              reverse(path.begin(),path.end());
         }
        for(auto &p : path) p = rdict[p];
        for(int i=0;i<(int)(path.size()) -1 ;i++)
        {
            res.push_back(vector<int>{path[i],path[i+1]});
        }
        
        return res; 
        
    }
};
