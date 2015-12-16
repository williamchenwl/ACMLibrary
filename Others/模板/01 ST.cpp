/*  
     ID 01
     ST Algorithm to calculate the RMQ problem
*/
     
#include <cmath>
#include <algorithm>
     
     int t = (int)(log(n)/log(2));
     for (int i = 1,p = 1;i <= t;i++) {calp[i] = p; p = p * 2; }
     for (int k = 1;k <= t;k++)
     	for (int i = 1;i <= n;i++)
           if (i+calp[j]-1 <= n) f[i][j] = max(f[i][j-1],f[i+calp[j-1],j-1]);

    cin >> x >> y;

    if (x > y) swap(x,y);

    int p = int(log(y-x+1)/log(2));
   
    int ans = max(f[x][p],f[y-calp[j]+1,p]);
