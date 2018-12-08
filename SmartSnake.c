#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

#define SNAKE_MAX_LENGTH 20    
#define SNAKE_HEAD 'H'
#define SNAKE_BODY 'X'
#define BLANK_CELL ' '
#define SNAKE_FOOD '$'
#define WALL_CELL '*'

void sigroutine(int signo);
char whereGoNext(int Hx,int Hy,int Fx,int Fy);
int calculate_distance(int Hx,int Hy,int Fx,int Fy);
void snakeMove(int, int);       
void put_food(void);
void output(void); 
void gameover(void);

char map[12][12] = 
	{"************",
	"*XXXXH     *",
	"*       *  *",
	"*          *",
	"*    *     *",
	"*          *",
	"* *        *",
	"*       *  *",
	"*    *     *",
	"*          *",
	"* *        *",
	"************"};
	
int snakeX[SNAKE_MAX_LENGTH] = {1, 2, 3, 4, 5};		//初始化蛇的坐标 
int snakeY[SNAKE_MAX_LENGTH] = {1, 1, 1, 1, 1};		 
int snakeLength = 5;
int foodx = 0, foody = 0;
int overflag = 1, foodflag = 1;
int score = 0;

int main(void){
	
   struct itimerval value, ovalue;
   
   printf("Game Start!\n");
   
   signal(SIGALRM, sigroutine);
   value.it_value.tv_sec = 1;
   value.it_value.tv_usec = 0;
   value.it_interval.tv_sec = 1;
   value.it_interval.tv_usec = 0;
   setitimer(ITIMER_REAL, &value, &ovalue);
   
   for(  ;overflag; );
   
   return 0;
}

void sigroutine(int signo){
	
	char instruction;
	
	put_food();	
	output();
	instruction = whereGoNext(snakeX[snakeLength - 1], snakeY[snakeLength - 1], foodx, foody); 
	switch(instruction) {						
		case 'A': {
			snakeMove(-1, 0);
			break;
		}
		case 'D': {
			snakeMove(1, 0);
			break;
		}
		case 'W': {
			snakeMove(0, -1);
			break;
		}
		case 'S': {
			snakeMove(0, 1);
			break;
		}
	}
	
	signal(SIGALRM, sigroutine);
    
	return;
}

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
	
	if(map[Hy][Hx] == ' ' || map[Hy][Hx - 1] == '$')
		return abs(Fx - (Hx - 1)) + abs(Fy - Hy);
	else
		return 9999;
}

void snakeMove(int x, int y) {
	
	int i;
	
	int previous_tailx = snakeX[0];						//记录移动前蛇尾坐标 
	int previous_taily = snakeY[0];					 
	int previous_headx = snakeX[snakeLength - 1];		//记录移动前蛇头坐标
	int previous_heady = snakeY[snakeLength - 1];	 
	
	
	for(i = 0; i < snakeLength - 1; i++) {				//坐标数组元素前移一位，去掉蛇尾坐标 
		snakeX[i] = snakeX[i + 1];
		snakeY[i] = snakeY[i + 1];
	}
	
	snakeX[snakeLength - 1] += x;				//根据传入参数确定移动后蛇头坐标 
	snakeY[snakeLength - 1] += y;
	
	int present_headx = snakeX[snakeLength - 1];
	int present_heady = snakeY[snakeLength - 1];
	
	if(map[present_heady][present_headx] == SNAKE_BODY || 		//移动后蛇头坐标为蛇身或墙壁，游戏结束
	map[present_heady][present_headx] == WALL_CELL) gameover();
	
	else if(map[present_heady][present_headx] == BLANK_CELL) {	//移动后蛇头坐标为空格 
		map[present_heady][present_headx] = SNAKE_HEAD;			//移动后蛇头坐标修改为蛇头 
		map[previous_heady][previous_headx] = SNAKE_BODY;		//移动前蛇头坐标修改为蛇身 
		map[previous_taily][previous_tailx] = BLANK_CELL;		//移动前蛇尾坐标修改为空格 
	}
	
	else if(map[present_heady][present_headx] == SNAKE_FOOD) {	//移动后蛇头坐标为食物 
		
		map[present_heady][present_headx] = SNAKE_HEAD;			//移动后蛇头坐标修改为蛇头
		map[previous_heady][previous_headx] = SNAKE_BODY;		//移动前蛇头坐标修改为蛇身
		
		snakeLength++;
		
		for(i = snakeLength - 1; i > 0; i--) {					//坐标数组后移一位 
		snakeX[i] = snakeX[i - 1];
		snakeY[i] = snakeY[i - 1];
		}
		
		snakeX[0] = previous_tailx;								//移动后蛇尾坐标 = 移动前蛇尾坐标
		snakeY[0] = previous_taily;
		
		foodflag = 1;
		
		score++;
	}
	
}

void put_food(void) {
	
	if(foodflag) {
		while(!(map[foody][foodx] == BLANK_CELL)) {				//食物坐标不为空格 
			srand((unsigned)time(0));  							//随机生成食物坐标 
			foodx = rand() % 11;
			foody = rand() % 11;	
		}
		map[foody][foodx] = SNAKE_FOOD;
		foodflag = 0;
	}
}

void output(void) {
	int i, j;
	for(i = 0; i < 12; i++) {
		for(j = 0; j < 12; j++)
			printf("%c", map[i][j]);
		printf("\n");
	}
} 

void gameover(void) {
	overflag = 0;
	printf("Game Over!\nYour score is %d\n", score);
}