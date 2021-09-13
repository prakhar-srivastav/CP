struct suffix
{
private:
	int _n, _log;
	string s;
	vector<int> suffixArray, lcp;
	vector<vector<int>> p;
	vector<vector<int>> c;
	vector<vector<int>> inv;
	void buildSuffixArray()
	{
		int _log = 0;
		int __n = 1;
		while (__n < _n) __n *= 2, _log++;
		c = vector<vector<int>>(_log + 1, vector<int>(_n));
		p = vector<vector<int>>(_log + 1, vector<int>(_n));
		inv = vector<vector<int>>(_log + 1, vector<int>(_n));
		vector<int> cnt(26);
		p[0][0] = _n - 1;
		c[0][0] = _n - 1;
		for (int i = 0; i < _n - 1; i++)
		{
			cnt[s[i] - 'a']++;
		}
		for (int i = 1; i < 26; i++)
			cnt[i] += cnt[i - 1];
		for (int i = 0; i < _n - 1; i++)
		{
			p[0][cnt[s[i] - 'a']--] = i;
		}
		for (int i = 0, _c = 0; i < _n;)
		{
			char ch = s[p[0][i]];
			while (i < _n and ch == s[p[0][i]])
			{
				c[0][i] = _c;
				i++;
			}
			_c++;
		}
 
		for (int i = 1, _m = 1; i < _log + 1; i++, _m *= 2)
		{
 
			for (int j = 0; j < _n; j++) inv[i - 1][p[i - 1][j]] = j;
			vector<pair<pair<int, int>, int>> sorted(_n);
			for (int j = 0; j < _n; j++)
			{
				sorted[j] = { {c[i - 1][inv[i - 1][j]],c[i - 1][inv[i - 1][(j + _m < _n ? (j + _m) : (j + _m) - _n)]]},j };
			}
			sort(sorted.begin(), sorted.end());
			for (int j = 0; j < _n; j++) p[i][j] = sorted[j].second;
			for (int j = 0, _c = 0; j < _n;)
			{
				pair<int, int> x = sorted[j].first;
				while (j < _n and sorted[j].first == x)
				{
					c[i][j] = _c;
					j++;
 
				}
				_c++;
			}
		}
		suffixArray = vector<int>(_n - 1);
		for (int i = 1; i < _n; i++)
			suffixArray[i - 1] = p[_log][i];
 
		lcp = vector<int>(_n - 1);
 
 
		for (int j = 0; j < _n; j++)
			inv[_log][p[_log][j]] = j;
 
		for (int i = 1; i < _n - 1; i++)
		{
			int _i = p[_log][i];
			int _j = p[_log][i + 1];
			for (int j = _log, _m = (1 << _log); j >= 0; j--)
			{
				if (c[j][inv[j][_i]] == c[j][inv[j][_j]])
				{
					_i = (_i + _m < _n ? (_i + _m) : (_i + _m) - _n);
					_j = (_j + _m < _n ? (_j + _m) : (_j + _m) - _n);
					lcp[i - 1] += _m;
				}
				_m /= 2;
			}
		}
 
 
 
 
 
	}
public:
	suffix(string _s) :s(_s)
	{
		_n = (int)s.size();
		s += '$';
		s = s;
		_n++;
		buildSuffixArray();
	}
	vector<int> get_suffixArray()
	{
		return suffixArray;
	}
	vector<int> get_lcp()
	{
		return lcp;
	}
 
 
};