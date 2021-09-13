// Default Value:
// p=31 m=1000000007
// Other values you can prefer:
// p=37 m=1000000007
// p=41 m=900000011
struct string_hash
{
private:

   
    vector<ll> pw, ipw; 
    ll p, m; 
    ll power(ll a, ll b, ll m)
    {
        if (a == 0 and b == 0) return 1; 
        if (a == 0) return 0;
        if (b == 0) return 1;
        if (b == 1) return a; 
        ll x = power(a, b / 2, m);
        x *= x;
        x %= m;
        if (b % 2 != 0)
        {
            x *= a;
            x %= m;
        }
        return x; 
    }
    void init(ll num)
    {
        pw = vector<ll>(num + 3, 1);
        ipw = vector<ll>(num + 3, 1);
        for (ll i = 1; i < pw.size(); i++)
        {
            pw[i] = pw[i - 1] * p; 
            pw[i] %= m; 
        }
        ipw[num + 2] = power(pw[num + 2], m - 2, m);
        for (ll i = num + 1; i >= 0; i--)
        {
            ipw[i] = ipw[i + 1] * (p);
            ipw[i] %= m; 
        }
    }
    void make_hash(const string& str)
    {
        h_func.clear();
        h_func.resize(si(str), 1);
        for (ll i = 0; i < str.size(); i++)
        {
            ll prev = i - 1 >= 0 ? h_func[i - 1] : 0;
            h_func[i] = (pw[i] * (str[i] - 'a' + 1))%m + prev;
            h_func[i] %= m;
        }
    }
public:

  
    vector<ll> h_func;
    string_hash(const string &str,ll p=31, ll m=1000000007) : p(p), m(m)
    {
        init(si(str)); 
        make_hash(str);
    }
    ll get_hash(ll i, ll j)
    {
       
        ll prev = i - 1 >= 0 ? h_func[i - 1] : 0; 
        ll ans = h_func[j] - prev + m;
        ans %= m; 
        ans = ans * ipw[j];
        ans %= m;
        return ans;
    }
};
