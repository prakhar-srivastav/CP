
vector<ll> f,inv_f; 
ll power(ll a,ll b,ll m)
{
    if(a==0 and b==0 ) return 1;
    if(a==0) return 0;
    if(b==0) return 1 ;
    if(b==1 ) return a;
    ll x=power(a,b/2,m);
    x*=x;
    x%=m ;
    if(b%2!=0)
    {x*=a;
    x%=m;}
    return x; 
}
void pre(ll n=1000000)
{
 f= vector<ll>(n+1,1);
 inv_f=vector<ll>(n+1,1);
 for(ll i=2; i<=n;i++)
 {
   f[i]= f[i-1]*(i);
   f[i]%=mod; 
 }
  inv_f[n]= power(f[n],mod-2,mod);
  for(ll i=n-1;i>=0;i--)
  {
   inv_f[i]= inv_f[i+1]*(i+1);
   inv_f[i]%=mod; 
  }
}
ll cnk(ll n, ll k){
  if(n==k) return 1;
    if(k<0 || k >n) return 0; 
    ll ans= f[n];
    ans*=inv_f[k];
    ans%=mod;
    ans*=inv_f[n-k];
    ans%=mod;
    return ans ; 
}
