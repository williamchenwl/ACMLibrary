##### GENERAL

1.INTUITIVE WAY OR NUMERIC WAY OF ANALYZING?

2.THINK ABOUT THE REVERSE PROBLEM

3.THINK ABOUT MEET IN THE MIDDLE

4.考虑均摊复杂度（每个位置的操作次数）

5.考虑每个答案的贡献（类似于期望）

6.可以考虑使用类似于归并排序式的分治

7.考虑操作倒序

##### DEBUG

1.加模取模，是否每一步都模

2.如果使用printf,则考虑输出格式是否正确

3.$O(\sqrt{n})$分解质因子时需要考虑是否留下了一个大素数

4.变量名错误

##### Tricks

1.二分分数区间$[\frac{a}{b},\frac{c}{d}]$时，$mid = \frac{a + c}{b + d}$

##### 压位分块

1.模2意义下的加法，就是xor

2.二进制问题通常需要1.按位考虑 2.01字典树

##### 图论

1.最短路问题常常需要考虑优化建图，思路有构造新节点和贪心去掉没有意义的边

