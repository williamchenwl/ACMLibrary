/*
    correctly used times = 
    used in = { 
   	
    }
    
*/
    
typedef long long ll;

ll v[M],vx[M],ians[N];

int n,m,k;

typedef struct que{
	int l,r,id;
}que;

int a[N],pos[N]; que q[N];

int bkn;

bool cmp(que a,que b){
	if (pos[a.l] == pos[b.l]) return a.r < b.r;
	return a.l < b.l;
}

int init(){
	bkn = int(sqrt(n));
	for (int i = 1;i <= n;i++)
		pos[i] = (i - 1)/bkn + 1;
}

int main(){

	cin >> n >> m >> k;

	init();

	for (int i = 1;i <= n;i++)
		scanf("%d",&a[i]);

    for (int i = 1;i <= n;i++)
        a[i] = a[i - 1] ^ a[i];

	for (int i = 1;i <= m;i++){
		scanf("%d%d",&q[i].l,&q[i].r);
		q[i].id = i;
	}

	sort(q+1,q+m+1,cmp);

	int l = 1,r = 0;

	ll ans = 0;


	for (int i = 1;i <= m;i++){

		int pl = q[i].l,pr = q[i].r;

		while (r < pr){
            r++;
            v[a[r-1]]++;
            vx[a[r]]++;
			ans += v[a[r] ^ k];
        }



		while (r > pr){
			ans -= v[a[r] ^k];
			v[a[r-1]]--;
			vx[a[r]]--;
			r--;
		}


        while (l < pl){
            ans -= vx[a[l-1] ^ k];
			v[a[l-1]]--;
			vx[a[l]]--;
            l++;
		}


		while (l > pl){
            l--;
            v[a[l-1]]++;
            vx[a[l]]++;
			ans += vx[a[l-1] ^ k];
		}

		ians[q[i].id] = ans;
	}

	for (int i = 1;i <= m;i++)
		printf("%I64d\n",ians[i]);
}

