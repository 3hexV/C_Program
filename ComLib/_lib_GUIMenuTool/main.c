#include "./lib/gui_menu_tool/gui_menu_tool.h"
#include <stdio.h>

char itemText[3][50] = {"1.Star","2.Stop","3.Quit"};

int main()
{
	initMenu("Menu",itemText,sizeof(itemText)/sizeof(itemText[0]));
	createMenu(20,13);
	showMenu();

	return 0;
}
