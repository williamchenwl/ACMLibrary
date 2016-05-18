int dfn[N],ctl[N],ctr[N],ti = 0;

int dfs(int u){ 
	vis[u] = 1; ctl[u] = dfn[u] = ++ti;
	for (int i = base[u];i;i = nxt[i])
		dfs(to[i]);
	ctr[u] = ti;
}