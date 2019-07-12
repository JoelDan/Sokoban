#pragma once

void gameControl(enum _DIRECTION direct);

#define	WIDE		960		//���ڵĿ�
#define	TALL		768		//���ڵĸ�

#define	MAP_LINE	9		//��ͼ������
#define	MAP_FILE	12		//��ͼ������

#define	PROPS_SIZE	61		//���ߵĴ�С

#define	X_OFFSET	100		//X�����ƫ����
#define	Y_OFFSET	150		//Y�����ƫ����

#define KEY_UP		'w'		//����
#define KEY_DOWN	's'		//����
#define KEY_LEFT	'a'		//����
#define KEY_RIGHF	'd'		//����
#define KET_QUIT	'q'		//�˳�

#define isValid(next_pos) next_pos.x >= 0 && next_pos.x < MAP_LINE && next_pos.y >= 0 && next_pos.y < MAP_FILE

enum PRORS {
	WALL,	//ǽ
	FLOOR,	//�ذ�
	DES,	//Ŀ�ĵ�
	MAN,	//����
	BOX,	//����
	BOX_HIT,//��������Ŀ��
	ALL		//����
};

struct _POS {
	int x;	//С�����ڵĶ�ά�������
	int y;	//С�����ڵĶ�ά�������
};

enum _DIRECTION {
	UP,
	DOWN,
	LEFT,
	RIGHF
};

