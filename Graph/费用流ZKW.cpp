//ZKW.cpp
#include <cstdio>
#include <cstring>
#include <iostream>

#define debug printf("xxxxxx");

using namespace std;

const int maxn=2010;

const int inf=~0U>>1;

int f,fa,fb,n,a,b;

int tmp,ans=0,tot;

typedef struct edge{int x,op,f,cost,next;}edge;

edge v[maxn*2100]; int dis[maxn],base[maxn]; bool vis[maxn];

int S,T; int cur[maxn];

int min(int a,int b) {if (a<b) return a;else return b;}

int aug(int u,int flow){
  if (u==T) {ans += flow*dis[S]; return flow;}
  vis[u]=1; int now=0;
  for (int i=base[u];i;i=v[i].next){
       int x=v[i].x; 
       if (vis[x]||!v[i].f||dis[u]!=dis[x]+v[i].cost) continue;
       int tmp=aug(x,min(flow-now,v[i].f));
       if (tmp) v[i].f-=tmp; v[v[i].op].f+=tmp;
       now+=tmp;  if (now==flow) return flow; 
     }
  return now;
}

int modlable()
  {  int del=inf;
  	 for (int i=S;i<=T;i++)
     if (vis[i]) 
     for (int j=base[i];j;j=v[j].next)
     if (v[j].f) {int x=v[j].x;  
      if (!vis[x]) del=min(del,dis[x]+v[j].cost-dis[i]);}
     if (del==inf) return 0;
     for (int i=S;i<=T;i++)
       if (vis[i]) vis[i]=0,dis[i]+=del,cur[i]=base[i]; return 1;
   }
int zkw()
  {  for (int i=S;i<=T;i++) cur[i]=base[i];
  	 do {while (aug(S,inf)) memset(vis,0,sizeof(vis));}
     while (modlable()); printf("%d\n",ans);
   }

int add(int x,int y,int f,int c)
   {  v[++tot].x=y; v[tot].op=tot+1;
      v[tot].f=f; v[tot].cost=c;
      v[tot].next=base[x]; base[x]=tot;
      v[++tot].x=x; v[tot].op=tot-1;
      v[tot].f=0; v[tot].cost=-c;
      v[tot].next=base[y]; base[y]=tot;
   }

int main(){
     scanf("%d%d%d%d%d%d",&n,&a,&b,&f,&fa,&fb);
     S=0; T=2*n+1;
      for (int i=1;i<=n;i++) 
      	 { scanf("%d",&tmp);  
           add(S,i,tmp,f);
           add(i,T,tmp,0);
           add(S,n+i,tmp,0);
           for (int j=i+a+1;j<=n;j++)
       	   add(n+i,j,inf,fa);
           for (int j=i+b+1;j<=n;j++)
           add(n+i,j,inf,fb);
      	 }
      zkw(); 
}
