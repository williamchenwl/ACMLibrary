template <typename X>  
struct tree_array{  
    struct tree_array_single{  
        X arr[MAXN];  
        void add(int x,X n){while(x<=N)arr[x]+=n,x+=lowbit(x);}  
        X sum(int x){X sum=0;while(x)sum+=arr[x],x-=lowbit(x);return sum;}  
    }T1,T2;  
    void reset(){CLR(T1.arr,0); CLR(T2.arr,0);}  
    void add(int x,X n){T1.add(x,n);T2.add(x,x*n);}  
    void update(int L,int R,int n){add(L,n);add(R+1,-n);}  
    X sum(int x){return (x+1)*T1.sum(x)-T2.sum(x);}  
    X query(int L,int R){return sum(R)-sum(L-1);}  
};  