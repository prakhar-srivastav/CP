/*
 _One_last_try
*/



//#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector")
#include <bits/stdc++.h>
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




struct line
{
    ll m,c;
    line(): m(0),c(0){}
    line(ll m0,ll c0) : m(m0), c(c0) {}   
};




vector<ll> t,d,x;


multiset<ll> sl,sr;
ll m, c, tfl,tfr;
 


 
void _minimize()
{

    

    while (m > 0)
    {
 
        ll y0, x0;
        auto it = sr.end();
        it--;
        x0 = *it;
        sr.erase(sr.find(x0));
        x0 += tfr;
        y0 = m * x0 + c;
        ll new_c = y0 - (m - 1)*x0;
        c = new_c;
        m--;
    }
}
 


void _translate_left(ll b)
{
    tfl-=b;
    tfr-=b;
    c+=b*m;
}
void _translate_right(ll b)
{
    tfl+=b;
    tfr+=b;
    c-=b*m;
}
void _local_minimize(ll b)
{
    tfl-=b;
    tfr+=b;
    c-=b*m;
} 
void _add(vector<ll> pts, ll m1, ll c1)
{
    
    m += m1;
    c += c1;
    for(auto ms:pts)
    {
         if(si(sr)<m)
            {
              if(sl.empty())
              {
                sr.insert(ms-tfr);
              }
              else 
              {
                auto it= (sl.end());
                it--;
                auto itr= *(it);
                sl.erase(sl.find(itr));
                itr+=tfl;
                if(itr>ms)
                    swap(itr,ms);
                sr.insert(ms-tfr);
                sl.insert(itr-tfl);
              }
                }
        else 
        {
             if(sr.empty())
              {
                sl.insert(ms-tfl);
              }
              else 
              {
                auto itr= *(sr.begin());
                sr.erase(sr.find(itr));
                itr+=tfr;
                if(itr>ms)
                    swap(itr,ms);
                sr.insert(ms-tfr);
                sl.insert(itr-tfl);
              }

        }

        }    
}
 
ll _get_min()
{
    _minimize();
    return c;
 
}


void solve()
{
 
  int n;
  cin >> n ; 

 t.resize(n);
 d.resize(n);
 x.resize(n);
  m=0,c=0,tfl=0,tfr=0;
  ll L=0;
  for(int i=0;i<n;i++)
  {
     cin >> t[i] >> d[i] >> x[i] ;
     // if(i>0)
     _local_minimize(t[i]-((i-1>=0)?t[i-1]:0));
     L=t[i];
     if(d[i]==0)
     {
        _add(vector<ll>{min(L,x[i])},0,x[i]-min(x[i],L));
     }
     else 
     {
       _add(vector<ll>{max(-L,x[i])},1,-x[i]);
     }

   
  }

  cout <<_get_min() << endl; 
   
}


signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif



    //int t; cin >> t; while (t--)
    solve();

}

