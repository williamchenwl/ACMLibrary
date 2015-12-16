#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <stack>

using namespace std;

const int N=300010;
typedef long long ll;

const ll inf=1e18;

int son[N][2],sum[N],f[N],key[N],tag[N];

ll M[N],om[N];




int up(int x)
  { sum[x]=sum[son[x][0]]+sum[son[x][1]];
   	sum[x]+=key[x];
    M[x]=M[son[x][0]] * M[son[x][1]] * om[x];
    if (M[x] > inf) M[x] = 0;
  }

bool isroot(int x)
  {return !f[x]||son[f[x]][0]!=x&&son[f[x]][1]!=x;}

int reverse(int x)
  { swap(son[x][0],son[x][1]); tag[x]^=1;}

int pb(int x)
  {  if (tag[x])
     { reverse(son[x][0]);
       reverse(son[x][1]);}
      tag[x]=0; }

int rotate(int x)
   {  int y=f[x];
      int w=(son[y][0]==x);
      son[y][!w]=son[x][w];
      if (son[x][w]) f[son[x][w]]=y;
      if (f[y])
      {int z=f[y];
       if(son[z][0]==y) son[z][0]=x;
       if(son[z][1]==y) son[z][1]=x;}
      f[x]=f[y]; f[y]=x; son[x][w]=y; up(y); up(x);
     }

stack<int>S;
int splay(int x)
   {  int y=x; S.push(y);
   	  while (!isroot(y)) S.push(f[y]),y=f[y];
   	  while (!S.empty()) pb(S.top()),S.pop();
   	  while (!isroot(x))
        { int y=f[x];
          if (!isroot(y))
           { if ((son[f[y]][0]==y)^(son[y][0]==x))
              rotate(x); else rotate(y); }
           rotate(x);
          }
       }

int access(int x)
   { for (int y=0;x;y=x,x=f[x])
   	 { splay(x); son[x][1]=y; up(x); }
    }

int root(int x)
  { access(x);
    splay(x);
    while (son[x][0]) x=son[x][0];
    return x;}

int makeroot(int x)
  { access(x);
  	splay(x);
  	reverse(x);
    }

int link(int x,int y)
    { makeroot(x);
      f[x]=y;  access(x);}

int change(int x,int c)
   { access(x); splay(x);key[x]=c; up(x);}

int ask_sum(int x,int y)
  { makeroot(x); access(y);
    splay(x);  printf("%d\n",sum[x]);}

int ask_max(int x,int y)
   { makeroot(x); access(y);
     splay(x);
     return M[x];}

int n,m,k,x,y,z,a[N],b[N];

int main(){
      scanf("%d%d",&n,&m);
      for (int i = 0;i <= 3*n;i++) M[i] = 1;
      for (int i = 0;i <= 3*n;i++) om[i] = 1;
      for (int i=1;i<=n-1;i++){
           scanf("%d%d%I64d",&x,&y,&M[i+n]);
           om[i+n] = M[i+n];
           link(x,i+n);
           link(i+n,y);
      }
     int ty;    ll yi;
     while (m--){
        scanf("%d",&ty);
        if (ty == 1){
            scanf("%d%d%I64d",&x,&y,&yi);
            ll t = ask_max(x,y);
            if (t == 0) printf("0\n");
            else printf("%I64d\n",yi/t);
        }
        if (ty == 2){
            scanf("%d%I64d",&x,&yi);
            makeroot(x+n);
            splay(x+n);
            om[x+n] = yi;
            up(x+n);
        }
    }
       return 0;
       }
