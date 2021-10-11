/*
 _One_last_try
*/



#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector")
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

const int mod = 1e9+7;


void exgcd(int &x,int &y ,int a,int b)
{
  if(a==0)
  {
    x=0,y=1;
    return ;
  }
  exgcd(x,y,b%a,a);
  int nx=(y-(b/a)*x);
  int ny=x;
  x=nx,y=ny;
  return ; 

}

int gcd(int a,int b)
{
    if(a==0) return b;
    return gcd(b%a,a);
}

int FLOOR(int &a,int &b,int &c)
{
  if(a>b) return (a-b)/c;
  else return -1*(b-a+c-1)/c;  
}
int CEIL(int &a,int &b,int &c)
{
    if(a>b) return (a-b+c-1)/c;
  else return -1*(b-a)/c; 
}
int m,n;
int range1[2],range2[2];
int dopentine_equations(int a,int b,int X,int Y,int c)
{
    
    int g,x0,y0;
    if(b!=a+1)
    {
         g=gcd(a,b);
         if(c%g!=0) return 0 ;
         x0=0,y0=0;
         exgcd(x0,y0,a,b);
         x0=x0*c/g;
         y0=y0*c/g;
    }
    else 
    {
        g=1;
        x0=-c;
        y0=c;
        // return max(1+min((y0-1)/a,(X-x0)/b)-max((y0-Y+a-1)/a,(b-x0)/b),0)%mod;
    }
     a/=g;
     b/=g;
     m=y0,n=Y;
     range1[0]= CEIL(m,n,a);
     n=1;
     range1[1]=FLOOR(m,n,a);
     m=1,n=x0;
     range2[0]= CEIL(m,n,b);
     m=X;
     range2[1]=FLOOR(m,n,b);
    return max(0,min(range2[1],range1[1])-max(range2[0],range1[0])+1);
}
int power(int a, int b)
{
    if(a==0 and b==0)
        return 1;
    if(a==0) return 0;
    if(b==0) return 1;
    if (b == 1) return a;
    ll x = power(a, b / 2);
    x *= x;
    
    if (b % 2 == 1)
    {
        x *= a;
    }
    return x;
}
int self( int x,int X,int S)
{
    if(S%x!=0) return 0 ; 
    int l =S/x;
    X=9*power(10,x-1);
    return max(0,X-l+1)%mod;
}
int self2( int x,int X,int S)
{
    if(S%x!=0) return 0 ; 
    ll l =S/x;
   
    X=(X-l+1);
    if(X<0) X+=mod;
    if(X>=mod) X-=mod;
    return X;
}

void solve()
{
  

  int S;
  cin >> S ; 

 int res=0; 


 for(int i=1;i<=8;i++)
   {
     for(int j=i+1;j<=8;j++)
    {
        int a=9*power(10,i-1),b=9*power(10,j-1),s=0;
        for(ll k=i+1;k<=j-1;k++)
        {
            s+= (9*power(10,k-1))*k;
        }

        if(s<=S)
        {
            res=(res+dopentine_equations(i,j,a,b,S-s))%mod;           
        }

       
    }
 
   }
  
   for(int i=8,j=i+1;i<=1e8;i++,j++)
   {
     m=S,n=S;
     range1[0]= CEIL(m,n,i);
     n=1;
     range1[1]=FLOOR(m,n,i);
     m=1,n=-S;
     range2[0]= CEIL(m,n,j);
     m=S;
     range2[1]=FLOOR(m,n,j);
        res=(res+max(0,min(range2[1],range1[1])-max(range2[0],range1[0])+1));
        if(res>=mod) res-=mod;
   }


   

    
 for(int i=1,y=9;i<=1e8;i++)
 {
    if(i<=8)
        res=(res+self(i,y,S));
    else 
        res=(res+self2(i,y,S));
    y=(1ll*y*10)%mod;
    if(res>=mod)
        res-=mod;
 }

 // cout << self(1,9,S) << endl;
 cout << res<< endl;
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

