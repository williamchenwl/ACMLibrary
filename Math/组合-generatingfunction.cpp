//fact1 : C(n,r) = C(n,n - r)
//fact2 : C(n,r) = C(n,r - 1) + C(n - 1,r - 1)
//fact3 : C(n,r) * r = C(n - 1,r - 1) * n
//fact4 : sigma(C(n,i)^2)(0<=i<=n) = C(n,2 * n)
//fact5 : n * (3 * n - 1) / 2 五边形数
//拆分数计算 
  
void Init()  
{  
    int t=1000;  
    for(int i=-1000;i<=1000;i++)  
        tmp[i+t]=i*(3*i-1)/2;  
    ans[0]=1;  
    for(int i=1;i<N;i++)  
    {  
        ans[i]=0;  
        for(int j=1;j<=i;j++)  
        {  
            if(tmp[j+t]<=i)  
            {  
                if(j&1)  ans[i]+=ans[i-tmp[j+t]];  
                else     ans[i]-=ans[i-tmp[j+t]];  
            }  
            else break;  
            ans[i]=(ans[i]%MOD+MOD)%MOD;  
            if(tmp[t-j]<=i)  
            {  
                if(j&1) ans[i]+=ans[i-tmp[t-j]];  
                else    ans[i]-=ans[i-tmp[t-j]];  
            }  
            else break;  
        }  
        ans[i]=(ans[i]%MOD+MOD)%MOD;  
    }  
}  

//带K限制的拆分数

void Init()  
{  
    dp[0] = 1;  
    for(int i=1;i<N;i++)  
    {  
        dp[i] = 0;  
        for(int j=1;;j++)  
        {  
            int t = (3*j-1)*j / 2;  
            if(t > i) break;  
            int tt = dp[i-t];  
            if(t+j <= i) tt = (tt + dp[i-t-j])%MOD;  
            if(j&1) dp[i] = (dp[i] + tt)%MOD;  
            else    dp[i] = (dp[i] - tt + MOD)%MOD;  
        }  
    }  
}  
  
int Work(int n,int k)  
{  
    int ans = dp[n];  
    for(int i=1;;i++)  
    {  
        int t = k*i*(3*i-1) / 2;  
        if(t > n) break;  
        int tt = dp[n-t];  
        if(t + i*k <= n) tt = (tt + dp[n-t-i*k])%MOD;  
        if(i&1) ans = (ans - tt + MOD)%MOD;  
        else    ans = (ans + tt)%MOD;  
    }  
    return ans;  
}  