typedef struct seg{ 
	
	int id,va;

	seg(int a,int b){id = a; va = b;}

	bool operator <(const seg &x)const{ 
		if (va == x.va) return id < x.id;
		return va > x.va;
	}

}seg;

priority_queue<seg>Q;

bool vis[N];

int dij(int s){ 
	
	for (int i = 1;i <= n;i++) d[i] = inf;

	d[s] = 0; 
	
	memset(vis,0,sizeof(vis));
	
	Q.push(seg(s,d[s]));
    
    while (!Q.empty()){ 
    	seg tmp = Q.top();
    	while (vis[tmp.id]) {Q.pop(); tmp = Q.top();}
    	int u = tmp.id; 
    	for (int i = base[u];i;i = nxt[i]){ 
    		int v = now[i];
    		if (d[v] > d[u] + va[i]){ 
    			d[v] = d[u] + va[i];
    			Q.push(seg(v,d[v]));
    		}
    	}
    	vis[u] = 1;
    	Q.pop();
    }
}


int main(){ 


}