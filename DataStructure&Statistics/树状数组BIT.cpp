/*
    correctly used times = 1
    used in = { 
   		cf635dD,
    }
*/
//树状数组

typedef struct Fenwick_Tree{  
	
	dtype C[N];
	int siz;
	
	int init(int x){ 
		for (int i = 0;i <= x+1;i++) C[i] = 0;
		return siz = x;
	}

	inline int lowbit(int x){ 
		return x & (-x);
	}

	inline int add(int x,dtype t){ 
		if (t == 0) return 0;
		for (;x <= siz;x += lowbit(x)) 
		   C[x] += t;
	}

	inline dtype sum(int x){ 
		dtype ans = 0;
		for (;x;x -= lowbit(x)){ 
			ans += C[x];
		}
		return ans;
	}

	inline dtype intersum(int l,int r){ 
		if (l > r) return 0;
		return sum(r) - sum(l-1);
	}

}Fenwick_Tree;

Fenwick_Tree Fen;


