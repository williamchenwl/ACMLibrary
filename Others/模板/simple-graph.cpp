#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <set>
#include <queue>
#include <stack>
#include <vector>
#include <climits>

using namespace std;

typedef long long ll;

const int MaxInt = ~0U>>1;

const int N = 1000000,M = 100000000;

int tot,n,m,k,x,y,CASE,T;


typedef struct GraphX{  
	
	int vis[N],base[N],nx[M],now[M],va[M],tot;
	
	int init(){ 
		memset(base,0,sizeof(tot));
		tot = 0;
	}

    int addsingle(int x,int y){ 
    	now[++tot] = y;
    	nx[tot] = base[x];
    	base[x] = tot;
    	return tot;
    }

    int adddouble(int x,int y){ 
    	addsingle(x,y);
    	addsingle(y,x);
    }

    int addsinglev(int x,int y,int v){ 
    	va[addsingle(x,y)] = v;
    }

    int adddoublev(int x,int y,int v){ 
    	addsinglev(x,y);
    	addsinglev(y,x);
    }

    int treedfs(int fa){  
    	vis[fa] = 1;
    	for (int i = base[x];i;i = nx[i]){ 
    	 	int son = now[i];
    	 	if (vis[son]) continue;
    	 	dfs(son); 
    	}
    }

}Graphx;


int main(){ 


} 