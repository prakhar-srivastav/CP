// https://atcoder.jp/contests/abc213/tasks/abc213_h

#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>
#include<assert.h>
using namespace std;
const int mod = 998244353;

using ll = long long;
vector<vector<ll>> dp(11);
vector<ll> p[11][11];
vector<pair<int, int>> edge;



vector<vector<ll>> w_inv, w;
ll inv_2, g_inv;


ll power(ll a, ll b, ll mod)
{
	if (a == 0 and b == 0) return 1;
	if (a == 0) return 0;
	if (b == 0) return 1;
	if (b == 1) return a;

	ll x = power(a, b / 2, mod);
	x *= x;
	x %= mod;
	if (b % 2 != 0)
	{
		x *= a;
		x %= mod;
	}
	return x;
}
void pre()
{
	g_inv = power(3, mod - 2, mod);
	inv_2 = power(2, mod - 2, mod);
	ll g = 3;
	ll num = 0;
	ll n = 1;
	while (num < 18)
	{
		n *= 2, num++;
	}
	w.clear();
	w_inv.clear();
	n *= 2;

	w.resize(num + 1);
	w_inv.resize(num + 1);

	for (ll i = num; i >= 1; i--)
	{
		w[i] = vector<ll>(i + 1);
		w_inv[i] = vector<ll>(i + 1);
		n /= 2;
		w[i][i] = power(g, (mod - 1) / n, mod);
		w_inv[i][i] = power(g_inv, (mod - 1) / n, mod);
		for (ll j = i - 1; j >= 0; j--)
		{
			w[i][j] = w[i][j + 1] * w[i][j + 1];
			w_inv[i][j] = w_inv[i][j + 1] * w_inv[i][j + 1];
			w[i][j] %= mod;
			w_inv[i][j] %= mod;
		}
	}
}


void ntt(vector<ll>& a, bool invert, int n, int num, int pos)
{
	if (n == 1) return;

	vector<ll> a0(n / 2), a1(n / 2);
	for (ll i = 0; i < n / 2; i++)
	{
		a0[i] = a[i * 2];
		a1[i] = a[i * 2 + 1];
	}
	ntt(a0, invert, n / 2, num, pos - 1);
	ntt(a1, invert, n / 2, num, pos - 1);

	ll w0 = 1;
	ll wn = (invert) ? w_inv[num][pos] : w[num][pos];

	for (ll i = 0; i < n / 2; i++)
	{
		a[i] = a0[i] + (w0 * a1[i]) % mod;
		a[i + n / 2] = a0[i] - (w0 * a1[i]) % mod + mod;
		a[i] %= mod;
		a[i + n / 2] %= mod;
		if (invert)
		{
			a[i] *= inv_2;
			a[i + n / 2] *= inv_2;
			a[i] %= mod;
			a[i + n / 2] %= mod;
		}
		w0 *= wn;
		w0 %= mod;
	}
}
bool pre_called = false;
vector<ll> mult(vector<ll>& a, vector<ll>& b)
{
	if (!pre_called)
	{
		pre();
		pre_called = true;
	}
	ll n = 1;
	ll num = 0;
	while (n < (int)(a.size()) + (int)(b.size()))
	{
		n *= 2, num++;
	}
	a.resize(n);
	b.resize(n);
	ntt(a, false, n, num, num);
	ntt(b, false, n, num, num);
	for (ll i = 0; i < n; i++)
	{
		a[i] *= b[i];
		a[i] %= mod;
	}
	ntt(a, true, n, num, num);
	

	return a;
}


vector<ll> get_vec(ll a, ll b, vector<ll> &arr)

{
	vector<ll> t;
	for (int i = a; i <= b; i++) t.push_back(arr[i]);
	return t;
}


void dnc(int l, int r)
{
	if (l == r) return;

	int m = (l + r) / 2;
	dnc(l, m);
	for (auto e : edge)
	{
		int a = e.first, b = e.second;
		auto A = get_vec(l, m, dp[a]);
		auto B = get_vec(0, r - l, p[a][b]);

		auto C = mult(A, B);
		for (int j = m + 1; j <= r; j++)
		{
			dp[b][j] = (dp[b][j] + C[j - l]) % mod;
			
		}
		A = get_vec(l, m, dp[b]);
		B = get_vec(0, r - l, p[a][b]);
		C = mult(A, B);
		for (int j = m + 1; j <= r; j++)
		{
			dp[a][j] = (dp[a][j] + C[j - l]) % mod;
			
		}
	}
	dnc(m + 1, r);

}


int main()
{

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n, m, t;
	cin >> n >> m >> t;
	int a, b;
	for (int i = 0; i < m; i++)
	{
		cin >> a >> b;
		a--, b--;
		edge.push_back({ a,b });
		p[a][b] = vector<ll>(t + 1);
		for (int j = 1; j <= t; j++) cin >> p[a][b][j];

	}
		for (int i = 0; i < n; i++) dp[i] = vector<ll>(t+1);
		dp[0][0] = 1;
		dnc(0, t);
		cout << dp[0][t] << endl;

	



	return 0;
}
