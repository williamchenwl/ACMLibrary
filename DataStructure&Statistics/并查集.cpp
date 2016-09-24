/*
    correctly used times = 
    used in = { 
    
    }
*/
/*************************************************************************
	> File Name: 并查集.cpp
	> Author: 
	> Mail: 
	> Created Time: 2015年12月09日 星期三 12时49分08秒
 ************************************************************************/



// 并查集：
 int par[maxn];
 void init(int n)
 {
        for(int i=0; i<n; i++)
            par[i] = i;

 }
 int Find(int x)
 {
        if(par[x] == x) return x;
        else return par[x] = Find(par[x]);

 }
  
   
  // 切记执行合并集合的操作时找到两个元素的根然后par[x] = y
int x = Find(fir), y = Find(sec);
if(x != y)
{
    par[x] = y;
}
