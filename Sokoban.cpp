#include <graphics.h>
#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include "Game_data.h"

using namespace std;

IMAGE images[ALL]; //道具加载

struct _POS man; //小人中的位置

/*************************************
**功能：游戏地图
**含义：墙：0； 地板：1； 箱子的目的地：2；
**		人物：3； 箱子：4； 箱子命中目标：5
*************************************/
int map[MAP_LINE][MAP_FILE]{
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0 },
{ 0, 1, 4, 1, 0, 2, 1, 0, 2, 1, 0, 0 },
{ 0, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0 },
{ 0, 1, 0, 2, 0, 1, 1, 4, 1, 1, 1, 0 },
{ 0, 1, 1, 1, 0, 3, 1, 1, 1, 4, 1, 0 },
{ 0, 1, 2, 1, 1, 4, 1, 1, 1, 1, 1, 0 },
{ 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};

//初始化界面背景
void initialize(void) {
	IMAGE backdrop;  //窗口背景图片
	initgraph(WIDE, TALL);

	loadimage(&backdrop, _T("blackground.bmp"), WIDE, TALL, true);
	putimage(0, 0, &backdrop);
}

/*******************************************
*改变游戏视图中一格对应道具并重新显示
*输入：line - 道具地图数组的行下标
*		column - 道具在地图数组的列下标
*		prop - 道具的类型
*返回值：无
********************************************/
void changeMap(int line, int column, enum PRORS prop) {
	map[line][column] = prop;
	putimage(X_OFFSET + column * PROPS_SIZE, Y_OFFSET + line * PROPS_SIZE, &images[prop]);
}

//加载道具图片
void Map_initialization(void) {

	loadimage(&images[WALL], _T("wall_right.bmp"), PROPS_SIZE, PROPS_SIZE, true);
	loadimage(&images[FLOOR], _T("floor.bmp"), PROPS_SIZE, PROPS_SIZE, true);
	loadimage(&images[DES], _T("des.bmp"), PROPS_SIZE, PROPS_SIZE, true);
	loadimage(&images[MAN], _T("man.bmp"), PROPS_SIZE, PROPS_SIZE, true);
	loadimage(&images[BOX], _T("box.bmp"), PROPS_SIZE, PROPS_SIZE, true);
	loadimage(&images[BOX_HIT], _T("box.bmp"), PROPS_SIZE, PROPS_SIZE, true);

	for (int i = 0; i < MAP_LINE; i++) {
		for (int j = 0; j < MAP_FILE; j++) {
			if (map[i][j] == MAN) {
				man.x = i;
				man.y = j;
			}
			putimage(X_OFFSET + j * PROPS_SIZE, Y_OFFSET + i * PROPS_SIZE, &images[map[i][j]]);
		}
	}
}


//实现游戏四个方向（上，下，左，右）
void gameControl(enum _DIRECTION direct) {
	int x = man.x;
	int y = man.y;

	struct _POS next_pos = man;
	switch (direct){
	case UP:
		next_pos.x--;
		break;
	case DOWN:
		next_pos.x++;
		break;
	case LEFT:
		next_pos.y--;
		break;
	case RIGHF:
		next_pos.y++;
		break;
	}

		if (isValid(next_pos) && map[next_pos.x][next_pos.y] == FLOOR) {
				changeMap(next_pos.x, next_pos.y, MAN);  //小人前进一格
				changeMap(man.x, man.y, FLOOR);
				man = next_pos;
		}

}

//人物控制
void man_control(void) {
	bool quit = false;

	do {
		if (_kbhit()) { //玩家有按键
			char ch = _getch();
			
			if (ch == KEY_UP) {
				gameControl(UP);
			} else if (ch == KEY_DOWN) {
				gameControl(DOWN);
			} else if (ch == KEY_LEFT) {
				gameControl(LEFT);
			} else if (ch == KEY_RIGHF) {
				gameControl(RIGHF);
			} else if (ch == KET_QUIT) {
				quit = true;
			}
		}
		Sleep(100);
	} while (!quit);
}


int main(void) {
	initialize();
	Map_initialization();
	man_control();

	system("pause");
	return 0;
}