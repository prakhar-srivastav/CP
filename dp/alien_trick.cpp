/*
 :Prakhar Srivastava
*/
// https://atcoder.jp/contests/abc218/submissions/25809279

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

/*
.*..
abc
*/
pair<ll, ll> calc(ll C, vector<ll> &a)
{

	int n = si(a) + 1;
	vector<vector<ll>> dp(n, vector<ll>(2));
	vector<vector<ll>> dp2(n, vector<ll>(2));

	ll ans = numeric_limits<ll>::min(), cnt = 0;
	for (int i = 0; i < n; i++)
	{
		if (i == 0)
		{
			dp[i][0] = 0;
			dp[i][1] = -C;
			dp2[i][1] = 1;
			dp2[i][0] = 0;
			continue;
		}
		dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] + a[i - 1]);
		if (dp[i - 1][0] == dp[i - 1][1] + a[i - 1]) dp2[i][0] = max(dp2[i - 1][0], dp2[i - 1][1]);
		else dp2[i][0] = (dp[i - 1][0] > (dp[i - 1][1] + a[i - 1]) ? dp2[i - 1][0] : dp2[i - 1][1]);

		dp[i][1] = dp[i - 1][0] + a[i - 1] - C;
		dp2[i][1] = dp2[i - 1][0] + 1;

	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < 2; j++) ans = max(ans, dp[i][j]);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < 2; j++) if (dp[i][j] == ans) cnt = max(cnt, dp2[i][j]);

	return { ans,cnt };
}

void solve()
{
	int n, r;
	cin >> n >> r;
	r = min(r, n - r);
	vector<ll> arr(n - 1);
	for (auto &a : arr)
		cin >> a;
	if (r == n / 2 or r == (n + 1) / 2)
	{
		cout << sum_all(arr) << '\n';
		return;
	}
	ll res = 0;
	ll _low = 0, _high = 1e10 ;
	pair<ll, ll> ans;
	while (_low <= _high)
	{
		if (_low == _high)
		{
			ans = calc(_low, arr);
			break;
		}
		ll _mid = (_low + _high) / 2 + 1;
		ans = calc(_mid, arr);
		if (ans.ss >= r) _low = _mid ;
		else  _high = _mid - 1;
	
	}


	
	cout << ans.ff + _low * r << endl;

}


int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	


	//int t; cin >> t; while (t--)
	solve();

}

