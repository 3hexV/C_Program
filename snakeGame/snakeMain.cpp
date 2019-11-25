#include <graphics.h>      // 引用图形库头文件
#include <stdio.h>
#include <conio.h>
#include <windows.h>	
#include "values.h"
#include <stdlib.h>
#include <time.h>


void GameV();
int GetKeyBoard();
char WhatKeyPress(int kv);
void Num_String(int num);

void GameOver(); //游戏结束
int Play(); //玩游戏的过程
void dwall(); //画墙
void wall(int x, int y, int dir); //画组成墙的砖
int Speed(); //获取速度
void ddebug();
void dsnake(int x, int y, int node);
void dfood(int x, int y);
void END(int how);

char tmp[100];

void main()
{	
	int speed = 0;

	GameV();
//	wall(100,100,1);
//	wall(100,150,2);
//	wall(100,200,3);
//	wall(100,250,4);
	
	speed = Speed(); //获取速度
	//初始化数据
	debug.level = speed;
	
	dwall();
	ddebug();

	Play();
	_getch();
	closegraph();

//	while(1){
//		printf("请从键盘输入：\n");
//		ch = WhatKeyPress(GetKeyBoard());
//		printf("KeyBoard_Value: %c\n",ch);
//	}
}

int Play(){
	int last[2];
	char ch;

	snake.x[0] = 210;
	snake.y[0] = 350;
	snake.x[1] = 200;
	snake.y[1] = 350;
	snake.node = 2;
	snake.dir = 1;
	snake.life = 0;

	food.flag = 1;

	ddebug();

	for(int i=0;i<snake.node;i++)
	{
		if (i==0){
			dsnake(snake.x[i],snake.y[i],1);
		}else
		{
			dsnake(snake.x[i],snake.y[i],2);
		}
	}

	srand((unsigned long)time(0));

	do
	{
		while(!kbhit())
		{
			Sleep((3 - debug.level)*100+100);

			if(food.flag == 1)
			{
				do{
					food.x = rand()%200+100;
					food.y = rand()%200+100;
					food.flag = 0;
				}while(!((food.x%10 ==0)&&(food.y%10 ==0)&&(food.y>210)&&(food.x>20)&&(food.x<480)&&(food.y<480)));
			}

			if (food.flag == 0)
			{
				dfood(food.x, food.y);
			}


			if((snake.x[0]==food.x)&&(snake.y[0]==food.y))
			{
				dsnake(food.x,food.y,3);
				food.flag = 1;
				snake.node++;
				snake.x[snake.node-1] = snake.x[snake.node-1]-10;
				snake.y[snake.node-1] = snake.y[snake.node-1];
			}


			last[0] = snake.x[snake.node-1];
			last[1] = snake.y[snake.node-1];

			for(i=snake.node-1;i>0;i--)
			{
				snake.x[i] = snake.x[i-1];
				snake.y[i] = snake.y[i-1];
			}
			

			switch(snake.dir)
			{
				case 1: snake.x[0] += 10; break;
				case 2: snake.x[0] -= 10; break;
				case 3: snake.y[0] -= 10; break;
				case 4: snake.y[0] += 10; break;
			}

			if (snake.life == 1) break;
		
//			printf("SX: %d\n", snake.x[0]);
//			printf("SY: %d\n", snake.y[0]);

			for(int i=0;i<snake.node;i++)
			{
				if (i==0){
					dsnake(snake.x[i],snake.y[i],1);
				}else
				{
					dsnake(snake.x[i],snake.y[i],2);
				}
			}
			dsnake(last[0],last[1],3);

			if(snake.node==N){
				goto win;
			}

			if ((snake.x[0]>=480)||(snake.y[0]>=480)||(snake.x[0]<20)||(snake.y[0]<160)) 
			{
				snake.life = 1;
				break;
			}

			for(i=3;i<snake.node;i++)
			{
				if((snake.x[0]==snake.x[i])&&(snake.y[0]==snake.y[i]))
				{
					snake.life = 1;
					printf("EAT me");
					break;
				}
			}

			ddebug();
		}
		ch = WhatKeyPress(GetKeyBoard());
		
		debug.keyv = ch;

		if ((ch=='U')&&(snake.dir!=4)){
			snake.dir = 3;
		}else if ((ch=='D')&&(snake.dir!=3)){
			snake.dir = 4;
		}else if ((ch=='L')&&(snake.dir!=1)){
			snake.dir = 2;
		}else if ((ch=='R')&&(snake.dir!=2)){
			snake.dir = 1;
		}else if (ch=='E')
		{
			snake.life = 1;
		}

	}while(snake.life==0);
	printf("Game Over!");
	END(2);

	return 0;
	win:
	END(1);
	return 0;
}

void END(int how){
	if(how==1){
		cleardevice();
		outtextxy(150,350,"你赢了！");
	}else if(how==2)
	{
		cleardevice();
		outtextxy(150,350,"你输了！");
	}
}

void dfood(int x, int y){
	int size_x = 9;
	int size_y = 9;
	setlinecolor(WHITE);
	setfillcolor(WHITE);
	fillrectangle(x,y,x+size_x,y+size_y);
}

void dsnake(int x, int y, int node){
	int size_x = 9;
	int size_y = 9;
	int deep = 5;

	//头
	if (node == 1){
		setlinecolor(BLACK);
		setfillcolor(RED);
		fillrectangle(x,y,x+size_x,y+size_y);
		setlinecolor(WHITE);
		setfillcolor(WHITE);
		fillcircle(x+size_x/2,y+size_y/2,1);
	}
	// 尾部
	else if (node == 2){
		setlinecolor(BLACK);
		setfillcolor(RED);
		fillrectangle(x,y,x+size_x,y+size_y);
	}
	// 清空
	else
	{
		setlinecolor(BLACK);
		setfillcolor(BLACK);
		fillrectangle(x,y,x+size_x,y+size_y);
	}
}

void ddebug(){
	int lan1=0,lan2=120,lan3=280, step=80;

	debug.snake_dir = snake.dir;
	debug.snake_head_x = snake.x[0];
	debug.snake_head_y = snake.y[0];
	debug.snake_life = snake.life;
	debug.snake_node = snake.node;
	debug.food_x = food.x;
	debug.food_y = food.y;
	debug.food_flag = food.flag;

	//第一栏信息
	outtextxy(lan1,0, "游戏难度:");

	Num_String(debug.level);
	outtextxy(lan1+step,0,tmp);

	outtextxy(lan1,30, "你按下的键位:");
	outtextxy(lan1+step/2,60,"  ");
	outtextxy(lan1+step/2,60,debug.keyv);

	//第二栏信息
	outtextxy(lan2,0, "蛇头方向:");
	Num_String(debug.snake_dir);
	outtextxy(lan2+step,0,"   ");
	outtextxy(lan2+step,0,tmp);
	switch(debug.snake_dir){
	case 1: {
				outtextxy(lan2+step+20,0,"   ");
				outtextxy(lan2+step+20,0,"右");
				break;
			}
	case 2: {
				outtextxy(lan2+step+20,0,"   ");
				outtextxy(lan2+step+20,0,"左");
				break;
			}
	case 3: {
				outtextxy(lan2+step+20,0,"   ");
				outtextxy(lan2+step+20,0,"上");
				break;
			}
	case 4: {
				outtextxy(lan2+step+20,0,"   ");
				outtextxy(lan2+step+20,0,"下");
				break;
			}
	}

	outtextxy(lan2,30, "蛇的长度:");
	Num_String(debug.snake_node);
	outtextxy(lan2+step,30,"        ");
	outtextxy(lan2+step,30,tmp);

	outtextxy(lan2,60, "蛇头坐标:");
	Num_String(debug.snake_head_x);
	outtextxy(lan2+step,60,"        ");
	outtextxy(lan2+step,60,tmp);

	Num_String(debug.snake_head_y);
	outtextxy(lan2+step+40,60,"       ");
	outtextxy(lan2+step+40,60,tmp);

	//第三栏信息
	outtextxy(lan3,0, "食物标志:");
	Num_String(debug.food_flag);
	outtextxy(lan3+step,0,"        ");
	outtextxy(lan3+step,0,tmp);

	outtextxy(lan3,30, "食物坐标:");
	Num_String(debug.food_x);
	outtextxy(lan3+step,30,"        ");
	outtextxy(lan3+step,30,tmp);

	Num_String(debug.food_y);
	outtextxy(lan3+step+40,30,"        ");
	outtextxy(lan3+step+40,30,tmp);
}

void dwall(){
	cleardevice();
	int i,j,k,l;
	//左边的砖
	for(i=150;i<500;i+=10){
		wall(0,i,3);
	}
	//右边的砖
	for(j=150;j<500;j+=10){
		wall(490,j,4);
	}
	//上面的砖
	for(k=0;k<500;k+=10){
		wall(k,150,1);
	}
	//下面的砖
	for(l=0;l<500;l+=10){
		wall(l,490,2);
	}
}


void wall(int x, int y, int dir){
	int size_x = 9;
	int size_y = 9;
	int deep = 5;

	setlinecolor(WHITE);
	setfillcolor(LIGHTBLUE);
	fillrectangle(x,y,x+size_x,y+size_y);

	setlinestyle(PS_SOLID | PS_ENDCAP_SQUARE, 2);
	//上面的砖头
	if (dir == 1){
	line(x,y+size_y,x+size_x-deep,y+size_y);//砖的下面

	setlinecolor(BLUE);
	line(x,y,x,y+size_y); //砖左面
	line(x,y,x+size_x,y); //砖的上面
	line(x+size_x,y,x+size_x,y+size_y);//砖右面

	}
	//下面的砖头
	else if (dir==2){
		line(x,y,x+size_x,y);

		setlinecolor(BLUE);
		line(x,y,x,y+size_y);
		line(x+size_x,y,x+size_x,y+size_y);
		line(x,y+size_y,x+size_x,y+size_y);
	}
	//左面的砖头
	else if (dir==3){
		line(x,y+size_y,x+size_x-deep,y+size_y);
		line(x+size_x,y,x+size_x,y+size_y);

		setlinecolor(BLUE);
		line(x,y,x+size_x,y);
		line(x,y,x,y+size_y);
	}
	//右面的砖头
	else if (dir==4){
		line(x,y+size_y,x+size_x-deep,y+size_y);
		line(x,y,x,y+size_y);

		setlinecolor(BLUE);
		line(x,y,x+size_x,y);
		line(x+size_x,y,x+size_x,y+size_y);	
	}	
}

int Speed(){
	int d_v = 100;
	char ch;
	cleardevice();
	outtextxy(150,50, "请选择游戏难度：");
	outtextxy(150,400, "上下箭头选择，Ente确认");
	outtextxy(150,100, "Level 1");
	outtextxy(150,150, "Level 2");
	outtextxy(150,200, "Level 3");
	outtextxy(250,d_v, "<-");
	ch = WhatKeyPress(GetKeyBoard());
	while(1)
	{
		switch(ch){
		case 'D': d_v+=50; break;
		case 'U': d_v-=50; break;
		case 'T': goto game_bein;
		case 'E': goto game_exit;
		}
		
		if (d_v == 250) d_v = 100;
		if (d_v == 50) d_v = 200;

		outtextxy(250,100, "   ");
		outtextxy(250,150, "   ");
		outtextxy(250,200, "   ");
		outtextxy(250,d_v, "<-");

		ch = WhatKeyPress(GetKeyBoard());
		printf("%c\n",ch);
	}

	game_bein:
	cleardevice();
	switch(d_v){
	case 100: {
				outtextxy(150,50, "Grade: Level 1");
				return 1;
			  }
	case 150: {
				outtextxy(150,50, "Grade: Level 2");
				return 2;
			  }
	case 200: {
				outtextxy(150,50, "Grade: Level 3");
				return 3;
			  }
	default:{
				outtextxy(150,50, "Error: 1");
				return 0;
			}
	}
	game_exit:
		closegraph();
}

void GameV(){
	initgraph(500,500, SHOWCONSOLE | NOMINIMIZE);
	outtextxy(150, 50, "贪吃蛇...");
	
	outtextxy(150, 200, "请按下任意键开始！");
	_getch();
}


int GetKeyBoard(){
	int ch,ch2;
	ch = _getch();
	//	printf("--->%x\n",ch);
	if ((ch&0xff) == 0xe0){
		printf("again:\n");
		ch2 = _getch();
		return (ch<<8|ch2);
	}else{
		return ch;
	}
	
}

char WhatKeyPress(int kv){
	switch(kv){
	case UP: return 'U';
	case DOWN: return 'D';
	case LEFT: return 'L';
	case RIGHT: return 'R';

	case ENTER: return 'T';
	case ESC: return 'E';
	case RUN: return 'R';
	default: return 'N';	
	}
}	

void Num_String(int num){
	int num_tmp=0,i=0,len=0;
	tmp[0] = '\0';
	while(num!=0){
		num_tmp = num%10;
		tmp[i] = num_tmp + '0';
		num /= 10;
		i++;
	}
	tmp[i] = '\0';
	//	printf("tmp = %s\n",tmp);
	len = i;
	//	printf("len = %d\n",len);
	for(i=0;i<len/2;i++)
	{
		//	printf("i: %d %c %c\n",i, tmp[i], tmp[len-1-i]);
		tmp[i] ^= tmp[len-1-i];
		tmp[len-1-i] = tmp[i] ^ tmp[len-1-i];
		tmp[i] = tmp[i] ^ tmp[len-1-i];
	}
}