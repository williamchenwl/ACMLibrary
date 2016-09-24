/*
    correctly used times = 
    used in = { 
   	
    }
*/
//动态树
typedef struct link_cut_tree{ 

	int son[N][2],sum[N],f[N],key[N],tag[N];

	//更新部分
	int up(int x){ 
		sum[x] = sum[son[x][0]] + sum[son[x][1]] + key[x];
		//
		//
	}

	/判断是否为根
	bool isroot(int x){ 
		return !f[x] || son[f[x]][0] != x && son[f[x]][1] !=x;
	} 

	int reverse(int x){ 
		swap(son[x][0],son[x][1]);
		tag[x] ^= 1;
	}

	int pd(int x){ 
		if (tag[x]){ 
			reverse(son[x][0]);
			reverse(son[x][1]);
			tag[x] = 0;
		}
		//
		//
	}

	int rotate(int x){ 
		int y = f[x];
		int w = (son[y][0] == x);
		son[y][!w] = son[x][w];
		if (son[x][w]) f[son[x][w]] = y;
		if (f[y]){ 
			int z = f[y];
			if (son[z][0] == y) son[z][0] = x;
			if (son[z][1] == y) son[z][1] = x;
		}
		f[x] = f[y]; f[y] = x; son[x][w] = y;
		up(y); up(x);
	}

	stack<int>S;

	int splay(int x){ 
		for (int y = x;!isroot(y);y = f[y]) S.push(y);
		for (;!S.empty();S.pop()) pb(S.top());
		while (!isroot(x)){ 
			int y = f[x];
			if (!isroot(y)){ 
				if ((son[f[y]][0] == y)^(son[y][0] == x))
					rotate(x); else rotate(y);
				rotate(x);
			}
		}
		up(x);
	}

	int access(int x){ 
		for (int y = 0;x;y = x,x = f[x]){ 
			splay(x); son[x][1] = y; up(x);
		}
	}

	int root(int x){ 
		access(x);
		splay(x);
		while (son[x][0]) x = son[x][0];
		return x;
	}

	int makeroot(int x){ 
		access(x);
		splay(x);
		reverse(x);
	}

	int link(int x,int y){ 
		makeroot(x);
		f[x] = y;
		access(x);
	}

	int ask_sum(int x,int y){ 
		makeroot(x);
		access(y);
		splay(x);
		return sum[x];
	}

}link_cut_tree;
