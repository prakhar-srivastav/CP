ll power(ll a, ll b, ll m)
{
    if (b == 1) return a;
    ll x = power(a, b / 2, m);
    x *= x;
    x %= m;
    if (b % 2 == 1)
    {
        x *= a;
        x %= m;
    }
    return x;
}