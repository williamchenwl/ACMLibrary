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
int eular(int n)
{
        int ret = 1,i;
        for (i = 2;i * i <= n;i++)
            if (n % i == 0)
    {
                    n /= i;
                    ret *= (i - 1);
                    while (n % i == 0)
        {
                            n /= i;
                            ret *= i;
                        
        }
                
    }
        if (n > 1)
            ret *= (n - 1);
        return ret;

}
