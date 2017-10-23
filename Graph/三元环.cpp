typedef long long ll;

const int N = 110000;

int u[N],v[N],d[N];

vector<int>G[N];

map<pair<int,int>,int>M;

int main(){

	ios_base::sync_with_stdio(false);

	int n,m;

	int T; cin >> T;

	while(cin >> n >> m){

		M.clear();

		for (int i = 1;i <= n;i++) d[i] = 0,G[i].clear();

		for (int i = 1;i <= m;i++){
			int x,y;
			cin >> x >> y;
			u[i] = x; v[i] = y;
			d[x]++; d[y]++;
			M[make_pair(x,y)] = 1;
			M[make_pair(y,x)] = 1;
		}

		for (int i = 1;i <= m;i++){
            int x = u[i],y = v[i];
            if (d[x] > d[y]) G[x].push_back(y);
            else G[y].push_back(x);
		}

        for (int i = 1;i <= n;i++)
            sort(G[i].begin(),G[i].end());

		ll ans = 0;

		for (int i = 1;i <= m;i++){
			int x = u[i],y = v[i];
			int pos = 0;
			for (int j = 0;j < G[x].size();j++){
                if (pos < G[y].size() && G[y][pos] < G[x][j]) pos++;
                if (pos >= G[y].size()) break;
                if (G[y][pos] == G[x][j]) ans++,pos++;
			}
		}

		cout << ans << endl;

	}
}
