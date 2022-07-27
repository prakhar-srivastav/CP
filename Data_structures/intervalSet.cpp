/*

Properties:
1. The intervalSet data structure stores all the ranges and make sure that the ranges with same values remains connected if they are adjacent.
2. Useful in some query based tasks where we have limited number of insertion operations and it basically make deletion also limited since
   it is related to insertions only.
3. By defining intervalSet with true, we will also mantain the color info, which will probably make the operations slow as it will add extra cost to
   the operation but just putting a check, [Default value is set to false]

void _insert(int l,int r,T val,bool overRide=false): It will insert the range[l,r] into the set with value [val]. At the same time, it will ensure the property of the intervalSet.
                                                overRide = False --> It must hold that (l,r) is previously empty other it will assert false
                                                overRide = True --> If there are any previous value, it will overide it.
                                                Default value is False

int _erase(int l,int r): It will erase all the ranges within (l,r) and return the count of number of deleted ranges.

vector<pair<pair<int,int>,T>> _fetch(int l,int r): It will fetch all the ranges within the range [l,r]
*/
template <class T> struct intervalSet
{
private:
    bool mantainColorInfo = false;
    map<pair<int, int>, T> dict;
    map<T, set<pair<int, int>>> col;

    void __insert(int l, int r, T val)
    {
        dict[{l, r}] = val;
        if (mantainColorInfo)
            col[val].insert({ l,r });
    }
    void __erase(int l, int r, T val)
    {
        // assert(dict[{l,r}]==val);
        dict.erase({ l,r });
        if (mantainColorInfo)
            col[val].erase({ l,r });
    }
public:
    intervalSet() : intervalSet(false) {}
    intervalSet(bool col) : mantainColorInfo(col)
    {
        dict = {};
        col = {};
    }

    int _erase(int l, int r)
    {
        int cnt = 0;
        auto itr = dict.upper_bound({ l,-1 });
        if (itr != dict.begin())
            itr--;
        vector<pair<pair<int, int>, T>> toInsert;
        while (itr!=dict.end() and (*itr).ff.ff <= r)
        {
            int l0 = (*itr).ff.ff;
            int r0 = (*itr).ff.ss;
            T val = (*itr).ss;
            // overlap check
            if (max(l0, l) <= min(r0, r))
            {
                itr = next(itr);
                __erase(l0, r0, val);
                if (l0 < l) toInsert.push_back({ {l0, l - 1}, val});
                if (r < r0) toInsert.push_back({ {r + 1,r0},val });
                cnt++;
            }
            else
            {
                itr = next(itr);
            }
            
        }
        for (auto& item : toInsert) dict[{item.ff.ff,item.ff.ss}] = item.ss;
        return cnt;
    }
    void _insert(int l, int r, T val)
    {
        _erase(l, r);
        auto itr = dict.upper_bound({ l,-1 });
        if (itr != dict.begin())
        {
            auto p = prev(itr);
            int r0 = (*p).ff.ss;
            int l0 = (*p).ff.ff;
            T val0 = (*p).ss;
            if (r0 + 1 == l and val == val0)
            {
                __erase(l0, r0, val);
                l = l0;
            }
        }

        if (itr != dict.end() and next(itr) != dict.end())
        {
            auto n = next(itr);
            int r0 = (*n).ff.ss;
            int l0 = (*n).ff.ff;
            T val0 = (*n).ss;
            if (r + 1 == l0 and val == val0)
            {
                __erase(l0, r0, val);
                r = r0;
            }
        }
        __insert(l, r, val);
    }

    vector<pair<pair<int, int>, T>> _fetch(int l, int r)
    {

        vector<pair<pair<int, int>, T>> res;
        auto itr = dict.upper_bound({ l,-1 });
        if (itr != dict.begin())
            itr--;

        while (itr!=dict.end() and (*itr).ff.ff <=r)
        {
            int l0 = (*itr).ff.ff;
            int r0 = (*itr).ff.ss;
            T val = (*itr).ss;
            // overlap check
            if (max(l0, l) <= min(r0, r))
                res.push_back({{ max(l0,l),min(r0,r) }, val});
            itr = next(itr);
            
        }
        return res;

    }
};








