# 智能蛇实验报告

本次项目的任务是让蛇有一定的智能，能通过算法具有 “感知 - 决策 - 行动” 的能力

### 一、实验目的

1. 了解 算法 与 “智能” 的关系

2. 通过算法赋予蛇智能

3. 了解 Linux IO 设计的控制

### 二、实验环境

1. 使用 Vbox Linux 虚拟机

![](http://m.qpic.cn/psb?/V10TtYkp2MvHv1/Vh0L02Myvpw8oIVQ2ZeO*2cGLfhxzq6VatNYacgXE7M!/b/dFMBAAAAAAAA&bo=GQMqAgAAAAADBxA!&rf=viewer_4)

1. Linux (Unbutu发行版)

![](http://m.qpic.cn/psb?/V10TtYkp2MvHv1/KkFGUJhuMZbE3A66X5*mGj9R9lRGnw0yfzgnae3Uuco!/b/dDYBAAAAAAAA&bo=IgOyAgAAAAADJ5M!&rf=viewer_4)

3. 编辑环境 Vim , 编译 gcc


### 三、控制输入/输出设备

#### 1、VT 100 终端标准

 DEC公司1978制造的型号为VT100的终端，由于设计非常良好，成为史上最流行的字符终端，并且为其他字符终端设立了永久的标准。

 在 Linux 上尝试用C语言+VT100控制码的形式实现sin函数的动态效果

 代码来源及详细内容可参考[C语言与VT100控制码编程](http://www.cnblogs.com/zengjfgit/p/4373564.html)，在此仅摘抄 [sin-demo.c](https://github.com/iLaiPW/LPW-homework/blob/gh-pages/sin-demo.c) 的代码

 实现效果如下

 ![](http://m.qpic.cn/psb?/V10TtYkp2MvHv1/UE32WhTyq2cIU53lJsX.z2xzpq9X5cX4HbXOFNvPssA!/b/dDEBAAAAAAAA&bo=2ALtAQAAAAACNyU!&rf=viewer_4)

#### 2、实现 kbhit()

tty一词源于Teletypes，或者teletypewriters，原来指的是电传打字机，是通过串行线用打印机键盘通过阅读和发送信息的东西，后来这东西被键盘与显示器取代，所以现在叫终端比较合适。终端是一种字符型设备，它有多种类型，通常使用tty来简称各种类型的终端设备。

代码来源：[Linux下非阻塞地检测键盘输入的方法 (整理)](http://bbs.chinaunix.net/thread-935410-1-1.html)

代码作用：

1. getchar()获得输入字符不需要按回车
2. 非阻塞得检测键盘输入
3. 输入的字符不回显

实现效果如下

![](http://m.qpic.cn/psb?/V10TtYkp2MvHv1/wHPcW8mk4YhhUVuy75HG4JxYBVt3Ng9pQzTiiLIR1qI!/b/dDQBAAAAAAAA&bo=2ALtAQAAAAACFwU!&rf=viewer_4)

### 四、编写智能算法

编写人工智能程序，使得 snake 每秒自动走一步

#### 1.智能蛇的程序框架

```
输出字符矩阵
	WHILE not 游戏结束 DO
        wait(time)
		ch＝whereGoNext(Hx,Hy,Fx,Fy)
		CASE ch DO
		‘A’:左前进一步，break 
		‘D’:右前进一步，break    
		‘W’:上前进一步，break    
		‘S’:下前进一步，break    
		END CASE
		输出字符矩阵
	END WHILE
	输出 Game Over!!! 
```

#### 2.决定蛇行走的方向函数的伪代码

```
    set Hx, Hy //头的位置
    set Fx, Fy //食物的位置
    set direction[4] = {'A', 'D', 'W', 'S'} //记录可走的方向
    set distance[4] = {0, 0, 0, 0} //记录离食物的距离

    // 分别计算蛇头周边四个位置到食物的距离。H头的位置，F食物位置
    //     例如：假设输入”a” 则distance[0] = |Fx – (Hx-1)| + |Fy – Hy|
    //           如果 Hx-1，Hy 位置不是Blank，则 distance[0] = 9999
    FOR i from 0 to 3
        distance[i] = calculate_distance from Hx +- 1, Hy +- 1 to Fx, Fy
    END FOR

    // 选择distance中存最小距离的下标p
    FOR i from 0 to 3
        IF min > distance[i]
            index = i
        END IF
    END FOR
	
    return direction[index]

```

```C
char whereGoNext(int Hx,int Hy,int Fx,int Fy) {
	char move[4] = {'A', 'D', 'W', 'S'};
	int distance[4] = {0};
	int min = 9999, index = 0;
	int i;
	
	distance[0] = calculate_distance(Hx - 1, Hy, Fx, Fy);
	distance[1] = calculate_distance(Hx + 1, Hy, Fx, Fy);
	distance[2] = calculate_distance(Hx, Hy - 1, Fx, Fy);
	distance[3] = calculate_distance(Hx, Hy + 1, Fx, Fy);
		
	for(i = 0; i < 4; i++) {
		if(distance[i] < min) {
			min = distance[i];
			index = i;
		}
	}
	
	return move[index];
}

int calculate_distance(int Hx,int Hy,int Fx,int Fy) {
	
	if(map[Hy][Hx] == ' ' || map[Hy][Hx] == '$')
		return abs(Fx - Hx) + abs(Fy - Hy);
	else
		return 9999;
}

```

完整代码：[SmartSnake.c](https://github.com/iLaiPW/LPW-homework/blob/gh-pages/SmartSnake.c)

实现效果如下

![](http://m.qpic.cn/psb?/V10TtYkp2MvHv1/s9t4gfg.41reWYsE1RQ1IQXrMgrTtTnATwmP0d.4TQc!/b/dDYBAAAAAAAA&bo=2gLtAQAAAAACFwc!&rf=viewer_4)

#### 3.思考：一个长度为5的障碍物能困死该自动跑的蛇吗？

能，只要该障碍物将蛇头围住，往任何方向走都会使游戏结束

### 五、总结

1. 学会使用 Vbox 虚拟机及在 Lunix 系统下编程；体会到命令行编程的乐趣
2. 初步了解了I/O输入输出设备及其检测
3. 学习编写智能算法，感受算法与智能的密切联系
4. 了解了 Linux 中定时器的设置与使用，应用了setitimer()
5. 在实践中发现算法的缺陷，如：无法将远处的障碍物纳入计算距离的公式，不会考虑蛇身对路径的影响……仍有待改进