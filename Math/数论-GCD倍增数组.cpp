#include <bits/stdc++.h>

using namespace std;

const int N = 1e5+5;

typedef long long LL;

int n, m;

int block;

int a[N];

LL ans[N];

struct PP {
    int l, r;
    int id;
    bool operator < (const PP &cmp) const {
        if(l/block == cmp.l/block) return r < cmp.r;
        return l/block < cmp.l/block;
    }
}q[N];

int gcd(int a, int b) {
    return b?gcd(b, a%b):a;
}

struct He {
    int idx;    //存区间的下标
    LL g;       //存区间的gcd值
};

vector <He> vl[N], vr[N];

void preDeal() {
    for(int i = 1;i <= n; i++) {
        if(i == 1) vl[i].push_back((He){i, a[i]});  
        else {
            int curg = a[i];    
            int l = i;
            for(int j = 0;j < vl[i-1].size();j++) {
                He it = vl[i-1][j];
                int tmp = gcd(it.g, curg);
                if(tmp != curg)                     
                    vl[i].push_back((He){l, curg});
                curg = tmp, l = it.idx;
            }
            vl[i].push_back((He){l, curg});
        }
    }
    for(int i = n;i >= 1; i--) {
        if(i == n) vr[i].push_back((He){i, a[i]});  
        else {
            int curg = a[i];
            int r = i;
            for(int j = 0;j < vr[i+1].size();j++) {
                He it = vr[i+1][j];
                int tmp = gcd(it.g, curg);
                if(tmp != curg)
                    vr[i].push_back((He){r, curg});
                curg = tmp, r = it.idx;
            }
            vr[i].push_back((He){r, curg});
        }
    }
}

map<LL,LL>M;

void solve1(){
    preDeal();
    for (int i = 1;i <= n;i++){
        LL pre = i;
        for (int j = 0;j < vl[i].size();j++){
            LL l = pre - vl[i][j].idx + 1;
            M[vl[i][j].g] += l;
            pre = vl[i][j].idx - 1;
        }
    }
}

int tot = 0;

void solve() {
    printf("Case #%d:\n",++tot);
    for(int i = 1;i <= n; i++) vl[i].clear(), vr[i].clear();
    block = (int)sqrt(n);
    solve1();
    for (int i = 0;i < m;i++){
        int t = q[i].r;
        LL ans = 0;
        for (int j = 0;j < vl[t].size();j++)
            if (vl[t][j].idx <= q[i].l){
                ans = vl[t][j].g;
                break;
            }
        printf("%lld %lld\n",ans,M[ans]);
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        M.clear();
        for(int i = 1;i <= n; i++) scanf("%d", &a[i]);
        scanf("%d", &m);
        for(int i = 0;i < m; i++) scanf("%d%d", &q[i].l, &q[i].r);
        for(int i = 0;i < m; i++) q[i].id = i;
        solve();
    }
    return 0;
}
