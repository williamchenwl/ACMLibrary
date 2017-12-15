Some Specific Problems

[TOC]

##### 1.不相交的圆面积并

```c++
#include <bits/stdc++.h>

using namespace std;

int nowx;

const int N = 2100000;

typedef long long ll;

struct circle{
	int x,y;
	ll r;
	circle(){}
	circle(int _x,int _y,int _r):x(_x),y(_y),r(_r){}
};

circle C[N];

struct qu{
    int x,ty,id;
    qu(){}
    qu(int _x,int _ty,int _id):x(_x),ty(_ty),id(_id){}
    bool operator<(const qu& a)const{
        if (a.x != x) return x < a.x;
        else return ty < a.ty;
    }
};

qu q[N * 2];

int col[N];

double posx(int id,int ty){
		double delta = nowx - C[id].x;
		delta = delta * delta;
		delta = (double)C[id].r * (double)C[id].r - delta;
		delta = sqrt(delta);
		return C[id].y + ty * delta;
}

typedef struct seg{
	int id,ty;

	seg(int _id,int _ty):id(_id),ty(_ty){}

	bool operator <(const seg& a)const{
		double p1 = posx(id,ty);
		double p2 = posx(a.id,a.ty);
		if (p1 != p2) return p1 < p2;
		else return ty < a.ty;
	}
}seg;

set<seg>S;

int n;

int main(){
	while(cin >> n){
		int tot = 0;
		for (int i = 1;i <= n;i++){
			int x,y,c;
			scanf("%d%d%d",&x,&y,&c);
            C[i] = circle(x,y,c);
            q[++tot] = qu(x-c,1,i);
            q[++tot] = qu(x+c,-1,i);
		}

		sort(q+1,q+tot+1);
		S.clear();
		col[0] = -1;
		for (int i = 1;i <= tot;i++)if(q[i].ty==1){
            nowx = q[i].x;
		    if(!S.empty()){
                set<seg>::iterator itr;
                itr = S.upper_bound(seg(q[i].id,1));
                if (itr == S.end()){
                    col[q[i].id] = 1;
                }else{
                    seg ng = *itr;
                    if (ng.ty == 1){
                        col[q[i].id] = -col[ng.id];
                    }else col[q[i].id] = col[ng.id];
                }
		    }else col[q[i].id] = 1;
			S.insert(seg(q[i].id,1));
			S.insert(seg(q[i].id,-1));
		}else{
		    nowx = q[i].x;
			S.erase(seg(q[i].id,1));
			S.erase(seg(q[i].id,-1));
		}

		long long ans = 0;
		for (int i = 1;i <= n;i++){
            ans = ans + (long long)C[i].r * (long long)C[i].r * col[i];
		}
		cout << ans << endl;
	}
}
```

#####2.Shift-And算法

```c++
#include <bits/stdc++.h>

using namespace std;
const int N = 5000005;

char s[N];

bitset<1002>dp,pos[15];

int main(){
	int n;
	scanf("%d",&n);
	for (int i = 0;i < n;i++){
		int cnt; scanf("%d",&cnt);
		for (int j = 0;j < cnt;j++){
            int x;
			scanf("%d",&x);
			pos[x].set(i);
		}
    }
	getchar();
	gets(s);
	//cout << s << endl;
	int len = strlen(s);
	for (int i = 0;i < len;i++){
		dp = (dp << 1);
        dp.set(0);
		dp &= pos[s[i]-'0'];
		if (dp[n-1] == 1){
			char ch = s[i+1];
			s[i+1] = 0;
			puts(s + i - n + 1);
			s[i+1] = ch;
		}
	}
}

```

##### 3.数位DP

```
通常用eq表示当前状态是否等于dp数
用lim表示是否还需要满足某些条件
now_len表示数的真正长度
```

```c++
#include <bits/stdc++.h>

using namespace std;

const int N = 50;

int n,m;

typedef long long ll;

ll dp[N][N][39],a[N],tmp[N];

const ll M = 1e9+7;

int a_mod = 0;

ll dpit(int now,int now_len,int eq,int mod,bool lim){
    if (now == 0) return eq;
    if (eq == 0) return 0;
    if (!lim && dp[now][now_len][mod] != -1)
        return dp[now][now_len][mod];
    int maxnum = mod - 1;
    if (lim) maxnum = a[now];
    ll ans = 0;
    for (int ch = 0;ch <= maxnum;ch++){
        bool ismaxnum = (ch == maxnum);
        bool v = lim && ismaxnum;
        if (ch == 0 && now_len == now){
            ans += dpit(now-1,now_len-1,eq,mod,v);
            continue;
        }
        tmp[now] = ch;
        if (now <= now_len / 2 && eq)
            ans += dpit(now-1,now_len,eq && (tmp[now] == tmp[now_len - now + 1]),mod,v);
        else ans += dpit(now-1,now_len,eq,mod,v);
    }
    if (!lim) dp[now][now_len][mod] = ans;
    return ans;
}

ll solve(int mod,ll x){
    a[1] = 0;
    n = 0; ll tmp = x; a_mod = mod;
    while(x) a[++n] = x % mod,x /= mod;
    n = max(n,1);
    ll cnt = dpit(n,n,1,mod,1);
    //cout << cnt << endl;
    return cnt;
}

int main(){
    int T; scanf("%d",&T);
    memset(dp,-1,sizeof(dp));
    int nc = 0;
    while(T--){
        int L,R,l,r;
        scanf("%d%d%d%d",&L,&R,&l,&r);
        ll ans = 0;
        for (int mod = l;mod <= r;mod++){
             ll cnt = solve(mod,R) - solve(mod,L - 1);
             ans += cnt * (ll)mod + (ll)(R - L + 1 - cnt);
        }
        printf("Case #%d: ",++nc);
        printf("%lld\n",ans);
    }
}
```

##### 4.手动实现Bitset

```c++
#include <bits/stdc++.h>

using namespace std;

const int K = 50;

typedef long long ll;

const int N = 58000;

const int len = (N / K) + 1;

typedef unsigned long long ull;

int tmppos[N];

struct bitSet{

	ull bits[N];

	bitSet(){
		for (int i = 0;i <= len * 2;i++)
			bits[i] = 0;
	}

	void _clear(){
        memset(bits,0,sizeof(bits));
	}

	int getpos(int pos){
		int loc = pos / K;
		ull shift = pos - loc * K;
		return (int)((bits[loc] >> shift) & 1ull);
	}

	void init(bool a[],int n){

		for (int i = 0;i <= len;i++)
			bits[i] = 0ull;

		for (int i = n;i >= 0;i--){
            int now = i / K;
            bits[now] = (bits[now] << 1ull) | (ull)a[i];
		}
	}

	void xxor(const bitSet& a,int l,int r){
		ull shift = l - (l/K)*K;
		for (int lx = 0;lx <= r - l;lx += K){
            int lt = lx / K * K + l;
            int rt = lx / K * K + l + K - 1;
            rt = min(rt,r);
            int pos = lt/K;
            ull ans = a.bits[pos + 1] & ((1ull << shift) -1ull);
            ans = ans << ((ull)K - shift);
            ans = ans | (a.bits[pos] >> shift);
            if (lx / K * K + l + K - 1 != rt){
                ull shift2 = rt - lt + 1;
                ans = ans & ((1ull << shift2) - 1ull);
            }
            bits[lx/K] ^= ans;
		}
	}
};

int n,m,k;

bool a[N],b[N];

bitSet now,ans;

int main(){
	int T; scanf("%d",&T);
	while(T--){
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		ans._clear();
		now._clear();
		scanf("%d%d%d",&n,&m,&k);
		int maxa = 0,maxb = 0;
		for (int i = 0;i < n;i++){
			int x; scanf("%d",&x);
			a[x] ^= 1;
			maxa = max(maxa,x);
		}
		now.init(a,maxa);
		/*
		for (int i = 0;i <= maxa;i++)
            cout << now.getpos(i) << " ";
        cout << endl;
        */

		for (int i = 0;i < m;i++){
			int op; scanf("%d",&op);
			b[op] ^= 1;
			maxb = max(maxb,op);
		}

        //ans.xxor(now,1,1);
        //ans.xxor(now,3,3);
        //ans.xxor(now,1,5);

		for (int i = 1;i <= maxb;i++)if(b[i]){
			for (int j = 0;j <= maxa;j += i){
				int l = j;
				int r = j + i - 1;
				r = min(r,maxa);
				ans.xxor(now,l,r);
			}
			//printf("%d\n",ans.getpos(0));
		}

		for (int i = 1;i <= k;i++){
			int x; scanf("%d",&x);
			printf("%d\n",ans.getpos(x));
		}
	}
}
```

##### 5.反素数

```
求第d(i) = n的最小数，d(i)表示约束个数
```

```c++
    #include <iostream>  
    #include <string.h>  
    #include <stdio.h>  
      
    using namespace std;  
    typedef unsigned long long ULL;  
    const ULL INF = ~0ULL;  
      
    int p[16] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53};  
      
    ULL ans,n;  
    int best;  
      
    void dfs(int dept,int limit,ULL tmp,int num)  
    {  
        if(tmp > n) return;  
        if(num > best)  
        {  
            best = num;  
            ans = tmp;  
        }  
        if(num == best && ans > tmp) ans = tmp;  
        for(int i=1;i<=limit;i++)  
        {  
            double cur = (double)tmp;  
            if(n < cur*p[dept]) break;  
            dfs(dept+1,i,tmp *= p[dept],num*(i+1));  
        }  
    }  
      
    int main()  
    {  
        int T;  
        cin>>T;  
        while(T--)  
        {  
            cin>>n;  
            ans = INF;  
            best = 0;  
            dfs(0,60,1,1);  
            cout<<ans<<" "<<best<<endl;  
        }  
        return 0;  
    }  

```



##### 6.树上dp+分组背包

```c++
int dfs(int u){
	vis[u] = 1;
	for (int i = LinkGx.base[u];i;i = LinkGx.nxt[i]){
		int y = LinkGx.now[i];
		if (vis[y]) continue;
		dfs(y);
		for (int j = k;j;j--){
            dp[u][j] = dp[u][j] + 2 * LinkGx.val[i] + dp[y][0];
			for (int v = 1;v <= j;v++)
				dp[u][j] = min(dp[u][j],dp[y][v] + v * LinkGx.val[i] + dp[u][j - v]);
		}
		dp[u][0] = dp[u][0] + 2 * LinkGx.val[i] + dp[y][0];
	}
	//cout << u << " " << dp[u][0] << endl;
	return dp[u][k];
}
```

#####6.DMST

```c++
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>

using namespace std;

const int N = 1100;

const int M = N * N;

const int inf = ~0U>>1;

int ROOT;

int abs(int x){
    return x > 0 ? x : -x;
}

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

int n,X,Y,Z;

typedef struct node{
	int x,y,z;
	int anode(int _x,int _y,int _z){
		x = _x;
		y = _y;
		z = _z;
		return 0;
	}
}node;

node V[N];

inline int dist(node A,node B){
	return abs(A.x - B.x) + abs(A.y - B.y) + abs(A.z - B.z);
}

inline int delta(node A,node B){
	if (A.z >= B.z) return 0;
	return 1;
}

int GraphBuild(){
	scanf("%d%d%d%d",&n,&X,&Y,&Z);
	if (!n && !X && !Y && !Z) return -1;
	for (int i = 1;i <= n;i++){
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		V[i].anode(x,y,z);
	}
	G.init(n + 1);
	for (int i = 1;i <= n;i++){
		G.add(0,i,X * V[i].z);
		int k,des;
		scanf("%d",&k);
		for (int j = 1;j <= k;j++){
			scanf("%d",&des);
			if (des == i) continue;
			G.add(i,des,dist(V[i],V[des]) * Y + Z * delta(V[i],V[des]));
		}
	}
	int ans = G.dmst(0);
	printf("%d\n",ans);
	return 0;
}

int main(){
	while(~GraphBuild());
}
```



##### 8.求桥

```c++
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

const int M = 2100000;

const int N = 2000;

int base[N],nxt[M],now[M];

int va[M];

int tot = 1;

inline void add(int x,int y){
    now[++tot] = y;
    nxt[tot] = base[x];
    base[x] = tot;
    now[++tot] = x;
    nxt[tot] = base[y];
    base[y] = tot;
}

struct Tarjan{

	int dfn[N],low[N],f[N],from[N],cut[M],cnt;

	void tarjan(int x){
		dfn[x] = low[x] = ++tot;
		for (int i = base[x];i;i = nxt[i]){
			int y = now[i];
			if (!dfn[y]){
				f[y] = i >> 1;
				tarjan(y);
				if (low[x] > low[y]) low[x] = low[y];
			}else if (f[x] != (i >> 1) && low[x] > dfn[y]) low[x] = dfn[y];
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
		memset(f,0,sizeof(f));
		memset(from,0,sizeof(from));
		memset(cut,0,sizeof(cut));
		cnt = 0;
		tarjan(1);
		//for (int i = 1;i <= n;i++)
		//	dfs(i,++cnt);
	}

	/*
		The ID of edges should start at 2
	*/
}Ta;

int f[N];

int getf(int x){
    if (f[x] == x) return x;
    return f[x] = getf(f[x]);
}

const int inf = ~0U>>1;

int main(){
    ios_base::sync_with_stdio(false);
    int n,m;
    while(cin >> n >> m){
           if (n == 0 && m == 0) break;
           tot = 1;
           memset(base,0,sizeof(base));
           for (int i = 1;i <= n;i++) f[i] = i;
           for (int i = 1;i <= m;i++){
                int x,y;
                cin >> x >> y >> va[i];
                add(x,y);
                if (getf(x) != getf(y))
                f[getf(x)] = getf(y);
           }
           int cnt = 0;
           for (int i = 1;i <= n;i++) if (getf(i) == i) cnt++;
           if (cnt != 1){
                cout << 0 << endl;
                continue;
           }
           Ta.init(n);
           int ans = inf;
           for (int i = 1;i <= m;i++) if (Ta.cut[i]) ans = min(ans,va[i]);
           if (ans == inf){
             cout << "-1" << endl;
           }else  cout << (ans ? ans : 1) << endl;
    }
}
```

#####9.斜率优化DP

```
f[i]=min{f[j]+(s[i]-s[j])^2+M}
展开得
f[i]=min{f[j]+s[i]^2+s[j]^2-2*s[i]*s[j]+M}
令f[i]=B,f[j]+s[j]^2=y,2*s[j]=x,k=s[i]
因此k*x+B=y
k是s[i]，前缀和随着i增大而增大，因为求最小值，故维护下凸包。
```

```c++
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<vector>
#include<cstdio>
#include<cmath>
#include<queue>
using namespace std;
inline const int Get_Int() {
    int num=0,bj=1;
    char x=getchar();
    while(x<'0'||x>'9') {
        if(x=='-')bj=-1;
        x=getchar();
    }
    while(x>='0'&&x<='9') {
        num=num*10+x-'0';
        x=getchar();
    }
    return num*bj;
}
long long n,m,Q[500005],f[500005],s[500005];
double Slope(long long j,long long k) { //求斜率 
    return double((f[j]+s[j]*s[j])-(f[k]+s[k]*s[k]))/(2*s[j]-2*s[k]);
}
int main() {
    while(scanf("%lld%lld",&n,&m)!=EOF) {
        for(int i=1; i<=n; i++)s[i]=s[i-1]+Get_Int();
        int Left=1,Right=1;
        Q[1]=0;
        f[0]=0;
        for(int i=1; i<=n; i++) {
            while(Left<Right&&Slope(Q[Left],Q[Left+1])<=s[i])Left++; //维护队首（删除非最优决策） 
            int Front=Q[Left];
            f[i]=f[Front]+(s[i]-s[Front])*(s[i]-s[Front])+m; //计算当前f 
            while(Left<Right&&Slope(Q[Right-1],Q[Right])>=Slope(Q[Right],i))Right--; //维护队尾（维护下凸包性质） 
            Q[++Right]=i; //入队 
        }
        printf("%lld\n",f[n]);
    }
    return 0;
}
```

##### 10.杜教筛

```c++
using namespace std;
ll n,h[size+5]={0},f[size+5];
int phi[limit+5],sum[limit+5],tot=0;
bool prime[limit+5]={0};

int hash(ll x)
{
  int pos=x%smod;
  while(h[pos]&&h[pos]!=x) pos=(pos+1)%smod;
  return pos;
}

void calc_phi(ll x)
{
  for(int i=1;i<=x;i++)
    phi[i]=i;
  for(ll i=2;i<=x;i++)
    if (!prime[i])
    {
      for(ll j=1;j*i<=x;j++)
      {
        prime[i*j]=1;
        phi[i*j]=phi[i*j]/i*(i-1);
      }
    }
  sum[0]=0;
  for(int i=1;i<=x;i++) sum[i]=(sum[i-1]+phi[i])%mod;
}

ll mult(ll a,ll b,ll c)
{
  if (a%c==0) a/=c;
  else b/=c;
  a%=mod,b%=mod;
  return (a*b)%mod;
}

ll count(ll x)
{
  int pos=hash(x);
  if (x<=limit) return (ll)sum[x];
  if (h[pos]==x) return f[pos];
  ll s=0,i=2,next;
  while(i<=x)
  {
    next=x/(x/i);
    s=(s+mult(next-i+1,count(x/i),1))%mod;
    i=next+1;
  }
  h[pos]=x,f[pos]=((mult(x,x+1,2)-s)%mod+mod)%mod;
  return f[pos];
}

int main()
{
  calc_phi(limit);
  scanf("%lld",&n);
  printf("%lld",count(n));
  return 0;
}
```

