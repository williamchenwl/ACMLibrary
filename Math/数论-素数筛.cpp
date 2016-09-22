/*************************************************************************
	> File Name: 素数筛.cpp
	> Author: 
	> Mail: 
	> Created Time: 2015年12月08日 星期二 13时43分25秒
 ************************************************************************/


#include<iostream>
using namespace std;    
const long N = 200000;   
long prime[N] = {0},num_prime = 0;    
int isNotPrime[N] = {1, 1};   
int main()    
{     
        for(long i = 2 ; i < N ; i ++)       
        {            
                if(! isNotPrime[i])               
                    prime[num_prime ++]=i;  
                for(long j = 0 ; j < num_prime && i * prime[j] <  N ; j ++)
                    {               
                                    isNotPrime[i * prime[j]] = 1;  
                                if( !(i % prime[j] )  )                  
                                    break;           
                            }        
            }        
    return 0;   
}  

