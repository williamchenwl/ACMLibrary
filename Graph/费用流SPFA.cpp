/*
    correctly used times = 
    used in = { 
   	
    }
*/
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

#define DEBUG printf("xxxxx");

const int inf = ~0U>>1;

const int N = 610;

const int M = N * 400;

int S,T;

struct Edge{
    int from,to,next,cap,cost;
    Edge(){}
    Edge(int From,int To,int Next,int Cap,int Cost)
    {
        from=From,to=To,next=Next,cap=Cap,cost=Cost;
    }
}e[M];

int head[N];

struct Mcmf{

    int tot;

    int dis[N],vis[N];

    int path[N],low[N];

    void init(){
        tot=0;
        memset(head,-1,sizeof(head));
    }

    void add(int from,int to,int cap,int cost){
        e[tot]=Edge(from,to,head[from],cap,cost);
        head[from]=tot++;
        e[tot]=Edge(to,from,head[to],0,-cost);
        head[to]=tot++;
    }

    int spfa(int s,int t){
        memset(vis,0,sizeof(vis));
        memset(dis,0x3f,sizeof(dis));
        memset(low,0,sizeof(low));
        queue<int > Q;
        Q.push(s);
        vis[s] = 1;
        low[s] = inf;
        dis[s] = 0;
        while(!Q.empty()){
            int u=Q.front();Q.pop();
            vis[u]=0;
            for(int i=head[u];i!=-1;i=e[i].next){
                int v=e[i].to;
                if(e[i].cap>0&&(dis[v]>dis[u]+e[i].cost)){
                    path[v]=i;
                    low[v]=min(low[u],e[i].cap);
                    dis[v]=dis[u]+e[i].cost;
                    if(!vis[v]){
                        vis[v]=1;
                        Q.push(v);
                    }
                }
            }
        }
        return low[t];
    }

    int _mcmf(int s,int t){

        int flow=0;
        int cost=0;

        while(spfa(s,t)){

            int f=low[t];

            for(int i=t;i!=s;i=e[path[i]].from){
                e[path[i]].cap-=f;
                e[path[i]^1].cap+=f;
            }

            flow+=f;

            cost+=dis[t]*f;
        }

        return cost;
    }
}mcmf;

int main(){
    int P,n,m;
    cin >> P;
    while (P--){
        mcmf.init();
        scanf("%d%d",&m,&n);
        int x;
        S = 0;
        T = n + m * n + 1;
        for (int i = 1;i <= n;i++)
            for (int j = 1;j <= m;j++){
                scanf("%d",&x);
                for (int k = 1;k <= n;k++)
                mcmf.add(i,j * n + k,1,k * x);
            }
        for (int i = 1;i <= n;i++)
            mcmf.add(S,i,1,0);
        for (int i = 1;i <= m;i++)
            for (int j = 1;j <= n;j++)
                mcmf.add(i * n + j,T,1,0);
        printf("%d\n",mcmf._mcmf(S,T));
    }
}
