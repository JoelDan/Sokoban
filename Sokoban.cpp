#include <graphics.h>
#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include "Game_data.h"

using namespace std;

IMAGE images[ALL]; //���߼���
POS man; //С���е�λ��

/*******************************************
*�ж���Ϸ�Ƿ�ʤ�����������������Ŀ�ĵأ��ʹ�����Ϸ������
*���룺��
*����ֵ��true - ��Ϸ����
		 false - ��Ϸ����
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
*��Ϸ���������������ͨ������ʾ
*���룺bg - ����ͼƬ������ָ��
*����ֵ�� ��
********************************************/
void GameOvercene(IMAGE *bg) {
	putimage(0, 0, bg);
	settextcolor(WHITE);
	RECT rec = { 0, 0, WIDE, TALL };
	settextstyle(20, 0, _T("����"));
	drawtext(_T("��ϲ��~ \n�����ڳ�Ϊ��һ���ϸ�İ�������˾����"), &rec, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

/*******************************************
*�ı���Ϸ��ͼ��һ���Ӧ���߲�������ʾ
*���룺line - ���ߵ�ͼ��������±�
*		column - �����ڵ�ͼ��������±�
*		prop - ���ߵ�����
*����ֵ����
********************************************/
void changeMap(POS *pos, PRORS prop) {
	map[pos->x][pos->y] = prop;
	putimage(X_OFFSET + pos->y * PROPS_SIZE, Y_OFFSET + pos->x * PROPS_SIZE, &images[prop]);
}

/****************************
*������Ϸ��ͼ�Ķ�ά����ѵ��߼�����ȥ
*���룺��
*����ֵ����
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
*ʵ����Ϸ��������ƶ�
*���룺direct - �����ƶ���ö��
*����ֵ����
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

		if (isValid(next_pos) && map[next_pos.x][next_pos.y] == FLOOR) { //�˵�ǰ���ǵذ�
			changeMap(&next_pos, MAN);  //С��ǰ��һ��
			changeMap(&man, FLOOR);
			man = next_pos;
		} else if (isValid(next_next_pos) && map[next_pos.x][next_pos.y] == BOX) { //�˵�ǰ��������
			//�������������ǰ���ǵذ����������Ŀ�ĵ�
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
	IMAGE backdrop;  //���ڱ���ͼƬ
	initgraph(WIDE, TALL);

	loadimage(&backdrop, _T("blackground.bmp"), WIDE, TALL, true);
	putimage(0, 0, &backdrop);

	Map_initialization();

	bool quit = false;

	do {
		if (_kbhit()) { //����а���
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

	//�ͷ���Դ
	closegraph();
	return 0;
}