int dfn[N],low[N],num,cnt[N],q[N],t;

stack<int>tarjan_s;

void tarjan(int x){   
	dfn[x] = low[x] = ++num;
	tarjan_s.push(x);
	for (int i = 0;i < G[x].size();i++){   
		int y = G[x][i];
		tarjan(y);
		if (low[x] > low[y]) low[x] = low[y];
		if (dfn[x] <= low[x]){  
			cut[x] = 1;
			while(S.top() != x) 
		}
	}
}