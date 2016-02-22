/*
    correctly used times = 
    used in = { 
   	
    }
*/
/*************************************************************************
	> File Name: 拓扑排序.cpp
	> Author: 
	> Mail: 
	> Created Time: 2015年12月09日 星期三 13时03分50秒
 ************************************************************************/

voi topo()
{
       priority_queue<int, vector<int>, greater<int> > que;
       for(int i=1; i<=N; i++)
           if(indegree[i] == 0) que.push(i);
       int c = 1;
       while(!que.empty())
        {
           int v = que.top(); que.pop();
           printf("%d%c", v, c==N?'\n':' ');
            c++;
           for(int i=1; i<=N; i++)
        {
             if(Map[v][i])
            {
                indegree[i]--;
                if(indegree[i]==0) que.push(i);
                           
            }
                   
        }
           
    }

}              

