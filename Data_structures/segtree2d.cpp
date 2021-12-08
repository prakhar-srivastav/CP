struct segtree_2d
{
  	private:
	int N,M;
	vector<vector<int>> a,t;
	
	int op(int a,int b)
	{
		return max(a,b);
	}



	void build_y(int vx, int lx, int rx, int vy, int ly, int ry)
	{
    if (ly == ry) {
        if (lx == rx)
            t[vx][vy] = a[lx][ly];
        else
            t[vx][vy] = op(t[vx*2][vy],t[vx*2+1][vy]);
    } else {
        int my = (ly + ry) / 2;
        build_y(vx, lx, rx, vy*2, ly, my);
        build_y(vx, lx, rx, vy*2+1, my+1, ry);
        t[vx][vy] = op(t[vx][vy*2],t[vx][vy*2+1]);  
    }
	}


void build_x(int vx, int lx, int rx) {
    if (lx != rx) {
        int mx = (lx + rx) / 2;
        build_x(vx*2, lx, mx);
        build_x(vx*2+1, mx+1, rx);
    }
    build_y(vx, lx, rx, 1, 0, M-1);
}


int sum_y(int vx, int vy, int tly, int try_, int ly, int ry) {
    if (ly > ry) 
        return 0;
    if(ly>try_ or ry<tly or tly>try_ ) return 0;
    if (ly <= tly && try_ <= ry)
        return t[vx][vy];
    int tmy = (tly + try_) / 2;
    return op(sum_y(vx, vy*2, tly, tmy, ly, ry)
           ,sum_y(vx, vy*2+1, tmy+1, try_, ly, ry));
}

int sum_x(int vx, int tlx, int trx, int lx, int rx, int ly, int ry) {
    if (lx > rx)
        return 0;
    if(lx>trx or rx<tlx or tlx>trx ) return 0;
    if (lx <= tlx && trx <= rx)
        return sum_y(vx, 1, 0, M-1, ly, ry);
    int tmx = (tlx + trx) / 2;
    return op(sum_x(vx*2, tlx, tmx, lx, rx, ly, ry)
           ,sum_x(vx*2+1, tmx+1, trx, lx, rx, ly, ry));

}
void update_y(int vx, int lx, int rx, int vy, int ly, int ry, int x, int y, int new_val) {
    if (ly == ry) {
        if (lx == rx)
            t[vx][vy] = new_val;
        else
            t[vx][vy] = op(t[vx*2][vy],t[vx*2+1][vy]);
    } else {
        int my = (ly + ry) / 2;
        if (y <= my)
            update_y(vx, lx, rx, vy*2, ly, my, x, y, new_val);
        else
            update_y(vx, lx, rx, vy*2+1, my+1, ry, x, y, new_val);
        t[vx][vy] = op(t[vx][vy*2],t[vx][vy*2+1]);
    }
}

void update_x(int vx, int lx, int rx, int x, int y, int new_val) {
    if (lx != rx) {
        int mx = (lx + rx) / 2;
        if (x <= mx)
            update_x(vx*2, lx, mx, x, y, new_val);
        else
            update_x(vx*2+1, mx+1, rx, x, y, new_val);
    }
    update_y(vx, lx, rx, 1, 0, M-1, x, y, new_val);
}

 


	public:
	segtree_2d (vector<vector<int>> &arr) : N(si(arr[0])), M(si(arr[1]))
	{
		a=arr;
		t=vector<vector<int>>(N*4+1,vector<int>(N+4+1));
		build_x(1,0,N-1);
	}

	int query(int lx,int ly,int rx,int ry)
	{
		return sum_x(1,0,N-1,lx,rx,ly,ry);
	}

	void update(int x,int y,int new_val)
	{
		update_x(1,0,N-1,x,y,new_val);
	}
};
