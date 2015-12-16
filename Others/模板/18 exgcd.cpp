int exgcd(int a,int b,int &x,int &y){  
     if (!b) return x = 1,y = 0;
     exgcd(b,a&b,y,x);
     y = y - (a/b)*x;
}