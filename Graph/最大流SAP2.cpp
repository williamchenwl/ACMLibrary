#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N=55101;

const int inf=~0U>>1;

typedef struct seg{
  int next,x,f,op;
}seg;

int n,m;  

//数组记得开够！！！

seg v[N*8];

int S,T,tt;

int x,y,tmp,z,tot=0;

int base[N],d[N],num[N];

int add(int x,int y,int f){
  v[++tot].x=y; v[tot].f=f; v[tot].op=tot+1;
  v[tot].next=base[x]; base[x]=tot;
  v[++tot].x=x; v[tot].f=0; v[tot].op=tot-1;
  v[tot].next=base[y]; base[y]=tot; 
}
 
int sap(int u,int flow){
	 if (u==T) return flow; 
     int tmp,now=0;
     for (int i=base[u];i;i=v[i].next){
       int x=v[i].x;
       if (!v[i].f||d[u]!=d[x]+1) continue;
       tmp=sap(x,min(flow-now,v[i].f));
       now+=tmp; v[i].f-=tmp; v[v[i].op].f+=tmp;
          if (now==flow) return now; 
     }
     if (d[S]>=tt) return now;
     num[d[u]]--; if (!num[d[u]]) d[S]=tt;
     num[++d[u]]++; return now;
}
 
int main(){

   scanf("%d%d",&n,&m); 

   S=0; T=n+m+1; tt=T+1; int sum=0;

   for (int i=1;i<=n;i++)
     scanf("%d",&tmp),add(i+m,T,tmp);

   for (int i=1;i<=m;i++){
   	scanf("%d%d%d",&x,&y,&z); 
   	sum+=z;
    add(S,i,z); 
    add(i,x+m,inf);
    add(i,y+m,inf);
   }

   memset(num,0,sizeof(num));

   num[0]=tt; int ans=0;

   while (d[S]<tt) ans+=sap(S,inf);

   printf("%d\n",sum-ans);
}