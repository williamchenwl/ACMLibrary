/*
    correctly used times = 
    used in = { 
   	
    }
*/
/*************************************************************************
	> File Name: Floyd.cpp
	> Author: 
	> Mail: 
	> Created Time: 2015年12月09日 星期三 13时03分06秒
 ************************************************************************/

int n, d[maxn][maxn];
 
 void floyd(){
        for(int k=1; k<=n; k++)
            for(int i=1; i<=n; i++)
                for(int j=1; j<=n; j++)
            d[i][j] = min(d[i][j], d[i][k]+d[k][j]);
}
