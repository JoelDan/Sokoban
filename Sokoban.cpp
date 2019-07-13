#include <graphics.h>
#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include "Game_data.h"

using namespace std;

IMAGE images[ALL]; //道具加载
POS man; //小人中的位置

/*******************************************
*判断游戏是否胜利，如果不存在箱子目的地，就代表游戏结束了
*输入：无
*返回值：true - 游戏结束
		 false - 游戏继续
********************************************/
bool isGameOver(void) {
	for (int i = 0; i < MAP_LINE; i++) {
		for (int j = 0; j < MAP_FILE; j++) {
			if (map[i][j] == DES) {
				return false;
			}
		}
	}
	return true;
}

/*******************************************
*游戏结束场景，在玩家通过后显示
*输入：bg - 背景图片变量的指针
*返回值： 无
********************************************/
void GameOvercene(IMAGE *bg) {
	putimage(0, 0, bg);
	settextcolor(WHITE);
	RECT rec = { 0, 0, WIDE, TALL };
	settextstyle(20, 0, _T("宋体"));
	drawtext(_T("恭喜您~ \n您终于成为了一个合格的搬箱子老司机！"), &rec, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

/*******************************************
*改变游戏视图中一格对应道具并重新显示
*输入：line - 道具地图数组的行下标
*		column - 道具在地图数组的列下标
*		prop - 道具的类型
*返回值：无
********************************************/
void changeMap(POS *pos, PRORS prop) {
	map[pos->x][pos->y] = prop;
	putimage(X_OFFSET + pos->y * PROPS_SIZE, Y_OFFSET + pos->x * PROPS_SIZE, &images[prop]);
}

/****************************
*按照游戏地图的二维数组把道具加载上去
*输入：无
*返回值：无
*****************************/
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

/********************************************
*实现游戏中人物的移动
*输入：direct - 人物移动的枚举
*返回值：无
*********************************************/
void gameControl(DIRECTION direct) {

	POS next_pos = man;
	POS next_next_pos = man;
	switch (direct){
	case UP:
		next_pos.x--;
		next_next_pos.x -= 2;
		break;
	case DOWN:
		next_pos.x++;
		next_next_pos.x += 2;
		break;
	case LEFT:
		next_pos.y--;
		next_next_pos.y -= 2;
		break;
	case RIGHF:
		next_pos.y++;
		next_next_pos.y += 2;
		break;
	}

		if (isValid(next_pos) && map[next_pos.x][next_pos.y] == FLOOR) { //人的前方是地板
			changeMap(&next_pos, MAN);  //小人前进一格
			changeMap(&man, FLOOR);
			man = next_pos;
		} else if (isValid(next_next_pos) && map[next_pos.x][next_pos.y] == BOX) { //人的前方是箱子
			//两种情况，箱子前面是地板或者是箱子目的地
			if (map[next_next_pos.x][next_next_pos.y] == FLOOR) {
				changeMap(&next_next_pos, BOX);
				changeMap(&next_pos, MAN);
				changeMap(&man, FLOOR);
				man = next_pos;
			} else if (map[next_next_pos.x][next_next_pos.y] == DES) {
				changeMap(&next_next_pos, BOX_HIT);
				changeMap(&next_pos, MAN);
				changeMap(&man, FLOOR);
				man = next_pos;
				
			}
		}
}

int main(void) {
	IMAGE backdrop;  //窗口背景图片
	initgraph(WIDE, TALL);

	loadimage(&backdrop, _T("blackground.bmp"), WIDE, TALL, true);
	putimage(0, 0, &backdrop);

	Map_initialization();

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

			if (isGameOver()) {
				GameOvercene(&backdrop);
				quit = true;
			}
		}
		Sleep(100);
	} while (!quit);

	system("pause");

	//释放资源
	closegraph();
	return 0;
}