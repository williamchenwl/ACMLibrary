#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cstring>
#define inf 1000000000
#define ll long long

using namespace std;

int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}

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