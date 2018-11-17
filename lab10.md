# python 编程实验报告

### 高等数学

#### 准备阶段

导入`math`库和`sympy`库中所有函数和常量、变量

![](http://m.qpic.cn/psb?/V10TtYkp2MvHv1/kk0vARdFA6jEZxzX38CQe8ma*EH4s3fYmbBKOHrqaAg!/b/dFQBAAAAAAAA&bo=yASqAQAAAAARF0c!&rf=viewer_4)

`math`库

包含基本的数学函数库

`sympy`库

具有强大科学运算功能的符号型数学计算库

#### 求不定积分

$$ \int\frac{dx}{x(x^{5}+2)} = \frac{1}{10}ln|\frac{x^{5}}{x^{5}+2}| + C $$

![](http://m.qpic.cn/psb?/V10TtYkp2MvHv1/ychHpkndakWxgHUpZC1PkssGEOGC9Xyw8Om0R43lKco!/b/dD4BAAAAAAAA&bo=wwSsAQAAAAARF0o!&rf=viewer_4)

####  解微分方程

$$ f''(x) - 2f'(x) + 2f(x) = 0 $$

![](http://m.qpic.cn/psb?/V10TtYkp2MvHv1/ZTMpcJLYShCI56VDtBqQHXKr3otMkWQo0q8zMVs*IyI!/b/dFQBAAAAAAAA&bo=xwSTAQAAAAARF3E!&rf=viewer_4)

$$ f(x) = e^{x}(C1sinx + C2cosx) (C1,C2为常数) $$

### 线性代数

#### 准备阶段

导入`numpy`库中所有函数和常量、变量

![](http://m.qpic.cn/psb?/V10TtYkp2MvHv1/sqalwUPgPWaXqKGdEQMkahPQ0RbjNibnfzv1kklPD3A!/b/dFIBAAAAAAAA&bo=wgSGAQAAAAARF2E!&rf=viewer_4)

`numpy`库

支持数组和矩阵运算，还有丰富的数学和物理方程可供使用

#### 矩阵的逆

$$ m = \left[ \begin{array}{ccc}
3 & -7 & -2 & 2\\
-3 & 5 & 1 & 0\\
6 & -4 & 0 & -5\\
-9 & 5 & -5 & 12
\end{array} 
\right ] $$

![](http://m.qpic.cn/psb?/V10TtYkp2MvHv1/xCWF8Quckv1n*NGooaFt7yrEtLynpIBXLCK6aHL0gPE!/b/dC8BAAAAAAAA&bo=xgSsAQAAAAARF08!&rf=viewer_4)

$$ m^{-1} = \left[ \begin{array}{ccc}
17 & 169/6 & 4 & -7/6\\
8 & 27/2 & 2 & -1/2\\
11 & 18 & 2 & -1\\
14 & 23 & 3 & -1
\end{array} 
\right ] $$

#### 矩阵乘法

$$ m = \left[ \begin{array}{ccc}
3 & -7 & -2 & 2\\
-3 & 5 & 1 & 0\\
6 & -4 & 0 & -5\\
-9 & 5 & -5 & 12
\end{array} 
\right ] 
;
 n = \left[ \begin{array}{ccc}
4 & -2 & 5 \\
-8 & 1 & 7 \\
5 & 3 & -6 \\
6 & 1 & -3 
\end{array} 
\right ] $$

![](http://m.qpic.cn/psb?/V10TtYkp2MvHv1/bWYfzK9i8Dl8tBBHKce0WZC*C6JOcI1A5D4W1VZLLPI!/b/dC4BAAAAAAAA&bo=xgTAAQAAAAARFyM!&rf=viewer_4)

$$ m*n = \left[ \begin{array}{ccc}
3 & -7 & -2 & 2\\
-3 & 5 & 1 & 0\\
6 & -4 & 0 & -5\\
-9 & 5 & -5 & 12
\end{array} 
\right ] 
\left[ \begin{array}{ccc}
4 & -2 & 5 \\
-8 & 1 & 7 \\
5 & 3 & -6 \\
6 & 1 & -3 
\end{array} 
\right ] 
=
\left[ \begin{array}{ccc}
70 & -17 & -28 \\
-47 & 14 & 14 \\
26 & -21 & 17 \\
-29 & 20 & -16 
\end{array} 
\right ] $$





