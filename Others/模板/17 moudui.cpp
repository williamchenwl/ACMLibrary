#include cstdio
#include cstring
#include algorithm
#include cmath
#define debug printf(xxxx);
using namespace std;
const int maxn=50100;
int a[maxn]; typedef struct que{int l,r,pos;}que;
que b[maxn]; int c[maxn],pos[maxn];
long long ans1[maxn],ans2[maxn];
int gcd(long long x,long long y)
{if (x%y==0) return y; return gcd(y,x%y);}
int n,m,k,u; long long now=0;
bool cmp(que x,que y)
  {   if (pos[x.l]!=pos[y.l]) return pos[x.l]pos[y.l];
      else return x.ry.r;
  }

int modify(long long x,long long y,int pos) 
  {  y=y(y-1)2; 
     int t=gcd(x,y);
     x=t; y=t;
     ans1[pos]=x; ans2[pos]=y;
  }

int change(int x,int del)
   {  now-=c[x]c[x];
      c[x]+=del;
      now+=c[x]c[x];}

int main()
  { scanf(%d%d,&n,&m);
    for (int i=1;i=n;i++) scanf(%d,&a[i]);
    for (int i=1;i=m;i++)
    scanf(%d%d,&b[i].l,&b[i].r),b[i].pos=i;
    u=(int)sqrt(n);
    for (int i=1;i=n;i++) pos[i]=1+(iu);
    sort(b+1,b+m+1,cmp); int l=1,r=0; 
    memset(c,0,sizeof(c));
    for (int i=1;i=m;i++)
      {  while (rb[i].r) r++,change(a[r],1);
         while (rb[i].r) change(a[r],-1),r--;
         while (lb[i].l) change(a[l],-1),l++;
         while (lb[i].l) l--,change(a[l],1);
         printf(%d %d %dn,l,r,now);
         modify((now-(r-l+1))2,r-l+1,b[i].pos);
       }
   
    for (int i=1;i=m;i++) 
      printf(%lld%lldn,ans1[i],ans2[i]);
}