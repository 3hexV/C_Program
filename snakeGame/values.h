#ifndef VALUES_H_
#define VALUES_H_

#define UP 0xe048
#define DOWN 0xe050
#define LEFT 0xe04b
#define RIGHT 0xe04d

#define ENTER 0x000d
#define ESC 0x001b
#define RUN 0x0009

#define N 100 //蛇的最大长度


struct food{
	int x;
	int y;
	int flag; //是否出现食物
}food;

struct snake{
	int x[N];
	int y[N];
	int node; //蛇的节数
	int dir; //蛇的方向
	int life; //蛇是否存活
}snake;


struct Debug{
	int level;
	int snake_dir;
	int snake_node;
	int snake_life;
	int food_x;
	int food_y;
	int food_flag;
	int snake_head_x;
	int snake_head_y;
	char keyv;
}debug;

#endif