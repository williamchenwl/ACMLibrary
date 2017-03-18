#include <cstdio>
#include <iostream>
#include <cstring>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 401000;

#define mp(x,y) make_pair(x,y)
#define fi first
#define se second

typedef long long ll;

int n,m;

typedef pair<int,int> P;

vector<P>G[N];

int cnt,id[N];

int col[N],fa[N],top[N],siz[N],dep[N],son[N];

int dfs1(int u){
	siz[u] = 1;
	for (int i = 0;i < G[u].size();i++){
		int x = G[u][i].fi;
		if (fa[u] == x) continue;
		col[x] = G[u][i].se;
		dep[x] = dep[fa[x] = u] + 1;
		siz[u] += dfs1(x);
		if (siz[x] > siz[son[u]]) son[u] = x;
	}
	return siz[u];
}

int dfs2(int u,int ff){
	top[u] = ff; id[u] = ++cnt;
	if (son[u]) dfs2(son[u],ff);
	for (int i = 0;i < G[u].size();i++){
		int x = G[u][i].fi;
		if (x == son[u] || x == fa[u]) continue;
		dfs2(x,x);
	}
	return id[u];
}

int lca(int x,int y){
	for (;top[x] != top[y];((dep[top[x]] > dep[top[y]]) ? x = fa[top[x]] : y = fa[top[y]]));
	return (dep[x] < dep[y]) ? x : y;
}

typedef struct seg{
	int l,r,num;
}seg;

seg Merge(seg s1,seg s2){
	seg ans; ans.l = s1.l; ans.r = s2.r;
	ans.num = (s1.num + s2.num - (s1.r == s2.l));
	return ans;
}

typedef struct segment_tree{

	int tot;
	int sl[N],sr[N];
	int tl[N],tr[N];
	int sum[N],vl[N],vr[N],flag[N];

	int init(int x){
		tot = 0;
	}

	void newnode(int x){
		vl[x] = vr[x] = 0;
		sum[x] = 1;
		flag[x] = -1;
		sl[x] = sr[x] = 0;
	}

	inline void tagit(int x,int c){
		sum[x] = 1;
		vl[x] = vr[x] = c;
		flag[x] = c;
	}

	inline void pd(int x){
		if (~flag[x] && tl[x] != tr[x]){
			tagit(sl[x],flag[x]);
			tagit(sr[x],flag[x]);
			flag[x] = -1;
		}
	}

	inline void update(int x){
		sum[x] = sum[sl[x]] + sum[sr[x]];
		if (vr[sl[x]] == vl[sr[x]]) sum[x]--;
		vl[x] = vl[sl[x]];
		vr[x] = vr[sr[x]];
	}

	int build(int l,int r){
		int x = ++tot; newnode(x);
		tl[x] = l; tr[x] = r;
		if (l == r) return x;
		int mid = (l + r) >> 1;
		sl[x] = build(l,mid);
		sr[x] = build(mid + 1,r);
		update(x);
		return x;
	}

	void add(int x,int lx,int rx,int c){
		if (tl[x] >= lx && tr[x] <= rx){
			tagit(x,c);
			return;
		}
		int mid = (tl[x] + tr[x]) >> 1;
		pd(x);
		if (mid >= lx) add(sl[x],lx,rx,c);
		if (mid < rx) add(sr[x],lx,rx,c);
		update(x);
	}

	seg query(int x,int lx,int rx){
		seg ans; pd(x);
		ans.l = vl[x]; ans.r = vr[x]; ans.num = sum[x];
		if (tl[x] >= lx && tr[x] <= rx) return ans;
		int mid = (tl[x] + tr[x]) >> 1;
		if (mid >= rx){
			return query(sl[x],lx,rx);
		} else if (lx > mid){
			return query(sr[x],lx,rx);
		}
		else return Merge(query(sl[x],lx,rx),query(sr[x],lx,rx));
	}
}Se;

Se Seg;

void add(int x,int y,int c){
	int Fa = lca(x,y);
	while(top[Fa] != top[x]){
		Seg.add(1,id[top[x]],id[x],c);
		x = fa[top[x]];
	}
	if (Fa != x) Seg.add(1,id[Fa] + 1,id[x],c);
	while(top[Fa] != top[y]){
		Seg.add(1,id[top[y]],id[y],c);
		y
		= fa[top[y]];
	}
	if (Fa != y) Seg.add(1,id[Fa] + 1,id[y],c);
}

void change(seg& x,seg y){
    if (x.num == 0) x = y;
    else x = Merge(y,x);
}

seg go(int x,int Fa){
    seg ans; ans.num = 0;
    while(top[x] != top[Fa]){
        change(ans,Seg.query(1,id[top[x]],id[x]));
        x = fa[top[x]];
    }
    seg u = ans;
    if (x != Fa) {change(ans,Seg.query(1,id[Fa] + 1,id[x])); u = Seg.query(1,id[Fa] + 1,id[x]);}
    return ans;
}

int ask(int x,int y){
	int Fa = lca(x,y);
	seg ans1 = go(x,Fa);
	seg ans2 = go(y,Fa);
	if (ans1.num == 0) return ans2.num;
	if (ans2.num == 0) return ans1.num;
	swap(ans1.l,ans1.r);
	return Merge(ans1,ans2).num;
}

void init(int n){
	memset(son,0,sizeof(son[0]) * n);
	memset(dep,0,sizeof(dep[0]) * n);
    for (int i = 0;i <= n;i++) G[i].clear();
}

int main(){
	ios_base::sync_with_stdio(false);
	while(cin >> n >> m){
		init(n);
		for (int i = 1;i < n;i++){
			int x,y,z;
			cin >> x >> y >> z;
			G[x].push_back(mp(y,z));
			G[y].push_back(mp(x,z));
		}

		dfs1(1);

		cnt = 0;
		dfs2(1,1);

		Seg.init(n);
		Seg.build(1,n);

		for (int i = 2;i <= n;i++)
			Seg.add(1,id[i],id[i],col[i]);

		while(m--){
			char op[10];
			cin >> op;
			int x,y,z;
			cin >> x >> y;
			if (op[0] == 'Q') cout << ask(x,y) << endl;
			else{
				cin >> z;
				add(x,y,z);
			}
		}
	}
}
