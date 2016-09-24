#include <cstdio>
#define rep(i,n) for(int i=0;i<n;i++)
#define N 16
typedef long long ll;
ll a[N][N],b[N][N],t[N][N],c[N][N],m,n,p,B[N],C[N],sum[N],ans;int k;
inline void mul(ll t[N][N],ll a[N][N],ll b[N][N],int n,int r,int m){//a*b=c
  rep(i,n)rep(j,m)c[i][j]=0;
  rep(i,n)rep(j,m)rep(k,r)(c[i][j]+=a[i][k]*b[k][j])%=p;
  rep(i,n)rep(j,m)t[i][j]=c[i][j];
}
ll getsum(ll n){
  if(n<=k)return sum[n];
  rep(i,k+1)rep(j,k+1)a[i][j]=b[i][j]=t[i][j]=0;
  rep(i,k)b[i][0]=B[i];b[k][0]=sum[k-1];
  rep(i,k-1)a[i][i+1]=1;rep(i,k)a[k-1][i]=C[k-i-1]%p;a[k][k-1]=a[k][k]=1;
  rep(i,k+1)t[i][i]=1;
  for(n=n-k+1;n;n>>=1LL,mul(a,a,a,k+1,k+1,k+1))if(n&1LL)mul(t,t,a,k+1,k+1,k+1);
  mul(b,t,b,k+1,k+1,1);
  return b[k][0];
}
int main(){
  scanf("%d",&k);
  rep(i,k)scanf("%lld",&B[i]);
  rep(i,k)scanf("%lld",&C[i]);
  scanf("%lld%lld%lld",&m,&n,&p);
  for(int i=1;i<=k;i++)sum[i]=(sum[i-1]+B[i-1])%p;
  ans=getsum(n)-getsum(m-1);
  while(ans<0)ans+=p;
  return printf("%lld",ans),0;
}