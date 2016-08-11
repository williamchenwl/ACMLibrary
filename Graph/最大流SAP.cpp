/*
    correctly used times = 
    used in = { 
   	
    }
*/

#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

const int N = 405;

const int M = 4400;

typedef long long ll;

const ll inf = 9223372036854775805;

int base[N],num[N],d[N],ntot,tot,S,T;

int to[M],op[M],nxt[M];

ll fl[M],tmp[M];

ll sap(int u,ll flow){
	if (u == T) return flow;
	ll tmp,rec = 0;
	for (int i = base[u];i;i = nxt[i]){
		int x = to[i];
		if (fl[i] <= 0 || d[u] != d[x] + 1) continue;
		tmp = sap(x,min(flow - rec,fl[i]));
		rec += tmp; fl[i] -= tmp; fl[op[i]] += tmp;
		if (rec == flow) return flow;
	}
	if (d[S] >= ntot) return rec;
	num[d[u]]--; if (!num[d[u]]) d[S] = ntot;
	num[++d[u]]++; return rec;
}

int nadd(int x,int y,ll f){
	to[++tot] = y; tmp[tot] = f;
	nxt[tot] = base[x]; base[x] = tot;
	op[tot] = tot + 1;
	to[++tot] = x; tmp[tot] = 0;
	nxt[tot] = base[y]; base[y] = tot;
	op[tot] = tot - 1;
}

ll solve(double k){
	memset(d,0,sizeof(d));
	memset(num,0,sizeof(num));
	ll ans = 0;
 	while(d[S] < ntot) ans += sap(S,inf);
	return ans;
}

int main(){ 
	BuildGraph(S,T,ntot);
}