/*
    correctly used times = 2
    used in = { 
   		cf#343D,cf634D
    }
*/
#define dtype int

typedef struct discrete{ 

	dtype tmp[N];
	int n,tot;

	int search(dtype x){
		int l = 1,r = tot;
		do{ 
			int mid = (l + r) >> 1;
			if (tmp[mid] == x) return mid;
			if (tmp[mid] > x) r = mid - 1;
			else l = mid + 1;
			}while(l <= r);
		return 0;
	}

	int init(int x,dtype a[]){ 
		n = x;
		tot = 0;
		for (int i = 1;i <= n;i++) tmp[i] = a[i];
		sort(tmp+1,tmp+n+1);
		for (int i = 1;i < n;i++) 
			if (tmp[i] != tmp[i+1]) tmp[++tot] = tmp[i];
		tmp[++tot] = tmp[n];
		for (int i = 1;i <= n;i++) 
			posx[i] = search(a[i]);
		return tot;
	}

}discrete;

discrete DisC;
