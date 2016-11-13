LL fun(LL n){
        if(n==1)
            return 1;
        if(n&1)
            return 2*fun((n-1)/2)+1;
        else
            return  2*fun(n/2)-1;
}

using namespace std;

int n,m;

int last(int i){
  if(i==1)
    return 0;
  else
    return (last(i-1)+ (n - i + 1) )%i;
}

int main(){
   cin>>m;
   while(m--){
   scanf("%d",&n);
   printf("%d\n",last(n) + 1);
   }
   return 0;
}
//某些约瑟夫可采用线段树来做
