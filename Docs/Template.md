[TOC]



## Glory-ICPC-2017-Template

#### 1.字符串

##### 1.1 AC自动机

多组数据必须调用init()，结构为trie图，根节点为0

```c++
int son[N][4],w[N],fail[N],id[N],n,L,tot = 0;
   
int mapp(char ch){
	return ch - 'a';
}

void clearnd(int x){  
	memset(son[x],0,sizeof(son[x]));
	id[x] = fail[x] = 0;
}

int init(){
	tot = 0;
	clearnd(0);
	clearnd(1);
}

int ins(string s,int p){
	for (int l = s.length(),x = 0,i = 0,w;i < l;i++){
		if (!son[x][w = mapp(s[i])]){ 
			son[x][w] = ++tot;
			clearnd(tot);
		}
		x = son[x][w];
		if (i == l - 1) id[x] |= (1 << p);
	}
}

int q[N];

void build(){
	int h = 1,t = 0,i,j,x; fail[0] = -1;
	for (int i = 0;i < 26;i++)
	if (son[0][i]) q[++t] = son[0][i];
	while(h <= t)for(x = q[h++],i = 0;i < 26;i++){
		if (son[x][i]){ 
			fail[son[x][i]] = son[fail[x]][i];
			q[++t] = son[x][i];
			//id[son[x][i]] |= id[fail[son[x][i]]];
		}
		else son[x][i] = son[fail[x]][i];
	}
}
int ask(const string& s){  
	int ans = 0;
	for (int l = s.length(),x = 0,w,i = 0;i < l;i++){  
		w = mapp(s[i]);
		x = son[x][w];
		for (int j = x;j && id[j] != -1;j = fail[j]){  
			ans += id[j];
		}
	}
}
```



##### 1.2 KMP

注意字符串的开始位置，字符串问题首先可以考虑的一个方向和思路

```c++
typedef struct PString{
    
    typedef char dtype;

    dtype s[N];

    int p[N],len,flag;

    int OnCreate(dtype ss[],int lenx){
        len = lenx;
        for (int i = 0;i < lenx;i++) s[i] = ss[i];
        int j = -1; p[0] = -1;
        for (int i = 1;i < len;i++){
            while (s[i] != s[j + 1] && j != -1) j = p[j];
            if (s[i] == s[j + 1]) j++;
            p[i] = j;
        }
    }

    int kmp(dtype pa[],int lenx){
        int j = -1;
        for (int i = 0;i < lenx;i++){
            while (pa[i] != s[j + 1] && j != -1) j = p[j];
            if (pa[i] == s[j + 1]) j++;
            if (j == len - 1) ans++,flag = 1,j = p[j];
        }
        return flag;
    }
  
}PString;
```



##### 1.3 Manacher

回文字串必备系列，p[i]表示以i为中心的最长回文字串长度，字符串被拓展了两倍以方便处理奇偶性不同的回文字串。

```C++
int manacher(){
	int m = 2 * n + 1;	
	for (int i = 1;i <= n;i++){
		a[i << 1] = s[i - 1];
		a[(i << 1) + 1] = '#';
	}
	
	a[0] = '+'; a[1] = '#'; a[m + 1] = '-';

	int mx = 0,id;
	for (int i = 1;i <= m;i++){
		if (mx >= i) p[i] = min(mx - i,p[2 * id - i]);
		else p[i] = 0;
		while(a[i + p[i] + 1] == a[i - p[i] - 1]) p[i]++;
		if (p[i] + i > mx) id = i,mx = p[i] + i;
	}

	int ans = 0;
	for (int i = 1;i <= m;i++) 
		if (p[i] > ans) ans = p[i];
	return ans;
}
```



##### 1.4 拓展KMP

e_kmp[i]数组表示的是i位置开始的后缀和主串的最大长公共前缀。

```C++
inline void e_kmp(char s[],int len){
	int j = 0,last = 1;
	for (;j < len && s[j] == s[j + 1];j++);
	e_kmp[0] = len; e_kmp[1] = j;
	for (int i = 2;i < len;i++){   
		int itmax = e_kmp[i - last]；
         int already = max(0,last + e_kmp[last] - i);
		if (itmax < already) e_kmp[i] = itmax;
		else{  
			e_kmp[i] = already; last = i;
			while(i + e_kmp[i] < len && s[i + e_kmp[i]] == s[e_kmp[i]]) ++e_kmp[i];
		}
	}
}
```



#### 2.数据结构

##### 2.1 线段树

    注意build中的初始赋值
    注意query中必须先push_down
    注意flag[x]不能是-1（分析具体情况）
    注意mx[x]的初始值
    通过tl[x],tr[x]可以计算自树的大小
    注意数组大小
```C++
typedef struct segment_tree{

    int siz,tot;

    int sl[N],sr[N];

    int tl[N],tr[N];

    ll sum[N],flag[N],mx[N];

    int init(int x){
        siz = x; tot = 0;
        memset(sl,0,sizeof(sl));
        memset(sr,0,sizeof(sr));
        memset(sum,0,sizeof(sum));
        memset(flag,-1,sizeof(flag));
        memset(mx,0,sizeof(mx));
    }

    inline void tagit(int x,int c){
        mx[x] = flag[x] = c;
        sum[x] = (ll)(tr[x] - tl[x] + 1) * c;
    }
    //flag[x] = -1? flag[x] = 0?
    inline void pd(int x){
        if (~flag[x] && tl[x] != tr[x]){
            tagit(sl[x],flag[x]);
            tagit(sr[x],flag[x]);
            flag[x] = -1;
        }
    }

    inline void update(int x){
        sum[x] = sum[sl[x]] + sum[sr[x]];
        mx[x] = max(mx[sl[x]],mx[sr[x]]);
    }

    int build(int l,int r){
        int x = ++tot;
        tl[x] = l; tr[x] = r;
        if (l == r) return flag[x] = -1,x;
        int mid = (l + r) >> 1;
        sl[x] = build(l,mid);
        sr[x] = build(mid + 1,r);
        update(x);
        return x;
    }

    void add(int x,int lx,int rx,ll c){
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


    ll query(int x,int lx,int rx){
        pd(x);
        if (tl[x] >= lx && tr[x] <= rx) return sum[x];
        int mid = (tl[x] + tr[x]) >> 1; ll ans = 0;
        if (mid >= lx) ans += query(sl[x],lx,rx);
        if (mid < rx) ans += query(sr[x],lx,rx);
        return ans;
    }

}segment_tree;

segment_tree Seg;

```



##### 2.2 离散化

```C++
#define dtype int

typedef struct discrete{ 

	dtype tmp[N];
	int n,tot;

	int search(dtype x){
		int l = 1,r = tot;
		do{ 
			int mid = (l + r) >> 1;
			if (tmp[mid] == x) return mid;
			if (tmp[mid] > x) r = mid - 1;
			else l = mid + 1;
			}while(l <= r);
		return 0;
	}

	int init(int x,dtype a[]){ 
		n = x;
		tot = 0;
		for (int i = 1;i <= n;i++) tmp[i] = a[i];
		sort(tmp+1,tmp+n+1);
		for (int i = 1;i < n;i++) 
			if (tmp[i] != tmp[i+1]) tmp[++tot] = tmp[i];
		tmp[++tot] = tmp[n];
		for (int i = 1;i <= n;i++) 
			posx[i] = search(a[i]);
		return tot;
	}

}discrete;

discrete DisC;
```



##### 2.3 树状数组

###### 2.3.1 普通版本

```
注意初始化，N的大小等，long long
```

```C++
typedef struct Fenwick_Tree{  
	
	dtype C[N];
	int siz;
	
	int init(int x){ 
		for (int i = 0;i <= x+1;i++) C[i] = 0;
		return siz = x;
	}

	inline int lowbit(int x){ 
		return x & (-x);
	}

	inline int add(int x,dtype t){ 
		if (t == 0) return 0;
		for (;x <= siz;x += lowbit(x)) 
		   C[x] += t;
	}

	inline dtype sum(int x){ 
		dtype ans = 0;
		for (;x;x -= lowbit(x)){ 
			ans += C[x];
		}
		return ans;
	}

	inline dtype intersum(int l,int r){ 
		if (l > r) return 0;
		return sum(r) - sum(l-1);
	}

}Fenwick_Tree;

Fenwick_Tree Fen;
```

###### 2.3.2 可支持区间修改，区间查询的版本

```c++
template <typename X>  
struct tree_array{  
    struct tree_array_single{  
        X arr[MAXN];  
        void add(int x,X n){while(x<=N)arr[x]+=n,x+=lowbit(x);}  
        X sum(int x){X sum=0;while(x)sum+=arr[x],x-=lowbit(x);return sum;}  
    }T1,T2;  
    void reset(){CLR(T1.arr,0); CLR(T2.arr,0);}  
    void add(int x,X n){T1.add(x,n);T2.add(x,x*n);}  
    void update(int L,int R,int n){add(L,n);add(R+1,-n);}  
    X sum(int x){return (x+1)*T1.sum(x)-T2.sum(x);}  
    X query(int L,int R){return sum(R)-sum(L-1);}  
};  
```

###### 2.3.3 二维树状数组

```c++
typedef long long dtype;

inline lowbit(int x){ 
	return x & (-x);
}

typedef struct 2DBIT{ 

	dtype c[N][N];

	int n;

	int init(int nx,int mx){ 
		n = max(nx,mx);
	}

	dtype sum(int x,int y){  
		dtype ans = 0;
		for (int i = x;i;i -= lowbit(i))
			for(int j = y;j;j -= lowbit(j))
				ans += c[i][j];
		return ans;
	}

	void add(int x,int y,int val){ 
		if (!x || !y) return 0;
		for (int i = x;i <= n;i += lowbit(i))
			for (int j = y;j <= n;j += lowbit(j))
				c[i][j] += val;
	}

}2DBit;

2DBit C;

```



##### 2.4 函数式线段树

###### 2.4.1 区间第K大

```C++
int siz[N],root[N],sl[trsize],sr[trsize];

void insert(int a,int b,int fx,int &nx,int p,int c){
	nx = ++tot;
	siz[nx] = siz[fx] + c;
	if (a == b) return;
	sl[nx] = sl[fx];
	sr[nx] = sr[fx];
	int mid = (a + b) >> 1;
	if (p <= mid) insert(a,mid,sl[fx],sl[nx],p,c);
	else insert(mid + 1,b,sr[fx],sr[nx],p,c);
}

int ask(int a,int b,int x,int y,int k){ 
	if (a == b) return a;
	int mid = (a + b) >> 1;
	if (siz[sl[y]] - siz[sl[x]] >= k)
		 return ask(a,mid,sl[x],sl[y],k);
	else return ask(mid + 1,b,sr[x],sr[y],k - siz[sl[y]] + siz[sl[x]]);
}
```

###### 2.4.2 区间众数

```C++
int n,m,sz;
int root[500010],ls[10000010],rs[10000010],sum[10000010];

inline int read()
{
    char ch=getchar	();
    while(!(ch>='0'&&ch<='9'))ch=getchar();
    int x=0;
    while(ch>='0'&&ch<='9'){x=x*10+(ch-'0');ch=getchar();}
    return x;
}

void update(int l,int r,int x,int &y,int v)
{
    y=++sz;
    sum[y]=sum[x]+1;
    if(l==r)return;
    ls[y]=ls[x];rs[y]=rs[x];
    int mid=(l+r)>>1;
    if(v<=mid)update(l,mid,ls[x],ls[y],v);
    else update(mid+1,r,rs[x],rs[y],v);
}

int que(int L,int R)
{
    int l=1,r=n,mid,x,y,tmp=(R-L+1)>>1;
    x=root[L-1];y=root[R];
    while(l!=r)
    {
        if(sum[y]-sum[x]<=tmp)return 0;
        mid=(l+r)>>1;
        if(sum[ls[y]]-sum[ls[x]]>tmp)
        {r=mid;x=ls[x];y=ls[y];}
        else if(sum[rs[y]]-sum[rs[x]]>tmp)
        {l=mid+1;x=rs[x];y=rs[y];}
        else return 0;
    }
    return l;
}

int main()
{
    n=read();m=read();
    for(int i=1;i<=n;i++)
    {
        int x;x=read();
        update(1,n,root[i-1],root[i],x);
    }
    for(int i=1;i<=m;i++)
    {
        int l,r;l=read();r=read();
        printf("%d\n",que(l,r));
    }
    return 0;
}
```



##### 2.5 树链剖分

```C++
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
```



##### 2.6 Link-Cut Tree

```c++
const int N = 610000;

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
	sum[x] += c * siz[x];
	val[x] += c;
	mx[x] += c;
	flag[x] += c;
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

//核心操作，打通x到目前根的一条链

void access(int x){
	for (int y = 0;x;y = x,x = f[x])
		splay(x),son[x][1] = y,up(x);
}


/* 
	get the root of the current set
	can be used as the union-find set
*/

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

int n,m,x,y;

int main(){

	while(cin >> n){

		LCTInit();

		for (int i = 1;i <= n;i++) siz[i] = 1;

		for (int i = 1;i < n;i++){
			scanf("%d%d",&x,&y);
			link(x,y);
		}

		for (int i = 1;i <= n;i++)
			scanf("%d",&val[i]),mx[i] = sum[i] = val[i];

		int q; scanf("%d",&q);

		while(q--){
			int ty,z,x,y;
			scanf("%d",&ty);
			scanf("%d%d",&x,&y);
			if (ty == 1){
                if (root(x) == root(y)){
                    printf("-1\n");
                    continue;
                }
                link(x,y);
			}
			if (ty == 2){
                if (root(x) != root(y) || x == y){
                    printf("-1\n");
                    continue;
                }
				makeroot(x);
				cutf(y);
			}
			if (ty == 3){
				scanf("%d",&z);
                if (root(z) != root(y)){
                    printf("-1\n");
                    continue;
                }
				makeroot(y);
				access(z);
				splay(z);
				add(z,x);
			}
			if (ty == 4){
                if (root(x) != root(y)){
                    printf("-1\n");
                    continue;
                }
				makeroot(x);
				access(y);
				splay(y);
				printf("%d\n",mx[y]);
			}
		}
		printf("\n");
	}
}

```



##### 2.7 二分+倍增

```c++
int T,n,q;
int bin[20],Log[100005];
int a[100005],f[100005][17];

void pre(){
    for(int i=1;i<=n;i++) f[i][0]=a[i];
    for(int i=1;i<=16;i++)
        for(int x=1;x<=n;x++)
            if(x+bin[i]-1<=n)
                f[x][i]=min(f[x][i-1],f[x+bin[i-1]][i-1]);
            else break;
}

int query(int l,int r){
    int t=Log[r-l+1];
    return min(f[l][t],f[r-bin[t]+1][t]);
}

int find(int l,int val){

    int L=l,R=n,ans=n+1;
    while(L<=R)
    {
        int mid=(L+R)>>1;
        if(query(L,mid)>val)L=mid+1;
        else ans=mid,R=mid-1;
    }
    return ans;
}

int main(){
	
    bin[0]=1;for(int i=1;i<20;i++)bin[i]=bin[i-1]<<1; 
    T=read();
    while(T--)
    {
        n=read();
        Log[0]=-1;for(int i=1;i<=n;i++)Log[i]=Log[i>>1]+1;
        for(int i=1;i<=n;i++)
            a[i]=read();
        pre();
        q=read();
        for(int i=1;i<=q;i++)
        {
            int l=read(),r=read();
            int tmp=a[l],now=l;
            while(1)
            {
                now=find(now+1,tmp);
                if(now>r)break;
                tmp=tmp%a[now];
            }
            printf("%d\n",tmp);
        }
    }
    return 0;
}
```



##### 2.8 莫队算法

```C++
typedef long long ll;

ll v[M],vx[M],ians[N];

int n,m,k;

typedef struct que{
	int l,r,id;
}que;

int a[N],pos[N]; que q[N];

int bkn;

bool cmp(que a,que b){
	if (pos[a.l] == pos[b.l]) return a.r < b.r;
	return a.l < b.l;
}

int init(){
	bkn = int(sqrt(n));
	for (int i = 1;i <= n;i++)
		pos[i] = (i - 1)/bkn + 1;
}

int main(){

	cin >> n >> m >> k;

	init();

	for (int i = 1;i <= n;i++)
		scanf("%d",&a[i]);

    for (int i = 1;i <= n;i++)
        a[i] = a[i - 1] ^ a[i];

	for (int i = 1;i <= m;i++){
		scanf("%d%d",&q[i].l,&q[i].r);
		q[i].id = i;
	}

	sort(q+1,q+m+1,cmp);

	int l = 1,r = 0;

	ll ans = 0;

	for (int i = 1;i <= m;i++){

		int pl = q[i].l,pr = q[i].r;

		while (r < pr){
            r++;
            v[a[r-1]]++;
            vx[a[r]]++;
			ans += v[a[r] ^ k];
        }



		while (r > pr){
			ans -= v[a[r] ^k];
			v[a[r-1]]--;
			vx[a[r]]--;
			r--;
		}


        while (l < pl){
            ans -= vx[a[l-1] ^ k];
			v[a[l-1]]--;
			vx[a[l]]--;
            l++;
		}


		while (l > pl){
            l--;
            v[a[l-1]]++;
            vx[a[l]]++;
			ans += vx[a[l-1] ^ k];
		}

		ians[q[i].id] = ans;
	}

	for (int i = 1;i <= m;i++)
		printf("%I64d\n",ians[i]);
}
```



##### 2.9 Splay

```C++
const int N = 10000;

int tr[80001][2],num[80001],fa[80001];

void rotate(int x,int &k){
    int y=fa[x],z=fa[y],l,r;
    if(tr[y][0]==x) l=0; else l=1;
    r=l^1;
    if(y==k)k=x;
    else{if(tr[z][0]==y)tr[z][0]=x;else tr[z][1]=x;}
    fa[x]=z;fa[y]=x;fa[tr[x][r]]=y;
    tr[y][l]=tr[x][r];tr[x][r]=y;
}

void splay(int x,int &k)
{
	int y,z;
	while(x!=k)
	{
		y=fa[x],z=fa[y];
		if(y!=k)
		{
			if((tr[y][0]==x)^(tr[z][0]==y))rotate(x,k);
			else rotate(y,k);
		}
		rotate(x,k);
	}
}
void ins(int &k,int x,int last)
{
	if(k==0){size++;k=size;num[k]=x;fa[k]=last;splay(k,rt);return;}
	if(x<num[k])ins(tr[k][0],x,k);else ins(tr[k][1],x,k);
}
void del(int x)
{
	splay(x,rt);
	if(tr[x][0]*tr[x][1]==0)
	{rt=tr[x][0]+tr[x][1];}
	else 
	{
		int k=tr[x][1];
		while(tr[k][0])k=tr[k][0];
		tr[k][0]=tr[x][0];fa[tr[x][0]]=k;
		rt=tr[x][1];
	}
	fa[rt]=0;
}
void ask_before(int k,int x)
{
	if(k==0)return;
	if(num[k]<=x){t1=k;ask_before(tr[k][1],x);}
	else ask_before(tr[k][0],x);
}
void ask_after(int k,int x)
{
	if(k==0)return;
	if(num[k]>=x){t2=k;ask_after(tr[k][0],x);}
	else ask_after(tr[k][1],x);
}
 
```



##### 2.10 CDQ分治

```c++
CDQ分治解决高维数点问题
```

```c++
const int N = 401000;

int n,m;

typedef struct seg{
	int x,y,z,kind,id;
}seg;

seg v[N],quryx[N];

int c[N],maxv,ans[N];

bool cmpx(seg a,seg b){
	return a.x < b.x || (a.x == b.x && a.kind < b.kind);
}

bool cmpy(seg a,seg b){
	return a.y < b.y || (a.y == b.y && a.kind < b.kind);
}

int lowbit(int x){return x & (-x);}

int add(int x,int v){
	for (;x <= maxv;x += lowbit(x))
		c[x] += v;
}

int sum(int x){
	int ans = 0;
	for (;x;x -= lowbit(x))
		ans += c[x];
	return ans;
}

void xsolve(int l,int r){
	if (l >= r) return;
	for (int i = l;i <= r;i++){
		if (quryx[i].kind == 0) add(quryx[i].z,1);
		else ans[quryx[i].id] += sum(quryx[i].z);
	}
	for (int i = l;i <= r;i++){
		if (quryx[i].kind == 0) add(quryx[i].z,-1);
	}
}

void solve(int l,int r){
	if (l >= r) return;
	int mid = (l + r) >> 1;
	solve(l,mid);
	solve(mid+1,r);
	int num = 0;
	for (int i = l;i <= mid;i++)
		if (v[i].kind == 0) quryx[++num] = v[i];
	for (int i = mid+1;i <= r;i++)
		if (v[i].kind) quryx[++num] = v[i];
	sort(quryx+1,quryx+num+1,cmpy);
	xsolve(1,num);
}


int main(){
	int T; cin >> T;
	while(T--){
		scanf("%d",&n);
		memset(c,0,sizeof(c));
		memset(ans,0,sizeof(ans));
		memset(v,0,sizeof(v));
		for (int i = 1;i <= n;i++){
			scanf("%d%d%d",&v[i].x,&v[i].y,&v[i].z);
			v[n + i] = v[i];
			v[n + i].kind = 1;
			v[i].id = v[i + n].id = i;
			maxv = max(maxv,v[i].x);
			maxv = max(maxv,v[i].y);
			maxv = max(maxv,v[i].z);
		}
		sort(v+1,v+2*n+1,cmpx);
		solve(1,2*n);
		for (int i = 1;i <= n;i++)
            printf("%d\n",ans[i] - 1);
	}
}
```



#####2.11 STL

###### 2.11.1 Bitset

```
部分操作可以被表示为01串的左移右移等二进制问题
注意bitset的内存问题
bitset的左右移都是逻辑的
```

```
#include <bitset>

using namespace std;

const int N = 200010;

bitset<N>a;

int example(){
	a = a ^ a;
	a ^= (a << x);
	a[0] = 1;
	a[1] = 0;
	a.set(1) // set the position 1 to 1
	a.reset() //clear to 0
	a.count()
}

int __builtin_popcount(unsigned int x);

int __builtin_clz(unsigned int x);
//求前缀0的个数

int __builtin_ctz(unsigned int x);
//求后缀0的个数
```

######2.11.2 Set

```C++
#include <set>

set<int>S;

S.insert();

set<int>::iterator i;

i = S.begin();

while (i != S.end())
	printf("%d\n",*i++);

S.clear();

S.count(4);

S.empty();

S.erase();

S.find();

S.lower_bound();

//大于或等于某值的第一个位置

S.rbegin();

S.upper_bound();

//大于某个数的第一个位置
```

###### 2.11.3 Rope

```c++
#include <iostream>
#include <cstdio>
#include <ext/rope>

using namespace std;
using namespace __gnu_cxx;

crope list;
int t,now;
char ch[3000005];

inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

int main()
{
    t=read();
    char s[10];int x;
    while(t--)
    {
        scanf("%s",s);
        switch(s[0])
        {
        case 'M':now=read();break;
        case 'P':now--;break;
        case 'N':now++;break;
        case 'I':
            x=read();
            for(int i=0;i<x;i++)
            {
                ch[i]=getchar();
                while(ch[i]=='\n')ch[i]=getchar();
            }
            ch[x]=0;
            list.insert(now,ch);
            break;
        case 'D':x=read();list.erase(now,x);break;
        case 'G':x=read();list.copy(now,x,ch);ch[x]=0;puts(ch);
        }
    }
    return 0;
}
```

###### 2.11.4 next_permutation

```c++
next_permutation(a + 0,a + n);
//这使得排列a变成自己的下一个排列
//原理是从尾部往前寻找到第一个相邻顺序对，记为i和i+1，再末尾开始找到第一个比i大的位置j,交换i和j，再翻转i以后的所有数
```



##### 2.12 Trie

######2.12.1 xor-trie

```c++
const int N = 2000 * 32;

int son[N][2];

int cnt[N];

typedef long long ll;

int tot = 0;

int init(int n){
    for (int i = 0;i <= n * 36;i++)
        son[i][1] = son[i][0] = 0;
	for (int i = 1;i <= n * 36;i++)
        cnt[i] = 0;
	tot = 0;
}

void ins(ll x){
	int now = 0;
	for (ll i = 32;i >= 0;i--){
		ll t = (x >> i) & 1ll;
		cnt[now]++;
		if (!son[now][t]) son[now][t] = ++tot;
		now = son[now][t];
	}
	cnt[now]++;
}

void del(ll x){
	int now = 0;
	for (ll i = 32;i >= 0;i--){
		ll t = (x >> i) & 1ll;
		cnt[now]--;
		now = son[now][t];
	}
	cnt[now]--;
}

ll walk(ll x){
	int now = 0;;
	ll ans = 0;
	for (ll i = 32;i >= 0;i--){
		ll t = (x >> i) & 1ll;
		t = t ^ 1;
		if (son[now][t] && cnt[son[now][t]]){
			ans += 1ll << i;
			now = son[now][t];
		}else now = son[now][t ^ 1];
	}
	return ans;
}

ll a[N];

int main(){
	int T;
	cin >> T;
	while(T--){
		int n;
		cin >> n;
		for (int i = 1;i <= n;i++)
			scanf("%lld",a + i);
        init(n);
		for (int i = 1;i <= n;i++) ins(a[i]);
		ll ans = 0;
		for (int i = 1;i <= n;i++)
        for (int j = i + 1;j <= n;j++){
            //del(a[i]);
            //del(a[j]);
            ans = max(ans,walk(a[i] + a[j]));
            ins(a[i]);
            ins(a[j]);
        }
		cout << ans << endl;
	}
}
```

###### 2.12.2 可持久化Trie

```c++
using namespace std;

inline int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

int bin[30];

int n,m;

int a[N],b[N],root[N];

struct trie{
	int cnt;
	int ch[N*24][2],sum[N*24];
	int insert(int x,int val){
		int tmp,y;tmp=y=++cnt;
		for(int i=23;i>=0;i--)
		{
			ch[y][0]=ch[x][0];ch[y][1]=ch[x][1];
			sum[y]=sum[x]+1;
			int t=val&bin[i];t>>=i;
			x=ch[x][t];
			ch[y][t]=++cnt;
			y=ch[y][t];
		}
		sum[y]=sum[x]+1;
		return tmp;
	}
	int query(int l,int r,int val){
		int tmp=0;
		for(int i=23;i>=0;i--)
		{
			int t=val&bin[i];t>>=i;
			if(sum[ch[r][t^1]]-sum[ch[l][t^1]])
				tmp+=bin[i],r=ch[r][t^1],l=ch[l][t^1];
			else r=ch[r][t],l=ch[l][t];
		}
		return tmp;
	}
}trie;

int main(){
	bin[0]=1;
	for(int i=1;i<30;i++)
		bin[i]=bin[i-1]<<1;
	n=read();m=read();
	n++;
	for(int i=2;i<=n;i++)
		a[i]=read();
	for(int i=1;i<=n;i++)
		b[i]=b[i-1]^a[i];
	for(int i=1;i<=n;i++)
		root[i]=trie.insert(root[i-1],b[i]);
	char ch[5];
	int l,r,x;
	while(m--)
	{
		scanf("%s",ch);
		if(ch[0]=='A')
		{
			n++;
			a[n]=read();b[n]=b[n-1]^a[n];
			root[n]=trie.insert(root[n-1],b[n]);
		}
		else 
		{
			l=read();r=read();x=read();
			printf("%d\n",trie.query(root[l-1],root[r],b[n]^x));
		}
	}
	return 0;
}
```



##### 2.13 树套树

```c++
int build(int a,int b){ 
	int x = ++tot;
	if (a == b) {root[a] = 1; return;}
	int mid = (a + b) >> 1;
	sl[x] = build(a,mid);
	sr[x] = build(mid + 1,b);
}

int change(int a,int b,int x,int p,int delta){ 
	int v = ++tot;
	val[v] = val[x] + delta;
	if (a == b) return v;
	if (p < mid){ 
		sr[v] = sr[x];
		sl[v] = change(a,mid,sl[x],p,delta);
	}else{ 
		sl[v] = sl[x];
		sr[v] = change(mid+1,b,sr[x],p,delta);
	}
	return v;
}

int ask(int a,int b,int x,int c,int d){ 
	if (c <= a && b <= d) return val[x];
	int mid = (a + b) >> 1;	
	int ans = 0;
	if (c <= mid) ans += ask(a,mid,sl[x],c,d);
	if (mid < d) ans += ask(mid+1,d,sr[x],c,d);
	return ans;
}

int lowbit(int x){ 
	return x & (-x);
}

int segchange(int x,int p,int c){ 
	for (int t;x <= n;x += lowbit(x)){ 
		t = root[x]; root[x] = tot++;
		change(1,n,t,p,c);
	}
}

int segsum(int x,int c,int d){ 
	if (c > d) return 0;
	int ans = 0;
	for (;x;x -= lowbit(x))
	   ans += ask(1,n,root[x],c,d);
	return ans;
}
```



#### 3.图论

##### 3.1 网络流

######3.1.1 SAP

```c++
const int N = 405;

const int M = 4400;

typedef long long ll;

const ll inf = 9223372036854775805;

int base[N],num[N],d[N],ntot,tot,S,T;

int to[M],op[M],nxt[M];

ll fl[M],tmp[M];

ll sap(int u,ll flow){
	if (u == T) return flow;
	ll tmp,rec = 0;
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

int nadd(int x,int y,ll f){
	to[++tot] = y; tmp[tot] = f;
	nxt[tot] = base[x]; base[x] = tot;
	op[tot] = tot + 1;
	to[++tot] = x; tmp[tot] = 0;
	nxt[tot] = base[y]; base[y] = tot;
	op[tot] = tot - 1;
}

ll solve(double k){
	memset(d,0,sizeof(d));
	memset(num,0,sizeof(num));
	ll ans = 0;
	num[0] = ntot;
 	while(d[S] < ntot) ans += sap(S,inf);
	return ans;
}

int main(){ 
	BuildGraph(S,T,ntot);
}
```

###### 3.1.2 ZKW

```c++
/*
    correctly used times = 
    used in = { 
   	
    }
*/
    
const int inf = ~0U>>1;

const int N = 5010;

typedef struct seg{
    int to,op,cost,nxt,f;
}seg;

seg v[N*40]; 

int ans =0,tot,dis[N],base[N],vis[N],ttf = 0;

int S,T; int cur[N];

int aug(int u,int flow){

    if (u == T){
        ans += flow * dis[S];
        ttf += flow;
        return flow;
    }

    vis[u] = 1;

    int now = 0;

    for (int i = base[u];i;i = v[i].nxt){
        int x = v[i].to;
        if (vis[x] || v[i].f <= 0 || dis[u] != dis[x] + v[i].cost)
            continue;
        int tmp = aug(x,min(flow - now,v[i].f));
        v[i].f -= tmp; v[v[i].op].f += tmp;
        now += tmp;
        if (now == flow) return flow;
    }

    return now;
}


int modlabel(){
    int del = inf;
    for (int i = S;i <= T;i++)
        if (vis[i]) for (int j = base[i];j;j = v[j].nxt)
            if (v[j].f){
                int x = v[j].to;
                if (!vis[x]) del = min(del,dis[x] + v[j].cost - dis[i]);
            }
    if (del == inf) return 0;
    for (int i = S;i <= T;i++)
    if (vis[i]) vis[i] = 0,dis[i] += del,cur[i] = base[i];
    return 1;
}


int zkw(){
    for (int i = S;i <= T;i++) cur[i] = base[i];
    int fl,t = 0;
    do{
        t = 0;
        while(t = aug(S,inf)) memset(vis,0,sizeof(vis));
    }while(modlabel());
    return ans;
}

int add(int x,int y,int f,int c){
    v[++tot].to = y; v[tot].op = tot + 1;
    v[tot].f = f; v[tot].cost = c;
    v[tot].nxt = base[x]; base[x] = tot;
    v[++tot].to = x; v[tot].op = tot - 1;
    v[tot].f = 0; v[tot].cost = -c;
    v[tot].nxt = base[y]; base[y] = tot;
}

int main(){
    int P,n,m;
    cin >> P;
    while (P--){
        memset(base,0,sizeof(base));
        memset(dis,0,sizeof(dis));
        tot = 0; ans = 0; ttf = 0;
        memset(vis,0,sizeof(vis));
        cin >> m >> n;
        int x;
        S = 0;
        T = n + m * n + 1;
        for (int i = 1;i <= n;i++)
            for (int j = 1;j <= m;j++){
                scanf("%d",&x);
                for (int k = 1;k <= n;k++)
                add(i,j * n + k,1,k * x);
            }
        for (int i = 1;i <= n;i++)
            add(S,i,1,0);
        for (int i = 1;i <= m;i++)
            for (int j = 1;j <= n;j++)
                add(i * n + j,T,1,0);
        zkw();
    }
}
```

###### 3.1.3 Dinic

```c++
int n,m,cnt=1,ans,T;

struct edge{int to,next,v;}e[200005];

int h[1005],last[1005],q[1005];

bool vis[1005];

void insert(int u,int v,int w)
{
	e[++cnt].to=v;e[cnt].next=last[u];last[u]=cnt;e[cnt].v=w;
	e[++cnt].to=u;e[cnt].next=last[v];last[v]=cnt;e[cnt].v=0;
}

bool bfs()
{
	int head=0,tail=1;
	for(int i=1;i<=T;i++)h[i]=-1;
	q[0]=0;h[0]=0;
	while(head!=tail)
	{
		int now=q[head];head++;
		for(int i=last[now];i;i=e[i].next)
			if(e[i].v&&h[e[i].to]==-1)
			{
				h[e[i].to]=h[now]+1;
				q[tail++]=e[i].to;
			}
	}
	return h[T]!=-1;
}
int dfs(int x,int f)
{
	if(x==T)return f;
	int w,used=0;
	for(int i=last[x];i;i=e[i].next)
		if(h[e[i].to]==h[x]+1)
		{
			w=f-used;
			w=dfs(e[i].to,min(e[i].v,w));
			e[i].v-=w;e[i^1].v+=w;
			used+=w;if(used==f)return f;
		}
	if(!used)h[x]=-1;
	return used;
}

void dinic(){
	while(bfs())
		ans+=dfs(0,inf);
}

int main(){
	n=read();T=n+85;
	for(int i=1;i<=n;i++)
		insert(0,i,1);
	for(int i=1;i<=84;i++)
		insert(i+n,T,1);
	for(int i=1;i<=n;i++)
	{
		int k=read();
		while(k--)
		{
			int p=read(),q=read();
			int t=(p-1)*12+q+n;
			insert(i,t,1);
		}
	}
	dinic();
	printf("%d",ans);
	return 0;
}
```



###### 3.1.4 SPFA费用流

```c++
const int inf = ~0U>>1;

const int N = 610;

const int M = N * 400;

int S,T;

struct Edge{
    int from,to,next,cap,cost;
    Edge(){}
    Edge(int From,int To,int Next,int Cap,int Cost)
    {
        from=From,to=To,next=Next,cap=Cap,cost=Cost;
    }
}e[M];

int head[N];

struct Mcmf{

    int tot;

    int dis[N],vis[N];

    int path[N],low[N];

    void init(){
        tot=0;
        memset(head,-1,sizeof(head));
    }

    void add(int from,int to,int cap,int cost){
        e[tot]=Edge(from,to,head[from],cap,cost);
        head[from]=tot++;
        e[tot]=Edge(to,from,head[to],0,-cost);
        head[to]=tot++;
    }

    int spfa(int s,int t){
        memset(vis,0,sizeof(vis));
        memset(dis,0x3f,sizeof(dis));
        memset(low,0,sizeof(low));
        queue<int > Q;
        Q.push(s);
        vis[s] = 1;
        low[s] = inf;
        dis[s] = 0;
        while(!Q.empty()){
            int u=Q.front();Q.pop();
            vis[u]=0;
            for(int i=head[u];i!=-1;i=e[i].next){
                int v=e[i].to;
                if(e[i].cap>0&&(dis[v]>dis[u]+e[i].cost)){
                    path[v]=i;
                    low[v]=min(low[u],e[i].cap);
                    dis[v]=dis[u]+e[i].cost;
                    if(!vis[v]){
                        vis[v]=1;
                        Q.push(v);
                    }
                }
            }
        }
        return low[t];
    }

    int _mcmf(int s,int t){

        int flow=0;
        int cost=0;

        while(spfa(s,t)){

            int f=low[t];

            for(int i=t;i!=s;i=e[path[i]].from){
                e[path[i]].cap-=f;
                e[path[i]^1].cap+=f;
            }

            flow+=f;

            cost+=dis[t]*f;
        }

        return cost;
    }
}mcmf;

int main(){
    int P,n,m;
    cin >> P;
    while (P--){
        mcmf.init();
        scanf("%d%d",&m,&n);
        int x;
        S = 0;
        T = n + m * n + 1;
        for (int i = 1;i <= n;i++)
            for (int j = 1;j <= m;j++){
                scanf("%d",&x);
                for (int k = 1;k <= n;k++)
                mcmf.add(i,j * n + k,1,k * x);
            }
        for (int i = 1;i <= n;i++)
            mcmf.add(S,i,1,0);
        for (int i = 1;i <= m;i++)
            for (int j = 1;j <= n;j++)
                mcmf.add(i * n + j,T,1,0);
        printf("%d\n",mcmf._mcmf(S,T));
    }
}
```



##### 3.2 最短路径

###### 3.2.1 Floyd以及最小环（有向）以及bitset优化

```c++
int n,d[maxn][maxn];
 
void floyd(){
        for(int k=1; k<=n; k++)
            for(int i=1; i<=n; i++)
                for(int j=1; j<=n; j++)
            d[i][j] = min(d[i][j], d[i][k]+d[k][j]);
}

//min-circle

int get_mc(){   
	int ans = inf;
	for (int k = 1;k <= n;k++){  
		for (int i = 1;i < k;i++)
			for (int j = i + 1;j < k;j++)
 				ans = min(ans,d[i][j]+d[i][k]+d[k][j]);
 		for (int i = 1;i < k;i++) 
 			for (int j = i + 1;j < k;j++)
 				d[i][j] = min(d[i][j],d[i][k] + d[k][j]);
 	}
}

//bitset
double ans;
bitset<1005>edge[maxn];

void floyd(){
    int i,j,k;
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            if(edge[j][i]) edge[j]|=edge[i];
        }
    }
    int num;
    ans=0;
}
```

###### 3.2.2 SPFA 以及负环检测

```c++
stack<int>S;   

bool spfa(){ 
  
  for (int i=1;i<=n;i++) {S.push(i); vis[i]=1;}

  while (!S.empty()){
      int u=S.top(); S.pop(); vis[u]=0;    
      for (int i=base[u];i;i=Nx[i]) 
          if (d[u]+c[i]<d[now[i]]){
             int x = now[i]; cnt[i]++; 
             if (cnt[i]==n) return 0;   
             if (!vis[x]) S.push(x);    
             d[x] = d[u]+c[i];
             vis[x] = 1;    
          }
  }
  return 1;    
}
```

###### 3.2.3 Dij+Priority Queue

```c++
typedef struct seg{ 
	
	int id,va;

	seg(int a,int b){id = a; va = b;}

	bool operator <(const seg &x)const{ 
		if (va == x.va) return id < x.id;
		return va > x.va;
	}

}seg;

priority_queue<seg>Q;

bool vis[N];

int dij(int s){ 
	for (int i = 1;i <= n;i++) d[i] = inf;
	d[s] = 0;
	memset(vis,0,sizeof(vis));
	Q.push(seg(s,d[s]));
    while (!Q.empty()){ 
    	seg tmp = Q.top();
    	while (vis[tmp.id]) {Q.pop(); tmp = Q.top();}
    	int u = tmp.id; 
    	for (int i = base[u];i;i = nxt[i]){ 
    		int v = now[i];
    		if (d[v] > d[u] + va[i]){ 
    			d[v] = d[u] + va[i];
    			Q.push(seg(v,d[v]));
    		}
    	}
    	vis[u] = 1;
    	Q.pop();
    }
}

```

##### 3.3 三元环

```c++
typedef long long ll;

const int N = 110000;

int u[N],v[N],d[N];

vector<int>G[N];

map<pair<int,int>,int>M;

int main(){

	ios_base::sync_with_stdio(false);

	int n,m;

	int T; cin >> T;

	while(cin >> n >> m){

		M.clear();

		for (int i = 1;i <= n;i++) d[i] = 0,G[i].clear();

		for (int i = 1;i <= m;i++){
			int x,y;
			cin >> x >> y;
			u[i] = x; v[i] = y;
			d[x]++; d[y]++;
			M[make_pair(x,y)] = 1;
			M[make_pair(y,x)] = 1;
		}

		for (int i = 1;i <= m;i++){
            int x = u[i],y = v[i];
            if (d[x] > d[y]) G[x].push_back(y);
            else G[y].push_back(x);
		}

        for (int i = 1;i <= n;i++)
            sort(G[i].begin(),G[i].end());

		ll ans = 0;

		for (int i = 1;i <= m;i++){
			int x = u[i],y = v[i];
			int pos = 0;
			for (int j = 0;j < G[x].size();j++){
                if (pos < G[y].size() && G[y][pos] < G[x][j]) pos++;
                if (pos >= G[y].size()) break;
                if (G[y][pos] == G[x][j]) ans++,pos++;
			}
		}
		cout << ans << endl;
	}
}

```



##### 3.4 Tarjan算法

###### 3.4.1 SCC

```c++
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
```

######3.4.2 割边

```
cut数组表示该边是否是割边
```

```c++
struct Tarjan{

    int dfn[N],low[N],f[N],from[N],cut[N * 2],cnt,tot;

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
```

###### 3.4.3 边割点

```c++
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
```



##### 3.5 匈牙利算法

```c++
#include <bitset>

using namespace std;

const int N = 1000001;

bitset<N>pos;

int find(int x){ 
	for (int i = 1;i <= n;i++)
		if (g[x][i] && !vis[i]){ 
			vis[i] = 1;
			if (lk[i] == 0||find(lk[i])){ 
				lk[i] = x; return 1;
			}
		}
		return 0;
}

for (int i = 1;i <= n;i++){
	vis.reset();
	if (find(i)) ans++;
}
```



##### 3.6 LCA

```c++
int dfs(int u){
     vis[u]=1;  
     for (int i=base[u];i;i=next[i])
       if (!vis[now[i]]){ 
       	  int x=now[i]; 
          dp[x][0]=u; d[x]=d[u]+1;   
          dfs(x);  
       }
}
  
int predo(){ 
   dfs(1);
   for (int i = 1;i <= 20;i++)
    for (int j = 1; j <= n;j++)
      dp[j][i] = dp[dp[j][i-1]][i-1];
}

int lca(int x,int y){ 
	  if (x == y) return x;
    if (d[x] < d[y]) swap(x,y);   
    
    for (int i=k;i>=0;i--)
    if (d[dp[x][i]]>=d[y]) x=dp[x][i];
    
    if (x==y) return x;
    
    for (int i=k;i>=0;i--)
    if (dp[x][i]!=dp[y][i])
     x=dp[x][i],y=dp[y][i];
    return dp[x][0];   
}

d[0] = 1
```



##### 3.7 最小树形图

```c++
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
```



#### 4.数学

##### 4.1 莫比乌斯函数

```
包含一个常见的加速求和技巧
```

```c++
#define ll long long 

using namespace std;

int tot;

int mu[50005],sum[50005],pri[50005];

bool mark[50005];

void get(){
	mu[1]=1;
	for(int i=2;i<=50000;i++)
	{
		if(!mark[i])pri[++tot]=i,mu[i]=-1;
		for(int j=1;j<=tot&&i*pri[j]<=50000;j++)
		{
			mark[i*pri[j]]=1;
			if(i%pri[j]==0){mu[i*pri[j]]=0;break;}
			else mu[i*pri[j]]=-mu[i];
		}
	}
	for(int i=1;i<=50000;i++)
		sum[i]=sum[i-1]+mu[i];
}

int cal(int n,int m){
	if(n>m)swap(n,m);
	int ans=0,pos;
	for(int i=1;i<=n;i=pos+1)
	{
		pos=min(n/(n/i),m/(m/i));
		ans+=(sum[pos]-sum[i-1])*(n/i)*(m/i);
	}
	return ans;
}

int main(){
	get();
	int T=read();
	while(T--){
		int a=read(),b=read(),d=read();
		printf("%d\n",cal(a/d,b/d));
	}
	return 0;
}
```

```
单个数的莫比乌斯函数
```

```c++
void getprim(){
	//initializing
	for (int i = 2;i < N;i++)if(!prim[i]){
		pri.push_back(i);
		for (int j = 2 * i;j < N;j += i)
			prim[j] = 1;
	}
}

ll mou(int x){
	ll ans = 1;
	for (int i = 0;i < pri.size() && pri[i] <= x;i++)
		if (x % pri[i] == 0){
			if (x % (pri[i] * pri[i]) == 0)
				return 0;
			ans *= -1;
			x /= pri[i];
		}
	if (x != 1) ans *= -1;
	return ans;
}
```



##### 4.2 数论基础

```
exgcd 逆元 CRT 递推逆元
```

```c++
//ex_gcd
ll ex_gcd(ll a,ll b,ll& x,ll& y){   
	if (!b) return x = 1,y = 0,a;
	ll gcd = ex_gcd(b,a%b,x,y);
	ll t = x; x = y; y = t - a / b * y;
	return gcd;
}

//prime_set
int prim[N],p_tab[N],pcnt;
void get_prim(){   
	for (int i = 2;i < N;i++){  
		if (!prim[i]) p_tab[++pcnt] = i;
		for (int j = 1;j <= pcnt && i * p_tab[j] < N;j++){  
			prim[i * p_tab[j]] = 1;
			if (!(i % p_tab[j])) break;
		}
	}
}

//num_theory_inverse 递推逆元,模数M
int inv[N],sinv[N];
void get_inv(){  
	int i;
	for (inv[0] = inv[1] = 1,i = 2;i < M;i++){   
		inv[i] = -inv[M%i]*(M/i)%M；
		while(inv[i] < 0) inv[i] += M;
 	}

 	for (sinv[0] = 1,i = 1;i < M;i++)
 		sinv[i] = sinv[i - 1] * inv[i] % M;
}

//CRT

ll CRT(ll* a,ll* b,int n){  
	ll ans,P = 1;
	for (int i = 0;i < n;i++)
		P *= a[i];
	for (int i = 0;i < n;i++){
		ll x,y;
		ll now = P / a[i];
		ex_gcd(now,a[i],x,y);
		ans = (ans + now * x * a[i]) % P;
	}
	while(ans < 0) ans += P;
}
```



##### 4.3 欧拉函数

```c++
for(int i=1;i<=n;i++) phi[i]=i; 
   for (int i=2;i<=n;i++) 
   if (!b[i]){
         phi[i]--;
         for (int j=2;j*i<=n;j++)
         phi[i*j]=(phi[i*j]/i)*(i-1),b[i*j]=1; 
   }
    

//求单个数的欧拉函数

ll eular(ll n){
    ll ans = n;
    ll i;
    for (i = 2; i*i <= n; i++){
        if (n%i == 0){
            while (n%i == 0)
                n /= i;
            ans = ans/i*(i-1) ;
        }
    }
    if (n != 1)
        ans = ans/n*(n-1);
    return ans;
}
```



##### 4.4 组合数取模

```
模数小时，可以使用Lucas定理
对合数取模，可以分解质因数，各自用Lucas定理求解，然后CRT合并
```

```c++
LL a[3];
LL m[3]={7,11,13};
 
LL qpow(LL x,LL n,LL mod)    
{
    LL ret=1;
    for(; n; n>>=1)
    {
        if(n&1) ret=ret*x%mod;
        x=x*x%mod;
    }
    return ret;
}
LL inv(LL x,LL mod)
{
    return qpow(x,mod-2,mod);
}
LL C(LL n,LL m,LL mod)
{
    if(m<0||n<m) return 0;
    if(m>n-m) m=n-m;
    LL a=1,b=1;
    for(int i=0; i<m; i++)
    {
        a=(n-i)%mod*a%mod;
        b=(1+i)%mod*b%mod;
    }
    return a*inv(b,mod)%mod;
}
LL Lucas(LL n,LL k,LL p)
{
    if(k==0) return 1;
    return C(n%p,k%p,p)*Lucas(n/p,k/p,p)%p;
}
 
LL China(LL a[],LL m[],LL k)
{
    LL M=1;
    for(int i=0;i<k;i++) M*=m[i];
    LL ret=0;
    for(int i=0;i<k;i++)
        ret=(ret+a[i]*inv(M/m[i],m[i])*(M/m[i]))%M;
    if(ret<0) ret+=M;
    return ret;
}
 
LL v[100005];
 
int main()
{
//  freopen("test.in","r",stdin);
//  freopen("test.out","w",stdout);
    int T;
    scanf("%d",&T);
    while(T--)
    {
        int n;
        scanf("%d",&n);
        for(int i=0;i<n;i++)
            scanf("%d",&v[i]);
        memset(a,0,sizeof(a));
        for(int i=0;i<n;i++)
            for(int j=0;j<3;j++)
                a[j]=(a[j]+v[i]%m[j]*Lucas(n-1,i,m[j]))%m[j];
        LL ans=China(a,m,3);
        assert(ans<1001&&ans>=0);
        printf("%lld\n",ans);
    }
}
```



##### 4.5 大步小步法

```
大步小步法 用于求(Y^X = Z) mod P
```

```c++
#define ll long long
using namespace std;
int T,K;
int read()
{
    int x=0;char ch=getchar();
    while(ch<'0'||ch>'9')ch=getchar();
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x;
}
int gcd(int a,int b)
{
	return b==0?a:gcd(b,a%b);
}
void exgcd(int a,int b,int &x,int &y)
{
	if(b==0){x=1,y=0;return;}
	exgcd(b,a%b,x,y);
	int t=x;x=y;y=t-a/b*y;
}
int solve1(ll y,int z,int p)
{
	y%=p;
	ll ans=1;
	for(int i=z;i;i>>=1,y=y*y%p)
		if(i&1)ans=ans*y%p;
	return ans;
}
void solve2(int y,int z,int p)
{
	p=-p;
	int t=gcd(y,p);
	if(z%t){puts("Orz, I cannot find x!");return;}
	y/=t;z/=t;p/=t;
	int a,b;exgcd(y,p,a,b);
	a=(ll)a*z%p;
	while(a<0)a+=p;
	printf("%d\n",a);
}
map<int,int> mp;
void solve3(int y,int z,int p)
{
	y%=p;
	if(!y&&!z){puts("1");return;}
	if(!y){puts("Orz, I cannot find x!");return;}
	mp.clear();
	ll m=ceil(sqrt(p)),t=1;
	mp[1]=m+1;
	for(ll i=1;i<m;i++)
	{
		t=t*y%p;
		if(!mp[t])mp[t]=i;
	}
	ll tmp=solve1(y,p-m-1,p),ine=1;
	for(ll k=0;k<m;k++)
	{
		int i=mp[z*ine%p];
		if(i)
		{
			if(i==m+1)i=0;
			printf("%lld\n",k*m+i);
			return;
		}
		ine=ine*tmp%p;
	}
	puts("Orz, I cannot find x!");
}
```



##### 4.6 拓展欧拉定理

```c++
 
ll cnt,y;
 
 
ll euler(ll n){
        ll ret = 1,i;
        for (i = 2;i * i <= n;i++)
            if (n % i == 0){
                n /= i;
                ret *= (i - 1);
                while (n % i == 0){
                    n /= i;
                    ret *= i;
                }
        }
        if (n > 1)
            ret *= (n - 1);
        return ret;
}
 
ll quick(ll a, ll b,ll m)
{
    ll ans=1;
    while(b)
    {
        if(b&1)
        {
            ans=(ans*a)%m;
            b--;
        }
        b/=2;
        a=a*a%m;
    }
    return ans;
}
 
ll cal(ll a,ll b,ll y,ll c)
{
    ll phi,p,ans;
    phi=euler(c);
    p=1;
    for(ll i = 1;i <= y;i++){
        p = p * b;
        if(p > phi) break;
    }
    if(p>phi)
    {
        return quick(a,(quick(b,y,phi) + phi),c);
    }
    else ans=quick(a,p,c);
    return ans;
}
 
int main()
{
    ll a,b,c;
    while(cin>>a>>b>>y>>c)
    {
        ll ans=cal(a,b,y,c);
        cout<<ans<<endl;
    }
}
```



##### 4.7 GCD倍增数组

```c++
#include <bits/stdc++.h>

using namespace std;

const int N = 1e5+5;

typedef long long LL;

int n, m;

int block;

int a[N];

LL ans[N];

struct PP {
    int l, r;
    int id;
    bool operator < (const PP &cmp) const {
        if(l/block == cmp.l/block) return r < cmp.r;
        return l/block < cmp.l/block;
    }
}q[N];

int gcd(int a, int b) {
    return b?gcd(b, a%b):a;
}

struct He {
    int idx;    //存区间的下标
    LL g;       //存区间的gcd值
};

vector <He> vl[N], vr[N];

void preDeal() {
    for(int i = 1;i <= n; i++) {
        if(i == 1) vl[i].push_back((He){i, a[i]});  
        else {
            int curg = a[i];    
            int l = i;
            for(int j = 0;j < vl[i-1].size();j++) {
                He it = vl[i-1][j];
                int tmp = gcd(it.g, curg);
                if(tmp != curg)                     
                    vl[i].push_back((He){l, curg});
                curg = tmp, l = it.idx;
            }
            vl[i].push_back((He){l, curg});
        }
    }
    for(int i = n;i >= 1; i--) {
        if(i == n) vr[i].push_back((He){i, a[i]});  
        else {
            int curg = a[i];
            int r = i;
            for(int j = 0;j < vr[i+1].size();j++) {
                He it = vr[i+1][j];
                int tmp = gcd(it.g, curg);
                if(tmp != curg)
                    vr[i].push_back((He){r, curg});
                curg = tmp, r = it.idx;
            }
            vr[i].push_back((He){r, curg});
        }
    }
}

map<LL,LL>M;

void solve1(){
    preDeal();
    for (int i = 1;i <= n;i++){
        LL pre = i;
        for (int j = 0;j < vl[i].size();j++){
            LL l = pre - vl[i][j].idx + 1;
            M[vl[i][j].g] += l;
            pre = vl[i][j].idx - 1;
        }
    }
}

int tot = 0;

void solve() {
    printf("Case #%d:\n",++tot);
    for(int i = 1;i <= n; i++) vl[i].clear(), vr[i].clear();
    block = (int)sqrt(n);
    solve1();
    for (int i = 0;i < m;i++){
        int t = q[i].r;
        LL ans = 0;
        for (int j = 0;j < vl[t].size();j++)
            if (vl[t][j].idx <= q[i].l){
                ans = vl[t][j].g;
                break;
            }
        printf("%lld %lld\n",ans,M[ans]);
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        M.clear();
        for(int i = 1;i <= n; i++) scanf("%d", &a[i]);
        scanf("%d", &m);
        for(int i = 0;i < m; i++) scanf("%d%d", &q[i].l, &q[i].r);
        for(int i = 0;i < m; i++) q[i].id = i;
        solve();
    }
    return 0;
}
```



##### 4.8 卷积计算

###### 4.8.1 NTT+CDQ

```c++
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N = 41000;

ll x1[N],x2[N];

ll f[N],g[N],n,m;

const ll M = 152076289;

const ll G = 106;

ll powx(ll a,ll b){
	ll ans = 1;
	while(b){
		if (b&1) ans = ans * a % M;
		a = a * a % M;
		b >>= 1;
	}
	return ans;
}

void change(ll *y,int len){
	int i,j,k;
	for(i = 1,j = len / 2;i < len - 1;i++){
		if (i < j) swap(y[i],y[j]);
		k = len / 2;
		while(j >= k){
			j -= k;
			k /= 2;
		}
		if (j < k) j += k;
	}
}


void ntt (ll *y, int len, int on) {
    change (y, len);
    int id = 0;
    for(int h = 2; h <= len; h <<= 1) {
        id++;
        ll wn = powx(G, (M - 1) / (1<<id));
        for(int j = 0; j < len; j += h) {
            ll w = 1;
            for(int k = j; k < j + h / 2; k++) {
                ll u = y[k] % M;
                ll t = w * (y[k + h / 2] % M) % M;
                y[k] = (u + t) % M;
                y[k + h / 2] = ((u - t) % M + M) % M;
                w = w * wn % M;
            }
        }
    }
    if (on == -1) {
        for (int i = 1; i < len / 2; i++)
            swap (y[i], y[len - i]);
        ll inv = powx(len, M - 2);
        for(int i = 0; i < len; i++)
            y[i] = y[i] % M * inv % M;
    }
}

ll rev[N],fac[N];

void calcrev(){
	rev[0] = fac[0] = 1;
	for (int i = 1;i < N;i++){
		fac[i] = fac[i - 1] * i % M;
	}
	rev[N - 1] = powx(fac[N-1],M-2);
	for (int i = N - 2;i >= 0;i--)
        rev[i] = rev[i + 1] * (i + 1) % M;
}


void cdq(int l,int r){
	if (l == r){
		f[l] += g[l];
		f[l] %= M;
		return;
	}
	int mid = (l + r) >> 1;
	cdq(l,mid);
	int len = 1;
	while(len <= r - l + 1) len <<= 1;
	for (int i = 0;i < len;i++)
		x1[i] = x2[i] = 0;
	for (int i = l;i <= mid;i++)
		x1[i-l] = f[i] * rev[i-1] % M;
	for (int i = 1;i <= r - l;i++)
		x2[i-1] = g[i] * rev[i] % M;

	ntt(x1,len,1); ntt(x2,len,1);
	for (int i = 0;i < len;i++){
		x1[i] = x1[i] * x2[i] % M;
	}
	ntt(x1,len,-1);
	for (int i = mid + 1;i <= r;i++){
		f[i] -= ((x1[i-l-1] * fac[i-1]) % M);
		f[i] += M;
		f[i] %= M;
	}
	cdq(mid+1,r);
}

int main(){
	calcrev(); int T; int nc = 0;
    scanf("%d",&T);
	while(T--){
		ll n,m;
        scanf("%lld%lld",&n,&m);
        memset(f,0,sizeof(f));
		for (int i = 1;i <= n;i++){
			g[i] = powx((m + 1),i * (i - 1) / 2) % M;
		}
        cdq(1,n);
		ll ans = f[n] % M;
		ans = ans - (powx(n,n-2) * powx(m,n-1) % M);
		ans %= M;
		ans += M;
		ans %= M;
		printf("Case #%d: ",++nc);
		printf("%lld\n",ans % M);
	}
	return 0;
}
```

###### 4.8.2 FFT+CDQ

```c++
typedef complex<double>Complex;

const double PI = acos(-1.0);

void radar(Complex *y,int len){
    for (int i = 1,j = len / 2;i < len - 1;i++){
        if (i < j) swap(y[i],y[j]);
        int k = len / 2;
        while(j >= k){
            j -= k;
            k /= 2;
        }
        if (j < k) j += k;
    }
}

void fft(Complex *y,int len,int op){
    radar(y,len);
    for (int h = 2;h <= len;h <<= 1){
        double ang = op * 2 * PI / h;
        Complex wn(cos(ang),sin(ang));
        for (int j = 0;j < len;j += h){
            Complex w(1,0);
            for (int k = j;k < j + h / 2;k++){
                Complex u = y[k];
                Complex t = w * y[k + h / 2];
                y[k] = u + t;
                y[k + h / 2] = u - t;
                w = w * wn;
            }
        }
    }
    if (op == -1) for (int i = 0;i < len;i++) y[i]/=len;
}


const int N = 200005,M = 313;


Complex A[N << 1],B[N << 1];

int f[N],a[N];

void cdq(int l,int r){
    if (l == r) return;
    int mid = (l + r) >> 1;
    cdq(l,mid);
    int len = 1;
    while(len <= r - l + 1) len <<= 1;
    for (int i = 0;i < len;i++){
        A[i] = Complex(l + i <= mid ? f[l + i] : 0,0);
        B[i] = Complex(l + i + 1 <= r ? a[i + 1] : 0,0);
    }
    fft(A,len,1);
    fft(B,len,1);
    for (int i = 0;i < len;i++)
        A[i] *= B[i];
    fft(A,len,-1);
    for (int i = mid + 1;i <= r;i++){
        f[i] += fmod(A[i - l - 1].real(),M) + 0.5;
        if (f[i] >= M) f[i] -= M;
    }
    cdq(mid + 1,r);
}


int main(){
    int n;
    double clock_t = clock();
    ios_base::sync_with_stdio(0);
    while(~scanf("%d",&n) && n){
        for (int i = 1;i <= n;i++){
            scanf("%d",a + i);
            a[i] %= M;
        }
        memset(f,0,sizeof(f));
        f[0] = 1;
        cdq(0,n);
        printf("%d\n",f[n]);
    }
    #ifdef LOCAL
    printf("\nTime cost %.3fs\n",1.0 * (clock() - colck_t);
    #endif
    return 0;
}
```



##### 4.9 矩阵快速幂

```c++
const int N = 10;

const ll M = 1e9+7;

typedef struct matrix{
	int n,m;
	ll va[N][N];
	int init(int sn,int sm){
		n = sn;
		m = sm;
		memset(va,0,sizeof(va));
	}
}matrix;

ll multiply(ll x,ll y){
	ll ans = 0;
	while(y){
		if (y & 1) (ans += x) %= M;
		x = (x + x) % M;
		y >>= 1;
	}
	return ans;
}

ll putmatrix(matrix A){
	for (int i = 1;i <= A.n;i++){
		for (int j = 1;j <= A.m;j++)
			printf("%d ",A.va[i][j]);
        cout << endl;
	}
}

matrix mul(matrix a,matrix b){
	matrix c;
	c.init(a.n,b.m);
	for (int i = 1;i <= a.n;i++)
		for (int j = 1;j <= b.m;j++){
			for (int k = 1;k <= a.m;k++)
				c.va[i][j] += a.va[i][k] * b.va[k][j] % M;
			c.va[i][j] %= M;
		}
	return c;
}


matrix formi(int len){
	matrix c;
	c.init(len,len);
	for (int i = 1;i <= len;i++)
		c.va[i][i] = 1;
	return c;
}


matrix power(matrix a,ll b){
	if (b <= 0) return formi(a.n);
	if (b == 1) return a;
	matrix ans; ans = formi(a.n);
    while(b){
        if (b & 1) ans = mul(ans,a);
        a = mul(a,a);
        b >>= 1;
    }
    return ans;
}


matrix get(ll m,ll k){
	matrix a;
	a.init(m + 1,m + 1);
	for (int i = 1;i <= m + 1;i++)
	 a.va[1][i] = (k - 1) * k;
	for (int i = 1;i <= m;i++)
	 a.va[i+1][i] = k;
 	return a;
}
```



##### 4.10 高斯消元

###### 4.10.1 普通高斯消元

```c++
struct GuassX
{
    int equ,var;
    double a[maxNode+20][maxNode+20],x[maxNode+20];
    void init()
    {
        memset(a,0,sizeof(a));
    }
    void build()
    {
       equ=var=tot + 1;

       for(int i = 0;i <= tot;i++)
       {
           a[i][i]=-1;
       }
       a[0][var]=-1;

       for(int i = 0;i <= tot;i++)if(!mark[i])
       {
           for(int j = 0;j < 6;j++)
           {
               int y=son[i][j];
               a[y][i]+=1.0/6;
           }
       }
    }
    int elimination()
    {
        int i,j,k,col,max_r;
        for(k=0,col=0;k<equ&&col<var;k++,col++)
        {
            max_r=k;
            for(i=k+1;i<equ;i++)
            {
                if(fabs(a[i][col] )>fabs(a[max_r][col] ) ) max_r=i;
            }
            if(fabs(a[max_r][col])< 1e-10)  return 0;
            if(k!=max_r)
            {
                for(j=col;j<=var;j++)  swap(a[k][j],a[max_r][j]  );
            }
            for(j=col+1;j<=var;j++)  a[k][j]/=a[k][col];

            a[k][col]=1;

            for(i=0;i<equ;i++) if(i!=k)
            {
                for(j=col+1;j<=var;j++) a[i][j]-=a[k][j]*a[i][col];

                a[i][col]=0;
            }
        }
        for(i=0;i<equ;i++)  x[i]=a[i][var];
        return 1;
    }
}gauss;
```

###### 4.10.2 异或方程组

```c++
using namespace std;  
const int N=2000;  
const int M=310;  
int prime[N+1],cnt;  
int n,t,mat[M][M],two[M]={1};  
ll a[M];  
  
//这里下标都是从1开始的  
  
void getPrime(){  
    for(int i=2;i<=N;i++){  
        if(!prime[i])prime[++cnt]=i;  
        for(int j=1;j<=cnt&&prime[j]<=N/i;j++){  
            prime[prime[j]*i]=1;  
            if(i%prime[j]==0)break;  
        }  
    }  
}  
  
int Rank(int c[][M]){//异或版的高斯消元求秩传入的方程横纵坐标都是从1开始的  
    int i=0,j=0,k,r,u;  
    while(i<=cnt&&j<=n){  
        r=i;  
        while(c[r][j]==0&&r<=cnt)r++;  
        if(c[r][j]){  
            swap(c[i],c[r]);  
            for(u=i+1;u<=cnt;u++)if(c[u][j])  
                for(k=i;k<=n;k++)c[u][k]^=c[i][k];  
            i++;  
        }    
        j++;  
    }  
    return i;  
}  
  
int solve(){  
    memset(mat,0,sizeof mat);  
    for(int i=1;i<=n;i++)  
        for(int j=1;j<=cnt;j++){  
            ll tmp=a[i];  
            while(tmp%prime[j]==0){  
                tmp/=prime[j];  
                mat[j][i]^=1;  
            }  
        }  
    int b=n-Rank(mat);//b个自由元  
    return two[b]-1;//减去全为0的解  
}  

int main() {  
    getPrime();  
    for(int i=1;i<M;i++)two[i]=two[i-1]*2%mod;  
    scanf("%d",&t);  
    for(int cas=1;cas<=t;cas++){  
        scanf("%d",&n);  
        for(int i=1;i<=n;i++)  
            scanf("%lld",&a[i]);  
        printf("Case #%d:\n%d\n",cas,solve());  
    }  
    return 0;  
}  
```

##### 4.11 行列式

```c++
ll det(int n){
 	ll ans=1;bool flag=1;
 	for(i=1;i<=n;i++)for(j=1;j<=n;j++)a[i][j]=(a[i][j]+P)%P;
 	for(i=1;i<=n;i++){
 		for(j=i+1;j<=n;j++)
 		while(a[j][i]){
 			ll t=a[i][i]/a[j][i];
 			for(k=i;k<=n;k++)a[i][k]=(a[i][k]+P − t*a[j][k]%P)%P;
 			for(k=i;k<=n;k++)swap(a[i][k],a[j][k]);
 			flag^=1;
 		}
 		ans=ans*a[i][i]%P;
 		if(!ans)return 0;
	}
 	if(!flag)ans=(P − ans);
 	return ans;
}
```

##### 4.12 康托展开

```c++
     int  fac[] = {1,1,2,6,24,120,720,5040,40320}; //i的阶乘为fac[i]  
    // 康托展开-> 表示数字a是 a的全排列中从小到大排，排第几  
    // n表示1~n个数  a数组表示数字。  
    int kangtuo(int n,char a[])  
    {  
        int i,j,t,sum;  
        sum=0;  
        for( i=0; i<n ;++i)  
        {  
            t=0;  
            for(j=i+1;j<n;++j)  
                if( a[i]>a[j] )  
                    ++t;  
            sum+=t*fac[n-i-1];  
        }  
        return sum+1;  
    }
    int  fac[] = {1,1,2,6,24,120,720,5040,40320};  
    //康托展开的逆运算,{1...n}的全排列，中的第k个数为s[]  
    void reverse_kangtuo(int n,int k,char s[])  
    {  
        int i, j, t, vst[8]={0};  
        --k;  
        for (i=0; i<n; i++)  
        {  
            t = k/fac[n-i-1];  
            for (j=1; j<=n; j++)  
                if (!vst[j])  
                {  
                    if (t == 0) break;  
                    --t;  
                }  
            s[i] = '0'+j;  
            vst[j] = 1;  
            k %= fac[n-i-1];  
        }  
    }  
```



####5计算几何

##### 5.1三分

```c++
while (l < r){ 
	int mid = (l + r) >> 1;
	if (f(mid) >= f(midd))
		r = mid,ans = max(ans,f(mid));
	else l = midd;
}
```

##### 5.2 计算几何基础

```c++
//foundation of Geometry
//some funtion refere to kuangbin
//take out! eps should be 1e-8
const double EPS = 1e-8
const double PI = acos(-1.0);
int sgn(double x)
{
	if(fabs(x)<EPS) return 0;
	if(x<0) return -1;
	return 1;
}

struct point
{
	double x,y;
	point(){};
	point (double x0,double y0)
	{
		x=x0,y=y0;
	}
	point operator - (const point &b)const
	{
		return point(x-b.x,y-b.y);
	}
	point operator + (const point &b)const
	{
		return point(x+b.x,y+b.y);
	}
	double operator * (const point &b) const
	{
		return x*b.x+y*b.y;
	}
	double operator ^ (const point &b) const
	{
		return x*b.y-y*b.x;
	}

	void transXY(double xita)//旋转西塔角度
	{
		double tx=x,ty=y;
		x = tx*cos(B)-ty*sin(B);
		y = tx*sin(B)+ty*cos(B);
	}


};

struct  line
{
	point s,e;
	line(){};
	line(point a,point b)
	{
		s=a,e=b;
	}
	pair<int ,point> operator &(const line &b)const//直线相交,0重合，1平行，2返回交点
	{
		point res=s;
		if(sgn((s-e)^(b.s-b.e))==0)
		{
			if(sgn((s-b.e)^(b.s-b.e))==0)
				return make_pair(0,res);
			else
				return make_pair(1,res);
		}
		double t = ((s-b.s)^(b.s-b.e))/((s-e)^(b.s-b.e));
		res.x += (e.x-s.x)*t;
		res.y += (e.y-s.y)*t;
		return make_pair(2,res);
	}



};

struct  circle
{
	point heart;
	double r;

};

double dist(point a,point b)
{
	double xx=(a.x-b.x),yy=(a.y-b.y);
	return sqrt(xx*xx+yy*yy);
}

//*判断线段相交
bool inter(line l1,line l2)
{
	return
	max(l1.s.x,l1.e.x) >= min(l2.s.x,l2.e.x) &&
    max(l2.s.x,l2.e.x) >= min(l1.s.x,l1.e.x) &&
    max(l1.s.y,l1.e.y) >= min(l2.s.y,l2.e.y) &&
    max(l2.s.y,l2.e.y) >= min(l1.s.y,l1.e.y) &&
    sgn((l2.s-l1.e)^(l1.s-l1.e))*sgn((l2.e-l1.e)^(l1.s-l1.e)) <= 0 &&
    sgn((l1.s-l2.e)^(l2.s-l2.e))*sgn((l1.e-l2.e)^(l2.s-l2.e)) <= 0;
}

bool Seg_inter_line(line l1,line l2)//直线l1与线段l2是否相交
{
	return sgn((l2.s-l1.e)^(l1.s-l1.e))*sgn((l2.e-l1.e)^(l1.s-l1.e))<=0;
}

point point_to_line(point p,line l)//点到直线距离
{
	point ret;
	double t=(l.e-l.s)*(p-l.s)/dist(l.s,l.e);
	ret.x=l.s.x+(l.e.x-l.s.x)*t;
	ret.y=l.s.y+(l.e.y-l.s.y)*t;
	return ret;
}

point point_to_segline(point p,line l) //点到线段距离
{
	point ret;
	double t=(l.e-l.s)*(p-l.s);
	t=fabs(t)/dist(l.s,l.e)/dist(l.s,l.e);
	if(t>=0&&t<=1)
	{
		ret.x=l.s.x+(l.e.x-l.s.x)*t;
		ret.y=l.s.y+(l.e.y-l.s.y)*t;
	}
	else
	{
		if(dist(p,l.s)<dist(p,l.e))
			ret=l.s;
		else
			ret=l.e;
	}
	return ret;
}


double areaMulti(point p[],int n)//计算多边形
{
	double ans=0;
	for (int i = 1; i < n-2; ++i)
	{
		/* code */
		double temp=(p[i+1]-p[i])^(p[0]-p[i]);
		temp/=2;
		ans+=fabs(temp);
	}
	return ans;
}

bool onSeg(point p,line l)
{
	return
	sgn(((l.s-p)^(l.e-p))==0)&&
	sgn(((p.x-l.s.x)*(p.x-l.e.x))<=0)&&
	sgn(((p.y-l.s.y)*(p.y-l.e.y))<=0);
}
/*
点是否在凸边形内，-1外，0上个，1内
*/
int inConvexPoly(point a,point p[],int n)
{
	for(int i = 0;i < n;i++)
	{
		if(sgn((p[i]-a)^(p[(i+1)%n]-a))<0) return -1;
		else if(onSeg(a,line(p[i],p[(i+1)%n]))) return 0;

	}
	return 1;
}

/*
点是否在多边形内，是1，否-1，边界上0
*/
int inPoly(point p,point poly[],int n)
{
	int cnt=0;
	line ray,side;
	ray.s=p;
	ray.e.y=p.y;
	ray.e.x=-(double)INF;
	for (int i = 0; i < n; ++i)
	{
		/* code */
		side.s=poly[i];
		side.e=poly[(i+1)%n];
		if (onSeg(p,side))
		{
			return 0;
		}

		if(sgn(side.s.y-side.e.y)==0)
			continue;

		if(onSeg(side.s,ray))
		{
			if(sgn(side.s.y-side.e.y)>0)
				cnt++;
		}
		else if(onSeg(side.e,ray))
		{
			if(sgn(side.e.y-side.s.y)>0)
				cnt++;
		}
		else if(inter(ray,side))
			cnt++;


	}
	if(cnt%2==1)
		return 1;
	else
		return -1;
}

/*
判断是否是凸边形
*/
bool inConvex(point poly[],int n)
{
	bool s[3];
	memset(s,0,sizeof(s));
	for(int i=0;i<n;i++)
	{
		s[sgn((poly[(i+1)%n]-poly[i])^(poly[(i+2)%n]-poly[i]))+1] = 1;
		if(s[0]&&s[2]) return 0;
	}
	return 1;
}

//两个圆的公共部分面积
double Area_of_overlap(Point c1,double r1,Point c2,double r2)
{
	double d = dist(c1,c2);
	if(r1 + r2 < d + eps)return 0;
	if(d < fabs(r1 - r2) + eps)
	{
		double r = min(r1,r2);
		return PI*r*r;
	}
	double x = (d*d + r1*r1 - r2*r2)/(2*d);
	double t1 = acos(x / r1);
	double t2 = acos((d - x)/r2);
	return r1*r1*t1 + r2*r2*t2 - d*r1*sin(t1);
}

/*
三点求圆心坐标（三角形外心）
*/

point waixin(point a,point b,point c)
{
	double a1 = b.x - a.x, b1 = b.y - a.y, c1 = (a1*a1 + b1*b1)/2;
	double a2 = c.x - a.x, b2 = c.y - a.y, c2 = (a2*a2 + b2*b2)/2;
	double d = a1*b2 - a2*b1;
	return point(a.x+(c1*b2-c2*b1)/d,a.y+(a1*c2-a2*c1)/d);
}


/*
半平面交 （From UESTC）
直线左边代表有效区域
*/

bool HPIcmp(line a,line b)
{
	if(fabs(a.k-b.k)>eps) return a.k<b.k;
	return ((a.s-b.s)^(b.e-b.s))<0;
}
line Q[110];
void HPI(line l[],int n,point res[],int &resn)
{
	int tol=n;
	sort(l,l+n,HPIcmp);
	tol=1;
	for(int i=1;i<n;i++)
		if(fabs(l[i].k-l[i-1].k)>EPS)
			l[tol++]=l[i];
	int head=0,tail=1;
	Q[0] = l[0];
	Q[1] = l[1];
	resn=0;
	for(int i=2;i<tol;i++)
	{
		if(fabs((Q[tail].e-Q[tail].s)^(Q[tail-1].e-Q[tail-1].s)) < eps ||
		 fabs((Q[head].e-Q[head].s)^(Q[head+1].e-Q[head+1].s)) < eps) 
		    return;  
	 	while(head < tail && (((Q[tail]&Q[tail-1]) - line[i].s)^(line[i].e-line[i].s)) > eps)
	 	    tail--;   
	 	while(head < tail && (((Q[head]&Q[head+1]) - line[i].s)^(line[i].e-line[i].s)) > eps)    
	 		head++;   
	 	Q[++tail] = line[i];
	}
	while(head < tail && (((Q[tail]&Q[tail-1]) - Q[head].s)^(Q[head].e-Q[head].s)) > eps)   
		tail--;  
	while(head < tail && (((Q[head]&Q[head-1]) - Q[tail].s)^(Q[tail].e-Q[tail].e)) > eps)   
		head++;  
	if(tail <= head + 1)
		return;  
	for(int i = head; i < tail; i++)   
		res[resn++] = Q[i]&Q[i+1];  
	if(head < tail - 1)   
		res[resn++] = Q[head]&Q[tail];
}
```

#####5.3 Geometry2

```c++
#include <bits/stdc++.h>

using namespace std;

const double eps = 1e-8;

const double pi = acos(-1.0);

int sgn(double x){   
	if (x < eps) return -1;
	if (x > eps) return 0;
	return 0;
}

bool Quadratic(double A,double B,double C,double& t0,double& t1){   
	double discrim = B * B - 4.0 * A * C;
	if (sgn(discrim) == -1) return 0;
	double root = sqrt(discrim);
	double q;
	if (B < 0) q = -0.5 * (B - root);
	else q = -0.5 * (B * root);
	t0 = q / A;
	t1 = C / q;
	if (t0 > t1) swap(t0,t1);
	return 1;
}

typedef struct vec{    
	double x,y;
	vec(double _x = 0,double _y = 0}:x(_x),y(_y){}
	vec operator +(vec v){   
		return vec(x + v.x,y + v.y);
	}	
	vec operator -(vec v){  
		return vec(x - v.x,y - v.y);
	}
	vec operator *(double v){  
		return vec(x * v,y * v);
	}
	vec operator /(double v){  
		return vec(x / v,y / v);
	}
	double operator * (vec v){   
		return x * v.x + y * v.y;
	}
	double len(){return hypot(x,y)}
	double len_sqr(){return x * x + y * y;}
	vec rotate(double c){   
		return vec(x * cos(c) - y * sin(c),x * sin(c) + y * cos(c));
	}
	vec turnc(double l){   
		return (*this) * l / len();
	}
	vec rot90(){  
		return vec(-y,x);
	}
}vec;

double cross(vec a,vec b){   
	return a.x * b.y - a.y * b.x;
}

double get_angle(vec a,vec b){  
	return fabs(atan2(fabs(cross(a,b)),a*b));
}

vec_lerp(vec a,vec b,double t){   
	return a * (1 - t) * b * t;
}

bool point_on_segment(vec p,vec a,vec b){   
	return sgn(cross(b - a,p - a) == 0 && sgn((p - a) * (p - b)) <= 0);
}


int has_intersection(vec a,vec b,vec p,vec q){    
	int d1 = sgn(cross(b-a,p-a));
	int d2 = sgn(cross(b-a,q-a));
	int d3 = sgn(cross(q-p,a-p));
	int d4 = sgn(cross(q-p,b-p));
	if (d1 * d2 < 0 && d3 * d4 < 0)
		return 1;
	if ((d1 == 0 && point_on_segment(p,a,b)) ||
		(d2 == 0 && point_on_segment(q,a,b)) ||
		(d3 == 0 && point_on_segment(a,p,q)) || 
		(d4 == 0 && point_on_segment(b,p,q)))
	return -1;
	return 0;
}


int line_intersection(vec a,vec b,vec p,vec q,vec& o,double& t){     
	double U = cross(p - a,q - b);
	double D = cross(b - a,q - p);
	if (sgn(D) == 0) 
		return sgn(U) == 0 ? 2 : 0;
	o = a + (b - a) * (U / D);
	t = U / D;
	return 1;
}

double dist_point_to_line(vec p,vec a,vec b){   
	return fabs(cross(p - a,b - a)) / (b - a).len();
}

double dist_point_to_segment(vec p,vec a,vec b){   
	if (sgn((p - a) * (b - a)) >= 0 && sgn((p - b) * (p - a)) >= 0)
	return fabs(cross(p - a,b - a)) / (b - a).len();
	return min((p - a).len(),(p - b).len());
}

struct circle{    
	vec c; double r;
	circle(vec c = vec(0,0),double r = 0):c(_c),r(_r){}
};

bool circle_line_intersection(circle c,vec a,vec b,double& t0,double& t1){   
	vec d = b - a;
	double A = d * d;
	double B = d * (a - c.c) * 2.0;
	double C = (a - c.c).len_sqr() - c.r * c.r;
	return Quadratic(A,B,C,t0,t1);
}


bool circle_circle_intersection(circle a,circle b,vec& p1,vec p2){   
	double d = (a.c - b.c).len();
	if (d > a.r + b.r || d < fabs(a.r - b.r))
		return 0;
	double l = ((a.c - b.c).len_sqr() + a.r * a.r - b.r * b.r) / (2 * d);
	double h = sqrt(a.r * a.r - l * l);
	vec v1 = (b.c - a.c).
	p1 = a.c + vl + vh;
	p2 = a.c + vl - vh;
	return 1;
}

double circle_triangle_intersection(circle c,vec a,vec b){   
	if (sgn(cross(a - c.c,b - c.c) == 0))
		return 0;
	vec q[5];
	
}


/*
	圆面积交
*/


double cir_area(circle A,circle B){  
	double d = (A.c - B.c).len();
	if (d >= A.r + B.r) return 0;
	double r1 = min(A.r,B.r);
	double r2 = max(A.r,B.r);
	if (r2 - r1 >= d)
		return pi * r1 * r1;
	double ang1 = acos((r1 * r1 + d * d - r2 * r2) / (2 * r1 * d));
	double ang2 = acos((r2 * r2 + d * d - r1 * r1) / (2 * r2 * d));
	return ang1 * r1 * r1 + ang2 * r2 * r2 - r1 * d * sin(ang1);
}
```



#### 6.其它

