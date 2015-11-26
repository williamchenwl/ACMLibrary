typedef struct Fenwick_Tree{  
	
	ll C[N];
	int siz;
	
	int init(int x){ 
		for (int i = 0;i <= x+1;i++) C[i] = 0;
		return siz = x;
	}

	int lowbit(int x){ 
		return x & (-x);
	}

	int add(int x,ll t){ 
		for (;x <= siz;x += lowbit(x)) 
		   C[x] += t;
	}

	ll sum(int x){ 
		ll ans = 0;
		for (;x;x -= lowbit(x)){ 
			ans += C[x];
		}
		return ans;
	}

	ll intersum(int l,int r){ 
		if (l > r) return 0;
		return sum(r) - sum(l-1);
	}

}Fenwick_Tree;

Fenwick_Tree Fen;


