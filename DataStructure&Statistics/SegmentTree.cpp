typedef struct segment_tree{

    int siz,tot;

    int sl[N],sr[N];

    int tl[N],tr[N];

    ll sum[N],flag[N],mx[N];

    int init(int x){
        siz = x; tot = 0;
        memset(sl,0,sizeof(sl));
        memset(sr,0,sizeof(sr));
        memset(sum,0,sizeof(sum));
        memset(flag,-1,sizeof(flag));
        memset(mx,0,sizeof(mx));
    }

    inline void tagit(int x,int c){
        mx[x] = flag[x] = c;
        sum[x] = (ll)(tr[x] - tl[x] + 1) * c;
    }
    //flag[x] = -1? flag[x] = 0?
    inline void pd(int x){
        if (~flag[x] && tl[x] != tr[x]){
            tagit(sl[x],flag[x]);
            tagit(sr[x],flag[x]);
            flag[x] = -1;
        }
    }

    inline void update(int x){
        sum[x] = sum[sl[x]] + sum[sr[x]];
        mx[x] = max(mx[sl[x]],mx[sr[x]]);
    }

    int build(int l,int r){
        int x = ++tot;
        tl[x] = l; tr[x] = r;
        if (l == r) return flag[x] = -1,x;
        int mid = (l + r) >> 1;
        sl[x] = build(l,mid);
        sr[x] = build(mid + 1,r);
        update(x);
        return x;
    }

    void add(int x,int lx,int rx,ll c){
        if (tl[x] >= lx && tr[x] <= rx){
            tagit(x,c);
            return;
        }
        int mid = (tl[x] + tr[x]) >> 1;
        pd(x);
        if (mid >= lx) add(sl[x],lx,rx,c);
        if (mid < rx) add(sr[x],lx,rx,c);
        update(x);
    }


    ll query(int x,int lx,int rx){
        pd(x);
        if (tl[x] >= lx && tr[x] <= rx) return sum[x];
        int mid = (tl[x] + tr[x]) >> 1; ll ans = 0;
        if (mid >= lx) ans += query(sl[x],lx,rx);
        if (mid < rx) ans += query(sr[x],lx,rx);
        return ans;
    }

}segment_tree;

segment_tree Seg;

/*
    注意build中的初始赋值
    注意query中必须先push_down
    注意flag[x]不能是-1
    注意mx[x]的初始值
    通过tl[x],tr[x]可以计算自树的大小
*/



#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int maxInt = 200010;

typedef long long ll;

struct segTree{
    public:
        int intervalSiz, totNodes;
        vector<int> sonL, sonR, valL, valR;
        vector<ll> sumVal, lazyFlag, mxVal;
        segTree(int size){
            intervalSiz = size;
            totNodes = 0;
            int treeSize = size * 4 + 1;
            sonL.resize(treeSize);
            sonR.resize(treeSize);
            valL.resize(treeSize);
            valR.resize(treeSize);
            sumVal.resize(treeSize);
            lazyFlag.resize(treeSize, -1);
            mxVal.resize(treeSize);
        }
        
        inline ll getIntervalSize(int x){
            return (ll)(valR[x] - valL[x] + 1);
        }

        inline void addTag(int x, ll val){
            mxVal[x] = lazyFlag[x] = val;
            sumVal[x] = getIntervalSize(x) * val;
        }

        inline int pushDown(int x){
            if (~lazyFlag[x] && valL[x] != valR[x]){
                addTag(sonL[x], lazyFlag[x]);
                addTag(sonR[x], lazyFlag[x]);
                lazyFlag[x] = -1;
                return 1;
            }
            return 0;
        }

        inline void update(int x){
            sumVal[x] = sumVal[sonL[x]] + sumVal[sonR[x]];
            mxVal[x] = max(mxVal[sonL[x]], mxVal[sonR[x]]);
        }
        
    public:

        int build(int left, int right){
            int x = ++totNodes;
            valL[x] = left;
            valR[x] = right;
            if (left == right)
                return lazyFlag[x] = -1, x;
            int mid = (left + right) >> 1;
            sonL[x] = build(left, mid);
            sonR[x] = build(mid+1, right);
            update(x);
            return x;
        }

        void addInterval(int x, int left, int right, ll c){
            if (valL[x] >= left && valR[x] <= right){
                addTag(x, c);
                return;
            }
            int mid = (valL[x] + valR[x]) >> 1;
            pushDown(x);
            if (mid >= left) addInterval(sonL[x], left, right, c);
            if (mid < right) addInterval(sonR[x], left, right, c);
            update(x);
        }
        
}Tree;
