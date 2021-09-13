template<class S,
    S(*op)(S, S),
    S(*e)(),
    class F,
    S(*mapping)(F, S),
    F(*composition)(F, F),
    F(*id)()
> struct treap {
private:

    struct node {
        int prior, size;
        S val, q;
        F lazy;
        bool rev;
        struct node* l, * r;
        node() : prior(rand()), size(1), val(e()), q(e()), lazy(id()), rev(false), l(NULL), r(NULL) {}
        node(S x) : prior(rand()), size(1), val(x), q(x), lazy(id()), rev(false), l(NULL), r(NULL) {}
    };
    node* t;
    typedef node* pnode;



    int sz(pnode& t) {
        return t ? t->size : 0;
    }
    void upd_sz(pnode& t) {
        if (t)t->size = sz(t->l) + 1 + sz(t->r);
    }

    void lazy(pnode& t) {

        if (t != NULL)
        {
            t->val = mapping(t->lazy, t->val);
            t->q = mapping(t->lazy, t->q);
            if (t->l) t->l->lazy = composition(t->lazy, t->l->lazy);
            if (t->r)t->r->lazy = composition(t->lazy, t->r->lazy);
            t->lazy = id();
        }
        if (t && t->rev)
        {
            t->rev = false;
            swap(t->l, t->r);
            if (t->l)  t->l->rev ^= true;
            if (t->r)  t->r->rev ^= true;
        }
    }


    void reset(pnode& t) {
        if (t)t->q = t->val;
    }
    void combine(pnode& t, pnode& l, pnode& r) {
        if (!l || !r)t = l ? l : r;
        else t->q = op(l->q, r->q);
    }
    void operation(pnode& t) {
        if (!t)return;
        reset(t);
        lazy(t->l);
        lazy(t->r);
        combine(t, t->l, t);
        combine(t, t, t->r);
    }



    void heapify(pnode& t) {
        if (t == NULL) return;
        pnode temp = t;
        if (t->l != NULL && t->l->prior > temp->prior)
            temp = t->l;
        if (t->r != NULL && t->r->prior > temp->prior)
            temp = t->r;
        if (temp != t) {
            swap(t->prior, temp->prior);
            heapify(temp);
        }
    }

    pnode build(S* a, int n) {

        if (n == 0) return NULL;
        int mid = n / 2;
        pnode t = new node(a[mid]);
        t->l = build(a, mid);
        t->r = build(a + mid + 1, n - mid - 1);
        heapify(t);
        upd_sz(t);
        operation(t);
        return t;
    }





    void split(pnode t, pnode& l, pnode& r, int pos, int add = 0) {
        if (!t)
        {
            l = r = NULL;
            return;
        }
        lazy(t);
        int curr_pos = add + sz(t->l);
        if (curr_pos <= pos)
            split(t->r, t->r, r, pos, curr_pos + 1), l = t;
        else
            split(t->l, l, t->l, pos, add), r = t;
        upd_sz(t);
        operation(t);
    }
    void merge(pnode& t, pnode l, pnode r) {
        lazy(l);
        lazy(r);
        if (!l || !r) t = l ? l : r;
        else if (l->prior > r->prior)merge(l->r, l->r, r), t = l;
        else    merge(r->l, l, r->l), t = r;
        upd_sz(t);
        operation(t);
    }

    S range_query(pnode& t, int l, int r) {
        assert(t != NULL);
        pnode L, mid, R;

        split(t, L, mid, l - 1);
        split(mid, t, R, r - l);

        S ans = t->q;
        merge(mid, L, t); merge(t, mid, R);
        return ans;
    }
    void range_update(pnode& t, int l, int r, F val) {
        assert(t != NULL);
        pnode L, mid, R;
        split(t, L, mid, l - 1);
        split(mid, t, R, r - l);
        t->lazy = composition(val, t->lazy);
        merge(mid, L, t);
        merge(t, mid, R);
    }
    void range_update(pnode& t, int l, int r, S val) {
        pnode L, mid, R;
        split(t, L, mid, l - 1);
        split(mid, t, R, r - l);
        t = new node(val);
        merge(mid, L, t); merge(t, mid, R);
    }
    void del(pnode& t, int pos) {
        
       
        if (pos == 0)
        {
            pnode L;
            split(t, L, t, 0);
            free(L);
            return;
        }
        pnode L, mid, R;
        split(t, L, mid, pos - 1);
        split(mid, t, R, 0);
        free(t);
        merge(t, L, R);

    }
    void ins(pnode& t, int pos, S val) {
        pnode L, mid, R;

        if (t == NULL)
        {
            t = new node(val);
            return;
        }
      
        if(pos == 0)
        {
            pnode t1 = new node(val);
            merge(t, t1, t);
            return;
        }
        assert(t != NULL);
        split(t, L, R, pos-1);
        t = new node(val);
        merge(mid, L, t);
        merge(t, mid, R);
    }

    void reverse(pnode& t, int l, int r, F val = id()) {
        pnode t1, t2, t3;
        split(t, t1, t2, l - 1);
        split(t2, t2, t3, r - l);
        t2->rev ^= true;
        t2->lazy = composition(val, t2->lazy);
        merge(t, t1, t2);
        merge(t, t, t3);
    }
public:
    treap() : t(NULL) {}
    treap(int n) : t(NULL)
    {
        vector<S> v(n, e());
        int x = (int)(v.size());
        S* a = &v[0];
        t = build(a, x);
    }
    treap(vector<S>& v) : t(NULL)
    {

        int x = (int)(v.size());
        S* a = &v[0];
        t = build(a, x);
    }

    void ins(int pos, S val)
    {
       
        ins(t, pos, val);
    }
    void del(int pos)
    {
        del(t, pos);
    }
    void update(int l, int r, F val)
    {
        range_update(t, l, r, val);
    }
    void replace(int pos, S val)
    {
        range_update(t,pos, pos, val);
    }
    int size()
    {
        return  sz(t);
    }
    S query(int l, int r)
    {
        return  range_query(t, l, r);
    }
    /* If reverse operation results in the modification of S value, then you have to handle it*/
    /* The queries where you dont handle it includes sum,max query etc*/
    void reverse(int l, int r, F val = id())
    {
        reverse(t, l, r, val);
    }
    S at(int pos)
    {
        return query(pos,pos);
    }
};






struct S
{
	ll sum, len; 
};
struct F
{
	ll a,b;
};
S op(S l, S r)
{
	return S{ l.sum+r.sum,l.len+r.len };
}
S e()
{
	return S{0,0};
}
S mapping(F l, S r)
{
	ll a = r.sum*l.a + r.len * l.b;
	return S{ a,r.len };
}
F composition(F l, F r)
{
	ll a, b;
	a = l.a * r.a;
	b = l.a * r.b + l.b;
	return F{ a,b };
}
F id() {
	return F{1,0};
}
