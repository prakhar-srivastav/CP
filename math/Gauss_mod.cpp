 https://codeforces.com/contest/1616/problem/F
//#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector")
#include<iostream>
#include<utility>
#include<assert.h>
#include<vector>
#include<set>
using namespace std;
#define ll long long
#define endl '\n'
#define endl2(j,x) (j==x-1?"\n":"")
#define pb push_back
#define ff first
#define ss second




#define si(x) int(x.size())
#define sum_all(a)     ( accumulate ((a).begin(), (a).end(), 0ll))
#define mine(a)    (*min_element((a).begin(), (a).end()))
#define maxe(a)    (*max_element((a).begin(), (a).end()))
#define mini(a)    ( min_element((a).begin(), (a).end()) - (a).begin())
#define maxi(a)    ( max_element((a).begin(), (a).end()) - (a).begin())


int n, m;
vector<vector<int>> adj;
vector<vector<int>> edgeColor, edgeId;
vector<pair<int, int>> revId;
vector<int> gauss(vector<vector<int>> arr)
{
    int row = arr.size();
    int col = (int)(arr[0].size()) - 1;
    vector<int> basis(col, -1);

    for (int c = 0, r = 0; c < col and r < row; c++)
    {
        int cur = -1;
        for (int i = r; i < row; i++)
        {
            if (arr[i][c] != 0)
            {
                cur = i;
                break;
            }
        }
        if (cur == -1) continue;

        swap(arr[r], arr[cur]);
        basis[c] = r;

        if (arr[r][c] == 2)
        {
            for (int j = 0; j < col + 1; j++)
                arr[r][j] = (arr[r][j] * 2) % 3;
        }
       
        for (int i = 0; i < row; i++)
        {
            if (i != r)
            {
                if (arr[i][c] == 0) continue;
                else if (arr[i][c] == 2)
                {
                    for (int j = 0; j < col + 1; j++)
                        arr[i][j] = (arr[i][j] * 2) % 3;
                }
               
                for (int j = 0; j < col + 1; j++)
                {
                    arr[i][j] = (arr[i][j] - arr[r][j] + 18) % 3;
                }

            }
        }
   
        r++;
    }
    vector<int> solution(col);
    for (int c = 0; c < col; c++)
    {
        if (basis[c] != -1)
        {
            if (arr[basis[c]][c] == 2)
            {
                int r = basis[c];
                for (int i = 0; i < col + 1; i++) arr[r][i] = (arr[r][i] * 2) % 3;
           }
            solution[c] = arr[basis[c]][col];
        }
    }
    for (int i = 0; i < row; i++)
    {
        int sum = 0;
        for (int j = 0; j < col; j++)
        {
            sum = sum + (solution[j] * arr[i][j]) % 3;
            sum %= 3;
        }
        if (sum != arr[i].back()) return vector<int>{};
    }
    return solution;
}
void solve()
{
    adj.clear();
    cin >> n >> m;
    adj.resize(n);
    edgeColor.clear();
    edgeColor = vector<vector<int>>(n, vector<int>(n, INT_MAX));
    edgeId.clear();
    edgeId = vector<vector<int>>(n, vector<int>(n, INT_MAX));
    revId.clear();
    for (int i = 0; i < m; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--, c--;
        if (c == -2) c++;
        adj[a].pb(b);
        adj[b].pb(a);
        if (a > b)
            swap(a, b);
        edgeColor[a][b] = c;
        edgeColor[b][a] = c;
        edgeId[a][b] = i;
        edgeId[b][a] = i;
        revId.pb({ a,b });
    }

    vector<vector<int>> equations;

    for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) for (int k = j + 1; k < n; k++)
    {
        if (edgeColor[i][j] != INT_MAX and edgeColor[j][k] != INT_MAX and edgeColor[k][i] != INT_MAX)
        {
            equations.push_back(vector<int>{edgeId[i][j], edgeId[j][k], edgeId[k][i]});
        }
    }
    for (auto& equation : equations)
    {
        vector<int> array(m + 1);
        for (auto i : equation)
        {
            int a = revId[i].ff;
            int b = revId[i].ss;
            if (edgeColor[a][b] != -1) array[m] = (array[m] - edgeColor[a][b] + 18) % 3;
            else array[i] = 1;
        }
        equation = array;
    }

    if (si(equations) == 0)
    {
        for (int i = 0; i < m; i++)
        {
            int a = revId[i].ff;
            int b = revId[i].ss;
            if (edgeColor[a][b] != -1) cout << edgeColor[a][b] + 1 << " ";
            else cout <<  1 << " ";
        }
        cout << endl;
        return; 
    }
    auto solution = gauss(equations);

    if (si(solution) == 0)
    {
        cout << -1 << endl;
        return;
    }
    else
    {
        for (int i = 0; i < m; i++)
        {
            int a = revId[i].ff;
            int b = revId[i].ss;
            if (edgeColor[a][b] != -1) cout << edgeColor[a][b]+1 << " ";
            else cout << solution[i]+1   << " ";
        }
        cout << endl;

    }
}


signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);




    int t; cin >> t; while (t--)
        solve();

}
 
