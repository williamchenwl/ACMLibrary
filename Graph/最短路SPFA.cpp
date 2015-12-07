/* ID 03
   get minipath 
   and find strange circle
 */
stack<int>S;   

bool spfa(){ 
  
  for (int i=1;i<=n;i++) {S.push(i); vis[i]=1;}

  while (!S.empty()){
      int u=S.top(); S.pop(); vis[u]=0;    
      for (int i=base[u];i;i=Nx[i]) 
          if (d[u]+c[i]<d[now[i]]){
             int x = now[i]; cnt[i]++; 
             if (cnt[i]==n) return 0;   
             if (!vis[x]) S.push(x);    
             d[x] = d[u]+c[i];
             vis[x] = 1;    
             }
         }return 1;    
   }




