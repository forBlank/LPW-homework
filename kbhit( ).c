#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <termios.h>
#include <unistd.h>

#define SNAKE_MAX_LENGTH 20    
#define SNAKE_HEAD 'H'
#define SNAKE_BODY 'X'
#define BLANK_CELL ' '
#define SNAKE_FOOD '$'
#define WALL_CELL '*'

char map[12][12] =  
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
	
int snakeX[SNAKE_MAX_LENGTH] = {1, 2, 3, 4, 5}; 
int snakeY[SNAKE_MAX_LENGTH] = {1, 1, 1, 1, 1};		 
int snakeLength = 5;
int overflag = 1, foodflag = 1;
int score = 0;


static struct termios ori_attr, cur_attr;

static __inline 
int tty_reset(void)
{
        if (tcsetattr(STDIN_FILENO, TCSANOW, &ori_attr) != 0)
                return -1;

        return 0;
}


static __inline
int tty_set(void)
{
        
        if ( tcgetattr(STDIN_FILENO, &ori_attr) )
                return -1;
        
        memcpy(&cur_attr, &ori_attr, sizeof(cur_attr) );
        cur_attr.c_lflag &= ~ICANON;
//        cur_attr.c_lflag |= ECHO;
        cur_attr.c_lflag &= ~ECHO;
        cur_attr.c_cc[VMIN] = 1;
        cur_attr.c_cc[VTIME] = 0;

        if (tcsetattr(STDIN_FILENO, TCSANOW, &cur_attr) != 0)
                return -1;

        return 0;
}

static __inline
int kbhit(void) 
{
                   
        fd_set rfds;
        struct timeval tv;
        int retval;

        /* Watch stdin (fd 0) to see when it has input. */
        FD_ZERO(&rfds);
        FD_SET(0, &rfds);
        /* Wait up to five seconds. */
        tv.tv_sec  = 0;
        tv.tv_usec = 0;

        retval = select(1, &rfds, NULL, NULL, &tv);
        /* Don't rely on the value of tv now! */

        if (retval == -1) {
                perror("select()");
                return 0;
        } else if (retval)
                return 1;
        /* FD_ISSET(0, &rfds) will be true. */
        else
                return 0;
        return 0;
}

void snakeMove(int x, int y) {
	
	int i;
	
	int previous_tailx = snakeX[0];	
	int previous_taily = snakeY[0];					 
	int previous_headx = snakeX[snakeLength - 1];
	int previous_heady = snakeY[snakeLength - 1];	 
	
	
	for(i = 0; i < snakeLength - 1; i++) { 
		snakeX[i] = snakeX[i + 1];
		snakeY[i] = snakeY[i + 1];
	}
	
	snakeX[snakeLength - 1] += x; 
	snakeY[snakeLength - 1] += y;
	
	int present_headx = snakeX[snakeLength - 1];
	int present_heady = snakeY[snakeLength - 1];
	
	if(map[present_heady][present_headx] == SNAKE_BODY || 
	map[present_heady][present_headx] == WALL_CELL) gameover();
	
	else if(map[present_heady][present_headx] == BLANK_CELL) { 
		map[present_heady][present_headx] = SNAKE_HEAD;	 
		map[previous_heady][previous_headx] = SNAKE_BODY;
		map[previous_taily][previous_tailx] = BLANK_CELL;
	}
	
	else if(map[present_heady][present_headx] == SNAKE_FOOD) {
		
		map[present_heady][present_headx] = SNAKE_HEAD;	
		map[previous_heady][previous_headx] = SNAKE_BODY;
		
		snakeLength++;
		
		for(i = snakeLength - 1; i > 0; i--) {
		snakeX[i] = snakeX[i - 1];
		snakeY[i] = snakeY[i - 1];
		}
		
		snakeX[0] = previous_tailx;
		snakeY[0] = previous_taily;
		
		foodflag = 1;
		
		score++;
	}
	
}

void put_food(void) {
	
	int foodx = 0, foody = 0;
	
	if(foodflag) {
		while(!(map[foody][foodx] == BLANK_CELL)) {
			srand((unsigned)time(0));
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

int main()
{
        //设置终端进入非缓冲状态
        int tty_set_flag;
        tty_set_flag = tty_set();

		char instruction;
	
		printf("Game Start!\n");
		while(overflag) {
			put_food();
			output();
			instruction = getchar(); 
			getchar();
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
		}
		
        printf("pressed `q` to quit!\n");
        while(1) {

                if( kbhit() ) {
                        const int key = getchar();
                        printf("%c pressed\n", key);
                        if(key == 'q')
                                break;
                } else {
                       ;// fprintf(stderr, "<no key detected>\n");
                }
        }

        //恢复终端设置
        if(tty_set_flag == 0) 
                tty_reset();
        return 0;
}