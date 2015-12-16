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

const int MaxInt = ~0U>>1;

const int N = 1000000,M = 100000000;

int tot,n,m,k,x,y,CASE,T;

typedef struct UJS{ 

	int fa[N];
    
    int Init(int x){ 
        for (int i = 1;i <= x;i++) fa[i] = i; 
        return x;
    }

    int Find(int x){ 
        if (fa[x] == x) return x;
        return fa[x] = Find(fa[x]);
    }

    int Union(int x,int y){ 
        x = find(x);
        y = find(y);
        if (x == y) return -1;
        fa[x] = y;
        return find(x);
    }

    int InSameSet(int x,int y){  
        if (find(x) == find(y)) return 1;
        else return 0;
     }

}UJS;


int main(){ 


} 