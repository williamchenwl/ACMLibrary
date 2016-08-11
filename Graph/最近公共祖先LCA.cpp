/*
    correctly used times = 1
    used in = { 
   	  cf343div2E,
    }
*/
//最近公共祖先LCA.cpp
int dfs(int u){
     vis[u]=1;  
     for (int i=base[u];i;i=next[i])
       if (!vis[now[i]]){ 
       	  int x=now[i]; 
          dp[x][0]=u; d[x]=d[u]+1;   
          dfs(x);  
       }
}
  
int predo(){ 
   dfs(1);
   for (int i = 1;i <= 20;i++)
    for (int j = 1; j <= n;j++)
      dp[j][i] = dp[dp[j][i-1]][i-1];
}

int lca(int x,int y){ 
	  if (x == y) return x;
    if (d[x] < d[y]) swap(x,y);   
    
    for (int i=k;i>=0;i--)
    if (d[dp[x][i]]>=d[y]) x=dp[x][i];
    
    if (x==y) return x;
    
    for (int i=k;i>=0;i--)
    if (dp[x][i]!=dp[y][i])
     x=dp[x][i],y=dp[y][i];
    return dp[x][0];   
}


d[0] = 1