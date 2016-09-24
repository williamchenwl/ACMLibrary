typedef struct link_cut_tree{ 
	
	int son[N][2],f[N],key[N],tag[N],sum[N],M[N];

	int init(int size){ 
		for (int i = 0;i <= size+1;i++) M[i] = 1;
		memset(son,0,sizeof(0));
		memset(f,0,sizeof(f)); 
	}

    int up(int x){ 
    	sum[x] = sum[son[x][0]] + sum[son[x][1]] + key[x];
    	M[x] = M[son[x][0]] * M[son[x][1]] * key[x];
    }

	int isroot(int x){ 
		return !f[x] || son[f[x]][0] != x && son[f[x]][1] != x;
	}  

	int reverse(int x){ 
		swap(son[x][0],son[x][1]);
		tag[x] ^= 1;
	}

	int push_down(int x){ 
		if (tag[x]){ 
			reverse(son[x][0]);
			reverse(son[x][1]);
			tag[x] = 0;
		}
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
    	f[x] = f[y]; 
    	f[y] = x;
    	son[x][w] = y;
    	up(y);
    	up(x);
    }

    stack<int>S;

    int splay(int x){ 
    	int y = x;
    	S.push(y);
    	while (!isroot(y)) {S.push(f[y]); y = f[y];}
    	while (!isroot(x)){ 
    		int y = f[x];
    		if (!isroot(y)){ 
    			if ((son[f[y][0]][0] == y) ^ (son[y][0] == x))
    				rotate(x);
    			else rotate(y);
    		}
    		rotate(x);
    	}
    }

    int access(int x){ 
    	for (int y = 0,x;y = x;x = f[x]){ 
    		splay(x); 
    		son[x][1] = y;
    		up(x);
    	}
    }

    int root(int x){ 
    	access(x);
    	splay(x);
    	while(son[x][0]) x = son[x][0];
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
    	access(y);
    }
    
}link_cut_tree;
