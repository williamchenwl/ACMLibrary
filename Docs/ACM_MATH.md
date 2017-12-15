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

###### 1.9 二项式反演

$a(n) = \sum\limits_{i = 0}^{n}\binom{n}{i}b(i) \to b(n) = \sum\limits_{i = 0}^{n}(-1)^{n - i}\binom{n}{i}a(i)$



###### 1.10 Polya与Burnside

$G$是目标集$[1,n]$上的置换群，$c(a_k)$是在置换$a_k$的作用下的不动点

则等价类的个数等于$\frac{1}{|G|} * \sum\limits_{i = 1}^gc(a_i)$

典型例子包括圆排列，只有一个置换有不动点,个数为n!，所以圆排列的数量要再除n（共有n个置换）

 一个置换对应若干个不相交的循环，记下循环的个数为$\lambda(a_i)$

比如旋转这种最常见的操作，转i次对应的循环个数是$gcd(i,n)$

Polya定理: $L = \frac{1}{|G|}\sum\limits_{a_i \in G} m ^{\lambda(a_i)}$，m是染色的颜色数



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

$F​$为平面中的分割区域数，$E​$为边数，$V​$为点数，$F = E- V +1​$



###### 2.4 双连通分量

加最少多少条边使得图变成双连通分量、

缩点成树后计算叶子节点树



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

3.$n = p^k \to \phi(n) = p^k - p^{k-1}$

4.$s(n) = \sum_{i=1}^{n}i * \lfloor\frac{n}{i}\rfloor = \sum_{i = 1}^{n}\sigma(i)$



###### 3.5 拓展欧拉定理

$a^n \equiv a^{n \ mod \ \phi(p) + \phi(p)} (mod p), (n \geq \phi(p))$



###### 3.7 反素数

对于任何正整数n，其约数个数记为$d(n)$，如果任意$i < n$, $d(i) <  d(n)$，则n被称为反素数，反素数的形式必定为$n = 2^{t_1} * 3^{t_2} * 5^{t_3} *....$,并且,fan$t1 \geq t2 \geq t3 ....$，反素数的求解通常使用dfs。建的dfs树形式为，每层若干个节点表示的某个质因子的若干次方。



###### 3.8 证明实例

1.计算$\sum_{i = 1}^{m}\sum_{j = 1}^{n}gcd(i,j)$

$f(d) = \sum_{i = 1}^{n}\sum_{j = 1}^{m}[gcd(i,j) == d] $

$F(d) = \sum_{i = 1}^n\sum_{j = 1}^m[d | gcd(i,j)]$

显然$F(d) = \sum\limits_{d|n} f(n)$,自然使用反演$f(d) = \sum\limits_{d | n}F(n) * \mu(\frac{n}{d})$

通过常用的加速技巧，即可在$O(\sqrt{n})$时间内完成计算



2.求第n个非完全平方数

先套一层二分，转化为求$f(n) = \sum_{i = 1}^{n}\sum\limits_{d}[d * d == n]$

这会是一种莫比乌斯式的容斥,也可以构造类似于1的两个函数，筛法求解

$f(n) = \sum_{d = 1}^{\sqrt{n}}\mu(d)\lfloor\frac{n}{i^2}\rfloor$



3.$f(n) = rad(n) * \phi(n), g(n) = \sum_{d|n}f(d),h(n) = \sum_{i = 1}^ng(i)$,rad(n)是n的因子中最大的无平方因子的因子

$n = \prod_{i = 1}^tp_i^{k_i} , $ $rad(n) = \prod_{i = 1}^{t}p_i$

$(n,m) = 1,rad(n * m) = rad(n) * rad(m)$ 

$f(n)$为积性函数

$g(n) = \sum_{d|n}f(d) = \prod_{i=1}^{t}\sum_{j = 0}^{k_i}f(p_i^j) = \prod_{i = 1}^t(1 + p_i *\sum_{j = 1}^{k_i}\phi(p_i^{j - 1})) = \prod_{i = 1}^t(p_i^{k_i} + 1)$

这个式子代表的含义是，每个质因子要么都选，要么都不选，得到的所有乘积

$g(n) = \sum_{d | n}[(d,\frac{n}{d}) = 1] * d = \sum_{i = 1}^{n}\sum_{j = 1}^n[(i,j) = 1] * [ij = n] * i$

 $h(n) = \sum_{k=1}^{n}\sum_{i = 1}^{n}\sum_{j = 1}^n[(i,j) = 1] * [ij = k] * i$

$h(n) = \sum_{i = 1}^{n}\sum_{j = 1}^n[(i,j) = 1] * [ij \leq k] * i$

$h(n) = \sum_{i = 1}^{n}\sum_{j = 1}^{n}[ij\leq n]i\sum\limits_d[d | i][d | j] \mu(d)$

$h(n) = \sum_{d = 1}^{\sqrt{n}}d\mu(d)\sum\limits_{i = 1}^{n}\sum\limits_{j = 1}^{n}[d | i][f | j][ij \leq n]\frac{i}{d}$

$h(n) = \sum\limits_{d = 1}^{\sqrt{n}}d\mu(d)\sum\limits_{i = 1}^{\lfloor\frac{n}{d}\rfloor}\sum\limits_{j = 1}^{\lfloor\frac{n}{d}\rfloor}[ijd^2 \leq n]i$

$h(n) = \sum\limits_{d = 1}^{\sqrt{n}}d\mu(d)\sum\limits_{i = 1}^{\lfloor\frac{n}{d^2}\rfloor}{\lfloor\frac{n}{i * d^2}}\rfloor i$

4.杜教筛

求$f(n) = \sum_{i = 1}^n\phi(i)$

$\sum_{i = 1}^{n}\sum_{d | i}\phi(d) = \frac{n(n + 1)}{2} = \sum_{i = 1}^{n}f(\lfloor\frac{n}{i}\rfloor) = \sum_{i = 1}^n\sum_{d = 1}^{\lfloor\frac{n}{i}\rfloor}\phi(d)$



##### 4.Calculus

###### 4.1调和级数

$\sum_{i = 1}^{n}\frac{1}{i}$在n较大时等于$ln n + r$, r为0.5772156649015328



##### 5.Others

###### 5.1 皮克定理

给定顶点坐标均是整点的简单多边形，面积$S$，内部格点$n$，边上格点$s$

三者的关系为$S = n + \frac{s}{2} + 1$



###### 5.2 幂和

$\sum\limits_{i = 1}^{n}i = \frac{n(n+1)}{2}$

$\sum\limits_{i=1}^{n}i^2 = \frac{n(n+1)(n+2)}{6}$

$\sum\limits_{i=1}^{n}i^3 = [\frac{n(n+1)}{2}]^2$

$\sum\limits_{i=1}^n i^4 = \frac{n(n+1)(2n+1)(3n^2+3n-1)}{30} $

$\sum\limits_{i=1}^{n}i^5 = \frac{n^2(n+1)^2(2n^2+2n-1)}{12}$

###### 5.3 计算几何

1.叉积和点积均具有关于向量加减的分配率。

2.多边形的面积等于所有点逆时针排序以后，相邻两个点的向量叉积的结果。

###### 5.4 三角形面积

$S = a * h / 2$

$S  = a * b *c / 4r$ : r是外接圆的半径

$S = sqrt(p(p - a) * (p - b) *(p - c))$

###### 5.5 牛顿迭代

$x^{'} = x - \frac{f(x)}{f^{'}(x)}$

可以用来逼近sqrt(n)等



###### 5.6 DP方程

```
f[i,j]=max{f[i-1,k]}+1 | (a[i]=b[j]) and (b[k]<b[j])

f[i,j]=f[i-1,j] | (a[i]<>b[j])

f[i,j]表示a串和b串的最上升长公共子串

需要在枚举j的过程中顺便更新最大的K，保证n^2复杂度
for(int i=1;i<=m;++i)
{
    maxf=0;
    for(int j=1;j<=n;++j)
        if(b[j]<a[i]) maxf=max(maxf,f[j]);
        else
            if(b[j]==a[i]) f[j]=maxf+1,ans=max(ans,f[j]);
}
```







