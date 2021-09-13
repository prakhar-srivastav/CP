ll euclid_gcd(ll a, ll b, ll& x, ll& y) {
 
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll g = euclid_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return g;
}
 
 
pair<ll, ll> crt(vector<ll>& r, vector<ll>& m)
{
    assert(r.size() == m.size());
    int n = int(r.size());
   ll r0 = 0, m0 =1;
 
  // cout << n << endl; 
    for (int i = 0; i < n; ++i)
    {
        ll m1 = m[i], r1 = r[i];
       
       
        assert(m1 >= 1);
      // if (r1 < 0) r1 = (r1 % m1) + m1;
      //  assert(r1 >= 0);
       
        if (m1 > m0)
        {
            swap(m1, m0);
            swap(r1, r0);
        }
 
        ll x, y, g = euclid_gcd(m0, m1, x, y);
        
        
        // No solution condition
        if ((r0 - r1) % g != 0) return{ 0,0 };
       
        ll lcm = m0 * (m1 / g);
        ll X= r0 +  x % m1 * (r1 - r0) % m1 /g*m0; 
        if (X < 0) X += lcm; 
        r0 = X;
        m0 = lcm; 
 
        
    }
    return{ r0,m0 };
}