# python 编程实验报告

[TOC]

### 目录

<a href=”#1.实验目的”>1.实验目的

2.[实验环境](#2.实验环境)

3.[高等数学练习](#3.高等数学练习)

4.[线性代数练习](#4.线性代数练习)

5.[实验小结](#5.实验小结)

### 1.实验目的

了解一种“解释型”语言 python

使用 python 做一些简单的科学计算

### 2.实验环境

编程工具：Python（Anaconda3）

操作系统：Windows

### 3.高等数学练习

#### 3.1.准备阶段

导入`math`库和`sympy`库中所有函数和常量、变量

```
from math import *
from sympy import *
```

![](http://m.qpic.cn/psb?/V10TtYkp2MvHv1/kk0vARdFA6jEZxzX38CQe8ma*EH4s3fYmbBKOHrqaAg!/b/dFQBAAAAAAAA&bo=yASqAQAAAAARF0c!&rf=viewer_4)

`math`库

包含基本的数学函数库

`sympy`库

具有强大科学运算功能的符号型数学计算库

#### 3.2.求不定积分

调用**integrate(ep,x)**，左边为被积函数，右边为积分变量

```
x = symbols('x') #声明符号变量 'x'
integrate((x*(x**5+2))**(-1),x) 
```

$$ \int\frac{dx}{x(x^{5}+2)} = \frac{1}{10}ln|\frac{x^{5}}{x^{5}+2}| + C $$

![](http://m.qpic.cn/psb?/V10TtYkp2MvHv1/ychHpkndakWxgHUpZC1PkssGEOGC9Xyw8Om0R43lKco!/b/dD4BAAAAAAAA&bo=wwSsAQAAAAARF0o!&rf=viewer_4)


#### 3.3.解微分方程

调用**dsolve(ep,x)**，左边为微分方程（要先将等式移项为右端为0的形式)，右边为要解的函数(在微分方程中)

调用**diff(f(x),x,n)**，求 f(x) 对 x 的 n 阶导数，n = 1时可省略不写

```
f = symbols('f', cls=Function) #声明符号变量 'f' ，代表一个函数
dsolve(diff(f(x),x,2) - 2*diff(f(x),x) + 2*f(x),f(x))
```

$$ f''(x) - 2f'(x) + 2f(x) = 0 $$

![](http://m.qpic.cn/psb?/V10TtYkp2MvHv1/ZTMpcJLYShCI56VDtBqQHXKr3otMkWQo0q8zMVs*IyI!/b/dFQBAAAAAAAA&bo=xwSTAQAAAAARF3E!&rf=viewer_4)

$$ f(x) = e^{x}(C_{1}sinx + C_{2}cosx) (C_{1},C_{2}为常数) $$

### 4.线性代数练习

#### 4.1.准备阶段

导入`numpy`库和`sympy`库中所有函数和常量、变量

```
from numpy import *
from sympy import *
```

![](http://m.qpic.cn/psb?/V10TtYkp2MvHv1/Bc3QwhrCwZugDrZqL565hRG5DndppFJ9ZJQC0cYtuUU!/b/dFMBAAAAAAAA&bo=xQRWAQAAAAARB6Y!&rf=viewer_4)

`numpy`库

支持数组和矩阵运算，还有丰富的数学和物理方程可供使用

#### 4.2.矩阵的逆

$$ m = \left[ \begin{array}{ccc}
3 & -7 & -2 & 2\\
-3 & 5 & 1 & 0\\
6 & -4 & 0 & -5\\
-9 & 5 & -5 & 12
\end{array} 
\right ] $$

```
m = matrix([[3,-7,-2,2],[-3,5,1,0],[6,-4,0,-5]])
m.I
```

![](http://m.qpic.cn/psb?/V10TtYkp2MvHv1/u*Ue1vxnVTfKNGHYSV3FXdlWkXoxzxdyYDnT67l2Rig!/b/dFMBAAAAAAAA&bo=yQSnAQAAAAARF0s!&rf=viewer_4)

$$ m^{-1} = \left[ \begin{array}{ccc}
17 & 169/6 & 4 & -7/6\\
8 & 27/2 & 2 & -1/2\\
11 & 18 & 2 & -1\\
14 & 23 & 3 & -1
\end{array} 
\right ] $$

#### 4.3.矩阵乘法

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

```
m = matrix([[3,-7,-2,2],[-3,5,1,0],[6,-4,0,-5]])
n = matrix([[4,-2,5],[-8,1,7],[5,3,-6],[12,9,-3]])
m*n
```

![](http://m.qpic.cn/psb?/V10TtYkp2MvHv1/1lYdPrpRsoh6ip2lXlKNK9vkAHMMTulQ3g7iQ.nh3uY!/b/dDEBAAAAAAAA&bo=xwQMAgAAAAARF.0!&rf=viewer_4)

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

#### 4.4矩阵方程

$$  A\vec x = \vec b $$

$$ A = \left[ \begin{array}{ccc}
1 & -7 & 0 & 6\\
0 & 0 & 1 & -2\\
-1 & 7 & -4 & 2
\end{array} 
\right ] 
;
\vec b = \left[ \begin{array}{ccc}
5\\
-3\\
7
\end{array} 
\right ] $$


```
A = Matrix([[1,-7,0,6],[0,0,1,-2], [-1,7,-4,2]])
b = Matrix([[5],[-3],[7]])
x = symarray('x',(4,1)) #声明符号数组x
solve(a*x-b)
```

![](http://m.qpic.cn/psb?/V10TtYkp2MvHv1/WjTEOR6FsGs22FpLGodx6iDM4htWsTtFILitCYQFmgQ!/b/dDIBAAAAAAAA&bo=xQQwAgAAAAARF9M!&rf=viewer_4)

$$ \vec x =  \left[ \begin{array}{ccc}
x_{0}\\
x_{1}\\
x_{2}\\
x_{3}
\end{array} 
\right ]  
= 
\left[ \begin{array}{ccc}
7x_{1} - 6x_{3} + 5\\
x_{1}\\
2x_{3} - 3\\
x_{3}
\end{array} 
\right ]    
=
x_{1}\left[ \begin{array}{ccc}
7\\
1\\
0\\
0
\end{array} 
\right ]   
+
x_{3}\left[ \begin{array}{ccc}
-6\\
0\\
2\\
1
\end{array} 
\right ]
+
\left[ \begin{array}{ccc}
5\\
0\\
-3\\
0
\end{array} 
\right ]

$$


### 5.实验小结

初步学习了一门新语言 python ，被其清晰简洁的语法所震撼，对解释型语言，交互式语言，面向对象语言有了更多认识

体会到了交互式编程的优点，对于简单的尝试性操作很是方便，输入语句之后，就可以立即得到结果，马上知道问题出在哪里，立即就可以修正

学会了用python解高数、线代题目，了解了许多强大的数学库及其函数的使用，深刻体会到计算机强大的计算能力

