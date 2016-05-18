typedef long long ll;

typedef struct Gra{ 
	ll base[N];
	ll nxt[M],now[M];
	ll tot;
	void init(){ 
		tot = 0;
		memset(base,0,sizeof(base));
	}
	void add(int x,int y){ 
		now[++tot] = y;
		nxt[tot] = base[x];
		base[x] = tot;
	}
}Gra;


Gra G1,G2;

int t,q[N],f[N];

void dfs1(int x){ 
	vis[x] = 1;
	for (int i = G1.base[x];i;i = G1.nxt[i]){ 
		int y = now[i];
		if (!vis[y]) dfs1(y);
	}
	q[++t] = x;
}

void dfs2(int x,int y){ 
	vis[x] = 0;
	f[x] = y;
	for (int i = G1.base[x];i;i = nxt[i]){ 
		int y = now[i];
		if (vis[y]) dfs2(y,x);
	}
}
