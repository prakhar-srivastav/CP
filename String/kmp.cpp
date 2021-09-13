vector<ll> kmp(string & x)
{
    vector<ll> lcp(x.size()); 
    for (int i = 1, j = 0; i < x.size(); i++)
    {

        if (x[i] == x[j]) lcp[i] = ++j;
        else if (j > 0)
        {
            j = lcp[j - 1];
            i--;
        }

    }
    return lcp; 
}
vector<ll> find_occurences(string& x, string &y,  vector<ll>& lcp)
{
    vector<ll> ans;
    ll m = (ll)(y.size()); 
    for (ll i = 0,j=0; i < x.size(); i++)
    {
        if (x[i] == y[j]) j++;
        else if (j > 0)
        {
            j = lcp[j - 1]; 
            i--; 
        }

        if (j == m)
        {
            ans.push_back(i - m + 1);
            j = lcp[j - 1] ; 
        }
    }
    return ans; 
}
