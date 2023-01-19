int k;
multiset<int> l, r;
int sum = 0;
void __insert(int a)
{

    if (l.size() < k)
    {
        l.insert(a);
        sum += a;
    }
    else
    {
        auto itr = l.rbegin();
        int lst = *itr;
        if (lst > a)
        {
            l.erase(l.find(lst));
            r.insert(lst);
            l.insert(a);
            sum += a - lst;
        }
        else
        {
            r.insert(a);
        }
    }
}

void __remove(int a)
{
    if (r.size() > 0 and r.find(a) != r.end())
    {
        r.erase(r.find(a));
        return;
    }
    else
    {
        l.erase(l.find(a));
        int fst = 0;
        if(r.size()>0)
            {
                auto itr = r.begin();
                fst = *(itr);
                r.erase(itr);
                l.insert(fst);
            }
        sum += fst - a;
    }
}

/*
https://atcoder.jp/contests/abc281/tasks/abc281_e
https://codingcompetitions.withgoogle.com/kickstart/round/00000000008cb409/0000000000bef943
*/
