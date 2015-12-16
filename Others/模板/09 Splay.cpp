
int rotate(int x){
   int k=a[x].f; bool b=(a[k].s[1]==x);
   a[x].f=a[k].f; 
   a[k].s[b]=a[x].s[!b]; a[a[x].s[!b]].f=k;
   a[x].s[!b]=k; int f=a[k].f; a[k].f=x; 
   if (f) a[f].s[a[f].s[1]==k]=x;
   up(k); up(x);
}
      
int splay(int x){
  int y;
  while(a[x].f){
    y=a[x].f;
    if(a[y].f){if((a[a[y].f].s[0]==y)^(a[y].s[0]==x))rotate(x);else rotate(y);}
    rotate(x); }
  root = x; return root;
}
 
int newnode(int x,int f)
  {a[++tt].k=x; a[tt].f=f;
   if (!f) return tt; bool b=a[tt].k>a[f].k;
   a[f].s[b]=tt; return tt;}
 
int add(int x,int f)
  { if (!f) return splay(newnode(x,f));
    bool b=(x>a[f].k);
    if (!a[f].s[b]) return splay(newnode(x,f));
    add(x,a[f].s[b]);}
 
int maxnum(int x){ if (!x||!a[x].s[1]) return x;return maxnum(a[x].s[1]);}
 
int minnum(int x){if (!x||!a[x].s[0]) return x;return minnum(a[x].s[0]);}
 
int split(int x,int y,bool b){a[x].s[b]=0;a[y].f=0;}
int merge(int x,int y,bool b){a[x].s[b]=y; a[y].f=x;}
 
int del(int x){
    splay(x);
    int l=a[x].s[0]; int r=a[x].s[1];
    split(x,l,0); split(x,r,1);
    if (!l)  return root=r;
    merge(splay(maxnum(l)),r,1);
    }  
 
int dfs(int x)
   {  if (x==0) return 0;
      dfs(a[x].s[0]);
      printf("%d ",a[x].k);
      dfs(a[x].s[1]);}
 