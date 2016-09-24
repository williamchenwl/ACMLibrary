//Vijos1040
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>

using namespace std;

struct comp{
    double r,i;
    comp (double _r=0,double _i=0){r=_r;i=_i;}
    comp operator + (const comp x){return comp(r+x.r,i+x.i);}
    comp operator - (const comp x){return comp(r-x.r,i-x.i);}
    comp operator * (const comp x){return comp(r*x.r-i*x.i,r*x.i+i*x.r);}
};


const double pi=acos(-1.0),eps=1e-4;

int FFT(comp a[],int n,int t){
  
   for(int i = 1,j = 0;i < n-1;i++){
      for(int s = n;j ^= s >> =1, ~j&s;);
           if( i < j) swap(a[i],a[j]);
  }
  
  for(int d = 0;(1 << d) < n;d++){
      int m = 1 << d,m2 = m << 1;
      double o = pi/m*t; comp _w(cos(o),sin(o));
      for(int i=0;i<n;i+=m2){
      comp w(1,0);
      for(int j=0;j<m;j++){//蝴蝶操作
        comp &A=a[i+j+m],&B=a[i+j],t=w*A;
        A=B-t;B=B+t;w=w*_w;
      }
    }
  }
  if(t==-1)for(int i=0;i<n;i++)a[i].r/=n;
} 

const int N=32768;

char s[N];comp a[N],b[N],c[N];int i,j,ans[N],l;

int main(){
  
  for(scanf("%s",s),i=0,j=strlen(s);i<j;i++)a[j-i-1].r=s[i]-'0';
  
  for(scanf("%s",s),i=0,j=strlen(s);i<j;i++)b[j-i-1].r=s[i]-'0';
  
  FFT(a,N,1);FFT(b,N,1);
  
  for(i=0;i<N;i++) c[i] = a[i]*b[i];
  
  FFT(c,N,-1);
  
  for(l=N-1,i=0;i<N;i++){
  
  ans[i]+=(int)(c[i].r+eps);
    
  if(ans[i]>=10)ans[i+1]+=ans[i]/10;
    ans[i]%=10;
  }
  
  while(l&&!ans[l])l--;
  
  for(;~l;l--)printf("%d",ans[l]);
  
  return 0;
}