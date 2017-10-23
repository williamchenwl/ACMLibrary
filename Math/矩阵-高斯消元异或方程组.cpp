#include <cstdio>  
#include <cstring>  
#include <cmath>  
#include <algorithm>  

#define ll long long  
#define mod 1000000007  

using namespace std;  
const int N=2000;  
const int M=310;  
int prime[N+1],cnt;  
int n,t,mat[M][M],two[M]={1};  
ll a[M];  
  
//这里下标都是从1开始的  
  
void getPrime(){  
    for(int i=2;i<=N;i++){  
        if(!prime[i])prime[++cnt]=i;  
        for(int j=1;j<=cnt&&prime[j]<=N/i;j++){  
            prime[prime[j]*i]=1;  
            if(i%prime[j]==0)break;  
        }  
    }  
}  
  
int Rank(int c[][M]){//异或版的高斯消元求秩传入的方程横纵坐标都是从1开始的  
    int i=0,j=0,k,r,u;  
    while(i<=cnt&&j<=n){  
        r=i;  
        while(c[r][j]==0&&r<=cnt)r++;  
        if(c[r][j]){  
            swap(c[i],c[r]);  
            for(u=i+1;u<=cnt;u++)if(c[u][j])  
                for(k=i;k<=n;k++)c[u][k]^=c[i][k];  
            i++;  
        }    
        j++;  
    }  
    return i;  
}  
  
int solve(){  
    memset(mat,0,sizeof mat);  
    for(int i=1;i<=n;i++)  
        for(int j=1;j<=cnt;j++){  
            ll tmp=a[i];  
            while(tmp%prime[j]==0){  
                tmp/=prime[j];  
                mat[j][i]^=1;  
            }  
        }  
    int b=n-Rank(mat);//b个自由元  
    return two[b]-1;//减去全为0的解  
}  

int main() {  
    getPrime();  
    for(int i=1;i<M;i++)two[i]=two[i-1]*2%mod;  
    scanf("%d",&t);  
    for(int cas=1;cas<=t;cas++){  
        scanf("%d",&n);  
        for(int i=1;i<=n;i++)  
            scanf("%lld",&a[i]);  
        printf("Case #%d:\n%d\n",cas,solve());  
    }  
    return 0;  
}  