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
char* key;//按键
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
void printKey();
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
		}
		map[head->positionX][head->positionY] = 6;//单独给蛇头一个值

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
					break;
				case 6:
					gotoxy(i, 2 * j);
					printf("■");
					break;
				}
			}
		}
	}
}

void iniSnake()
{
	/*对蛇进行初始化
	*初始长度为X节  蛇头坐标在中心
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
	tail = current;//尾指针 始终指向最后出现的一个
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
	int result = 0;
	addSnake(dirX, dirY);
	result = judge();
	if (result != 1)//不吃到食物时，每次移动都删掉尾节点
	{
		delTail();
	}

	foodClear();//清除过期的食物
}


//游戏主循环
void playGame()
{	

	int kbhitCount = 0;//统计按键次数
	int foodNum = rand_food_y() % 10 + 1;//最大食物数量
	foodGroup = (food*)calloc(sizeof(food), foodNum);
	gameStatus = 1;
	//这两个数组用来保存一系列指令的方向
	int directionX[20] = { 0 }, directionY[20] = { 0};
	 //初始方向向上
	 directionX[0] = -1;
	 directionY[0] = 0;

 key = (char*)calloc(sizeof(char),20);//按键数组最多接受20个
	for (int i = 0; i < 10; i++)
		key[i] = 0;

	
	int step = 0;//走的步数
	char lastKey;
	while (gameStatus)
	{
		printKey();
		generateFood();//生成食物及去除过期食物  !!吃到智慧草 食物寿命无限
		int hit = 0;
		if (!kbhit())
		{	

			//当 key 的数组中还存在 按键时 读取按键
			move(directionX[step], directionY[step]);
			//走过后清除这一步的数据(有多条指令的时候)，并准备读取下一指令
			if (step != 0) {
				lastKey = key[step];//?
				key[step] = 0;
				//directionX[step] = 0;
				//directionY[step] = 0;
				//step += 1;
			}
	
			//printf("   %d step", step);
			if (key[step+1] == 0)//读取下一步发现没有按键时
			{   
				//保留当前方向
				directionX[0] = directionX[step];
				directionY[0] = directionY[step];
				step = 0;//又返回第一步，第一步即等会输入的值
				kbhitCount = 0;//指令数变为1条
			}
			else { step += 1;
			//kbhitCount++;
			}//下一轮还是读取储存好的指令
			
			printMap();
			Sleep(400);


		}
		else//当检测到键盘输入时   如果本次输入与上次输入相同，不接受
		{

			    getch();//取得 方向键值 第一部分
				key[kbhitCount] = getch();
				//下面用于保存输入的值
				int compare;//比较的对象 的下标
				if (kbhitCount == 0) {//此时比较对象为自己原有的值，否则是和上一项比较
					compare = 0;
				}
				else
				{
					compare = kbhitCount - 1;
				}

					if (directionX[compare] == 1)//down   原来的方向向下时！就不能向上
					{

						switch (key[kbhitCount])//获取当前输入
						{
						case KEYLEFT:
							directionY[kbhitCount] = -1, directionX[kbhitCount] = 0;
							break;
						case KEYRIGHT:
							directionY[kbhitCount] = 1, directionX[kbhitCount] = 0;
							break;
						case KEYDOWN:
							directionX[kbhitCount] = 1, directionY[kbhitCount] = 0;
							break;
						case KEYUP:
							directionX[kbhitCount] = 1, directionY[kbhitCount] = 0;
							break;
							//如果不写这个蛇会消失-没有移动但删除了尾巴
						}
					}

					if (directionX[compare] == -1) //up
					{
						switch (key[kbhitCount])
						{
						case KEYLEFT:
							directionY[kbhitCount] = -1, directionX[kbhitCount] = 0;
							break;
						case KEYRIGHT:
							directionY[kbhitCount] = 1, directionX[kbhitCount] = 0;
							break;
						case KEYDOWN:
							directionX[kbhitCount] = -1, directionY[kbhitCount] = 0;
							break;
						case KEYUP:
							directionX[kbhitCount] = -1, directionY[kbhitCount] = 0;
							break;
						}
					}
					if (directionY[compare] == 1)//向右移动
					{
						switch (key[kbhitCount])
						{

						case KEYUP:
							directionX[kbhitCount] = -1, directionY[kbhitCount] = 0;
							break;
						case KEYDOWN:
							directionX[kbhitCount] = 1, directionY[kbhitCount] = 0;
							break;
						case KEYRIGHT:
							directionX[kbhitCount] = 0, directionY[kbhitCount] = 1;
							break;
						case KEYLEFT:
							directionX[kbhitCount] = 0, directionY[kbhitCount] = 1;
							break;
						}
					}

					if (directionY[compare] == -1)
					{
						switch (key[kbhitCount])
						{
						case KEYUP:
							directionX[kbhitCount] = -1, directionY[kbhitCount] = 0;
							break;
						case KEYDOWN:
							directionX[kbhitCount] = 1, directionY[kbhitCount] = 0;
							break;
						case KEYLEFT:
							directionX[kbhitCount] = 0, directionY[kbhitCount] = -1;
							break;
						case KEYRIGHT:
							directionX[kbhitCount] = 0, directionY[kbhitCount] = -1;
							break;
						}
				   gotoxy(26, 0);


				}
									
			kbhitCount++;
			//gotoxy(21, 0);
			printf("%按键%d\n", kbhitCount);
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
				foodGroup[foodCount].foodLife = (rand_food_x()*100) % 12 + 5;//食物的寿命
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
	if (map[head->positionX][head->positionY] == 5)//头的坐标和食物的坐标重合
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
	//撞墙了！
	else if (map[x][y] == 1)
		gameStatus = 0;

	//咬到自己
	else if (map[x][y] == 2)//蛇头坐标和身体坐标重合
	{
		//先找到咬到的地方
		snake * find;
		find = head->next;
		int loseNum = 0;//被咬掉的节数
		while (find != NULL)//遍历链表
		{
			if (find->positionX == x && find->positionY == y)
			{
				gotoxy(21, 8);
				printf("你失去了%d节", loseNum);
				//删除之后的节点
				snake * del;
				int count = 0;
				//从尾节点开始删除
				do
				{	
					count++;
					map[tail->positionX][tail->positionY] = 0;
					tail = tail->previous;
					free(tail->next);
					tail->next = NULL;
				} while (tail->positionX == find->positionX && tail->positionY == find->positionY);
				//再清除掉一段
				gotoxy(22, 0);
				printf("痛！！！！！你失去了%d",count);
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

void printKey()
{
	for (int i = 0; i < 10; i++) {//打印指令
		char k = key[i];
		switch (k)
		{
		case KEYUP:
			printf(" ↑ ");
			break;

		case KEYDOWN:
			printf(" ↓ ");
			break;

		case KEYLEFT:
			printf(" ← ");
			break;

		case KEYRIGHT:
			printf(" → ");
			break;

		default:
			break;

		}
	}
}

void BFS()
{
	
}