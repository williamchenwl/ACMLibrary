#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define XPREVN		(21*1024*1024)				/**/
#define XSQRTPREVN	(8*1024)
#define XPREVPI		(4*1024*1024)				/* PI(XPREVN) : 3957809 */
#define XMAXNTH		((LLong)10*1000*1000*1000)	/* NTH( 1E10 ) == 252097800623 */

#define XPREVDM		(7)
#define XPREVQ		(2*3*5*7*11*13*17)
#define XPREVPHQ	(1*2*4*6*10*12*16)

#ifdef _MSC_VER
#pragma warning( disable : 4244 )
typedef __int64		LLong;
#define LLFmt		"I64d"
#else
typedef long long	LLong;
#define LLFmt		"Ld"
#endif
int	 X_pi_small_prime;
int X_small_prime[XPREVPI];
int X_pi_prev_N[XPREVN/2+1];
int X_prev_V[XPREVQ+1];
static LLong phiX_p( LLong x, LLong a )
{
    if( a == XPREVDM )
        return x / XPREVQ * XPREVPHQ + X_prev_V[ x % XPREVQ ];
    if( x < X_small_prime[a-1] )
        return 1;
    return phiX_p( x, a - 1 ) - phiX_p( x / X_small_prime[a-1], a - 1 );
}

int X_pi_prev(int X){
    if (X<2) return 0;
    return X_pi_prev_N[(X+1)/2];
}

LLong phiX( LLong X )
{
    LLong cubeRootX, max, len3, len2, s, i, k;
    LLong sum, p;
    if( X <= XPREVN )
        return X_pi_prev(X);

    max   = (LLong)(pow( (double)X, 2./3 ) + 2);
    cubeRootX = (LLong)(pow( (double)X, 1./3 ) + .5);
    if( cubeRootX*cubeRootX*cubeRootX > X )
        --cubeRootX;
    len3 = X_pi_prev(cubeRootX);

    sum = 0;
    s = 0;
    k = max -1 ;
    for( i = len3; ; ++i )
    {
        p = X_small_prime[i];
        if( p * p > X ) break;

        s += X_pi_prev(k) - X_pi_prev((int)((double)X/p));
        k = (int)((double)X/p);

        sum += s;
    }
    len2 = X_pi_prev(p-1);

    sum = (len2-len3)*X_pi_prev(max-1) - sum;
    sum = len3 * (len3-1)/2 - len2 * (len2-1) / 2 + sum;

    return phiX_p( X, len3 ) - sum + len3 - 1;
}
void initSmallPrime()
{
    char *mark = (char*)calloc(1,XPREVN/2+1);
    int i, j;

    for( i = 3; i <= XSQRTPREVN; i += 2 )
    {
        if( mark[i/2] ) continue;
        for( j = i*i/2; j <= XPREVN/2; j+=i )
            mark[j] = 1;
    }
    X_small_prime[0] = 2;
    X_pi_small_prime = 1;
    X_pi_prev_N[0] = 0;
    X_pi_prev_N[1] = 1;
    for( i = 4; i <= XPREVN; i += 2 )
    {
        if( mark[(i-1)/2] )
        {
            X_pi_prev_N[i/2] = X_pi_prev_N[i/2-1];
        }
        else
        {
            X_pi_prev_N[i/2] = 1 + X_pi_prev_N[i/2-1];
            X_small_prime[X_pi_small_prime++] = i-1;
        }
    }
    free(mark);

    for( i = 0; i < XPREVQ; ++i )
        X_prev_V[i] = i;
    for( i = 1; i <= XPREVDM; ++i )
        for( j = XPREVQ-1; j >= 0; --j )
            X_prev_V[j] -= X_prev_V[ j/X_small_prime[i-1] ];
}

int main()
{
    LLong	x, r;
    initSmallPrime();

    while(scanf( "%I64d", &x )>0 )
    {
        r = phiX( x );
        printf("%I64d\n", r );
    }
    return 0;
}

//#include <stdio.h>
//#include <stdlib.h>
//#include <time.h>
//#include <math.h>
//
//#define XPREVN		(30*1024*1024)				/**/
//#define XSQRTPREVN	(8*1024)
//#define XPREVPI		(4*1024*1024)				/* PI(XPREVN) : 3957809 */
//#define XMAXNTH		((LLong)10*1000*1000*1000)	/* NTH( 1E10 ) == 252097800623 */
//
//int		*X_small_prime ,  X_pi_small_prime;
//int		*X_pi_prev_N   , *X_prev_V;
//
//#define XPREVDM		(7)
//#define XPREVQ		(2*3*5*7*11*13*17)
//#define XPREVPHQ	(1*2*4*6*10*12*16)
//
//#ifdef _MSC_VER
//#pragma warning( disable : 4244 )
//typedef __int64		LLong;
//#define LLFmt		"I64d"
//#else
//typedef long long	LLong;
//#define LLFmt		"Ld"
//#endif
//int X_pi_prev(int X){
//    if (X<2) return 0;
//    return X_pi_prev_N[(X+1)/2];
//}
//static LLong phiX_p( LLong x , LLong a )
//{
//	if( a == XPREVDM )
//		return x / XPREVQ * XPREVPHQ + X_prev_V[ x % XPREVQ ];
//	if( x < X_small_prime[a-1] )
//		return 1;
//	return phiX_p( x , a - 1 ) - phiX_p( x / X_small_prime[a-1] , a - 1 );
//}
//
//
//
//LLong phiX( LLong X )
//{
//	LLong cubeRootX  , max , len3 , len2 , s , i , k;
//	LLong sum , p;
//	if( X <= XPREVN )
//		return X_pi_prev(X);
//
//	max   = (LLong)(pow( (double)X , 2./3 ) + 2);
//	cubeRootX = (LLong)(pow( (double)X , 1./3 ) + .5);
//	if( cubeRootX*cubeRootX*cubeRootX > X )
//		--cubeRootX;
//	len3 = X_pi_prev(cubeRootX);
//
//	sum = 0; s = 0; k = max -1 ;
//	for( i = len3; ;++i )
//	{
//		p = X_small_prime[i];
//		if( p * p > X ) break;
//
//		s += X_pi_prev(k) - X_pi_prev((int)((double)X/p));
//		k = (int)((double)X/p);
//
//		sum += s;
//	}
//	len2 = X_pi_prev(p-1);
//
//	sum = (len2-len3)*X_pi_prev(max-1) - sum;
//	sum = len3 * (len3-1)/2 - len2 * (len2-1) / 2 + sum;
//
//	return phiX_p( X , len3 ) - sum + len3 - 1;
//}
//
//void initSmallPrime()
//{
//	char *mark = (char*)calloc(1,XPREVN/2+1);
//	int i , j;
//	X_small_prime = (int*)calloc(sizeof(int),XPREVPI );
//	X_pi_prev_N   = (int*)calloc(sizeof(int),XPREVN+1);
//	X_prev_V	  = (int*)calloc(sizeof(int),XPREVQ+1);
//
//	for( i = 3; i <= XSQRTPREVN; i += 2 )
//	{
//		if( mark[i/2] ) continue;
//		for( j = i*i/2; j <= XPREVN/2; j+=i )
//			mark[j] = 1;
//	}
//	X_small_prime[0] = 2;
//	X_pi_small_prime = 1;
//	X_pi_prev_N[0]=0;
//	X_pi_prev_N[1] = 1;
//	for( i = 3; i <= XPREVN; i += 2 )
//	{
//		if( mark[i/2] )
//		{
//			X_pi_prev_N[(i+1)/2] = X_pi_prev_N[i/2];
//		}
//		else
//		{
//			X_pi_prev_N[(i+1)/2] =1 + X_pi_prev_N[i/2];
//			X_small_prime[X_pi_small_prime++] = i;
//		}
//	}
//	free(mark);
//
//	for( i = 0; i < XPREVQ; ++i )
//		X_prev_V[i] = i;
//	for( i = 1; i <= XPREVDM; ++i )
//		for( j = XPREVQ-1; j >= 0; --j )
//			X_prev_V[j] -= X_prev_V[ j/X_small_prime[i-1] ];
//}
//
//int main()
//{
//    LLong	x, r;
//    initSmallPrime();
//
//    while(scanf( "%I64d", &x )>0 )
//    {
//        r = phiX( x );
//        printf("%I64d\n", r );
//    }
//    return 0;
//}
//
//

