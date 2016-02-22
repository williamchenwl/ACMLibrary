/*
    correctly used times = 
    used in = { 
   	
    }
*/
/*************************************************************************
	> File Name: 二进制中1的个数.cpp
	> Author: 
	> Mail: 
	> Created Time: 2015年12月08日 星期二 13时42分34秒
 ************************************************************************/

int BitCount2(unsigned int n)
{
        unsigned int c =0 ;
        for (c =0; n; ++c)
    {
                n &= (n -1) ; // 清除最低位的1
            
    }
        return c ;

}
//或者
int cal(int n)
{
         n = (n &0x55555555) + ((n >>1) &0x55555555) ;
        n = (n &0x33333333) + ((n >>2) &0x33333333) ;
        n = (n &0x0f0f0f0f) + ((n >>4) &0x0f0f0f0f) ;
        n = (n &0x00ff00ff) + ((n >>8) &0x00ff00ff) ;
        n = (n &0x0000ffff) + ((n >>16) &0x0000ffff) ;
        return n;

}
