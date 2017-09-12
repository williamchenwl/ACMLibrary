struct Graph{
	int n;
	vector<int>G[N];
	void init(int _n){
		n = _n;
		for (int i = 0;i < n;i++){
			G[i].clear();
		}
	}

	void add(int x,int y){
		G[x].push_back(y);
	}
};

int siz[N];

int n;

Graph G,nG;

int dfn[N],instack[N],low[N],st[N],belong[N];

int stamp = 0,stop = 0,cnt = 0;

void tarjan_init(int n){
	stamp = stop = 0;
	for (int i = 1;i <= n;i++)
		dfn[i] = instack[i] = low[i] = belong[i] = 0;
	cnt = 0;
}

void tarjan(int x){
	int y;
	dfn[x] = low[x] = ++stamp;
	instack[x] = 1;
	st[++stop] = x;
	for (int i = 0;i < G.G[x].size();i++){
		y = G.G[x][i];
		if (!dfn[y]){
			tarjan(y);
			if (low[y] < low[x])
				low[x] = low[y];
		}else if (instack[y] && dfn[y] < low[x])
				low[x] = dfn[y];
	}
	if (dfn[x] == low[x]){
		cnt++; int y;
		do{
			y = st[stop--];
			instack[y] = 0;
			belong[y] = cnt;
		}while(y != x);
	}
}


int main(){
	cin >> n;
	tarjan_init(n);
	for (int i = 1;i <= n;i++)
		if (!dfn[i]) tarjan(i);

	memset(hav,0,sizeof(hav));
	memset(siz,0,sizeof(siz));
	
	for (int i = 1;i <= cnt;i++) ind[i] = 0;
	nG.init(cnt);
	for (int i = 1;i <= n;i++){
		int x;
		siz[x = belong[i]]++;
		for (int j = 0;j < G.G[i].size();j++){
			int y = belong[G.G[i][j]];
			if(hav[x][y]) continue;
			if (x==y) continue;
			nG.add(x,y);
		}
	}
}
