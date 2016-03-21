/*
    correctly used times = 
    used in = { 
   	
    }
*/
const int inf = ~0U>>1;

const int N = 5010;

typedef struct seg{
    int to,op,cost,nxt,f;
}seg;

seg v[N*40]; 

int ans =0,tot,dis[N],base[N],vis[N],ttf = 0;

int S,T; int cur[N];

int aug(int u,int flow){

    if (u == T){
        ans += flow * dis[S];
        ttf += flow;
        return flow;
    }

    vis[u] = 1;

    int now = 0;

    for (int i = base[u];i;i = v[i].nxt){
        int x = v[i].to;
        if (vis[x] || v[i].f <= 0 || dis[u] != dis[x] + v[i].cost)
            continue;
        int tmp = aug(x,min(flow - now,v[i].f));
        v[i].f -= tmp; v[v[i].op].f += tmp;
        now += tmp;
        if (now == flow) return flow;
    }

    return now;
}


int modlabel(){
    int del = inf;
    for (int i = S;i <= T;i++)
        if (vis[i]) for (int j = base[i];j;j = v[j].nxt)
            if (v[j].f){
                int x = v[j].to;
                if (!vis[x]) del = min(del,dis[x] + v[j].cost - dis[i]);
            }
    if (del == inf) return 0;
    for (int i = S;i <= T;i++)
    if (vis[i]) vis[i] = 0,dis[i] += del,cur[i] = base[i];
    return 1;
}


int zkw(){
    for (int i = S;i <= T;i++) cur[i] = base[i];
    int fl,t = 0;
    do{
        t = 0;
        while(t = aug(S,inf)) memset(vis,0,sizeof(vis));
    }while(modlabel());
    return ans;
}

int add(int x,int y,int f,int c){
    v[++tot].to = y; v[tot].op = tot + 1;
    v[tot].f = f; v[tot].cost = c;
    v[tot].nxt = base[x]; base[x] = tot;
    v[++tot].to = x; v[tot].op = tot - 1;
    v[tot].f = 0; v[tot].cost = -c;
    v[tot].nxt = base[y]; base[y] = tot;
}

int main(){
    int P,n,m;
    cin >> P;
    while (P--){
        memset(base,0,sizeof(base));
        memset(dis,0,sizeof(dis));
        tot = 0; ans = 0; ttf = 0;
        memset(vis,0,sizeof(vis));
        cin >> m >> n;
        int x;
        S = 0;
        T = n + m * n + 1;
        for (int i = 1;i <= n;i++)
            for (int j = 1;j <= m;j++){
                scanf("%d",&x);
                for (int k = 1;k <= n;k++)
                add(i,j * n + k,1,k * x);
            }
        for (int i = 1;i <= n;i++)
            add(S,i,1,0);
        for (int i = 1;i <= m;i++)
            for (int j = 1;j <= n;j++)
                add(i * n + j,T,1,0);
        zkw();
    }
}