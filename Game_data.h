#pragma once

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

//�ж��Ƿ��Ǹ���Ч�ĵ�ַ
#define isValid(next_pos) next_pos.x >= 0 && next_pos.x < MAP_LINE && next_pos.y >= 0 && next_pos.y < MAP_FILE

typedef		enum PRORS			PRORS;
typedef		enum _DIRECTION		DIRECTION;
typedef		struct _POS			POS;

/*************************************
**���ܣ���һ����Ϸ��ͼ
**���壺ǽ��0�� �ذ壺1�� ���ӵ�Ŀ�ĵأ�2��
**		���3�� ���ӣ�4�� ��������Ŀ�꣺5
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

int map2[8][8]{
{ 0, 0, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 2, 0, 0, 0, 0 },
{ 0, 0, 0, 1, 0, 0, 0, 0 },
{ 0, 0, 0, 4, 1, 1, 2, 0 },
{ 0, 2, 1, 1, 1, 0, 0, 0 },
{ 0, 0, 0, 0, 1, 0, 0, 0 },
{ 0, 0, 0, 0, 1, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 0, 0 }
};

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

//�����ƶ�
enum _DIRECTION {
	UP,
	DOWN,
	LEFT,
	RIGHF
};