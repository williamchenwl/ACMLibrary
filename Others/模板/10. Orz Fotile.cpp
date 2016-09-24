#include <cstdio>
using namespace std;
const int maxn=1000005; const int maxm=100005;
typedef struct seg{int l,r,size;}seg;
seg a[maxm*14];   int p[maxn],root[maxm];
int n,m,t; int num=0;
int newnode(int size,int l,int r)
  {   a[++num].size=size; 
      a[num].l=l; a[num].r=r;
      return num;
   }
int build(int l,int r)
  {  int x=++num;
     if (l==r) return x;
     int mid=(l+r)>>1;
     a[x].l=build(l,mid);
     a[x].r=build(mid+1,r);
     return x;
  }
  
int add(int f,int l,int r,int c)
   {   int mid=(l+r)>>1; 
       int x=newnode(a[f].size+1,a[f].l,a[f].r);
       if (l==r) return x;
       if (mid>=c) a[x].l=add(a[x].l,l,mid,c);
       else a[x].r=add(a[x].r,mid+1,r,c);
       return x;
   }
int ask(int pa,int pb,int l,int r,int ll,int rr)
   {   int num=a[pb].size-a[pa].size;
       if (ll>=l&&rr<=r) return num;
       int mid=(ll+rr)>>1; int ans=0;
       if (mid>=l) ans+=ask(a[pa].l,a[pb].l,l,r,ll,mid);
       if (mid<r) ans+=ask(a[pa].r,a[pb].r,l,r,mid+1,rr);
       return ans;
   }
int main()
   {  scanf("%d",&n);  root[0]=build(1,n);
      for (int i=1;i<=n;i++)
      {  scanf("%d",&t);
         if (p[t]) root[i]=add(root[i-1],1,n,p[t]);
         else root[i]=root[i-1];
         p[t]=i;
       }
     scanf("%d",&m); int x,y;
     for (int i=1;i<=m;i++)
       {  scanf("%d%d",&x,&y);
          printf("%d\n",y-x+1-ask(root[x-1],root[y],x,y,1,n));
       }  return 0;
 }