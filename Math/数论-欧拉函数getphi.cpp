/*
    correctly used times = 
    used in = { 
   	
    }
*/
//欧拉函数
//筛法
for(int i=1;i<=n;i++) phi[i]=i; 
   for (int i=2;i<=n;i++) 
   if (!b[i]){
         phi[i]--;
         for (int j=2;j*i<=n;j++)
         phi[i*j]=(phi[i*j]/i)*(i-1),b[i*j]=1; 
   }
    

//求单个数的欧拉函数

ll eular(ll n){
    ll ans = n;
    ll i;
    for (i = 2; i*i <= n; i++){
        if (n%i == 0){
            while (n%i == 0)
                n /= i;
            ans = ans/i*(i-1) ;
        }
    }
    if (n != 1)
        ans = ans/n*(n-1);
    return ans;
}