#ifndef _MAIN_H_
#define _MAIN_H_

#define UI_WIDTH  16 //显示界面的宽度
#define UI_HEIGHT 25 //界面的高度
#define WALL 	  1
#define BLOCK     2
#define _VK_UP     72   //方向键上下左右的第二个值,方向键有两个值,第一个是224,分别是72,...
#define _VK_DOWN   80
#define _VK_LEFT   75
#define _VK_RIGHT  77
#define _VK_SPACE  0x20
#define _VK_ESC    0x1B
#define _VK_ENTER  0x0D
#define TRUE 	  1
#define FALSE     0
#define DEF_LEVEL 1
#define COLOR_LEN 12

#define GAME_DIV "  "
#define GAME_BLOCK "▉"
#define GAME_WALL_H "‖"
#define GAME_WALL_W "=="

void initia();			//初始化的一些工作
void gameShow(); 	/*游戏显示界面*/
void moveBlock(); 	/*方块的移动*/
short isCanMoveBlock(short x, short y); 	//是否能移动方块
void produceBlock();   //产生方块
void toBottom(short x, short y);				//方块到底了之后的操作 ，bottom：底
void wait(void);
int levelCalc(int level);
int gameMainMenu(void); 
void drawMainMenu(int nowIndex);
void drawDes(void);

struct _game_arr{
	short info;  //用来存放游戏界面的数组
	short  var;  //用来记录该数组的某个位置是否被占用 ，当方块没有移动了，
	//该位置才被占用，当移动方块是那个地方被占用就不能移动了 ,用1表示占用，0表示未占用
}game_arr[UI_HEIGHT][UI_WIDTH];


typedef struct _block
{
    short a[4][2]; /*定义方块形状的数组，每个方块共有4个小块组成，
	 用4行2列来记录每个小方块的相对 坐标， */
    short next; //下一个方块的号码
}ST_BLOCK;

#endif

