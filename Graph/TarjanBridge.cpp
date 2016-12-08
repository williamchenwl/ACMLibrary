#include <cstdio>
#include <iostream>
#include <cstring>

struct Tarjan{  
	
	int dfn[N],low[N],f[N],from[N],cut[N],cnt;

	void tarjan(int x){  
		dfn[x] = low[x] = ++tot;
		for (int i = base[x];i;i = nxt[i]){  
			int y = now[i];
			if (!dfn[y]){  
				f[y] = i >> 1;
				tarjan(y);
				if (low[x] > low[y]) low[x] = low[y];
			}else 
		}
		if (f[x] && low[x] == dfn[x]) cut[f[x]] = 1;
	}

	void dfs(int x,int y){  
		from[x] = y;
		for (int i = base[x];i;i = nxt[i])
			if (!from[now[i]] && !cut[i >> 1])
				dfs(now[i],y);
	}

	void init(int n){  
		memset(dfn,0,sizeof(dfn));
		memset(low,0,sizeof(low));
		memset(from,0,sizeof(from));
		memset(cut,0,sizeof(cut));
		cnt = 0;
		tarjan(1);
		for (int i = 1;i <= n;i++)
			dfs(i,++cnt);
	}

	/*
		The ID of edges should start at 2
	*/
}Tarjan;

