ll ternary_search(ll l, ll r)
{
    while (r - l > 2)
    {
        ll m1 = l + (r - l) / 3; 
        ll m2 = r - (r - l) / 3;
        ll f1 = calc(m1);
        ll f2 = calc(m2);
        if (f1 < f2) r = m2;
        else  l = m1; 
        
    }
    ll ans = numeric_limits<ll>::max();
    for (ll i = l; i <= r; ++i) ans = min(ans,calc(i));

    return ans; 
}