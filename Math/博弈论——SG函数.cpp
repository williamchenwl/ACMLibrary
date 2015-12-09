/*************************************************************************
	> File Name: 博弈论——SG函数.cpp
	> Author: 
	> Mail: 
	> Created Time: 2015年12月08日 星期二 17时16分29秒
 ************************************************************************/

/*
* SG函数
*  N求解范围 S[]数组是可以每次取的值，t是s的长度。
*  */
int sg[N];
bool hash[N];
void sg_solve(int *s,int t,int N)  
{
        int i,j;
        memset(sg,0,sizeof(sg));
        for(i=1;i<=N;i++)
    {
                memset(hash,0,sizeof(hash));
                for(j=0;j<t;j++)
                    if(i - s[j] >= 0)
                        hash[sg[i-s[j]]] = 1;
                for(j=0;j<=N;j++)
                    if(!hash[j])
                        break;
                sg[i] = j;
            
    }

}


/*
 * 注意 S数组要按从小到大排序 SG函数要初始化为-1 对于每个集合只需初始化1遍
 * n是集合s的大小 S[i]是定义的特殊取法规则的数组
 * */
 int s[110],sg[10010],n;
 int SG_dfs(int x)
 {
         int i;
         if(sg[x]!=-1)
             return sg[x];
         bool vis[110];
         memset(vis,0,sizeof(vis));
         for(i=0;i<n;i++)
     {
                 if(x>=s[i])
         {
                         SG_dfs(x-s[i]);
                         vis[sg[x-s[i]]]=1;
                     
         }
             
     }
         int e;
         for(i=0;;i++)
             if(!vis[i])
     {
                     e=i;
                     break;
                 
     }
         return sg[x]=e;

 }
