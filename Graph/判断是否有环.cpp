/*************************************************************************
	> File Name: 判断是否有环.cpp
	> Author: 
	> Mail: 
	> Created Time: 2015年12月09日 星期三 13时07分08秒
 ************************************************************************/

int G[maxn][maxn]
int c[maxn];
 
 bool dfs(int u)
 {
        c[u] = -1;
        for(int v=1; v<=n; v++) if(G[u][v])
     {
                if(c[v] < 0) return true;
                if(!c[v] && dfs(v)) return true;
            
     }
        c[u] = 1;
        return false;

 }
  
  bool pan()
  {
         memset(c, 0, sizeof(c));
         for(int u=1; u<=n; u++) if(!c[u])
             if(dfs(u)) return true;
         return false;

  }
