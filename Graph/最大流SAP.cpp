int sap(int u,int flow){
	if (u == T) return flow;
	int tmp,rec = 0;
	for (int i = base[u];i;i = nxt[i]){
		int x = to[i];
		if (fl[i] <= 0 || d[u] != d[x] + 1) continue;
		tmp = sap(x,min(flow - rec,fl[i]));
		rec += tmp; fl[i] -= tmp; fl[op[i]] += tmp;
		if (rec == flow) return flow;
	}
	if (d[S] >= ntot) return rec;
	num[d[u]]--; if (!num[d[u]]) d[S] = ntot;
	num[++d[u]]++; return rec;
}

int nadd(int x,int y,int f){
	to[++tot] = y; fl[tot] = f;
	nxt[tot] = base[x]; base[x] = tot;
	op[tot] = tot + 1;
	to[++tot] = x; fl[tot] = 0;
	nxt[tot] = base[y]; base[y] = tot;
	op[tot] = tot - 1;
}