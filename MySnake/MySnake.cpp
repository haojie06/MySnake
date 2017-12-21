// MySnake.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <math.h>
#include <malloc.h>
#include <stdlib.h>
#include <conio.h>

#define KEYUP 72
#define KEYDOWN 80
#define KEYLEFT 75
#define KEYRIGHT 77
#define MAPX 20
#define MAPY 20
#define UP -1
#define DOWN 1
#define LEFT -1
#define RIGHT 1
int map[MAPX][MAPY] = {0};

int r1, r2, r3, r4, r5, r6, round1, round2, round3, round4, round5, round6;
int xa, xb, xc, xd, xe, xf, ya, yb, yc, yd, ye, yf;//���ں������ɶ��ʳ��
int xA, xB, xC, xD, xE, xF, yA, yB, yC, yD, yE, yF;//���ں����������ʳ��
int gameStatus;											   //����Ϸ��ʼʱȷ��ͬʱ���ڵ����ʳ������
int score = 0;


struct snake
{	
	int position = 0;
	int positionX = 0;
	int positionY = 0;
	struct snake* next = NULL;
	struct snake* previous = NULL;
	
};

struct food
{
	int foodX;
	int foodY;
	int foodLife;//����ʱ��
	int status = 0;//�Ƿ��Ѿ���ʳ��
};
int foodCount = 0;//ͳ�����е�ʳ����
int foodNum;
food * foodGroup;

snake* head, *tail;

void iniMap();
void iniSnake();
void printMap();
void addSnake(int x, int y);
void delTail();
void move(int dirX, int dirY);
void gotoxy(int x, int y);
void playGame();
void HideCursor();
void generateFood();
int rand_food_x(void);
int rand_food_y(void);
int judge();
void foodClear();

int main()
{		
	foodNum = (rand_food_x() * 100) % 10 + 5;
	/*ע�� ȫ���ַ�ʹ��goto���ʱҪ*/
		HideCursor();
		iniMap();
		iniSnake();
		printMap();
		playGame();

		
  return 0;
}

//��ͼ��ʼ��
void iniMap()
{	//�߿�
	for (int i = 0; i < MAPX; i++)
	{
		map[i][0] = 1;
		map[i][19] = 1;
	}

	for (int j = 0; j < MAPY; j++)
	{
		map[0][j] = 1;
		map[19][j] = 1;
	}
}

void printMap()
{	
	//�ƺ�����BUG
	gotoxy(20, 0);
	printf("��ǰ�÷֣� %d", score);

	//���������ӡ������
	snake * cur = head;
	if (head == NULL)
	{
		printf("ͷָ��Ϊ��");
	}
	else
	{
		int count = 0;
		while (cur != NULL)
		{
			count += 1;
			map[cur->positionX][cur->positionY] = 2;
			cur = cur->next;
			//printf("%d,%d\n", cur->positionX, cur->positionY);
		}
		//printf("��%d", count);
		
		for (int i = 0; i < MAPX; i++)
		{
			for (int j = 0; j < MAPY; j++)
			{
				switch (map[i][j]) {
				case 0:
					gotoxy(i, 2 * j);
					printf("  ");
					break;
				case 1:
					gotoxy(i, 2 * j);
					printf("��");
					break;
				case 2:
					gotoxy(i, 2 * j);
					printf("��");
					break;
				case 4:
					gotoxy(i, 2 * j);
					printf("  ");
					break;
				case 5:
					gotoxy(i, 2 * j);
					printf("$$");
				}
			}
		}
	}
}
void iniSnake()
{
	/*���߽��г�ʼ��
	*��ʼ����Ϊ���� ����������
	*/
	//����˫������

	snake * current,*prev;
	for (int i = 0; i < 8; i++)
	{	
		current = (struct snake*) calloc(sizeof(struct snake),1);
		if (head == NULL)
		{
			current -> positionX = (MAPX / 2);
			current-> positionY = (MAPY / 2);
			prev = current;
			head = current;
		}
		else
		{	
			prev->next = current;
			current->previous = prev;
			current->positionX = (prev->positionX + 1);
			current->positionY = prev->positionY;
			prev = current;
		
		}
		
	}
	tail = current;//βָ�� ???
	//mallocû�г�ʼ����
	tail->next = NULL;
}

//����ͷ�ڵ�
void addSnake(int x, int y)
{
	snake* add = (snake*)calloc(sizeof(snake),1);
	add->positionX = head->positionX + x;
	add->positionY = head->positionY + y;
	add->next = head;
	head->previous = add;
	head = add;
}

//ɾ��β�ڵ�
void delTail()
{
	map[tail->positionX][tail->positionY] = 0;
	tail = tail->previous;
	free(tail->next);
	tail->next = NULL;
	
}
//�ߵ��ƶ�
void move(int dirX,int dirY)
{
	int isDel = 0;
	addSnake(dirX, dirY);
	isDel = judge();
	if (isDel != 1)
	{
		delTail();
	}
	foodClear();
}


//��Ϸ��ѭ��
void playGame()
{
	int foodNum = rand_food_y() % 10 + 1;
	foodGroup = (food*)calloc(sizeof(food), foodNum);
	 gameStatus = 1;
	int directionX = 0, directionY = 1;
	while (gameStatus)
	{
		generateFood();
		if (!kbhit())
		{
			move(directionX, directionY);

			printMap();
			//����������
			Sleep(500);
		}
		else
		{
			//�м�������ʱ
			char key = getch();
			if (directionX == 1)//down
			{
				switch (key)
				{
				case KEYLEFT:
					directionY = -1, directionX = 0;
					break;
				case KEYRIGHT:
					directionY = 1, directionX = 0;
					break;
				}
			}
			if (directionX == -1) //up
			{
				switch (key)
				{
				case KEYLEFT:
					directionY = -1, directionX = 0;
					break;
				case KEYRIGHT:
					directionY = 1, directionX = 0;
				}
			}
			if (directionY == 1)
			{
				switch (key)
				{

				case KEYUP:
					directionX = -1, directionY = 0;
					break;
				case KEYDOWN:
					directionX = 1, directionY = 0;
				}
			}

			if (directionY == -1)
			{
				switch (key)
				{
				case KEYUP:
					directionX = -1, directionY = 0;
					break;
				case KEYDOWN:
					directionX = 1, directionY = 0;
				}
			}
		}
	}
	system("cls");
	gotoxy(10, 10);
	printf("GAME OVER");
}


void gotoxy(int y, int x) {//x������,y������
	COORD pos = { x,y };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// ��ȡ��׼����豸���
	SetConsoleCursorPosition(hOut, pos);//���������ֱ���ָ���ĸ����壬����λ��
}
//���ع��
void HideCursor()
{
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}

void generateFood()
{	
	srand(time(NULL));
	gotoxy(24, 0);
	printf("FOOD NUM:%d FOOD COUNT: %d", foodNum, foodCount);
	int x, y;
	x = rand_food_x();
	y = rand_food_y();
	int isGenerate = 0;
	//��������ʳ�������
	isGenerate = (rand() * 100) % 10;
	if (isGenerate < 3)
	{
		if (x > 0 && x < MAPX && y>0 && y < MAPY && map[x][y] != 1 && foodCount < foodNum && map[x][y] != 2)
		{
			if (foodGroup[foodCount].status == 0)
			{//��λ�õ�ʳ�ﲻ����ʱ
				foodGroup[foodCount].foodX = x;
				foodGroup[foodCount].foodY = y;
				foodGroup[foodCount].foodLife = rand_food_x() % 5 + 5;//ʳ�������
				foodGroup[foodCount].status = 1;
				map[x][y] = 5;
				
			}
			    foodCount += 1;
		}
		if (foodCount == foodNum)
			foodCount = 0;
		
	}
}

//����ʳ��������//
int rand_food_x(void)
{
	int x;
	srand(time(NULL));
	x = (rand() * rand()) % MAPX;

	return x;
}

int rand_food_y(void)
{
	int y;
	srand(time(NULL));
	y = rand() % MAPY;
	return y;
}


int judge()
{
	int result = 0;
	int x = head->positionX;
	int y = head->positionY;
	//����ͷ�����ж�,�Ե�ʳ���ɾ��β��
	if (map[head->positionX][head->positionY] == 5)
	{

		for (int i = 0; i < foodCount; i++)
			if (foodGroup[i].foodX == x && foodGroup[i].foodY == y)
			{
				gotoxy(21, 0);
				printf("Good You eat a food !");
				foodGroup[i].status = 0;
				foodCount -= 1;
				score += 100;
				result = 1;

			}
	}
	else if (map[x][y] == 1)
		gameStatus = 0;
	else if (map[x][y] == 2)
	{
		//�������ҧ���Լ����д���
		snake * find;
		find = head;
		int i = 1;
		while (find != NULL)
		{
			if (find->positionX == x && find->positionY == y)
			{	//ɾ��֮��Ľڵ�
				snake * del;
				int count = 0;
				//while (tail != find->previous)
				//for(int i =0;i < 3;i++)
				do
				{
					map[tail->positionX][tail->positionY] = 0;
					tail = tail->previous;
					free(tail->next);
					tail->next = NULL;
				} while (tail->positionX == find->positionX && tail->positionY == find->positionY);
				//�������һ��
				gotoxy(22, 0);
				printf("ʹ����������");
				break;

			}
			find = find->next;
		}
	}
			
	
	return result;
}

void foodClear()
{
	//���д��ڵ�ʳ������� -1
	for (int i = 0; i < foodNum; i++)
	{
		if (foodGroup[i].status == 1)
		{
			foodGroup[i].foodLife--;

			if (foodGroup[i].foodLife <= 0)
			{
				foodGroup[i].status = 0;
				map[foodGroup[i].foodX][foodGroup[i].foodY] = 0;
			}
		}
	}
}