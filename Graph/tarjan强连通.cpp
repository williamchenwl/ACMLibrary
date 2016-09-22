#define inf 1000000000
#define ll long long 
using namespace std;
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int S,T;
int n,m,A,B,cnt;
int ind,top,scc,cost,ans;
int dfn[1005],low[1005],bl[1005];
int a[1005],b[1005],last[2005],last2[2005];
int d[2005],q[2005];
bool mark[2005],inq[1005];
struct edge{
	int to,next,v,c;
}e[100005],ed[100005];
void insert(int u,int v)
{
	e[++cnt].to=v;e[cnt].next=last[u];last[u]=cnt;
}
void insert2(int u,int v,int w,int c)
{
	ed[++cnt].to=v;ed[cnt].next=last2[u];last2[u]=cnt;ed[cnt].v=w;ed[cnt].c=c;
	ed[++cnt].to=u;ed[cnt].next=last2[v];last2[v]=cnt;ed[cnt].v=0;ed[cnt].c=-c;
}
void tarjan(int x)
{
	low[x]=dfn[x]=++ind;
	q[++top]=x;inq[x]=1;
	for(int i=last[x];i;i=e[i].next)
		if(!dfn[e[i].to])
		{
			tarjan(e[i].to);
			low[x]=min(low[x],low[e[i].to]);
		}
		else if(inq[e[i].to])
			low[x]=min(low[x],dfn[e[i].to]);
	if(low[x]==dfn[x])
	{
		int now=0;scc++;
		while(now!=x)
		{
			now=q[top--];inq[now]=0;
			bl[now]=scc;
		}
	}
}
bool spfa()
{
	memset(mark,0,sizeof(mark));
	for(int i=0;i<=S;i++)d[i]=-1;
	int head=0,tail=1;
	q[0]=T;d[T]=0;mark[T]=1;
	while(head!=tail)
	{
		int now=q[head];head++;if(head>2000)head=0;
		mark[now]=0;
		for(int i=last2[now];i;i=ed[i].next)
			if(ed[i^1].v&&d[now]+ed[i^1].c>d[ed[i].to])
			{
				d[ed[i].to]=d[now]+ed[i^1].c;
				if(!mark[ed[i].to])
				{
					mark[ed[i].to]=1;
					q[tail++]=ed[i].to;
					if(tail>2000)tail=0; 
				}
		}
	}
	return d[S]!=-1;
}
int dfs(int x,int f)
{
	mark[x]=1;
	if(x==T)return f;
	int w,used=0;
	for(int i=last2[x];i;i=ed[i].next)
		if(!mark[ed[i].to]&&ed[i].v&&d[x]-ed[i].c==d[ed[i].to])
		{
			w=dfs(ed[i].to,min(ed[i].v,f-used));
			ed[i].v-=w;ed[i^1].v+=w;cost+=ed[i].c*w;
			used+=w;
			if(used==f)return f;
		}
	return used;
}
void solve()
{
	cnt=1;
	T=2*scc+1;S=T+1;
	for(int i=1;i<=A;i++)insert2(0,bl[a[i]],inf,0);
	for(int i=1;i<=B;i++)insert2(bl[b[i]]+scc,T,inf,0);
	for(int x=1;x<=n;x++)
		for(int i=last[x];i;i=e[i].next)
			if(bl[x]!=bl[e[i].to])
				insert2(bl[x]+scc,bl[e[i].to],inf,0);
	for(int i=1;i<=scc;i++)
	{
		insert2(i,i+scc,1,1);
		insert2(i,i+scc,inf,0);
	}
	insert2(S,0,1,0);
	while(spfa())
	{
		int pre=cost;
		mark[T]=1;
		while(mark[T])
		{
			memset(mark,0,sizeof(mark));
			dfs(S,inf);
		}
		insert2(S,0,1,0);
		if(pre==cost)break;
		else ans++;
	}
}
int main()
{
	int T=read();
	while(T--)
	{
		memset(last,0,sizeof(last));
		memset(last2,0,sizeof(last2));
		memset(dfn,0,sizeof(dfn));
		ans=scc=cost=ind=cnt=0;
		n=read();m=read();A=read();B=read();
		for(int i=1;i<=A;i++)a[i]=read();
		for(int i=1;i<=B;i++)b[i]=read();
		for(int i=1;i<=m;i++)
		{
			int u=read(),v=read();
			insert(u,v);
		}
		for(int i=1;i<=n;i++)
			if(!dfn[i])tarjan(i);
		solve();
		if(cost!=scc)puts("no solution");
		else printf("%d\n",ans);
	}
	return 0;
}