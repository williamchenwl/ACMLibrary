#include <bitset>
#include <vector>

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

// without biset version 

int find(int x, vector<bool>& vis, vector<int>& assign, const vector<vector<int>>& graph) {
	for (auto nxt : graph[x]) {
		if (!vis[nxt]) {
			vis[nxt] = 1; 
			if (assign[nxt] == -1 || find(nxt, vis, assign, graph)) {
				
			}
		}
	}
	
}

void hungary(vector<vector<int>> graph, int n, int m) {
	vector<bool> vis(n, 0);
	vector<int> assign(m, -1);
	int ans = 0;
	for (int i = 0; i < n; i++) {
		vis.resize(n, 0);
		if (find(i, vis, assign, graph)) ans++;
	}
	return ans;
}

