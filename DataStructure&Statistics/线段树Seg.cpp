/*
    correctly used times = 1
    used in = { 
   		hdu5634,
    }
*/
//线段树
//
typedef long long ll;

typedef struct segment_tree{ 
	int siz,tot;
	int sl[N],sr[N];
	int tl[N],tr[N];
	ll sum[N],flag[N],mx[N];

	int init(int x){ 
		siz = x; tot = 0;
		memset(sl,0,sizeof(sl));
		memset(sr,0,sizeof(sr));
		memset(sum,0,sizeof(sum));
		memset(flag,0,sizeof(flag));
	}

	inline void tagit(int x,int c){ 
		mx[x] = flag[x] = c;
		sum[x] = (long long)(tr[x] - tl[x] + 1) * c;
	}

	inline void pd(int x){ 
	    if (flag[x] && tl[x] != tr[x]){
		tagit(sl[x]);
		tagit(sr[x]);
		flag[x] = 0;
		}
	}

	inline void update(int x){
		sum[x] = sum[sl[x]] + sum[sr[x]];
		mx[x] = max(mx[sl[x]],mx[sr[x]]);
	}

	int build(int l,int r){
		int x = ++tot;
		tl[x] = l; tr[x] = r;
		if (l == r) return mx[x] = sum[x] = a[l],x;
		int mid = (l + r) >> 1;
	    sl[x] = build(l,mid);
	    sr[x] = build(mid + 1,r);
	    update(x);
	    return x;
	}

	inline void add(int x,int lx,int rx,ll c){ 
		if (tl[x] >= lx && tr[x] <= rx) { 
			tagit(x,c);
			return;
		}
		int mid = (tl[x] + tr[x]) >> 1; 
		pd(x);
		if (mid >= lx) add(sl[x],lx,rx,c);
		if (mid < rx) add(sr[x],lx,rx,c);
		update(x);
	}

	int query(int x,int lx,int rx){ 
		if (tl[x] >= lx && tr[x] <= rx) return sum[x];
		pd(x);
		int mid = (tl[x] + tr[x]) >> 1; ll ans = 0;
		if (mid >= lx) ans += query(sl[x],lx,rx);
		if (mid < rx) ans += query(sr[x],lx,rx);
		return ans;
	}

}segment_tree;

segment_tree Seg;
