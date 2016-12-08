
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

