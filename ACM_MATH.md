###ACM_Math

[TOC]



##### 1.Combinatorial Mathematics

######1.1 Bell Number:　

$B_n$表示元素个数为n的集合划分成若干个不相交集合的方案数

$B_{n + 1} = \sum_{k = 0}^n C(n,k)B_k$



######1.2 Catalan Number: 

递推公式： $h_1 = 1, h_n = \frac{h_{n-1}(4n-2)}{n+1}$

组合数公式：$h_n = \frac{C(2n,2)}{n +1} = C(2n,n) - C(2n,n+1)$

前n项: 1,1,2,5,14,42,132,429,1430,4862,16796,58768

长度为$n$的合法括号匹配为$h_{n}$, 有$n+1$个叶子节点的二叉树的形态有$h_{n}$个

convex polygon with $n + 2$ sides can be cut into triangles in $h_{n}$ different ways



######1.3  Cayley's Theorem:

所有群G同构于在G上的对称群的子群

拓展版本：对于$n$个点, $m$个连通块，每个连通块$a[i]$个点，用$s-1$条边连通的方案数为$n^{s-2}a[1]a[2]...a[m]$。

n个节点（有标号）的树的形态个数为$n^{n-2}$



######1.4 Jacobi's Four Square Theorem

设$a^2 + b^2 + c^2+d^2 = n$的自然整数解的个数为$r4(n)$, $d(n)$为n的约数和，由Jacobi's Four Square Theorem可知，若n是奇数，则$r4(n) = 8d(n)$, 否则$r4(n) = 24d(k)$, $k$为n去除所有2后的结果


###### 1.5 Balls and Boxes

| k个球  | m个盒子 | 是否允许空盒子 | 方案数                                  |
| ---- | ---- | ------- | ------------------------------------ |
| 各不相同 | 各不相同 | 是       | $m^k$                                |
| 各不相同 | 各不相同 | 否       | $m!stirling2(k,m)$                   |
| 各不相同 | 完全相同 | 是       | $\sum_{i=1}^{m}Stirling2(k,i)$       |
| 各不相同 | 完全相同 | 否       | $Stirling2(k,m)$                     |
| 完全相同 | 各不相同 | 是       | $C_{m + k - 1}^{k-1}$                |
| 完全相同 | 各不相同 | 否       | $C_{k-1}^{m-1}$                      |
| 完全相同 | 完全相同 | 是       | $\frac{1}{(1-x)(1-x^2)...(1-x^m)}$   |
| 完全相同 | 完全相同 | 否       | $\frac{x^m}{(1-x)(1-x^2)...(1-x^3)}$ |



###### 1.6  Stirling2第二类斯特林数

$S(p,k)$:将p个物体划分成k个非空的不可辨别的集合的方案数（第一类为划分为排列）

$S(p,k) = kS(p-1,k) + S(p-1,k-1)$

$S(p,0)  = 0,p >= 1,S(p,p) = 1$

卷积形式$S(n,m) = \sum\limits_{k=0}^m\frac{(-1)^k}{k!}×\frac{(m-k)^n}{(m-k)!}$

###### 1.7 组合恒等式

2.对称恒等式$\binom{n}{k} = \binom{n}{n-k}$

3.吸收恒等式$\binom{n}{k} = \frac{n}{k} \binom{n-1}{k-1}$

4.加法恒等式$\binom{n}{k} = \binom{n-1}{k-1} + \binom{n-1}{k}$

5.三项式$\binom{n}{m}\binom{m}{k} = \binom{n}{k}\binom{n-k}{m-k}$

6.平行求和$\sum\limits_{k\leq m}\binom{n+k}{k} = \binom{n + m + 1}{m}$

7.范德蒙德卷积$\sum\limits_{k}\binom{n}{k}\binom{m}{r-k} = \binom{n+m}{r}$

###### 1.8 级数

$\frac{1}{(1+x)^n} = C(n-1,n-1) + C(n,n-1)x + C(n+1,n-1)x^2 + ....C(2n,n-1)x^n$











 

##### 2.Graph Theory 

###### 2.1独立集点覆盖匹配

二分图：

最小路径覆盖 = 最大独立集 = 总结点数 - 最大匹配  

最小点覆盖 = 最大匹配数

任意图：

最大独立集 + 最小点覆盖 = 点数

最大团 = 补图的最大独立集



######2.2 Matrix-Tree Theorem

$diag(D)$为点度数向量生成的对角矩阵，$G_{xy}$为邻接矩阵，则$n-1$阶子矩阵的行列式值$det([diag(D) - G_{xy}]_{n-1})$为生成树的个数。Clayey定理是特殊形式。



###### 2.3平面图

$F$为平面中的分割区域数，$E$为边数，$V$为点数，$F = E- V +1$





##### 3.Number Theory

###### 3.1 积性函数

$f(n)$的定义为正整数域，值域为复数域，$f(n)$则为数论函数

$f(n)$为数论函数，对于互质的整数$p,q$有$ f(p * q) = f(p) * f(q)$则为积性函数，没有互质条件限制时则被称为完全积性函数

1.$id(i) = i$ 单位函数  2.$e(i) = [i = 1]$ 元函数

3.$d(i)$,$i$的约数个数  4.$\sigma(i)$,$i$的约数和

5.$I(n) = 1$恒等函数  6.$\phi(n)$欧拉函数

7.$\mu(n)$, 莫比乌斯函数 

8.$\sigma_k(n) = \sum_{d|n}d^k$除数函数，n约数的k次幂和

单位函数，元函数，单位函数的幂，恒等函数都是完全积性函数

###### 3.2积性函数性质

$n = \sum\limits_{d|n}\phi(d)$

$e(n) = \sum\limits_{d|n}\mu(d)$

###### 3.3 Dirichlet Product

两个数论函数f和g的Dirichlet卷积为$(f*g)(n) = \sum_{d|n}f(d) * g(\frac{n}{d})$，Dirichlet卷积满足交换律，结合律，对加法满足分配律。

任意函数和元函数的Dirichlet卷积是函数本身。

恒等函数和莫比乌斯函数的Dirichlet卷积是元函数（3.2.1）。

恒等函数和欧拉函数的Dirichlet卷积是单位函数（3.2.2）。

两个积性函数的Dirichlet卷积是积性函数。

恒等函数$I$和莫比乌斯函数$\mu$在Dirichlet卷积意义下互为逆元，由此可以得到莫比乌斯反演$g = f *I, g * \mu = f$。

######3.4恒等式与技巧

1.$\sum_{i=1}^{n}\sigma_{k}(i) = \sum_{i = 1}^{n}\sum_{d|i}d^k = \sum_{d = 1}^nd^k\lfloor\frac{n}{d}\rfloor$

2.$[s = \emptyset] = \sum_{t \subset s}(-1)^{|t|}$







###### 3.5 拓展欧拉定理

$a^n \equiv a^{n \ mod \ \phi(p) + \phi(p)} (mod p), (n \geq \phi(p))$







##### 4.Calculus

###### 4.1调和级数

$\sum_{i = 1}^{n}\frac{1}{i}$在n较大时等于$ln n + r$, r为0.5772156649015328



##### 5.Others

###### 5.1 皮克定理

给定顶点坐标均是整点的简单多边形，面积$S$，内部格点$n$，边上格点$s$

三者的关系为$S = n + \frac{s}{2} + 1$



###### 5.2幂和

$\sum\limits_{i = 1}^{n}i = \frac{n(n+1)}{2}$

$\sum\limits_{i=1}^{n}i^2 = \frac{n(n+1)(n+2)}{6}$

$\sum\limits_{i=1}^{n}i^3 = [\frac{n(n+1)}{2}]^2$

$\sum\limits_{i=1}^n i^4 = \frac{n(n+1)(2n+1)(3n^2+3n-1)}{30} $

$\sum\limits_{i=1}^{n}i^5 = \frac{n^2(n+1)^2(2n^2+2n-1)}{12}$

