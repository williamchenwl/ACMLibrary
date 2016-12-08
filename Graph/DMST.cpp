struct EDGE{
    int u,v,cost;
	EDGE(){}
	EDGE(int a,int b,int c):u(a),v(b),cost(c){}
}E[M];

typedef struct DMST{
	int n,siz,pre[N],id[N],vis[N],in[N];
	void init(int _n){n = _n,siz = 0;}
	void add(int u,int v,int w){
		E[siz].u = u;
		E[siz].v = v;
		E[siz++].cost = w;
	}
	int dmst(int root){
		int u,v,cnt,ret = 0;
		while(1){
			for (int i = 0;i < n;i++) in[i] = inf;
			for (int i = 0;i < siz;i++){
				u = E[i].u; v = E[i].v;
				if (E[i].cost < in[v] && u != v){
					pre[v] = u,in[v] = E[i].cost;
					if (u == root) ROOT = i;
				}
			}
			for (int i = 0;i < n;i++)
				if (i != root && in[i] == inf) return -1;
			memset(vis,-1,sizeof(vis));
			memset(id,-1,sizeof(id));
            cnt = in[root] = 0;
			for (int i = 0;i < n;i++) id[i] = vis[i] = -1;
			for (int i = 0;i < n;i++){
				ret += in[i],v = i;
				while(vis[v] != i && id[v] == -1 && v != root)
					vis[v] = i,v = pre[v];
				if (v != root && id[v] == -1){
					for (u = pre[v];u != v;u = pre[u]) id[u] = cnt;
					id[v] = cnt++;
				}
			}
            if (!cnt) return ret;
			for (int i = 0;i < n;i++)if(id[i] == -1) id[i] = cnt++;
			for (int i = 0;v = E[i].v,i < siz;i++){
				E[i].u = id[E[i].u],E[i].v = id[E[i].v];
				if (E[i].u != E[i].v) E[i].cost -= in[v];
			}
			n = cnt;
			root = id[root];
			}
			return ret;
		}
}DMST;

DMST G;