#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <ctime>

using namespace std;

const int N = 100001;

int seed,mult = 131,modnum,n;

typedef struct node{
    int val,id;	
}node;

bool cmp(node x,node y){ 
	 return x.val < y.val;
}

node a[N]; 

int getrand(int modnum){  
	seed = (seed * mult) % modnum; 
	while (seed == 0) seed = rand();
	return seed; 
}

int makeTree(){ 
	for (int i = 1;i < n;i++)
	printf("%d %d\n",a[i].id,a[i+1].id);  	
}

int makeGraph(int m){ 
    makeTree();
	
	for (int i = 1;i <= n;i++) 
	    a[i].val = getrand(9999997);
	
	sort(a+1,a+n+1,cmp);
	
	for (int i = 1;i <= m-n+1;i++) 
	    printf("%d %d\n",a[i].id,a[i+1].id);   	
}



int main(){
    freopen("1.in","w",stdout);
    
	srand((unsigned)time(0));
	
	seed = rand();
	
	int n = 1000; 
    
	for (int i = 1;i <= n;i++){ 
		 a[i].val = getrand(999999997);
		 a[i].id = i;
	}   		
	
	sort(a+1,a+n+1,cmp);
	
	makeGraph(2*n);

}
