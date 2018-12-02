# 贪吃蛇实验报告

### 一、实验目的

- 了解字符游戏的表示

- 体验自顶向下的设计方法实现问题求解

- 使用伪代码表示算法

- 使用函数抽象过程

### 二、游戏要求与表示

#### 1、玩法

贪吃蛇游戏是一款经典的益智游戏，有PC和手机等多平台版本。既简单又耐玩。该游戏通过控制蛇头方向吃蛋，从而使得蛇变得越来越长。

#### 2、游戏表示

给定一个10*10的字符矩阵表示蛇的生存空间,其中有一条长度5的蛇(HXXXX), “H”表示蛇头,“X”表示蛇身体。空间中可能有食物（“$”表示）和障碍物（“*”表示）

可以使用“ADWS”按键分别控制蛇的前进方向“左右上下”, 当蛇头碰到自己的身体或走出边界,游戏结束,否则蛇按指定方向前进一步。

### 三、编程要求

#### 1、任务1：会动的蛇

- 程序头部要求

定义良好的头部，将使得程序更加易于阅读，易于维护。包括：常数定义、函数定义等。

```C
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SNAKE_MAX_LENGTH 20    
#define SNAKE_HEAD 'H'
#define SNAKE_BODY 'X'
#define BLANK_CELL ' '
#define SNAKE_FOOD '$'
#define WALL_CELL '*'

void snakeMove(int, int);       //控制蛇的移动 
void put_food(void);            //放置食物  
void output(void);              //输出地图 
void gameover(void);            //游戏结束 

char map[12][12] = 		//初始化地图 
	{"************",
	"*XXXXH     *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"*          *",
	"************"};
	
int snakeX[SNAKE_MAX_LENGTH] = {1, 2, 3, 4, 5};		//初始化蛇的坐标 
int snakeY[SNAKE_MAX_LENGTH] = {1, 1, 1, 1, 1};		 
int snakeLength = 5;
int overflag = 1, foodflag = 1;
int score = 0;

```
- 程序结构

程序总体结构必须严格符合以下伪代码框架 ::

	输出字符矩阵
	WHILE not 游戏结束 DO
		ch＝等待输入
		CASE ch DO
		‘A’:左前进一步，break 
		‘D’:右前进一步，break    
		‘W’:上前进一步，break    
		‘S’:下前进一步，break    
		END CASE
		输出字符矩阵
	END WHILE
	输出 Game Over!!! 

```C
int main(void) {
	
	char instruction;
	
	printf("Game Start!\n");
	while(overflag) {
		output();			//输出地图 
		instruction = getchar();	//获得指令 
		getchar();
		switch(instruction) {		//控制蛇的移动
			case 'A': snakeMove(-1, 0);break;
			case 'D': snakeMove(1, 0);break;
			case 'W': snakeMove(0, -1);break;
			case 'S': snakeMove(0, 1);break;
		}
	}
	return 0;
}
```

- 编程建议（自顶向下，逐步求精）

1. 先按伪代码写好总控（main）代码。

2. 所有函数都是 print 或 简单的语句。 例如： snakeMove 仅需要写几句，输出上下左右即可

3. 逐步完成涉及的函数

#### 2、任务2：会吃的蛇

- 功能需求：

1. snake 头撞到身体、障碍（边界或你在地图中定义） 游戏结束

2. snake 头吃到食物，snake就长一节



- 细化并完善随机放置食物的伪代码

1. 找一个空白位置

2. 在该位置放置食物
```
WHILE(place is not blank)

placeX = random number
placeY = random number

END WHILE

place = FOOD

```
```C
void put_food(void) {
	
	int foodx = 0, foody = 0;
	
	if(foodflag) {
		while(!(map[foody][foodx] == BLANK_CELL)) {	//食物坐标不为空格 
			srand((unsigned)time(0));  		//随机生成食物坐标 
			foodx = rand() % 11;
			foody = rand() % 11;	
		}
		map[foody][foodx] = SNAKE_FOOD;
		foodflag = 0;
	}
}
```

- 需要进一步细化的代码：

1. 蛇头撞到身体、障碍物 … …

2. 蛇头撞到食物 … …

3. 蛇头进入一个空位置 … … 

```C
void snakeMove(int x, int y) {
	
	int i;
	
	int previous_tailx = snakeX[0];			//记录移动前蛇尾坐标 
	int previous_taily = snakeY[0];					 
	int previous_headx = snakeX[snakeLength - 1];	//记录移动前蛇头坐标
	int previous_heady = snakeY[snakeLength - 1];	 
	
	
	for(i = 0; i < snakeLength - 1; i++) {		//坐标数组元素前移一位，去掉蛇尾坐标 
		snakeX[i] = snakeX[i + 1];
		snakeY[i] = snakeY[i + 1];
	}
	
	snakeX[snakeLength - 1] += x;			//根据传入参数确定移动后蛇头坐标 
	snakeY[snakeLength - 1] += y;
	
	int present_headx = snakeX[snakeLength - 1];
	int present_heady = snakeY[snakeLength - 1];
	
	if(map[present_heady][present_headx] == SNAKE_BODY || 		//移动后蛇头坐标为蛇身或墙壁，游戏结束
	map[present_heady][present_headx] == WALL_CELL) gameover();
	
	else if(map[present_heady][present_headx] == BLANK_CELL) {	//移动后蛇头坐标为空格 
		map[present_heady][present_headx] = SNAKE_HEAD;		//移动后蛇头坐标修改为蛇头 
		map[previous_heady][previous_headx] = SNAKE_BODY;	//移动前蛇头坐标修改为蛇身 
		map[previous_taily][previous_tailx] = BLANK_CELL;	//移动前蛇尾坐标修改为空格 
	}
	
	else if(map[present_heady][present_headx] == SNAKE_FOOD) {	//移动后蛇头坐标为食物 
		
		map[present_heady][present_headx] = SNAKE_HEAD;		//移动后蛇头坐标修改为蛇头
		map[previous_heady][previous_headx] = SNAKE_BODY;	//移动前蛇头坐标修改为蛇身
		
		snakeLength++;
		
		for(i = snakeLength - 1; i > 0; i--) {	//坐标数组后移一位 
		snakeX[i] = snakeX[i - 1];
		snakeY[i] = snakeY[i - 1];
		}
		
		snakeX[0] = previous_tailx;		//移动后蛇尾坐标 = 移动前蛇尾坐标
		snakeY[0] = previous_taily;
		
		foodflag = 1;
		
		score++;
	}
	
}
```