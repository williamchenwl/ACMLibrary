for (int i=1;i<=n;i++) phi[i]=i; 
   for (int i=2;i<=n;i++) 
   if (!b[i]){
         phi[i]--;
         for (int j=2;j*i<=n;j++)
         phi[i*j]=(phi[i*j]/i)*(i-1),b[i*j]=1; 
   }
    
