#include <bitset>

bitset<maxn>vis;

int pos[maxn]; 

vector<int>G[maxn*2];

int n,m;

bool dfs(int u){ 
    for (int i=0;i<G[u].size();i++){
        int x=G[u][i];
        if (vis[x]) continue; vis[x]=1;
        if (!pos[x]||dfs(pos[x])) {pos[x]=u;return 1;}  
        } 
      return 0;
}

int main(){  
     scanf("%d",&n); int x,y;
     for (int i=1;i<=n;i++)  
      {  scanf("%d%d",&x,&y);
         G[x].push_back(i);
         G[y].push_back(i);
         }
      int ans=0; vis.reset();
      while (dfs(++ans)) vis.reset();
      printf("%d\n",ans-1);
      }