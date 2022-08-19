#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#include <math.h>
//#include <winuser.h>
#include "main.h"
#include "gui_menu_tool.h"

short cur_block_coord_x ,cur_block_coord_y; //当前方块的横坐标及纵坐标
int blockRandColor = 0, colorCount=0;
int nowLevel = DEF_LEVEL;

//int game_arr[UI_HEIGHT][UI_WIDTH]; //游戏的界面数组
short next_blockarr[4][4];			//用来存放下一个方块的数组
short cur_boxindex,next_boxindex; //记录当前方块的下标和下一个方块的下标
int score;  //成绩
char player_name[10] = "3hex" ;    //玩家的姓名
HANDLE hOutput;

int levelSpeed[11] = {30,25,21,17,14,11,8,5,3,1,0};

ST_BLOCK block[19]= {
	//初始化各个游戏方块, 总共有19总方块形状
	{1,1,1,2,1,3,2,3,1},
	{0,2,1,2,2,2,0,3,2},
	{0,1,1,1,1,2,1,3,3},
	{2,1,0,2,1,2,2,2,0},
	{1,1,1,2,0,3,1,3,5},
	{0,1,0,2,1,2,2,2,6},
	{1,1,2,1,1,2,1,3,7},
	{0,2,1,2,2,2,2,3,4},
	{1,1,0,2,1,2,2,2,9},
	{1,1,1,2,2,2,1,3,10},
	{0,2,1,2,2,2,1,3,11},
	{1,1,0,2,1,2,1,3,8},
	{1,1,1,2,2,2,2,3,13},
	{1,2,2,2,0,3,1,3,12},
	{2,1,1,2,2,2,1,3,15},
	{0,2,1,2,1,3,2,3,14},
	{1,0,1,1,1,2,1,3,17},
	{0,2,1,2,2,2,3,2,16},
	{1,1,2,1,1,2,2,2,18},
};

int GMT_F_Array[COLOR_LEN] = {GMT_F_HALF_BLUE, GMT_F_HALF_GREEN,
                              GMT_F_HALF_LIGHT_BLUE, GMT_F_HALF_RED,
                              GMT_F_HALF_PURPLE, GMT_F_HALF_YELLOW, GMT_F_HALF_GRAY,
                              GMT_F_BLUE, GMT_F_GREEN, GMT_F_LIGHT_BLUE,
                              GMT_F_RED, GMT_F_PURPLE
                             };

void main() {
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTitle(TEXT("俄罗斯方块"));

	srand((unsigned int)time(NULL));

	SMALL_RECT rc = {0,0,UI_WIDTH*3+15,UI_HEIGHT+3};  //设置窗口大小，宽度和高度
	SetConsoleWindowInfo(hOutput,TRUE,&rc);
	srand(time(NULL));

GMMenu:
	// 游戏开始菜单
	switch(gameMainMenu()){
		case -1:
			exit(0);
			break;
		case 1:
			break;
		case 2:
			drawDes(); 
			goto GMMenu;
	}

	initia();
	//隐藏缓冲区的光标
	CONSOLE_CURSOR_INFO cci;
	cci.bVisible = 0;
	cci.dwSize =1;
	SetConsoleCursorInfo(hOutput, &cci);

	produceBlock();
	moveBlock();
}
void initia() {
	//初始化的一些工作
	short i,j;
	
	for(i = 0; i < UI_HEIGHT; i++) {
		for(j = 0; j < UI_WIDTH; j++) {
			if(i == 0 || i == UI_HEIGHT-1) {
				game_arr[i][j].info = WALL;    //.var=1表示该点被占用
				game_arr[i][j].var = 1;
				continue;
			}
			if(j == 0 || j == UI_WIDTH-1)  {
				game_arr[i][j].info = WALL;
				game_arr[i][j].var = 1;
				continue;
			}
		}
	}
	//printf("\n\n\t欢迎你的到来\n\t请您输入一个昵称吧!>:");
	//scanf("%s",&player_name);
	next_boxindex =  rand() % 19;	 //第一次要随机产生两个方块
}

void drawDes(void) {
	short i,j;

	system("cls");
	
	setConsoleTextColor(GMT_B_BLACK, GMT_F_WHITE);
	printf("\n\n\n\n\t\t    ▉▉▉▉▉▉▉▉▉▉▇▆▅▃▂\n");
	setConsoleTextColor(GMT_B_BLACK, GMT_F_BLUE);
	printf("\t\t    ▉ 俄 罗 斯 方 块 ▉▇▆▅▃▂\n");
	setConsoleTextColor(GMT_B_BLACK, GMT_F_RED);
	printf("\t\t    ▉▉▉▉▉▉▉▉▉▉▇▆▅▃▂\n\n\n");
	resetAll();

	for(i = 0; i < UI_HEIGHT; i++) {
		if(i==2) {
			printf("\t\t①通过固定方向按键操作方块移动和旋转\n\n");
		}else if(i==4){
			printf("\t\t②使用游戏中使用Space进行暂停和恢复\n\n");
		}else if(i==6){
			printf("\t\t③游戏难度随得分增加而增加，共11级难度\n\n");
		}else if(i==8){
			printf("\t\t祝您游戏愉快！任意键返回主菜单...");
		}
	}
	fflush(stdin);
	getchar();
}


void drawMainMenu(int nowIndex) {
	short i,j;

	system("cls");
	
	setConsoleTextColor(GMT_B_BLACK, GMT_F_WHITE);
	printf("\n\n\n\n\t\t    ▉▉▉▉▉▉▉▉▉▉▇▆▅▃▂\n");
	setConsoleTextColor(GMT_B_BLACK, GMT_F_BLUE);
	printf("\t\t    ▉ 俄 罗 斯 方 块 ▉▇▆▅▃▂\n");
	setConsoleTextColor(GMT_B_BLACK, GMT_F_RED);
	printf("\t\t    ▉▉▉▉▉▉▉▉▉▉▇▆▅▃▂\n\n\n");
	resetAll();

	for(i = 0; i < UI_HEIGHT; i++) {
		if(i==2) {
			if(nowIndex == 1) {
				setConsoleTextColor(GMT_B_WHITE, GMT_F_RED);
				puts("\t\t\t >> 1.开始游戏  ");
				resetAll();
			} else {
				puts("\t\t\t     1.开始游戏  ");
			}
		} else if(i==4) {
			if(nowIndex == 2) {
				setConsoleTextColor(GMT_B_WHITE, GMT_F_RED);
				puts("\t\t\t >> 2.游戏介绍  ");
				resetAll();
			} else {
				puts("\t\t\t     2.游戏介绍  ");
			}
		} else if(i==6) {
			if(nowIndex == 3) {
				setConsoleTextColor(GMT_B_WHITE, GMT_F_RED);
				puts("\t\t\t >> 3.退出游戏  ");
				resetAll();
			} else {
				puts("\t\t\t     3.退出游戏  ");
			}
		} else if(i==7) 	puts("\n\n\n\t\t       ↑↓键位选择，Enter确定  ");
		else if(i==8)   break;
	}

	printf("    			\n\
						(           \n\
					     ︶(.)︵	  	\n \
					       /)		  	\n \
					       \\ ︵︶		\n \
					  ︶︵ |/			\n \
					      \\|			\n \
					       |	3hex.\n");

}

int gameMainMenu(void) {
	int nowIndex=1;
	int ch = _VK_ENTER;
	drawMainMenu(nowIndex);
GBAgain:
	//fflush(stdin);
	while(ch = getch()) { //用户按键
		//printf("%#X\t", getch());
		//fflush(stdin);
		switch(ch) {
			case _VK_UP:
				nowIndex--;
				if(nowIndex==0) nowIndex = 3;
				break;
			case _VK_DOWN:
				nowIndex++;
				if(nowIndex==4) nowIndex = 1;
				break;
			case _VK_ENTER:
				if(nowIndex == 1) return 1;
				else if(nowIndex == 2) return 2;
				else if(nowIndex == 3) return -1;
				return 0;
			default:
				goto GBAgain;
		}
		// 刷新界面
		drawMainMenu(nowIndex);
	}

}

/*游戏显示界面*/
void gameShow() {
	//1显示边框，空格，方块
	short i,j;
	system("cls");
	puts("\n\t\t<俄罗斯方块>");
	for(i = 0; i < UI_HEIGHT; i++) {
		for(j = 0; j < UI_WIDTH; j++) {
			if(game_arr[i][j].info == 0) {
				printf(GAME_DIV);
				continue;
			}
			if(game_arr[i][j].info == WALL) {
				if(i == 0 || i == UI_HEIGHT-1) printf(GAME_WALL_W);//画横
				else printf(GAME_WALL_H);
				continue;
			}
			if(game_arr[i][j].info == BLOCK) {
				setConsoleTextColor(GMT_B_WHITE, blockRandColor);
				printf(GAME_BLOCK);
				resetAll();
			}
		}
		if(i == 1)  printf("\t下一个方块");
		if(i >= 2 && i <= 5) { //下一个方块
			printf("\t");
			for(j = 0; j < 4; j++) {
				if(next_blockarr[i-2][j] == 0) printf("  "); //要减2，因为从i事从2开始的
				else {
					setConsoleTextColor(GMT_B_WHITE, (blockRandColor+1)%COLOR_LEN);
					printf(GAME_BLOCK);
					resetAll();
				}
			}
		}
		if(i==9)    printf("\t当前难度：%d",nowLevel);
		if(i == 10) printf("\t玩家：%s",player_name);
		if(i == 11) printf("\t得分：%d",score);
		if(i == UI_HEIGHT-7) printf("\t游戏操作");
		if(i == UI_HEIGHT-5) printf("\t↑旋转\tSpace 暂停");
		if(i == UI_HEIGHT-4) printf("\t←左移\t Esc  退出");
		if(i == UI_HEIGHT-3) printf("\t→右移");
		if(i == UI_HEIGHT-2) printf("\t↓下移");
		printf("\n");
	}
}
/*每一个方块的产生*/
void produceBlock() {
	//在游戏界面的中间放置方块
	short i,j;

	blockRandColor = GMT_F_Array[(colorCount++)%COLOR_LEN]; // 随机颜色

	cur_boxindex = next_boxindex;
	next_boxindex = rand() % 19; //方块的编号随机产生
	cur_block_coord_x = (UI_WIDTH-2)/2; //从中间落下
	cur_block_coord_y = 1;
	for(i = 0; i < 4; i++)
		for(j = 0; j < 4; j++)
			next_blockarr[i][j] = 0; //每次产生新的方块，都要将存放下一个方块的数组清零
	for(i = 0; i < 4; i++) {
		game_arr[cur_block_coord_y+block[cur_boxindex].a[i][1]][cur_block_coord_x+block[cur_boxindex].a[i][0]].info = BLOCK ;
		next_blockarr[block[next_boxindex].a[i][1]][block[next_boxindex].a[i][0]] = BLOCK;
	}
	if(!isCanMoveBlock(cur_block_coord_x,cur_block_coord_y)) { //产生新方块的这个地方被占用了，退出
		printf("游戏结束，再接再厉！");
		getch();
		exit(0);
	}
}
/*方块的移动*/
void moveBlock() {
	short i,j,to_bottom = FALSE;	//到底
	short old_x = cur_block_coord_x,old_y = cur_block_coord_y; //用来记录旧的方块的位置
	short old_boxindex = cur_boxindex;    //记录方块的下标，按上键时改变方块用
	while(1) {
		old_x = cur_block_coord_x,old_y = cur_block_coord_y;
		old_boxindex = cur_boxindex;
		while(kbhit()) { //用户按键
			// getch();
			switch(getch()) {
				case _VK_UP:
					cur_boxindex = block[cur_boxindex].next;
					if(!isCanMoveBlock(cur_block_coord_x, cur_block_coord_y))
						cur_boxindex =	old_boxindex;  //如果不能旋转的话要还原
					break;
				case _VK_DOWN:
					for(i = 0; i < 4; i++) //一次可以下降4个
						if(isCanMoveBlock(cur_block_coord_x, cur_block_coord_y + 1)) cur_block_coord_y++;
						else  {
							to_bottom = TRUE;    //到底
							break;
						}
					break;
				case _VK_LEFT:
					if(isCanMoveBlock(cur_block_coord_x - 1, cur_block_coord_y)) cur_block_coord_x--;
					break;
				case _VK_RIGHT:
					if(isCanMoveBlock(cur_block_coord_x + 1, cur_block_coord_y)) cur_block_coord_x++;
					break;
				case _VK_SPACE:
					wait();
					clearScreen();
					fflush(stdin);
					break;
				case _VK_ESC:
					return;
			}

			if(score>=10) nowLevel = score/10;
		}

		if(to_bottom) {
			if(old_x != cur_block_coord_x || old_y != cur_block_coord_y || old_boxindex != cur_boxindex) {
				for(i = 0; i < 4; i++)
					game_arr[old_y+block[old_boxindex].a[i][1]][old_x+block[old_boxindex].a[i][0]].info = 0;
				for(i = 0; i < 4; i++)
					game_arr[cur_block_coord_y+block[cur_boxindex].a[i][1]][cur_block_coord_x+block[cur_boxindex].a[i][0]].info = BLOCK;
				gameShow();  //要按键之后才刷新
			}
			to_bottom = FALSE;
			toBottom(cur_block_coord_x, cur_block_coord_y);
			gameShow();//到底
		} else {
			if(j++ % 10 == 0) { //自动下移,要放前面，
				if(isCanMoveBlock(cur_block_coord_x, cur_block_coord_y + 1)) cur_block_coord_y++;
				else  to_bottom = TRUE; //到底
			}
			if(old_x != cur_block_coord_x || old_y != cur_block_coord_y || old_boxindex != cur_boxindex) {
				for(i = 0; i < 4; i++)
					game_arr[old_y+block[old_boxindex].a[i][1]][old_x+block[old_boxindex].a[i][0]].info = 0;
				for(i = 0; i < 4; i++)
					game_arr[cur_block_coord_y+block[cur_boxindex].a[i][1]][cur_block_coord_x+block[cur_boxindex].a[i][0]].info = BLOCK;
				gameShow();  //要按键之后才刷新
			}
		}
		Sleep(levelCalc(nowLevel)); // Speed
	}
}

int levelCalc(int level) {
	return levelSpeed[level];
}

// 暂停游戏
void wait(void) {
	char ch;

	while(1) {
		setConsoleTextColor(GMT_B_RED, GMT_F_WHITE);
		setConsoleTextPositionByXY(UI_WIDTH/2,UI_HEIGHT/2);
		printf("%s", "->游戏暂停<-");

		fflush(stdin);
		ch = getch();
		if(ch == _VK_SPACE) break;
	}
	resetAll();
}

short isCanMoveBlock(short x, short y) {
	//是否能移动方块
	short i;
	for(i=0; i<4; i++)
		if(game_arr[y+block[cur_boxindex].a[i][1]][x+block[cur_boxindex].a[i][0]].var)
			return FALSE;	//如果该位置以及有方块填充，则不能移动
	return TRUE;
}
void toBottom(short x, short y) {
	//方块到底之后的操作，1.将方块的位置的状态变为1，表示被占用。2.是否满块，消行，改变状态 3.产生新的方块
	short i,j;
	for(i = 0; i < 4; i++)
		game_arr[y+block[cur_boxindex].a[i][1]][x+block[cur_boxindex].a[i][0]].var = 1;
	//2.是否满块，消行，改变状态
	for(i = UI_HEIGHT - 2; i >= 1; i--) { //有两行是墙 ,从底开始往上搜
		for(j = 1; j <= UI_WIDTH - 2; j++) {
			if( !game_arr[i][j].var)
				break;//一行有空的就跳出这个循环 ，继续搜下一行
			if(j == UI_WIDTH - 2) {	//一行都满了,消行,此时第i行是满行
				score += 10;
				int h,v;
				for(v = i; v >= 2; v--) { //第i行开始,
					for(h = 1; h <= UI_WIDTH - 2; h++) {
						game_arr[v][h].info = game_arr[v-1][h].info;
						game_arr[v][h].var = game_arr[v-1][h].var;
					}
				}//要从底行重新,之后i--,i =  UI_HEIGHT - 2,就会出现多行一起消时有行消不了
				i = UI_HEIGHT - 1;
			}
		}
	}
	produceBlock();
}
