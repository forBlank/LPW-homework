# 机器语言实验报告

## 任务 1：简单程序

### （1）打开网页 [The PIPPIN User’s Guide](https://sysu-swi.github.io/slides/The%20PIPPIN%20User's%20Guide.html#PROG2) ，然后输入 Program 1：Add 2 number

![](http://m.qpic.cn/psb?/V10TtYkp2MvHv1/KPF4*fafkazjYikzKsrTwX9L3D8DXrivYPCtdTB69HM!/b/dDIBAAAAAAAA&bo=8wRgAgAAAAADF6c!&rf=viewer_4)

### （2）点step after step。观察并回答下面问题：

![](http://m.qpic.cn/psb?/V10TtYkp2MvHv1/cYhztmcdseIVgqfXHgxeelZ4IzuJx.0Bzqy61Eqcr20!/b/dDMBAAAAAAAA&bo=bwKLAQAAAAADF9U!&rf=viewer_4)

#### 1.PC，IR 寄存器的作用。

IR : 存放正在执行的指令副本

PC : 存放下一条要执行指令的地址

#### 2.ACC 寄存器的全称与作用。

ACC 寄存器的全称为accumulator，用来储存计算产生的中间结果

#### 3.用“LOD #3”指令的执行过程，解释Fetch-Execute周期。

![](http://m.qpic.cn/psb?/V10TtYkp2MvHv1/IXusEduux4Ww9JBmgLFzOti6i0lYQC4uZXIkiMsR5eg!/b/dFMBAAAAAAAA&bo=bwKLAQAAAAACF9Q!&rf=viewer_4)

取得指令：从PC中获取指令地址，PC加2，再通过总线从内存中获取指令“LOD #3”，将指令送到IR中

解码指令：Decoder将IR内的指令译成机器语言“00010100 00000011”

执行指令：MUX根据Decoder结果通过总线获取IR中的数据“3”，送到ALU中进行运算

储存结果：将计算产生的中间结果“3”存储到ACC中

#### 4.用“ADD W” 指令的执行过程，解释Fetch-Execute周期。

![](http://m.qpic.cn/psb?/V10TtYkp2MvHv1/NJ12*9hXTeH8HC46OKyQ5kJscBJ.z8KAoo4g6g2ni3o!/b/dDcBAAAAAAAA&bo=bwKLAQAAAAACF9Q!&rf=viewer_4)

取得指令：从PC中获取指令地址，PC加2，再通过总线从内存中获取指令“ADD W”，将指令送到IR中

解码指令：Decoder将IR内的指令译成机器语言“00000000 10000000”

执行指令：MUX根据Decoder结果通过总线获取IR中W的地址“10000000”，再通过总线从内存中获取W的值，送到ALU中进行运算

储存结果：将计算产生的中间结果“3”存储到ACC中

#### 5.“LOD #3” 与 “ADD W” 指令的执行在Fetch-Execute周期级别，有什么不同。

“LOD #3”为单周期指令，在取指令周期中，指令取出到指令寄存器后，立即译码执行，不再需要其它的机器周期。“ADD W”为双周期指令，指令译码后，还需要从内存中获取数据，有两个机器周期。

### （3）点击“Binary”,观察回答下面问题：

![](http://m.qpic.cn/psb?/V10TtYkp2MvHv1/vmhg.nhYmAbyM7W*f7tRPWWOODM2tnQoX6wwJ6tKNv8!/b/dFQBAAAAAAAA&bo=fQKLAQAAAAADF8c!&rf=viewer_4)

#### 1.写出指令 “LOD #7” 的二进制形式，按指令结构，解释每部分的含义。

“LOD #7” 的二进制形式为“00010100 00000111”

“00010100”为指令说明符，第四位为寻址模式，“1”表示操作数是数值，后四位为操作码，“0100”表示该操作为“LOD”

“00000111”为操作数说明符，根据寻址模式此为数值，“00000111”表示数值“7”

#### 2.解释 RAM 的地址。

RAM电路由地址译码器、存储矩阵和读写控制电路三部分组成

存储矩阵由触发器排列而成，每个触发器能存储一位数据(0或1)。通常将每一组存储单元编为一个地址，存放一个“字”；每个字的位数等于这一组单元的数目。地址译码器将每个输入的地址代码译成高(或低)电平信号，从存储矩阵中选中一组单元，使之与读写控制电路接通。在读写控制信号的配合下，将数据读出或写入

所以RAM中的地址表示为一组高(或低)的电平信号

#### 3.该机器CPU是几位的？（按累加器的位数）

累加器为8位；CPU最多同时寄存和处理16位二进制数，所以是16位

#### 4.写出该程序对应的 C语言表达。

```c
int w = 3;
int x = 7;
int y = x + w;
```

## 任务 2：简单循环

### （1） 输入程序Program 2，运行并回答问题：

![](http://m.qpic.cn/psb?/V10TtYkp2MvHv1/IyIQiQn324QsEVFqz*PK6kvCBVSvgX0iFpe.RbUUfAQ!/b/dDQBAAAAAAAA&bo=NgZIAgAAAAADF0g!&rf=viewer_4)

![](http://m.qpic.cn/psb?/V10TtYkp2MvHv1/QghXnOxzWLpjSsVxDAI6UUmKUKjZgoEaLxaLlYXqA74!/b/dDYBAAAAAAAA&bo=fQKSAQAAAAADF94!&rf=viewer_4)

#### 1.用一句话总结程序的功能

将 x 从 3 不断减一，直到 x = 1

#### 2.写出对应的 c 语言程序

```c
int x = 3;
while(x-1 > 0)
    x--;
```

### （2） 修改该程序，用机器语言实现 10+9+8+..1 ，输出结果存放于内存 Y

![](http://m.qpic.cn/psb?/V10TtYkp2MvHv1/Uaonensxfvs0K8QzXyEqjvQ2AwTBTJArUfNo9ArvoO4!/b/dFMBAAAAAAAA&bo=YAKTAQAAAAACN.M!&rf=viewer_4)

#### 1.写出 c 语言的计算过程

```c
int y = 0;
int x = 10;
while(x > 0) {
    y += x;
    x--;
}
```

#### 2.写出机器语言的计算过程

00010100 00000000

00000101 10000010

00010100 00001010

00000101 10000001

00000000 10000010

00000101 10000010

00000100 10000001

00010001 00000001

00000101 10000001

00001101 00010110

00001100 00001000

00001111 00000000

#### 3.用自己的语言，简单总结高级语言与机器语言的区别与联系。

高级语言和机器语言都能用于编写程序，实现顺序，选择，循环执行

高级语言面向人类，符合人类语法，便于理解接受

机器语言面向机器，是计算机唯一能直接执行的语言，由二进制码组成，繁琐枯燥，不适于人类阅读


## 实验小结

**（1）理解了机器语言的构成与编写**

**（2）理解了指令周期及其执行**

**（3）理解了CPU的组成，作用及如何运行**