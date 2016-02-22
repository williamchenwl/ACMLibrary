/*
    correctly used times = 
    used in = { 
   	
    }
*/
    
/*************************************************************************
	> File Name: 最小生成树Kruskal.cpp
	> Author: 
	> Mail: 
	> Created Time: 2015年12月09日 星期三 13时10分23秒
 ************************************************************************/

#include<iostream>
using namespace std;
int par[maxn];
void init(int n)
{
       for(int i=0; i<=n; i++)
           par[i] = i;

}
int Find(int x)
{
       if(par[x] == x) return x;
       else return par[x] = Find(par[x]);

}
ll kruskal()
{
       init(n);                                                //并查集初始化
       sort(e, e+num);
       int m = 0; ll ans = 0;
       for(int i=0; i<num; i++)
    {
               int x = Find(e[i].u), y = Find(e[i].v);
               if(x != y)                                                
        {
                       ans += e[i].cost;
                       m++;
                       par[x] = y;                    //注意并查集合并操作 之前写错了
                   
        }
               if(m == n-1) break;                                         //n是顶点数
           
    }
       if(m != n-1)    //最小生成树不存在
       return ans;

}
