#pragma once

void gameControl(enum _DIRECTION direct);

#define	WIDE		960		//窗口的宽
#define	TALL		768		//窗口的高

#define	MAP_LINE	9		//地图的行数
#define	MAP_FILE	12		//地图的列数

#define	PROPS_SIZE	61		//道具的大小

#define	X_OFFSET	100		//X坐标的偏移量
#define	Y_OFFSET	150		//Y坐标的偏移量

#define KEY_UP		'w'		//向上
#define KEY_DOWN	's'		//向下
#define KEY_LEFT	'a'		//向左
#define KEY_RIGHF	'd'		//向右
#define KET_QUIT	'q'		//退出

#define isValid(next_pos) next_pos.x >= 0 && next_pos.x < MAP_LINE && next_pos.y >= 0 && next_pos.y < MAP_FILE

enum PRORS {
	WALL,	//墙
	FLOOR,	//地板
	DES,	//目的地
	MAN,	//人物
	BOX,	//箱子
	BOX_HIT,//箱子命中目标
	ALL		//总数
};

struct _POS {
	int x;	//小人所在的二维数组的行
	int y;	//小人所在的二维数组的列
};

enum _DIRECTION {
	UP,
	DOWN,
	LEFT,
	RIGHF
};

