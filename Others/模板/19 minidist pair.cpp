/*
排序后分治
暴力更新
*/
#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
struct pp{double x,y;}p[200001],t[200001];
double ans=1e20;int n;
inline bool cmpx(pp x,pp y){return x.x<y.x;}
inline bool cmpy(pp x,pp y){return x.y<y.y;}
inline double dis(pp x,pp y){return sqrt((x.x-y.x)*(x.x-y.x)+(x.y-y.y)*(x.y-y.y));}
inline void up(pp a,pp b,pp c){ans=min(ans,dis(a,b)+dis(b,c)+dis(c,a));}
void solve(int l,int r){
  if(r-l+1<=3){
    sort(p+l,p+r+1,cmpy);
    if(r-l+1==3)up(p[l],p[l+1],p[r]);
    return;
  }
  int m=(l+r)>>1,mx=p[m].x,tot=0;
  solve(l,m);solve(m+1,r);inplace_merge(p+l,p+m+1,p+r+1,cmpy);
  for(int i=l;i<=r;i++)if(abs(p[i].x-mx)<ans/2)t[++tot]=p[i];
  for(int i=1;i<=tot;i++)for(int j=i-1;j&&t[i].y-t[j].y<ans/2;j--)for(int k=i-1;k&&t[i].y-t[j].y<ans/2;k--)
    if(j!=k)up(t[i],t[j],t[k]);
}
int main(){
  scanf("%d",&n);
  for(int i=1;i<=n;i++)scanf("%lf%lf",&p[i].x,&p[i].y);
  sort(p+1,p+n+1,cmpx);solve(1,n);
  return printf("%.6lf",ans),0;
}