int n,d[maxn][maxn];
 
void floyd(){
        for(int k=1; k<=n; k++)
            for(int i=1; i<=n; i++)
                for(int j=1; j<=n; j++)
            d[i][j] = min(d[i][j], d[i][k]+d[k][j]);
}

//min-circle

int get_mc(){   
	int ans = inf;
	for (int k = 1;k <= n;k++){  
		for (int i = 1;i < k;i++)
			for (int j = i + 1;j < k;j++)
 				ans = min(ans,d[i][j]+d[i][k]+d[k][j]);
 		for (int i = 1;i < k;i++) 
 			for (int j = i + 1;j < k;j++)
 				d[i][j] = min(d[i][j],d[i][k] + d[k][j]);
 	}
}

//bitset
double ans;
bitset<1005>edge[maxn];

void floyd(){
    int i,j,k;
    for(i=1;i<=n;i++){
        for(j=1;j<=n;j++){
            if(edge[j][i]) edge[j]|=edge[i];
        }
    }
    int num;
    ans=0;
}