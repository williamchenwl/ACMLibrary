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
  

int lca(int x,int y){ 
	if (x==y) return x;
    
    if (d[x]<d[y]) swap(x,y);   
    
    for (int i=k;i>=0;i--)
    if (d[dp[x][i]]>=d[y]) x=dp[x][i];
    
    if (x==y) return x;
    
    for (int i=k;i>=0;i--)
    if (dp[x][i]!=dp[y][i])
     x=dp[x][i],y=dp[y][i];
    return dp[x][0];   
}


