//匈牙利
#include <bitset>

using namespace std;

const int N = 1000001;

bitset<N>pos;

int find(int x){ 
	for (int i = 1;i <= n;i++)
		if (g[x][i] && !vis[i]){ 
			vis[i] = 1;
			if (lk[i] == 0||find(lk[i])){ 
				lk[i] = x; return 1;
			}
		}
		return 0;
}

for (int i = 1;i <= n;i++){
	vis.reset();
	if (find(i)) ans++;
}


