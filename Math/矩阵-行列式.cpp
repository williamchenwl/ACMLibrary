ll det(int n){
 	ll ans=1;bool flag=1;
 	for(i=1;i<=n;i++)for(j=1;j<=n;j++)a[i][j]=(a[i][j]+P)%P;
 	for(i=1;i<=n;i++){
 		for(j=i+1;j<=n;j++)
 		while(a[j][i]){
 			ll t=a[i][i]/a[j][i];
 			for(k=i;k<=n;k++)a[i][k]=(a[i][k]+P − t*a[j][k]%P)%P;
 			for(k=i;k<=n;k++)swap(a[i][k],a[j][k]);
 			flag^=1;
 		}
 		ans=ans*a[i][i]%P;
 		if(!ans)return 0;
	}
 	if(!flag)ans=(P − ans);
 	return ans;
}