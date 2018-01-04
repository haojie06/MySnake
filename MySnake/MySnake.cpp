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
#include <graphics.h>
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


int pic[40][40] = { 0 };
int map[MAPX][MAPY] = { 0 };
//将来写到头文件中去
//草原，食物为南瓜 毒为腐肉
int mapSel[6][MAPX][MAPY] = {
{
{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
{ 1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },//起点
{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },//终点在本行
{ 1,0,0,0,1,1,0,1,0,0,0,0,1,0,1,1,0,0,0,1 },
{ 1,0,0,0,1,1,0,1,0,0,0,0,1,0,1,1,0,0,0,1 },
{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
{ 1,0,0,0,1,1,0,1,0,0,0,0,1,0,1,1,0,0,0,1 },
{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
{ 1,0,0,0,1,1,0,1,1,0,0,1,1,0,1,1,0,0,0,1 },
{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
{ 1,0,0,0,1,1,0,1,1,0,0,1,1,0,1,1,0,0,0,1 },
{ 1,0,0,0,1,1,0,1,1,0,0,1,1,0,1,1,0,0,0,1 },
{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
{ 1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } }
,
{//森林
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1 },
	{ 1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1 },
	{ 1,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,1,1 },
	{ 1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1 },
	{ 1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1 },
	{ 1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } },
	{
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
		{ 1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,1 },
		{ 1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1 },
		{ 1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1 },
		{ 1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1 },
		{ 1,0,0,0,1,0,0,0,1,0,0,1,0,0,0,1,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1 },
		{ 1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1 },
		{ 1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1 },
		{ 1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1 },
		{ 1,0,0,0,1,1,1,1,0,0,0,0,1,1,1,1,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
		{ 1,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1 },
		{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } },
		{    //冰原
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
			{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
			{ 1,1,0,0,0,0,0,0,0,1,0,0,0,1,1,1,0,0,0,1 },
			{ 1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1 },
			{ 1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1 },
			{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
			{ 1,1,0,0,0,0,0,0,0,1,0,0,0,1,1,1,0,0,0,1 },
			{ 1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1 },
			{ 1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1 },
			{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
			{ 1,1,0,0,0,0,0,0,0,1,0,0,0,1,1,1,0,0,0,1 },
			{ 1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1 },
			{ 1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1 },
			{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
			{ 1,1,0,0,0,0,0,0,0,1,0,0,0,1,1,1,0,0,0,1 },
			{ 1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1 },
			{ 1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1 },
			{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
			{ 1,1,0,0,0,0,0,0,0,1,0,0,0,1,1,1,0,0,0,1 },
			{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } } ,

			{
				{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
				{ 1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1 },
				{ 1,1,0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,1 },
				{ 1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1 },
				{ 1,1,0,0,0,1,0,1,0,0,0,0,1,0,1,0,0,0,0,1 },
				{ 1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1 },
				{ 1,1,0,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0,1 },
				{ 1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1 },
				{ 1,1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,1 },
				{ 1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1 },
				{ 1,1,0,0,0,1,0,1,0,0,0,0,0,0,1,0,0,0,0,1 },
				{ 1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1 },
				{ 1,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1,1 },
				{ 1,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,1 },
				{ 1,1,0,0,0,1,0,0,1,0,0,0,1,0,1,0,0,0,1,1 },
				{ 1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1 },
				{ 1,1,0,0,0,1,0,0,1,0,0,0,1,0,1,0,0,0,1,1 },
				{ 1,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,1 },
				{ 1,1,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,1,1 },
				{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } } ,

				{
					{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
					{ 1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
					{ 1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1 },
					{ 1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1 },
					{ 1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1 },
					{ 1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
					{ 1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1 },
					{ 1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
					{ 1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1 },
					{ 1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
					{ 1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
					{ 1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
					{ 1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
					{ 1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
					{ 1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
					{ 1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
					{ 1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
					{ 1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
					{ 1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
					{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } }};
int AX, AY;
int maze[MAPX][MAPY] = {0}; //用于搜索
int autoRound = 0;
int step;
int kbhitCount;
int gameStatus;											   //在游戏开始时确认同时存在的最多食物数量
int score = 0;
int dimageShow = 0; //收到伤害时显示时间
int directionX[50] = { 0 }, directionY[50] = { 0 };
/*
*********
用于BFS
*********
*/

struct point { int row, col, predecessor; } queue[1000];
int front = 0, rear = 0;
//队列的操作
void enqueue(struct point p)//入队
{
	queue[rear++] = p;
}

struct point dequeue(void)//出队 从head开始
{
	return queue[front++];//此时队首也向后移了 eg：0 -> 1 先返回front front再自加
}

int is_empty(void)
{
	return front == rear;
}
//????????
void clean_queue()
{
	for (int i = 0; i < 500; i++)
	{
		queue[i].col = NULL;
		queue[i].row = NULL;
		queue[i].predecessor = NULL;
	}
	front = 0;
	rear = 0;
}

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
	//int kind; 种类 后期扩展
};
struct poison
{
	int poisonX;
	int poisonY;
	int posionLife;
	int status;
	//int kind 
};
int difficulty = 0;//难度
int scene = 0;//地图


char playerName[20];
int foodCount = 0;//统计已有的食物数
int poisonCount = 0;
int foodNum;
int poisonNum;
food * foodGroup;
poison * poisonGroup;
char* key,* autoKey;//按键
int isFinish = 1;
snake* head, *tail;
int walkMode = 3;//行走模式 0-手动,1-自动 3_半自动
int modeCount = 0;
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
void generatePoison();
int rand_food_x(void);
int rand_food_y(void);
int judge();
void Clearer();
void printKey();
void loadKey();//加载计算出来的路径
void clearKey();//清除已有的路径
void BFS();
void theWall(int dirX,int dirY);//防止撞墙--在每次移动后进行
void beforeGame();//游戏开始界面
void setting();
int main()
{		
	
//	foodNum = (rand_food_x() *133) % 10 + 14;
	poisonNum = (rand_food_x() * 12) % 10 + 12;
	/*注意 全角字符使用goto语句时要*/
		initgraph(1000, 620);//画布大小
		HideCursor();
		beforeGame();
		
		setting();//游戏设置 玩家姓名，地图选择，难度选择
		iniMap();
		iniSnake();
		printMap();//关于gotoxy的显示问题 为什么不能goto到 地图右边？？


		playGame();

		
  return 0;
}

//地图初始化
void iniMap()
{	//边框
	initgraph(1000, 620);
	IMAGE img;
	loadimage(&img, L"E:\\store\\source code\\MySnake\\image\\level1.jpg");
	putimage(0, 0, &img);
	for (int i = 0; i < MAPX; i++)
	{
		map[i][0] = 1;
		map[i][MAPX - 1] = 1;
	}

	for (int j = 0; j < MAPY; j++)
	{
		map[0][j] = 1;
		map[MAPY - 1][j] = 1;
	}
}

void printMap()
{	
	//改为图形界面了
	IMAGE img[10];
	if (scene == 0)//平静草原
	{
		loadimage(&img[0], L"E:\\store\\source code\\MySnake\\image\\dirt.jpg");//泥土代表空
		loadimage(&img[1], L"E:\\store\\source code\\MySnake\\image\\food_apple.jpg");//苹果
		loadimage(&img[2], L"E:\\store\\source code\\MySnake\\image\\stone.jpg");//原石代表墙
		loadimage(&img[3], L"E:\\store\\source code\\MySnake\\image\\poison_rotton.jpg");//毒草
		loadimage(&img[4], L"E:\\store\\source code\\MySnake\\image\\furnace.jpg");
		loadimage(&img[5], L"E:\\store\\source code\\MySnake\\image\\stonebrick.jpg");
		
	}
	else if (scene == 1)//森林
	{
		loadimage(&img[0], L"E:\\store\\source code\\MySnake\\image\\dirt_forest.jpg");
		loadimage(&img[1], L"E:\\store\\source code\\MySnake\\image\\food_forest.jpg");
		loadimage(&img[2], L"E:\\store\\source code\\MySnake\\image\\wall_forest.jpg");
		loadimage(&img[3], L"E:\\store\\source code\\MySnake\\image\\poison_forest.jpg");
		loadimage(&img[4], L"E:\\store\\source code\\MySnake\\image\\furnace.jpg");
		loadimage(&img[5], L"E:\\store\\source code\\MySnake\\image\\stonebrick.jpg");
	}
	else if (scene == 3)
	{
		loadimage(&img[0], L"E:\\store\\source code\\MySnake\\image\\sand_floor.jpg");
		loadimage(&img[1], L"E:\\store\\source code\\MySnake\\image\\sand_food.jpg");
		loadimage(&img[2], L"E:\\store\\source code\\MySnake\\image\\sand_wall.jpg");
		loadimage(&img[3], L"E:\\store\\source code\\MySnake\\image\\sand_poison.jpg");
		loadimage(&img[4], L"E:\\store\\source code\\MySnake\\image\\furnace.jpg");
		loadimage(&img[5], L"E:\\store\\source code\\MySnake\\image\\stonebrick.jpg");
	}
	else if (scene == 2)
	{
		loadimage(&img[0], L"E:\\store\\source code\\MySnake\\image\\ice_floor.jpg");
		loadimage(&img[1], L"E:\\store\\source code\\MySnake\\image\\ice_food.jpg");
		loadimage(&img[2], L"E:\\store\\source code\\MySnake\\image\\ice_wall.jpg");
		loadimage(&img[3], L"E:\\store\\source code\\MySnake\\image\\ice_poison.jpg");
		loadimage(&img[4], L"E:\\store\\source code\\MySnake\\image\\furnace.jpg");
		loadimage(&img[5], L"E:\\store\\source code\\MySnake\\image\\stonebrick.jpg");
	}
	else if (scene == 4)
	{   //地狱
		loadimage(&img[0], L"E:\\store\\source code\\MySnake\\image\\nether_floor.jpg");
		loadimage(&img[1], L"E:\\store\\source code\\MySnake\\image\\nether_food.jpg");
		loadimage(&img[2], L"E:\\store\\source code\\MySnake\\image\\nether_wall.jpg");
		loadimage(&img[3], L"E:\\store\\source code\\MySnake\\image\\nether_poison.jpg");
		loadimage(&img[4], L"E:\\store\\source code\\MySnake\\image\\furnace.jpg");
		loadimage(&img[5], L"E:\\store\\source code\\MySnake\\image\\stonebrick.jpg");
	}
	//似乎存在BUG
	//gotoxy(5, 45);
	//printf("当前得分： %d", score);
	//gotoxy(7, 45);
//	printf("最大食物数： %d", foodNum);
	int count = 0;
	//遍历链表打印蛇身体
	snake * cur = head;
	if (head == NULL)
	{
		//printf("头指针为空");
	}
	else
	{
		
		while (cur != NULL)
		{
			count += 1;
			map[cur->positionX][cur->positionY] = 2;
			cur = cur->next;
		}
		if (count == 1)
		{
			gameStatus = 0;
		}

		map[head->positionX][head->positionY] = 6;//单独给蛇头一个值

		for (int i = 0; i < MAPX; i++)
		{
			for (int j = 0; j < MAPY; j++)
			{
				switch (map[i][j]) {
				case 0:
					//setfillcolor(BLACK);//数组的值对应空气的时候打印与底色相同或者不打印？
					//solidrectangle(j * 30, i * 30, (j + 1) * 30, (i + 1) * 30);
					putimage(j * 30, i * 30, &img[0]);
					break;
				case 1:
					putimage(j * 30, i * 30, &img[2]);
					break;
				case 2:
					putimage(j * 30, i * 30, &img[5]);
					break;
				/*case 4:
					gotoxy(i, 2 * j);
					printf("  ");
					break;*/
				case 5://食物
					putimage(j * 30, i * 30, &img[1]);
					break;
				case 6://头
					putimage(j * 30, i * 30, &img[4]);
					break;
				case 7://毒草
					putimage(j * 30, i * 30, &img[3]);
					break;
				/*case 12:
					gotoxy(i, 2 * j);
					printf("??");
					break;*/
				}
			}
		}

		//gotoxy(9, 45);
		//printf("场上食物数： %d", foodCount);
		gotoxy(2, 46);
	//	printf("                 ");
		gotoxy(2, 46);
		//printf("长度：%d", count);
	}
}

void iniSnake()
{
	/*对蛇进行初始化
	*初始长度为X节  蛇头坐标在中心
	*/
	//建立双向链表

	snake * current,*prev;
	for (int i = 0; i < 3; i++)
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

//蛇的移动,撞墙判断？
void move(int dirX,int dirY)
{
	int result = 0;
	AX = dirX;
	AY = dirY;

	if(walkMode == 1 ||walkMode == 3)
	theWall(dirX, dirY);                  

	addSnake(AX, AY);
	//if (walkMode == 1)	
	result = judge();
	if (result != 1)//不吃到食物时，每次移动都删掉尾节点
	{
		delTail();
		if(walkMode == 0)
		if (result == 2)
			delTail();//吃到毒 再减少一次
		result = 0;
	}

	
	Clearer();//清除过期的食物/清除过期的毒草
	if (dimageShow == 0) {
		gotoxy(21, 8);
		//printf("                                          ");
	}
	else
	{
		dimageShow--;
	}
}


//游戏主循环
void playGame()
{

	 kbhitCount = 0;//统计按键次数
	foodNum = rand_food_y() % 10 + 15;//最大食物数量
	poisonNum = (rand_food_y() * 213) % 10 + 4;//最大毒数量
	foodGroup = (food*)calloc(sizeof(food), foodNum);
	poisonGroup = (poison*)calloc(sizeof(poison), poisonNum);
	gameStatus = 1;
	//这两个数组用来保存一系列指令的方向
	int directionX[20] = { 0 }, directionY[20] = { 0 };
	//初始方向向上
	directionX[0] = -1;
	directionY[0] = 0;

	key = (char*)calloc(sizeof(char), 50);//按键数组最多接受20个
	autoKey = (char*)calloc(sizeof(char), 50);

	for (int i = 0; i < 50; i++) {
		key[i] = 0;
		autoKey[i] = 0;
	}

	
	int step = 0;//走的步数
	char lastKey;
	while (gameStatus)
	{
		printKey();
		generatePoison();
		generateFood();//生成食物及去除过期食物  !!吃到智慧草 食物寿命无限

		if (!kbhit())
		{

			if (walkMode == 1 || walkMode == 3)
			{
				gotoxy(1, 42);
				//printf("AUTO MODE");
				if (autoRound != 0)
				{
					isFinish = 0;//不执行BFS
					autoRound--;
				}
				else
					isFinish = 1;

				if ( isFinish) {
					BFS();				//BFS(); 计算   现在只能找一次。。。然后把自己撞死了
					loadKey();//加载-key 将autoKEY 转为 key
					kbhitCount = 0;
					step = 0;
				}
				

	  //下面的代码将key转化为具体的行走
				int compare;//比较的对象 的下标
					if (kbhitCount == 0){//此时比较对象为自己原有的值，否则是和上一项比较
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
						
			}

			kbhitCount++;

			//	getch();
			//step++;
		}
		//当 key 的数组中还存在 按键时 读取按键
		move(directionX[step], directionY[step]);
		//走过后清除这一步的数据(有多条指令的时候)，并准备读取下一指令
		if (step != 0) {
			lastKey = key[step];//?
			key[step] = 0;
		}

		if (walkMode == 1 &&key[step + 1] == 0)//读取下一步发现没有按键时   //撞墙判断---------------/////////////待修改
		{	
			clearKey();
			BFS();
			loadKey();
			//保留当前方向
			//directionX[0] = directionX[step];
			//directionY[0] = directionY[step];
			step = 0;//又返回第一步，第一步即等会输入的值
			kbhitCount = 0;//指令数变为1条
		}
		else if (key[step + 1] == 0)
		{
			directionX[0] = directionX[step];
			directionY[0] = directionY[step];
			step = 0;//又返回第一步，第一步即等会输入的值
			kbhitCount = 0;//指令数变为1条
		}
		else {
			step += 1;
			//kbhitCount++;
		}//下一轮还是读取储存好的指令

		printMap();
		Sleep(100);
	}
		else//当检测到键盘输入时   如果本次输入与上次输入相同，不接受
		{
			if (walkMode == 3 )
			{
				step = 0;
				clearKey();
				walkMode = 0;
			}
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
				
				//if (key[kbhitCount] == 'c')
					//walkMode = 1;
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
				//printf("%按键%d\n", kbhitCount);
			
			/*else if(walkMode == 2)
			{
				kbhitCount--;
				if (kbhitCount == 0)//当走完计算出的路径时返回手动行走
					walkMode = 1;
			}*/
			
		}
		
	}
	system("cls");
	gotoxy(10, 10);
	//printf("GAME OVER");
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
//	gotoxy(24, 0);
//	printf("FOOD NUM:%d", foodNum);
	int x, y;
	x = ((rand() * 133) % (MAPX - 3)) + 2;
	y = ((rand() * 334) % (MAPY - 3)) + 2;
	//printf("%d,%d", x, y);
	int isGenerate = 0;
	//调节生成食物的速率
	isGenerate = (rand() * 100) % 10;
	if (isGenerate < 8)
	{
		if (x > 1 && x < MAPX - 2  && y>1 && y < MAPY - 2 && map[x][y] != 1 && foodCount < (foodNum) && map[x][y] != 2 && map[x][y] != 5 && map[x][y] != 6 && map[x][y] != 7)
		{	
			for (int i = 0; i < foodNum; i++) {//找一个位置储存食物
				if (foodGroup[i].status == 0)//该位置本来不存在食物的时候
				{
					foodGroup[i].foodX = x;
					foodGroup[i].foodY = y;
					foodGroup[i].foodLife = (rand_food_x() * 100) % 50 + 50;//食物的寿命
					foodGroup[i].status = 1;
					map[x][y] = 5;
					i = foodNum;
					foodCount += 1;
				}
			}
			

			
			}	    
		}	
	}


void generatePoison()
{
	srand(time(NULL) + 100);
	int x, y;
	x = (rand() * 287) % MAPX + 1;
	y = (rand() * 99) % MAPY + 1;
	int isGenerate = 0;
	//调节生成的速率
	isGenerate = (rand() * 100) % 18;
	if (isGenerate < 12)
	{
		if (x > 0 && x < MAPX && y>0 && y < MAPY && map[x][y] != 1 && poisonCount < (poisonNum - 1) && map[x][y] != 2)
		{
			for (int i = 0; i < poisonNum; i++) {//找一个位置储存食物
				if (poisonGroup[i].status == 0)//该位置本来不存在食物的时候
				{
					poisonGroup[i].poisonX = x;
					poisonGroup[i].poisonY = y;
					poisonGroup[i].posionLife = (rand_food_x() * 100) % 22 + 20;//寿命
					poisonGroup[i].status = 1;
					map[x][y] = 7;
					i = poisonNum;
				}
			}
			poisonCount += 1;

			gotoxy(7, 45);
		//	printf("场上毒数： %d", poisonCount);
		}
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
	if (map[x][y] == 5)//头的坐标和食物的坐标重合
	{
		isFinish = 1;
		for (int i = 0; i < foodNum; i++)
			if (foodGroup[i].foodX == x && foodGroup[i].foodY == y)
			{
				gotoxy(21, 0);
				foodGroup[i].status = 0;
				foodCount -= 1;//有问题，不能这样。。这样写吃到中间一段 导致最后一个遍历不到了
				score += 100;
				result = 1;
				return result;

			}
	}

	if (map[x][y] == 7 && walkMode == 0)//头的坐标和毒物的坐标重合
	{
		walkMode = 3;
		for (int i = 0; i < poisonNum; i++)
			if (poisonGroup[i].poisonX == x && poisonGroup[i].poisonY == y)
			{	//找到吃到的坐标
				gotoxy(21, 0);
			
				
				//printf("No no no!!      ");
				poisonGroup[i].status = 0;
				poisonCount -= 1;
				score -= 100;
				result = 2;
				return result;

			}
	}
	//撞墙了！
	else if (map[x][y] == 1) {
		//if(walkMode == 0)
		gameStatus = 0;

	}

	//咬到自己


	else if (map[x][y] == 2 && walkMode == 0)//蛇头坐标和身体坐标重合
	{
				int count = 0;
				snake * find = tail;
				while (find != NULL)
				{
					count += 1;
					if (find->positionX == x && find->positionY == y)
						break;
					find = find->previous;
				}
				for (int i = 0; i < count; i++)
				{
					delTail();
				}
				gotoxy(21, 8);
			//	printf("！！痛！！你失去了%d节", count);
				dimageShow = 5;
				
	}
			
	
	return result;
}

void Clearer()
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
				foodCount--;
			}
		}
	}

	//所有存在的毒物的生命 -1
	for (int i = 0; i < poisonNum; i++)
	{
		if (poisonGroup[i].status == 1)
		{
			poisonGroup[i].posionLife--;

			if (poisonGroup[i].posionLife <= 0)
			{
				poisonGroup[i].status = 0;
				map[poisonGroup[i].poisonX][poisonGroup[i].poisonY] = 0;
				poisonCount--;
			}
		}
	}
}

void printKey()
{
	gotoxy(25, 0);
		printf(" ");//清除走过的
		gotoxy(25, 0);
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
		case 0:
			printf(" ");
			break;

		default:
			break;

		}
		//printf("\n");
	}
}
/*
----------------BFS---------------
*/

void visit(int row, int col)//下一步尝试的位置
{
	for (int i = 0; i < MAPX; i++)
	{
		maze[i][0] = 1;
		maze[i][MAPY - 1] = 1;
	}

	for (int i = 0; i < MAPY; i++)
	{
		maze[0][i] = 1;
		maze[MAPX - 1][i] = 1;
	}
	struct point visit_point = { row, col, front - 1 };
	if (maze[row][col] == 5)
		maze[row][col] = 5;
	else if (maze[row][col] == 1)
		maze[row][col] = 1;
	else if(maze[row][col] == 7)
		maze[row][col] = 7;
	else
	{
		maze[row][col] = 10;
	}
	//maze[row][col] = 11;//搜索标记 防止重复搜索
	enqueue(visit_point);
}

void BFS()
{
	int isSearch = 0;
	//加载地图 用于搜索路径
	for (int i = 0; i < MAPX; i++)
	{
		for (int j = 0; j < MAPY; j++)
		{

			maze[i][j] = map[i][j];//将地图拷贝
		}
	}


	//确认目标坐标   loop
	for (int i = 0; i < foodNum; i++)
	{
		if (foodGroup[i].status == 1) {
			int tarX = foodGroup[i].foodX;
			int tarY = foodGroup[i].foodY;
			maze[tarX][tarY] = 5;//打上记号--终点
		}
	}
	if (foodCount == 0)
	{
		clearKey();
		maze[tail->positionX][tail->positionY] = 5;
	}
		int x, y;
	clean_queue();
	struct point p;//起始点  蛇头---------------------------------怎么在第二期
	gotoxy(10, 42);
	//printf("SNAKE HEAD POI:%d,%d", head->positionX, head->positionY);
	p.col = head->positionY;
	p.row = head->positionX;
	x = head->positionX;
	y = head->positionY;
	p.predecessor = -1;
	enqueue(p);//入队,rear --1
	
	
	while (!is_empty()) {//队列不为空的时候，循环
		p = dequeue();//出队，p等于队首后一??   front----1
		if (maze[p.row][p.col] == 5) {			
			isSearch = 1;
			break;//到达目标点的时候   maze[p.row][p.col] == 5
		}

		if (p.col + 1 < MAPY - 1 /* right 向右不撞边界*/
			&& (maze[p.row][p.col + 1] == 0 || maze[p.row][p.col + 1] == 5 || maze[p.row][p.col + 1] == 6) && maze[p.row][p.col + 1] != 1  && maze[p.row][p.col + 1] != 10)//地图首先要可以走
			visit(p.row, p.col + 1);//visit这一区域

		if (p.row + 1 < MAPX - 1 /* down */
			&& (maze[p.row + 1][p.col] == 0 || maze[p.row + 1][p.col] == 5 || maze[p.row + 1][p.col] == 6) && maze[p.row + 1][p.col] != 1  && maze[p.row + 1][p.col] != 10)
			visit(p.row + 1, p.col);

		if (p.col - 1 > 0 /* left */
			&& (maze[p.row][p.col - 1] == 0 || maze[p.row][p.col - 1] == 5 || maze[p.row][p.col - 1] == 6) && maze[p.row][p.col - 1] != 1  && maze[p.row][p.col - 1] != 10)
			visit(p.row, p.col - 1);
		if (p.row - 1 > 0 /* up */
			&& (maze[p.row - 1][p.col] == 0 || maze[p.row - 1][p.col] == 5|| maze[p.row - 1][p.col] == 6) && maze[p.row - 1][p.col] != 1   && maze[p.row - 1][p.col] != 10)
			visit(p.row - 1, p.col);
	}
	

		if (isSearch == 1)//当搜索到食物的时候
		{
			isSearch = 0;

			int keyCount = 49;
			while (p.predecessor != -1) {//从最后一步一直打到第一步
				if (p.row != queue[p.predecessor].row)//如果行数发生了改变
				{
					if (p.row == (queue[p.predecessor].row - 1))//本行在上一行的上面
					{
						autoKey[keyCount] = KEYUP;
					}
					else {
						autoKey[keyCount] = KEYDOWN;
					}
				}

				if (p.col != queue[p.predecessor].col)//如果行数发生了改变
				{
					if (p.col == (queue[p.predecessor].col - 1))//本列在上一列的左边
					{
						autoKey[keyCount] = KEYLEFT;//下移
					}
					else {
						autoKey[keyCount] = KEYRIGHT;
					}
				}
				p = queue[p.predecessor];
				keyCount--;
			}
			
			//result = 0;
		}
}

void loadKey()
{   
	int i = 0;
	for (int j = 0;j < 50;j++)
	{	
		if (autoKey[j] != 0) {
			
			//printf("load key");
			key[i] = autoKey[j];
			autoKey[j] = 0;
			i++;
		}
	}
	autoRound = i;
	step = 0;
	isFinish = 0;
}

void clearKey() {  //清空所有按键
	int i = 0;
	while (key[i] != 0)
	{
		key[i] = 0;
		directionX[i] = 0;
		directionY[i] = 0;
		i++;
	}
	step = 0;
	kbhitCount = 0;

}

void theWall(int dirX,int dirY)
{
	if (foodCount == 0)
	{
		autoRound = 0;
		clearKey();
	}
	//WALKMODE3    手动躲模式
	int flag = 0;
	AX = dirX;
	AY = dirY;
	if (map[head->positionX + AX][head->positionY + AY] == 1) {//看看下一步的位置	
		if (walkMode == 3)
		{
			//autoRound = 0;
		//	isFinish = 1;//
			clearKey();
			char danger,get;
		    getch();
			danger = getch();//下一步就要撞墙手动躲避

			switch (danger)
			{
			case KEYUP:
				AX = -1;
				AY = 0;
				break;
			case KEYDOWN:
				AX = 1;
				AY = 0;
				break;
			case KEYLEFT:
				AX = 0;
				AY = -1;
				break;
			case KEYRIGHT:
				AX = 0;
				AY = 1;
				break;
			default:
				break;
			}

		}
		else if (walkMode == 1) {
			clearKey();
			//getch();
			//autoRound = 0;
			/**
			if (AX == 1)
				AX = -1;
			else if(AX == -1)
				AX = 1;
		else if (AY == 1)
			AY = -1;
		else if (AY == -1)
			AY = 1;
			*/
			
			if ((AX == 1 || AX == -1) && flag == 0)//当前方向向下或者向上
			{
				//autoRound = 0;
				flag = 1;
				//clearKey();
				AX = 0;
				AY = 1;
				if (map[head->positionX + AX][head->positionY + AY] == 1)
					AY = -1;
			}
			if ((AY == 1 || AY == -1) && flag == 0) {
				autoRound = 0;
				flag = 1;
				//clearKey();
				AY = 0;
				AX = 1;
				if (map[head->positionX + AX][head->positionY + AY] == 1)
					AX = -1;
			}

		}
	}
	

}

void beforeGame()//游戏开始时的选择界面
{
	IMAGE select[10];
	loadimage(&select[0], L"E:\\store\\source code\\MySnake\\image\\start.jpg");
	loadimage(&select[1], L"E:\\store\\source code\\MySnake\\image\\load.jpg");
	loadimage(&select[2], L"E:\\store\\source code\\MySnake\\image\\exit.jpg");
	loadimage(&select[3], L"E:\\store\\source code\\MySnake\\image\\rank.jpg");
	int choose = 0;
	putimage(0, 0, &select[0]);
	while (1)
	{
		if (kbhit)
		{   
			char get;
			if ((get = getch()) == 13)//按下回车时开始游戏-等操作
			{
				IMAGE lev;
				loadimage(&lev, L"E:\\store\\source code\\MySnake\\image\\level1.jpg");
				initgraph(1000, 620);
				putimage(0, 0, &lev);
				if (choose == 0)
					break;
				if (choose == 2)
					exit(0);
			}
			else
			{
				switch (get)
				{
				case KEYRIGHT:
					choose += 1;
					break;
				case KEYLEFT:
					choose -= 1;
					break;
				default:
					break;
				}
				if (choose == 4)
					choose = 0;

				if (choose == -1)
					choose = 2;
				putimage(0, 0, &select[choose]);
			}
		}
	}

}

void setting()
{
	initgraph(1000, 620);
	IMAGE sceneSel[5];
	IMAGE level[3];
	difficulty = 0;
	loadimage(&level[0], L"E:\\store\\source code\\MySnake\\image\\easy.jpg");
	loadimage(&level[1], L"E:\\store\\source code\\MySnake\\image\\medium.jpg");
	loadimage(&level[2], L"E:\\store\\source code\\MySnake\\image\\difficult.jpg");

	loadimage(&sceneSel[0], L"E:\\store\\source code\\MySnake\\image\\sceneselect0.jpg");
	loadimage(&sceneSel[1], L"E:\\store\\source code\\MySnake\\image\\sceneselect1.jpg");
	loadimage(&sceneSel[2], L"E:\\store\\source code\\MySnake\\image\\sceneselect2.jpg");
	loadimage(&sceneSel[3], L"E:\\store\\source code\\MySnake\\image\\sceneselect3.jpg");
	loadimage(&sceneSel[4], L"E:\\store\\source code\\MySnake\\image\\sceneselect4.jpg");
	//进行地图选择  产生不同的地形
	//温和草原
	//富饶森林
	//干旱沙漠
	//荒芜冰原
	//极端地狱
	//自定义

	//进行场景选择
	putimage(0, 0, &sceneSel[0]);
	while (1)
	{

		if (kbhit)
		{
			char get;
			if ((get = getch()) == 13)//按下回车时确认场景
				break;
			else
			{
				switch (get)
				{
				case KEYDOWN:
					scene += 1;
					break;
				case KEYUP:
					scene -= 1;
					break;
				default:
					break;
				}
				if (scene == 5)
					scene = 0;

				if (scene == -1)
					scene = 4;
				putimage(0, 0, &sceneSel[scene]);
			}
		}
	}


	//加载地图
	for (int i = 0; i < MAPX; i++)
		for (int j = 0; j < MAPY; j++)
			map[i][j] = mapSel[scene][i][j];


	//进行难度选择
	putimage(0, 0, &level[0]);
	while (1)
	{
		
		if (kbhit)
		{
			char get;
			if ((get = getch()) == 13)//按下回车时确认难度
				break;
			else
			{
				switch (get)
				{
				case KEYDOWN:
					difficulty += 1;
					break;
				case KEYUP:
					difficulty -= 1;
					break;
				default:
					break;
				}
				if (difficulty == 3)
					difficulty = 0;

				if (difficulty == -1)
					difficulty = 2;
				putimage(0, 0, &level[difficulty]);
			}
		}
	}

}