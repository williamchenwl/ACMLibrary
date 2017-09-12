#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

const int MAXN = 100005;
const int N = MAXN;

int T;
int n, m;

int f[N],son[N][2];

int val[N],sum[N],siz[N],mx[N];

int rev[N],flag[N];

void LCTInit(){
	memset(son,0,sizeof(son));
	memset(f,0,sizeof(f));
	memset(rev,0,sizeof(rev));
	memset(val,0,sizeof(val));
	memset(sum,0,sizeof(sum));
	memset(flag,0,sizeof(flag));
	memset(mx,0,sizeof(mx));
}

bool isroot(int x){
	return !f[x] || (son[f[x]][0] != x && son[f[x]][1] != x);
}

void reverse(int x){
	if (!x) return;
	swap(son[x][0],son[x][1]);
	rev[x]^=1;
}

void add(int x,int c){
	if (!x) return;
	sum[x] = c * siz[x];
	val[x] = c;
	mx[x] = c;
	flag[x] = c;
}

void pb(int x){
	if (rev[x])
	reverse(son[x][0]),reverse(son[x][1]),rev[x] = 0;
	if (flag[x])
	add(son[x][0],flag[x]),add(son[x][1],flag[x]),flag[x] = 0;
}

inline void up(int x){
	pb(x); siz[x] = 1; sum[x] = val[x]; mx[x] = val[x];
	if (son[x][0]) siz[x] += siz[son[x][0]],sum[x] += sum[son[x][0]],mx[x] = max(mx[x],mx[son[x][0]]);
	if (son[x][1]) siz[x] += siz[son[x][1]],sum[x] += sum[son[x][1]],mx[x] = max(mx[x],mx[son[x][1]]);
}

inline void rotate(int x){
	int y = f[x],w = son[y][1] == x;
	son[y][w] = son[x][w^1];
	if (son[x][w^1]) f[son[x][w^1]] = y;
	if (f[y]){
		int z = f[y];
		if (son[z][0] == y) son[z][0] = x;
		if (son[z][1] == y) son[z][1] = x;
	}
	f[x] = f[y]; f[y] = x;
	son[x][w^1] = y; up(y);
}

int tmp[N];

void splay(int x){
	int s = 1,i = x,y; tmp[1] = i;
	while(!isroot(i)) tmp[++s] = i = f[i];
	while(s) pb(tmp[s--]);
	while(!isroot(x)){
		y = f[x];
		if (!isroot(y)){
			if ((son[f[y]][0] == y) ^ (son[y][0] == x))
			rotate(x); else rotate(y);
		}
		rotate(x);
	}
	up(x);
}

void access(int x){
	for (int y = 0;x;y = x,x = f[x])
		splay(x),son[x][1] = y,up(x);
}

int root(int x){
	access(x);
	splay(x);
	while(son[x][0]) x = son[x][0];
	return x;
}

void makeroot(int x){
	access(x);
	splay(x);
	reverse(x);
}

void link(int x,int y){
	makeroot(x);
	f[x] = y;
	access(x);
}

void cutf(int x){
	access(x);
	splay(x);
	f[son[x][0]] = 0;
	son[x][0] = 0;
	up(x);
}

void cut(int x,int y){
	makeroot(x);
	cutf(y);
}

int find(int x){
	access(x);
	splay(x);
	int y = x;
	while(son[y][0]) y = son[y][0];
	return y;
}

inline int lca(int x,int y){
	int ans; access(y); y = 0;
	do{
		splay(x); if (!f[x]) ans = x;
		x = f[y = x];
	}while(x);
	return ans;
}

vector<int> gedges[MAXN], tedges[MAXN];

int tot = 1;

int base[N],nxt[N],now[N];

void add_e(int x,int y){  
	now[++tot] = y; nxt[tot] = base[x]; base[x] = tot;
	now[++tot] = x; nxt[tot] = base[y]; base[y] = tot;
}

struct Tarjan{  
	
	int dfn[N],low[N],f[N],from[N],cut[N],cnt,tot;

	void tarjan(int x){  
		dfn[x] = low[x] = ++tot;
		for (int i = base[x];i;i = nxt[i]){  
			int y = now[i];
			if (!dfn[y]){  
				f[y] = i >> 1;
				tarjan(y);
				if (low[x] > low[y]) low[x] = low[y];
			}else if (f[x] != (i >> 1) && low[x] > dfn[y])
					low[x] = dfn[y];
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
		for (int i = 1;i <= n;i++) if(!dfn[i]) tarjan(i);
		for (int i = 1;i <= n;i++)
			if (!from[i]) dfs(i,++cnt);
	}

};

int make_graph(int n,int m){  
	memset(base,0,sizeof(base));
	tot = 1;
	for (int i = 1;i <= m;i++){  
		int x,y; scanf("%d%d",&x,&y);
		add_e(x,y);
	}
}

int deep[MAXN];
int fa[MAXN][22];
int st[MAXN], ed[MAXN], _tot;
int siz[MAXN], max_son[MAXN];

Tarjan Tx;
int ufs[N];
int fin(int x){  
	if (ufs[x] == x) return x;
	else return ufs[x] = fin(ufs[x]);
}

void make_ng(int n){  
	for (int i = 1;i <= Tx.cnt;i++) ufs[i] = i;
	for (int i = 1;i <= n;i++)
		for (int j = base[i];j;j = nxt[j]){  
			int y = now[j];
			if (fin(Tx.from[y]) != fin(Tx.from[i])){  
				link(Tx.from[y],Tx.from[i]);
				ufs[fin(Tx.from[y])] = fin(Tx.from[i]);
			}
		}
}

int main() {
	freopen("g.in", "r", stdin);
	scanf("%d", &T);
	for (int cas = 1; cas <= T; cas++) {
		scanf("%d %d", &n, &m);
		for (int i = 1; i <= n; i++) {
			gedges[i].clear();
			tedges[i].clear();
		}
		tot = 1;
		make_graph(n, m);
		Tx.init(n);
		make_ng(n);
		LCTInit();
		int q;
		scanf("%d", &q);
		int op, a, b;
		while (q--) {
			scanf("%d%d%d",&op,&a,&b);
			makeroot(a); access(b);
			if (op == 0){
				splay(b); add(b,0)
			}else{  
				printf("%d\n",sum(a));
			}
		}
	return 0;
}
