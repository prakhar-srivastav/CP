struct ntt
{
private:
	vector<vector<int>> w, w_inv;
	int g;
	int _g;
	int _2;
	int LOG = 18;
	int cntr = 0;
	int power(int a, int b, int mod)
	{
		if (a == 0 and b == 0) return 1;
		if (a == 0) return 0;
		if (b == 0) return 1;
		if (b == 1) return a;
		int x = power(a, b / 2, mod);
		x = (1ll * x*x) % mod;
		if (b % 2)
			x = (1ll * x*a) % mod;
		return x;
	}
	void pre()
	{
		cntr++;
		_g = power(g, mod - 2, mod);
		_2 = power(2, mod - 2, mod);
		int n = power(2, LOG, mod);
		w = vector<vector<int>>(LOG + 1);
		w_inv = vector<vector<int>>(LOG + 1);
		for (int i = LOG; i >= 0; i--)
		{
			w[i] = vector<int>(i + 1);
			w_inv[i] = vector<int>(i + 1);
			w[i][i] = power(g, (mod - 1) / n, mod);
			w_inv[i][i] = power(_g, (mod - 1) / n, mod);
			for (int j = i - 1; j >= 0; j--)
			{
				w[i][j] = (1ll * w[i][j + 1] * w[i][j + 1]) % mod;
				w_inv[i][j] = (1ll * w_inv[i][j + 1] * w_inv[i][j + 1]) % mod;
			}
			n /= 2;
		}
	}
	void NTT(vector<int> &a, bool inv, int _N, int _i)
	{
		if (int(a.size()) == 1) return;
		int n = (int)a.size();
		vector<int> a0(n / 2), a1(n / 2);
		for (int i = 0; i < n; i += 2)
		{
			a0[i / 2] = (a[i]);
			a1[i / 2] = (a[i + 1]);
		}
		NTT(a0, inv, _N, _i - 1);
		NTT(a1, inv, _N, _i - 1);
		int w0 = 1, _w = (!inv ? w[_N][_i] : w_inv[_N][_i]);
		for (int i = 0; i < n / 2; i++)
		{
			a[i] = (a0[i] + (1ll * w0*a1[i]) % mod) % mod;
			a[i + n / 2] = (a0[i] - (1ll * w0*a1[i]) % mod + mod) % mod;
			if (inv)
			{
				a[i] = (1ll * _2*a[i]) % mod;
				a[i + n / 2] = (1ll * _2*a[i + n / 2]) % mod;
			}
			w0 = (1ll * w0*_w) % mod;
 
		}
	}
public:
	ntt() : g(3) { pre(); }
 
	vector<int> multiply(vector<int> &a, vector<int> &b)
	{
		assert(cntr == 1);
		vector<int> fa = a;
		vector<int> fb = b;
		int n = 1;
		int _n = 0;
		while (n < (int)a.size() + (int)b.size()) n *= 2, _n++;
		fa.resize(n);
		fb.resize(n);
		NTT(fa, 0, _n, _n);
		NTT(fb, 0, _n, _n);
		for (int i = 0; i < (int)fa.size(); i++) fa[i] = (1ll * fa[i] * fb[i]) % mod;
		NTT(fa, 1, _n, _n);
		return fa;
	}
};