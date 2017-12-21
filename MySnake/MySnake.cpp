// MySnake.cpp : 定义控制台应用程序的入口点。
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
int xa, xb, xc, xd, xe, xf, ya, yb, yc, yd, ye, yf;//用于后面生成多个食物
int xA, xB, xC, xD, xE, xF, yA, yB, yC, yD, yE, yF;//用于后面清除过期食物
int gameStatus;											   //在游戏开始时确认同时存在的最多食物数量
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
	int foodLife;//持续时间
	int status = 0;//是否已经有食物
};
int foodCount = 0;//统计已有的食物数
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
	/*注意 全角字符使用goto语句时要*/
		HideCursor();
		iniMap();
		iniSnake();
		printMap();
		playGame();

		
  return 0;
}

//地图初始化
void iniMap()
{	//边框
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
	//似乎存在BUG
	gotoxy(20, 0);
	printf("当前得分： %d", score);

	//遍历链表打印蛇身体
	snake * cur = head;
	if (head == NULL)
	{
		printf("头指针为空");
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
		//printf("有%d", count);
		
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
					printf("■");
					break;
				case 2:
					gotoxy(i, 2 * j);
					printf("□");
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
	/*对蛇进行初始化
	*初始长度为三节 坐标在中心
	*/
	//建立双向链表

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
	tail = current;//尾指针 ???
	//malloc没有初始化！
	tail->next = NULL;
}

//增加头节点
void addSnake(int x, int y)
{
	snake* add = (snake*)calloc(sizeof(snake),1);
	add->positionX = head->positionX + x;
	add->positionY = head->positionY + y;
	add->next = head;
	head->previous = add;
	head = add;
}

//删除尾节点
void delTail()
{
	map[tail->positionX][tail->positionY] = 0;
	tail = tail->previous;
	free(tail->next);
	tail->next = NULL;
	
}
//蛇的移动
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


//游戏主循环
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
			//检测键盘输入
			Sleep(500);
		}
		else
		{
			//有键盘输入时
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


void gotoxy(int y, int x) {//x行坐标,y列坐标
	COORD pos = { x,y };
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// 获取标准输出设备句柄
	SetConsoleCursorPosition(hOut, pos);//两个参数分别是指定哪个窗体，具体位置
}
//隐藏光标
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
	//调节生成食物的速率
	isGenerate = (rand() * 100) % 10;
	if (isGenerate < 3)
	{
		if (x > 0 && x < MAPX && y>0 && y < MAPY && map[x][y] != 1 && foodCount < foodNum && map[x][y] != 2)
		{
			if (foodGroup[foodCount].status == 0)
			{//该位置的食物不存在时
				foodGroup[foodCount].foodX = x;
				foodGroup[foodCount].foodY = y;
				foodGroup[foodCount].foodLife = rand_food_x() % 5 + 5;//食物的寿命
				foodGroup[foodCount].status = 1;
				map[x][y] = 5;
				
			}
			    foodCount += 1;
		}
		if (foodCount == foodNum)
			foodCount = 0;
		
	}
}

//生成食物的随机数//
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
	//对蛇头进行判断,吃到食物后不删除尾巴
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
		//在这里对咬到自己进行处理
		snake * find;
		find = head;
		int i = 1;
		while (find != NULL)
		{
			if (find->positionX == x && find->positionY == y)
			{	//删除之后的节点
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
				//再清除掉一段
				gotoxy(22, 0);
				printf("痛！！！！！");
				break;

			}
			find = find->next;
		}
	}
			
	
	return result;
}

void foodClear()
{
	//所有存在的食物的生命 -1
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