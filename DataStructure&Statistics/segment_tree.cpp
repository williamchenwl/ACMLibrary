typedef struct segment_tree{ 
	int siz,tot;
	int sl[N],sr[N];
	int tl[N],tr[N];
	ll sum[N],flag[N];

	int init(int x){ 
		siz = x; tot = 0;
		memset(sl,0,sizeof(l));
		memset(sr,0,sizeof(r));
		memset(sum,0,sizeof(sum));
		memset(flag,0,sizeof(flag));
	}

	int up(int x){ 
		if (!flag[x]) return 0;
		int mid = (l + r) >> 1;
		sum[x] += flag[x] * (tr[x] - tl[x] + 1);
		flag[sl[x]] += flag[x];
		flag[sr[x]] += flag[x];
		return flag[x] = 0;
	}

	int update(int x){ 
		if (tl[x] == tr[x]) return 0;
		int mid = (l + r) >> 1;
		up(x); up(sl[x]); up(sr[x]);
		sum[x] = sum[sl[x]] + sum[sr[x]];
	}

	int build(int l,int r){ 
		int x = ++tot;
		tl[x] = l; tr[x] = r;
		if (l == r) return x;
		int mid = (l + r) >> 1;
	    sl[x] = build(l,mid);
	    sr[x] = build(mid + 1,r);
	    update(x);
	}

	int add(int x,int lx,int rx,ll c){ 
		if (tl[x] >= lx && tr[x] <= rx) return flag[x] += c;
		int mid = (l + r) >> 1; up(x);
		if (mid >= lx) add(sl[x],lx,rx,c);
		if (mid < rx) add(sr[x],lx,rx,c);
		update(x);
	}

	int query(int x,int lx,int rx){ 
		update(x);
		if (tl[x] >= lx && tr[x] <= rx) return sum[x];
		int mid = (l + r) >> 1; ll ans = 0;
		if (mid >= lx) ans += query(sl[x],lx,rx);
		if (mid < rx) ans += query(sr[x],lx,rx);
		return ans;
	}

}segment_tree;

segment_tree Seg;
