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
#include <string.h> 
#include <mmsystem.h>
#include <setjmp.h>

#pragma comment(lib, "Winmm.lib") 
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
#define AIR 0
#define WALL 1
#define SNAKEHEAD 6
#define POISON 7
#define TNT 19
#define FOOD 5
#define SNAKEBODY 2
#define CLEVER 9
#define BOOM 20
#define SHINING 21
#define BEAUTY 22
int ad1 = 0, ad2 = 0;
int isUp = 1;//是否还进行进度打印---若通关开始无尽模式就不打印了
int hungry = 0, hungrySpeed = 4, hungryRound = 8, hungryStatus = 0, hungryShow = 4, hungryTem = 0, *hungryIc;//饥饿系统,饥饿情况
jmp_buf buf, set, upg,ove,con;//用于页面的跳转
int isSelectDifficulty = 1;
int temp = 0;
int pic[40][40] = { 0 };
int map[MAPX][MAPY] = { 0 };
//将来写到头文件中去
int beauty[MAPX][MAPY] = { 0 };
int snakeLength = 0;
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
							{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } } };
int AX, AY;
int maze[MAPX][MAPY] = { 0 }; //用于搜索
int autoNum = 0,autoRound = 5;
int step;
int kbhitCount;
int gameStatus = 1;											   //在游戏开始时确认同时存在的最多食物数量
int totalScore = 0,curScore = 0;
int dimageShow = 0; //收到伤害时显示时间
int directionX[50] = { 0 }, directionY[50] = { 0 }, curDirectionX = 0,curDirectionY = 0;
int result = 0, resultp = -1;

int gameSpeed,foodScore = 0,beginSpeed = 0,speedAdd = 0,maxHug = 5;//每吃一个食物的得分（难度越高，分越高）,目标得分（难度越高，目标越高）,开始时的刷新速度，吃到食物后减少的速度,最高饱食度，根据难度而定
int eatNum = 0;
float  len = 0, printLength = 0, ad = 0, process = 0, eatWhat = 0, complete = 0;//绘制进度条 time吃到食物的计数,complete过关
int targetScore;
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
	int shinning;
	//int kind 
};
struct tnt
{
	int poisonX;
	int poisonY;
	int tntLife;
	int status;
	//int kind 
};
int difficulty = 0;//难度
int scene = 0;//地图


char* playerName, *Name;
int cleverCount = 0;
int tntCount = 0;
int foodCount = 0;//统计已有的食物数
int poisonCount = 0;
int tntNum;
int foodNum;
int poisonNum;
tnt * tntGroup;
food * foodGroup;
poison * poisonGroup;

char* key, *autoKey;//按键
int isFinish = 1;
snake* head, *tail;
int walkMode = 0;//行走模式 0-手动,1-自动 3_半自动
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
void generateCleverwater();
void generateFood();
void generatePoison();
void generateTnt();
void printBeauty();
int rand_food_x(void);
int rand_food_y(void);
int judge();
void Clearer();
void loadKey();//加载计算出来的路径
void clearKey();//清除已有的路径
void BFS();
void theWall(int dirX, int dirY);//防止撞墙--在每次移动后进行
void beforeGame();//游戏开始界面
void setting();
void printWord();//负责文字输出  地图右边
void restart();//初始化
void rankList();//排行榜
void saveData();//结束一局后储存成绩
void saveGame();//如果不是由于死亡而退出，保存游戏
void continurGame();
void loadGame();
void loadSetting();
void upgradeProcess();//过关进度,过关后重新初始化
void upgrade();
void foodAndHungry();
void showStart();
void gameFinish();//通关
void generateRandBeauty();

DWORD WINAPI myfun1(LPVOID lpParameter);                   //声明线程函数  
DWORD WINAPI myfun2(LPVOID lpParameter);
DWORD WINAPI drawProcess(LPVOID lpParameter);
DWORD WINAPI clearBar(LPVOID lpParameter);
DWORD WINAPI hungryMsg(LPVOID lpParameter);
HANDLE h1,h2, h3,up,hug;                                         //定义句柄变量  
int main()
{

	playerName = (char*)calloc(sizeof(char), 20);
	playerName = "player";
	//h2 = ::CreateThread(NULL, 0, myfun2, NULL, 0, NULL);
	//	foodNum = (rand_food_x() *133) % 10 + 14;
	int n = 0;
	poisonNum = (rand_food_x() * 12) % 10 + 12;
	n = setjmp(buf);///最好在选择了难度后再决定								   /*注意 全角字符使用goto语句时要*/
	if(n == 0)
	initgraph(1000, 620);//画布大小
	HideCursor();
	while (gameStatus)
	{

		beforeGame();
		if (isSelectDifficulty == 1)//不是读档开始
		{
			setting();//游戏设置 玩家姓名，地图选择，难度选择
			iniSnake();
			showStart();
		}

		else {
			//upgradeProcess();
		}
		int m = setjmp(upg);
		isSelectDifficulty == 1;
		if (m == 1) {
			mciSendString(_T("close vic"), NULL, 0, NULL);//关闭音乐
			for (int i = 0; i < MAPX; i++)
				for (int j = 0; j < MAPY; j++)
					if (beauty[i][j] == BOOM)
					{
						beauty[i][j] = AIR;
					}
			iniSnake();
			walkMode = 0;
			clearrectangle(0, 603, 600, 620);
		}

		iniMap();
		loadSetting();
		generateRandBeauty();
		playGame();
	}

	return 0;
}

//地图初始化
void iniMap()
{	//边框
	//initgraph(1000, 620);
	IMAGE img[5];
	loadimage(&img[0], L"./image/scene_grassland.jpg");
	loadimage(&img[1], L"./image/scene_forest1.jpg");
	loadimage(&img[2], L"./image/scene_iceland.jpg");
	loadimage(&img[3], L"./image/scene_sand.jpg");
	loadimage(&img[4], L"./image/scene_nether.jpg");

	putimage(0, 0, &img[scene]);
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

	BeginBatchDraw();
	//改为图形界面了
	IMAGE img[10];
	if (scene == 0)//平静草原
	{
		loadimage(&img[0], L"./image/dirt.jpg");//泥土代表空
		loadimage(&img[1], L"./image/food_apple.jpg");//苹果
		loadimage(&img[2], L"./image/stone.jpg");//原石代表墙
		loadimage(&img[3], L"./image/poison_rotton.jpg");//毒草
		loadimage(&img[4], L"./image/furnace.jpg");
		loadimage(&img[5], L"./image/stonebrick.jpg");
		loadimage(&img[6], L"./image/tnt.jpg");
		loadimage(&img[7], L"./image/grass_clever.jpg");
		loadimage(&img[8], L"./image/grass_boom.jpg");
	}
	else if (scene == 1)//森林
	{
		loadimage(&img[0], L"./image/dirt_forest.jpg");
		loadimage(&img[1], L"./image/food_forest.jpg");
		loadimage(&img[2], L"./image/wall_forest.jpg");
		loadimage(&img[3], L"./image/poison_forest.jpg");
		loadimage(&img[4], L"./image/furnace.jpg");
		loadimage(&img[5], L"./image/stonebrick.jpg");
		loadimage(&img[6], L"./image/tnt.jpg");
		loadimage(&img[7], L"./image/forest_clever.jpg");
		loadimage(&img[8], L"./image/forest_boom.jpg");
	}
	else if (scene == 3)
	{
		loadimage(&img[0], L"./image/sand_floor.jpg");
		loadimage(&img[1], L"./image/sand_food.jpg");
		loadimage(&img[2], L"./image/sand_wall.jpg");
		loadimage(&img[3], L"./image/sand_poison.jpg");
		loadimage(&img[4], L"./image/furnace.jpg");
		loadimage(&img[5], L"./image/stonebrick.jpg");
		loadimage(&img[6], L"./image/tnt.jpg");
		loadimage(&img[7], L"./image/sand_clever.jpg");
		loadimage(&img[8], L"./image/sand_boom.jpg");
	}
	else if (scene == 2)
	{
		loadimage(&img[0], L"./image/ice_floor.jpg");
		loadimage(&img[1], L"./image/ice_food.jpg");
		loadimage(&img[2], L"./image/ice_wall.jpg");
		loadimage(&img[3], L"./image/ice_poison.jpg");
		loadimage(&img[4], L"./image/furnace.jpg");
		loadimage(&img[5], L"./image/stonebrick.jpg");
		loadimage(&img[6], L"./image/tnt.jpg");
		loadimage(&img[7], L"./image/ice_clever.jpg");
		loadimage(&img[8], L"./image/ice_boom.jpg");
	}
	else if (scene == 4)
	{   //地狱
		loadimage(&img[0], L"./image/nether_floor.jpg");
		loadimage(&img[1], L"./image/nether_food.jpg");
		loadimage(&img[2], L"./image/nether_wall.jpg");
		loadimage(&img[3], L"./image/nether_poison.jpg");
		loadimage(&img[4], L"./image/furnace.jpg");
		loadimage(&img[5], L"./image/stonebrick.jpg");
		loadimage(&img[6], L"./image/tnt.jpg");
		loadimage(&img[7], L"./image/nether_clever.jpg");
		loadimage(&img[8], L"./image/nether_boom.jpg");
	}

	//遍历链表打印蛇身体
	snake * cur = head;
	snakeLength = 0;
	while (cur != NULL)
	{
		snakeLength += 1;
		map[cur->positionX][cur->positionY] = 2;
		cur = cur->next;
	}

	if (snakeLength == 1)
	{
		TerminateThread(up, 0);
		mciSendString(_T("close music"), NULL, 0, NULL);//关闭音乐
		PlaySound(TEXT("./music/die.wav"), NULL, SND_FILENAME | SND_ASYNC);
		Sleep(1000);
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

			case 5://食物
				putimage(j * 30, i * 30, &img[1]);
				break;
			case 6://头
				putimage(j * 30, i * 30, &img[4]);
				break;
			case 7://毒草
				putimage(j * 30, i * 30, &img[3]);
				break;
			case 19://tnt
				putimage(j * 30, i * 30, &img[6]);
				break;
			case CLEVER:
				putimage(j * 30, i * 30, &img[7]);
				break;
			case BOOM:
				putimage(j * 30, i * 30, &img[8]);
				break;


			}
		}
	}


	printBeauty();
	EndBatchDraw();
	if (scene == 4 && curScore == targetScore)
		setjmp(con);
	if (eatWhat != 0 && isUp == 1) {
		upgradeProcess();
		upgrade();
	}
}

void iniSnake()
{

	/*对蛇进行初始化
	*初始长度为X节  蛇头坐标在中心
	*/
	//建立双向链表
	head = NULL;
	snake * current, *prev;
	for (int i = 0; i < 3; i++)
	{
		current = (struct snake*) calloc(sizeof(struct snake), 1);
		if (head == NULL)
		{
			current->positionX = (MAPX / 2);
			current->positionY = (MAPY / 2);
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
	snake* add = (snake*)calloc(sizeof(snake), 1);
	add->positionX = head->positionX + x;
	add->positionY = head->positionY + y;
	add->next = head;
	head->previous = add;
	head = add;
}

//删除尾节点
void delTail()
{
	if (temp == 1)
		map[tail->positionX][tail->positionY] = BOOM;
	else
		map[tail->positionX][tail->positionY] = 0;
	tail = tail->previous;
	free(tail->next);
	tail->next = NULL;

}

//蛇的移动,撞墙判断？
void move(int dirX, int dirY)
{

	AX = dirX;
	AY = dirY;

	if (walkMode == 1 || walkMode == 3)
		theWall(dirX, dirY);

	addSnake(AX, AY);
	//if (walkMode == 1)	
	result = judge();
	if (result != FOOD)//不吃到食物时，每次移动都删掉尾节点
	{
		delTail();

		if (result == POISON)
			delTail();//吃到毒 再减少一次

	}
	/*if (hungryStatus == 1)
	{
		hungryStatus = 0;
		delTail();
	}*/



	Clearer();//清除过期的食物/清除过期的毒草
	if (dimageShow == 0) {
		gotoxy(21, 8);
	}

}


//游戏主循环
void playGame()
{
	//根据场景切换音乐


	kbhitCount = 0;//统计按键次数


	gameStatus = 1;
	//这两个数组用来保存一系列指令的方向
	//初始方向向上
	if (isSelectDifficulty == 1)
	{
		directionX[0] = -1;
		directionY[0] = 0;
		isSelectDifficulty = 0;
	}
	key = (char*)calloc(sizeof(char), 50);//按键数组最多接受20个
	autoKey = (char*)calloc(sizeof(char), 50);

	for (int i = 0; i < 50; i++) {
		key[i] = 0;
		autoKey[i] = 0;
	}


	int step = 0;//走的步数
	char lastKey;
	if(gameStatus == 1)
	printMap();///kkkkkkkkkkkkkkkkkkkk

	Sleep(1000);
	while (gameStatus)
	{
		
		printWord();
		if (eatNum == 2) {
			generateCleverwater();
			eatNum = 0;
		}
		generatePoison();
		generateFood();//生成食物及去除过期食物  !!吃到智慧草 食物寿命无限
		generateTnt();
		if (!kbhit())
		{

			if ((walkMode == 1 || walkMode == 3) && autoRound > 0 && autoRound != 5)
			{

				if (autoNum != 0 )
				{
					isFinish = 0;//不执行BFS
					autoNum--;
				}
				else
					isFinish = 1;

				if (isFinish) {
					BFS();				//BFS(); 计算   现在只能找一次。。。然后把自己撞死了
					loadKey();//加载-key 将autoKEY 转为 key
					kbhitCount = 0;
					step = 0;
				}

				int flag = 0;
				//下面的代码将key转化为具体的行走
				int compare;//比较的对象 的下标
				if (kbhitCount == 0) {//此时比较对象为自己原有的值，否则是和上一项比较
					compare = 0;
				}
				else
				{
					compare = kbhitCount - 1;
				}


				if (directionX[compare] == 1 && flag == 0)//down   原来的方向向下时！就不能向上
				{
					flag = 1;
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


				if (directionX[compare] == -1 && flag == 0) //up
				{
					flag = 1;
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
				if (directionY[compare] == 1 && flag == 0)//向右移动
				{
					flag = 1;
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

				if (directionY[compare] == -1 && flag == 0)
				{
					flag = 1;
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
				flag = 0;
				kbhitCount++;

	
			}
			curDirectionX = directionX[step];
			curDirectionY = directionY[step];
			//当 key 的数组中还存在 按键时 读取按键
			move(directionX[step], directionY[step]);

			//走过后清除这一步的数据(有多条指令的时候)，并准备读取下一指令
			if (step != 0) {
				lastKey = key[step];//?
				key[step] = 0;
			}

			if (walkMode == 1 && key[step + 1] == 0)//读取下一步发现没有按键时   //撞墙判断---------------/////////////待修改
			{
				clearKey();
				BFS();
				loadKey();

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
			if (gameStatus != 0 )
				printMap();
			Sleep(gameSpeed);
		}
		else//当检测到键盘输入时   如果本次输入与上次输入相同，不接受
		{

			char command;
			command = getch();//取得 方向键值 第一部分
			if (command == 'q')
			{
				PlaySound(TEXT("./music/save.wav"), NULL, SND_FILENAME | SND_ASYNC);
				int tempM = walkMode;
				setbkmode(TRANSPARENT);
				settextcolor(BLACK);
				settextstyle(35, 0, _T("华文行楷"));
				TCHAR s[] = _T("游戏已经保存");
				outtextxy(665, 255, s);
				walkMode = 0;
				saveGame();
				walkMode = tempM;
				Sleep(500);
			}
			else if (command == 27)
			{
				//结束 putimiage
				Sleep(1000);
				exit(1);
			}
			else if(command == 32)
			{
				settextcolor(BLACK);
				settextstyle(40, 0, _T("华文行楷"));
				PlaySound(TEXT("./music/pause.wav"), NULL, SND_FILENAME | SND_ASYNC);
				TCHAR pause[] = _T("   -游戏暂停- ");
				outtextxy(665,450, pause);
				system("pause");
				PlaySound(TEXT("./music/notPause.wav"), NULL, SND_FILENAME | SND_ASYNC);
			}
			else if (command == 'c'){
				PlaySound(TEXT("./music/select.wav"), NULL, SND_FILENAME | SND_ASYNC);
				walkMode = 3;
		}
			else if(command == -32){//输入按键为方向键
				
				if (walkMode == 3 || walkMode == 1)//退出寻路
				{
					PlaySound(TEXT("./music/clever.wav"), NULL, SND_FILENAME | SND_ASYNC);
					autoRound = 5;
					resultp = 0;
					printWord();
					clearKey();
					step = 0;
					kbhitCount = 0;
					walkMode = 0;
					gameSpeed = beginSpeed;
				}   //自动寻路模式按键直接退出。。存在bug
				
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

			}
		}

	}
	
	//当一局over后
	setjmp(ove);
	h2 = ::CreateThread(NULL, 0, clearBar, NULL, 0, NULL);   //创建线程 
	process = 0;
	printLength = 0;
	mciSendString(_T("close music"), NULL, 0, NULL);//关闭音乐
	mciSendString(_T("open ./music/end.mp3 alias music"), NULL, 0, NULL);//打开文件
	mciSendString(_T("play music repeat"), NULL, 0, NULL);//重复播放
	IMAGE endimg[2];
	loadimage(&endimg[0], L"./image/end_restart.jpg");
	loadimage(&endimg[1], L"./image/end_exit.jpg");
	int choose = 0;
	int namecount = 5;
	TCHAR s[20];
	settextcolor(WHITE);
	settextstyle(50, 0, _T("Bauhaus 93"));
	MultiByteToWideChar(CP_ACP, 0, playerName, -1, s, 100);//转换char[]为TCHAR[]
	putimage(0, 0, &endimg[choose]);

	char* Name = (char*)calloc(sizeof(char), 20);

	TCHAR sco[20];
	_stprintf(sco, _T("%d"), totalScore);

	while (1)
	{
		outtextxy(260, 180, sco);
		outtextxy(260, 260, s);
		if (kbhit())
		{
			char get = getch();
			if (get == -32)
			{
				get = getch();
				switch (get)
				{
				case KEYDOWN:

					PlaySound(TEXT("./music/select.wav"), NULL, SND_FILENAME | SND_ASYNC);
					Sleep(100);
					choose += 1;
					if (choose == 2)
						choose = 0;
					break;
				case KEYUP:

					PlaySound(TEXT("./music/select.wav"), NULL, SND_FILENAME | SND_ASYNC);
					Sleep(100);
					choose -= 1;

					if (choose == -1)
						choose = 1;
					break;
				default:
					break;
				}
				putimage(0, 0, &endimg[choose]);



			}
			else if (get == 13)
			{
				saveData();
				PlaySound(TEXT("./music/确认.wav"), NULL, SND_FILENAME | SND_ASYNC);
				switch (choose)
				{
				case 0:
					restart();
					break;
				case 1:
					exit(0);
					break;
				default:
					break;
				}
				break;
			}
			else if (get >= 48 && get <= 126 && namecount < 10)
			{
				putimage(0, 0, &endimg[choose]);
				for (int i = 0; i < 20; i++)
					Name[i] = playerName[i];

				playerName[++namecount] = get;

				//playerName[namecount++] = get;
				//_T条件编译  使用的字符集不同
				settextcolor(WHITE);
				settextstyle(50, 0, _T("Bauhaus 93"));
				MultiByteToWideChar(CP_ACP, 0, playerName, -1, s, 100);//转换char[]为TCHAR[]
				outtextxy(260, 260, s);
			}
			else if (get == 8)
			{

				char* Name = (char*)calloc(sizeof(char), 20);
				//playerName = (char*)calloc(sizeof(char),20);
				for (int i = 0; i < namecount; i++)
					Name[i] = playerName[i];

				playerName = (char*)calloc(sizeof(char), 20);
				for (int i = 0; i < 20; i++)
					playerName[i] = Name[i];


				if (namecount >= 0)
					namecount--;
				putimage(0, 0, &endimg[choose]);
				IMAGE clear;
				loadimage(&clear, L"./image/nameclear.jpg");
				putimage(256, 256, &clear);

				MultiByteToWideChar(CP_ACP, 0, Name, -1, s, 100);//转换char[]为TCHAR[]
				outtextxy(260, 260, s);

			}

		}
	}

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
	ad1+=2;
	int isGenerate = 0;
	srand((unsigned)time(NULL) + ad1);
	ad1 *= ad1;
	int x, y;
	x = rand() % (MAPX - 3) + 2;
	srand(time(NULL) - ad2);
	y = rand() % (MAPY - 3) + 2;
	
	//调节生成食物的速率
	isGenerate = rand() % 10;
	printf("  ISGENERATE:%d  ", isGenerate);
	if (isGenerate < 7)
	{
		if (x > 1 && x < MAPX - 2 && y>1 && y < MAPY - 2 && map[x][y] != 1 && foodCount < (foodNum) && map[x][y] != 2 && map[x][y] != 5 && map[x][y] != 6 && map[x][y] != 7 && map[x][y] != 19 && map[x][y] != CLEVER)
		{
			for (int i = 0; i < foodNum; i++) {//找一个位置储存食物
				if (foodGroup[i].status == 0)//该位置本来不存在食物的时候
				{
					foodGroup[i].foodX = x;
					foodGroup[i].foodY = y;
					foodGroup[i].foodLife = (rand_food_x() * 100) % 50 + 40;//食物的寿命
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
	ad1 += ad1;
	srand((unsigned)time(NULL) + ad1);
	int x, y;
	x = rand() % MAPX + 1;
	ad1++;
	srand((unsigned)time(NULL) - ad1);
	y = rand() % MAPY + 1;
	int isGenerate = 0;
	//调节生成的速率
	isGenerate = rand() % 18;
	if (isGenerate < 6)
	{
		if (x > 0 && x < MAPX && y>0 && y < MAPY && map[x][y] != 1 && poisonCount < (poisonNum - 1) && map[x][y] != 2 && map[x][y] != 19 && map[x][y] != 7 && map[x][y] != 5 && map[x][y] != CLEVER)
		{
			for (int i = 0; i < poisonNum; i++) {//找一个位置储存
				if (poisonGroup[i].status == 0)//
				{
					poisonGroup[i].shinning = 8;//用于控制闪烁
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
		}
	}
}

void generateTnt()
{
	if (ad2 > 10000);
	ad2 = 0;

	ad2++;
	ad2 *= 2;
	srand((unsigned)time(NULL) - ad2);
	int x, y;
	x = rand() % MAPX + 1;
	srand((unsigned)time(NULL) + tail->positionY);
	y = rand() * 3 % MAPY + 1;
	int isGenerate = 0;
	//调节生成的速率
	isGenerate = rand()  % 20;
	if (isGenerate < 8)
	{
		if (x > 0 && x < MAPX && y>0 && y < MAPY && map[x][y] != 1 && poisonCount < (poisonNum - 1) && map[x][y] != 2 && map[x][y] != 5 && map[x][y] != 7)
		{
			for (int i = 0; i < tntNum; i++) {//找一个位置储存食物
				if (tntGroup[i].status == 0)//该位置本来不存在食物的时候
				{
					tntGroup[i].poisonX = x;
					tntGroup[i].poisonY = y;
					tntGroup[i].tntLife = (rand_food_x() * 100) % 22 + 20;//寿命
					tntGroup[i].status = 1;
					map[x][y] = 19;
					i = tntNum;
				}
			}
			tntCount += 1;
		}
	}
}

void generateCleverwater()
{
	cleverCount = 1;
	srand((unsigned)time(NULL));
	int x, y;
	x = rand() * 123 % MAPX + 1;
	srand((unsigned)time(NULL) + 1);
	y = rand() * 321 % MAPY + 1;
	if (map[x][y] == AIR)
		map[x][y] = CLEVER;
	//printf("%d,%d", x, y);
	//exit(1);
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

	int x = head->positionX;
	int y = head->positionY;
	//对蛇头进行判断,吃到食物后不删除尾巴
	if (map[x][y] == CLEVER)
	{
		if (autoRound == 5 || autoRound < 0) {

			//获得加速效果
			gameSpeed = 3;
			autoRound = 4;//吃到智慧药水后自动寻路吃四个食物
			PlaySound(TEXT("./music/clever.wav"), NULL, SND_FILENAME | SND_ASYNC);
			cleverCount = 0;
			walkMode = 3;
			result = CLEVER;//吃到智慧药水
		}

	}
	if (map[x][y] == 5)//头的坐标和食物的坐标重合
	{	
		if(autoRound != 5)
		autoRound--;
		eatNum++;
		hungryRound = hungrySpeed;
		hungry = maxHug;//吃到食物饱食度满
		for (int i = 0; i < maxHug ; i++)
		{
			hungryIc[i] = 0;//饱食度图片回复
		}
		curScore += foodScore;
		totalScore += foodScore;
		eatWhat = FOOD;
		result = FOOD;
		PlaySound(TEXT("./music/eat.wav"), NULL, SND_FILENAME | SND_ASYNC);
		isFinish = 1;
		for (int i = 0; i < foodNum; i++)
			if (foodGroup[i].foodX == x && foodGroup[i].foodY == y)
			{
				gotoxy(21, 0);
				foodGroup[i].status = 0;
				foodCount -= 1;//有问题，不能这样。。这样写吃到中间一段 导致最后一个遍历不到了

			}
	}

	if (map[x][y] == 7 && walkMode == 0)//头的坐标和毒物的坐标重合
	{
		eatNum--;
		eatWhat = POISON;
		cleverCount = 0;
		result = POISON;
		PlaySound(TEXT("./music/poison.wav"), NULL, SND_FILENAME | SND_ASYNC);
		for (int i = 0; i < poisonNum; i++)
			if (poisonGroup[i].poisonX == x && poisonGroup[i].poisonY == y)
			{	//找到吃到的坐标
				poisonGroup[i].status = 0;
				poisonCount -= 1;
				curScore -= 100;
				totalScore -= 100;
			}
	}
	if (map[x][y] == 19)
	{
		eatNum /= 2;
		eatWhat = TNT;
		result = TNT;
		int hx, hy;
		hx = head->positionX;
		hy = head->positionY;
		curScore /= 2;
		for (int i = 0; i < tntNum; i++)
		{
			if (tntGroup[i].poisonX == hx && tntGroup[i].poisonY == hy)
				tntGroup[i].status = 0;
			tntGroup[i].tntLife = 0;
		}
		beauty[hx][hy] = BOOM;
		beauty[hx + 1][hy] = BOOM;
		beauty[hx - 1][hy] = BOOM;
		beauty[hx][hy + 1] = BOOM;
		beauty[hx][hy - 1] = BOOM;
		PlaySound(TEXT("./music/tnt.wav"), NULL, SND_FILENAME | SND_ASYNC);
		snake * sum = head;
		int count = 0;
		while (sum != NULL)
		{
			count++;
			sum = sum->next;
		}
		for (int i = 0; i < count / 2; i++)
			delTail();
	}
	//撞墙了！
	else if (map[x][y] == 1) {
		TerminateThread(up, 0);
		PlaySound(TEXT("./music/die.wav"), NULL, SND_FILENAME | SND_ASYNC);
		Sleep(1000);
		//if(walkMode == 0)
		gameStatus = 0;


	}

	//咬到自己


	else if (map[x][y] == 2 && walkMode == 0)//蛇头坐标和身体坐标重合
	{
		PlaySound(TEXT("./music/hurt.wav"), NULL, SND_FILENAME | SND_ASYNC);
		result = SNAKEBODY;
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
			curScore -= foodScore;
			totalScore -= foodScore;
			eatWhat = POISON;//给进度条刷新
			delTail();
		}
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
			if (poisonGroup[i].posionLife < 8)
			{
				if((poisonGroup[i].shinning % 2) == 0)
				beauty[poisonGroup[i].poisonX][poisonGroup[i].poisonY] = SHINING;
				else
				beauty[poisonGroup[i].poisonX][poisonGroup[i].poisonY] = AIR;
				poisonGroup[i].shinning--;
			}

			if (poisonGroup[i].posionLife <= 0)
			{
				beauty[poisonGroup[i].poisonX][poisonGroup[i].poisonY] = AIR;
				poisonGroup[i].status = 0;
				map[poisonGroup[i].poisonX][poisonGroup[i].poisonY] = 0;
				poisonCount--;
			}
		}
	}
	//tnt
	for (int i = 0; i < tntNum; i++)
	{
		if (tntGroup[i].status == 1)
		{
			tntGroup[i].tntLife--;
			if (tntGroup[i].tntLife == 2)
			{
				mciSendString(_T("close boom"), NULL, 0, NULL);//关闭音乐
				//mciSendString(_T("open ./music/sisisi.mp3 alias tnt"), NULL, 0, NULL);
				//mciSendString(_T("play tnt"), NULL, 0, NULL);//重复播放
				int x = tntGroup[i].poisonX;
				int y = tntGroup[i].poisonY;
				beauty[x][y] = 9;// burning tnt
			}


			if (tntGroup[i].tntLife == 0 && tntGroup[i].status == 1)
			{

				//mciSendString(_T("close tnt"), NULL, 0, NULL);//关闭音乐
				int x = tntGroup[i].poisonX;
				int y = tntGroup[i].poisonY;
				if (map[x - 1][y] == SNAKEBODY || map[x + 1][y] == SNAKEBODY || map[x][y - 1] == SNAKEBODY || map[x][y + 1] == SNAKEBODY)
				{
					eatWhat = 12;//被tnt炸
					totalScore -= 2 * foodScore;
					curScore -= 2 * foodScore;
					delTail();
					delTail();
				}
				//mciSendString(_T("close tnt"), NULL, 0, NULL);//关闭音乐
				mciSendString(_T("open ./music/1tnt.mp3 alias boom"), NULL, 0, NULL);//打开文件
				mciSendString(_T("play boom"), NULL, 0, NULL);
			//	h1 = ::CreateThread(NULL, 0, myfun1, NULL, 0, NULL);   //创建线程 
				beauty[x][y] = BOOM;
				beauty[x + 1][y] = BOOM;
				beauty[x - 1][y] = BOOM;
				beauty[x][y + 1] = BOOM;
				beauty[x][y - 1] = BOOM;
				tntGroup[i].status = 0;
				map[tntGroup[i].poisonX][tntGroup[i].poisonY] = 0;
				tntCount--;
			}
		}
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
	else if (maze[row][col] == 7)
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
		maze[tail->positionX][tail->positionY] = 5;
	}
	int x, y;
	clean_queue();
	struct point p;//起始点  蛇头---------------------------------怎么在第二期
	gotoxy(10, 42);
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
			&& (maze[p.row][p.col + 1] == 0 || maze[p.row][p.col + 1] == 5 || maze[p.row][p.col + 1] == 6) && maze[p.row][p.col + 1] != 1 && maze[p.row][p.col + 1] != 10)//地图首先要可以走
			visit(p.row, p.col + 1);//visit这一区域

		if (p.row + 1 < MAPX - 1 /* down */
			&& (maze[p.row + 1][p.col] == 0 || maze[p.row + 1][p.col] == 5 || maze[p.row + 1][p.col] == 6) && maze[p.row + 1][p.col] != 1 && maze[p.row + 1][p.col] != 10)
			visit(p.row + 1, p.col);

		if (p.col - 1 > 0 /* left */
			&& (maze[p.row][p.col - 1] == 0 || maze[p.row][p.col - 1] == 5 || maze[p.row][p.col - 1] == 6) && maze[p.row][p.col - 1] != 1 && maze[p.row][p.col - 1] != 10)
			visit(p.row, p.col - 1);
		if (p.row - 1 > 0 /* up */
			&& (maze[p.row - 1][p.col] == 0 || maze[p.row - 1][p.col] == 5 || maze[p.row - 1][p.col] == 6) && maze[p.row - 1][p.col] != 1 && maze[p.row - 1][p.col] != 10)
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

			if (p.col != queue[p.predecessor].col)
			{
				if (p.col == (queue[p.predecessor].col - 1))//本列在上一列的左边
				{
					autoKey[keyCount] = KEYLEFT;
				}
				else {
					autoKey[keyCount] = KEYRIGHT;
				}
			}
			p = queue[p.predecessor];
			keyCount--;
		}

	}
}

void loadKey()
{
	int i = 0;
	for (int j = 0; j < 50; j++)
	{
		if (autoKey[j] != 0) {
			key[i] = autoKey[j];
			autoKey[j] = 0;
			i++;
		}
	}
	autoNum = i;
	step = 0;
	isFinish = 0;
}

void clearKey() {  //清空所有按键
	int i = 0;
	while (key[i] != 0)
	{
		key[i] = 0;
		if (i != 0) {
			directionX[i] = 0;
			directionY[i] = 0;
		}
		i++;
	}
	step = 0;
	kbhitCount = 0;

}

void theWall(int dirX, int dirY)
{
	if (foodCount == 0)
	{
		autoNum = 0;
		clearKey();
	}
	//WALKMODE3    手动躲模式
	int flag = 0;
	AX = dirX;
	AY = dirY;
	if (map[head->positionX + AX][head->positionY + AY] == 1) {//看看下一步的位置	
		if (walkMode == 3)
		{
			setbkmode(TRANSPARENT);
			settextcolor(BLACK);
			settextstyle(25, 0, _T("华文行楷"));
			TCHAR s[] = _T("下一步就要撞墙了，请你来决定方向");
			outtextxy(665, 350, s);
			//autoNum = 0;
			//isFinish = 1;//
			clearKey();
			char danger, get;
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


			if ((AX == 1 || AX == -1) && flag == 0)//当前方向向下或者向上
			{
				//autoNum = 0;
				flag = 1;
				//clearKey();
				AX = 0;
				AY = 1;
				if (map[head->positionX + AX][head->positionY + AY] == 1)
					AY = -1;
			}
			if ((AY == 1 || AY == -1) && flag == 0) {
				autoNum = 0;
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
	mciSendString(_T("open ./music/background0.mp3 alias music"), NULL, 0, NULL);//打开文件
	mciSendString(_T("play music repeat"), NULL, 0, NULL);//重复播放
	IMAGE select[10];
	loadimage(&select[0], L"./image/start.jpg");
	loadimage(&select[1], L"./image/load.jpg");
	loadimage(&select[2], L"./image/exit.jpg");
	loadimage(&select[3], L"./image/rank.jpg");
	int choose = 0;


	putimage(0, 0, &select[choose]);




	while (1)
	{


		if (kbhit())
		{
			char get;
			if ((get = getch()) == 13)//按下回车时开始游戏-等操作
			{
				PlaySound(TEXT("./music/确认.wav"), NULL, SND_FILENAME | SND_ASYNC);
				IMAGE lev;
				loadimage(&lev, L"./image/level1.jpg");
				//	initgraph(1000, 620);
				putimage(0, 0, &lev);
				if (choose == 0)
					break;
				if (choose == 2)
					exit(0);
				if (choose == 3)
				{
					rankList();
				}
				if (choose == 1)
				{
					isSelectDifficulty = 0;
					loadGame();
					break;
				}
			}

			else
			{
				switch (get)
				{
				case KEYRIGHT:
					PlaySound(TEXT("./music/select.wav"), NULL, SND_FILENAME | SND_ASYNC);
					Sleep(100);
					choose += 1;
					break;
				case KEYLEFT:
					PlaySound(TEXT("./music/select.wav"), NULL, SND_FILENAME | SND_ASYNC);
					Sleep(100);
					choose -= 1;
					break;
				default:
					break;
				}
				if (choose == 4)
					choose = 0;

				if (choose == -1)
					choose = 3;
				putimage(0, 0, &select[choose]);
			}
		}
	}

}

void setting()
{
	//initgraph(1000, 620);
	IMAGE sceneSel[5];
	IMAGE level[3];
	difficulty = 0;
	loadimage(&level[0], L"./image/easy.jpg");
	loadimage(&level[1], L"./image/medium.jpg");
	loadimage(&level[2], L"./image/difficult.jpg");

	loadimage(&sceneSel[0], L"./image/sceneselect0.jpg");
	loadimage(&sceneSel[1], L"./image/sceneselect1.jpg");
	loadimage(&sceneSel[2], L"./image/sceneselect2.jpg");
	loadimage(&sceneSel[3], L"./image/sceneselect3.jpg");
	loadimage(&sceneSel[4], L"./image/sceneselect4.jpg");
	//进行地图选择  产生不同的地形
	//温和草原
	//富饶森林
	//干旱沙漠
	//荒芜冰原
	//极端地狱
	//自定义
	setjmp(set);
	//进行场景选择
	putimage(0, 0, &sceneSel[0]);

	while (1)
	{

		if (kbhit())
		{

			char get;
			if ((get = getch()) == 13)//按下回车时确认场景
			{
				PlaySound(TEXT("./music/确认.wav"), NULL, SND_FILENAME | SND_ASYNC);
				break;
			}
			else if (get == 8)
			{
				PlaySound(TEXT("./music/return.wav"), NULL, SND_FILENAME | SND_ASYNC);
				get = 0;
				longjmp(buf, 1);

			}
			else
			{
				switch (get)
				{
				case KEYDOWN:
					PlaySound(TEXT("./music/select.wav"), NULL, SND_FILENAME | SND_ASYNC);
					scene += 1;
					break;
				case KEYUP:
					PlaySound(TEXT("./music/select.wav"), NULL, SND_FILENAME | SND_ASYNC);
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
				Sleep(120);
			}
		}
	}





	//进行难度选择
	putimage(0, 0, &level[0]);
	while (1)
	{

		if (kbhit())
		{

			char get;
			if ((get = getch()) == 13)//按下回车时确认难度    更换音乐
			{
				mciSendString(_T("close music"), NULL, 0, NULL);//关闭音乐
				PlaySound(TEXT("./music/确认.wav"), NULL, SND_FILENAME | SND_ASYNC);
				break;
			}
			else if (get == 8)
			{
				PlaySound(TEXT("./music/return.wav"), NULL, SND_FILENAME | SND_ASYNC);
				get = 0;
				longjmp(set, 1);

			}
			else
			{
				switch (get)
				{
				case KEYDOWN:
					PlaySound(TEXT("./music/select.wav"), NULL, SND_FILENAME | SND_ASYNC);
					difficulty += 1;
					break;
				case KEYUP:
					PlaySound(TEXT("./music/select.wav"), NULL, SND_FILENAME | SND_ASYNC);

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
				Sleep(200);
			}
		}
	}

}
/*
int foodScore = 0,beginSpeed = 0,speedAdd = 0,maxHug = 5;
//每吃一个食物的得分（难度越高，分越高）,目标得分（难度越高，目标越高）,
开始时的刷新速度，吃到食物后减少的速度,最高饱食度，根据难度而定
还有 毒草数，tnt数，食物数 ， tnt是否会自己爆炸。。。。
*/
void loadSetting()
{
	int k;//难度系数
	mciSendString(_T("close music"), NULL, 0, NULL);//关闭音乐
	switch (difficulty)
	{
	case 0:
		beginSpeed = 200;
		foodScore = 100;//每吃一个食物 +100分
		maxHug = 7;
		k = 1;
		break;
	case 1:
		maxHug = 6;
		beginSpeed = 350;
		k = 2;
		foodScore = 140;
		break;
	case 2:
		maxHug = 5;
		beginSpeed = 140;
		k = 3;
		foodScore = 180;
		break;
	}

	switch (scene)
	{
	case 0:
		mciSendString(_T("open ./music/grassland.mp3 alias music"), NULL, 0, NULL);
		break;
	case 1:
		mciSendString(_T("open ./music/forest.mp3 alias music"), NULL, 0, NULL);
		break;
	case 3:
		mciSendString(_T("open ./music/sand.mp3 alias music"), NULL, 0, NULL);
		break;
	case 2:
		mciSendString(_T("open ./music/iceland.mp3 alias music"), NULL, 0, NULL);
		break;
	case 4:
		mciSendString(_T("open ./music/nether.mp3 alias music"), NULL, 0, NULL);
		break;
	default:
		break;
	}
	//把音量降低。。
	mciSendString(_T("play music repeat"), NULL, 0, NULL);//重复播放
														  //加载地图
	for (int i = 0; i < MAPX; i++)
		for (int j = 0; j < MAPY; j++)
			map[i][j] = mapSel[scene][i][j];
	//加载目标分数
	switch (scene)//不同关卡目标分数不同
	{
	case 0:
		targetScore = 600* k;
		break;
	case 1:
		targetScore = 1200 * k;
		break;
	case 2:
		targetScore = 1600 * k;
		break;
	case 3:
		targetScore = 1800 * k;
		break;
	case 4:
		targetScore = 1800 * k;
		break;
	default:
		break;
	}
	hungry = maxHug;
	hungryIc = (int *)calloc(sizeof(int), maxHug);

	//根据难度各个物品的数量不一样
	foodNum = rand_food_y() % 12 + 6 - 1 * k;//最大食物数量
	poisonNum = (rand_food_y() * 213) % 10 + 5 * k;//最大毒数量
	tntNum = (rand_food_x() * 101) % 10 + 4 * k;
	
	tntGroup = (tnt*)calloc(sizeof(tnt), tntNum);
	foodGroup = (food*)calloc(sizeof(food), foodNum);
	poisonGroup = (poison*)calloc(sizeof(poison), poisonNum);
	gameSpeed = beginSpeed;
	
}




DWORD WINAPI myfun1(LPVOID lpParameter)                     //分别实现线程函数  
{
	mciSendString(_T("close tnt"), NULL, 0, NULL);//关闭音乐
	mciSendString(_T("open ./music/tnt.mp3 alias boom"), NULL, 0, NULL);//打开文件
	mciSendString(_T("play boom"), NULL, 0, NULL);
	Sleep(beginSpeed);
	mciSendString(_T("close boom"), NULL, 0, NULL);//关闭音乐
	ExitThread(0);
	return 0;
}

DWORD WINAPI clearBar(LPVOID lpParameter)
{
	TerminateThread(drawProcess,0);
	int i = 10;
	while (i >= 0)
	{
		clearrectangle(0, 600, 600, 620);
		i--;
	}
	return 1;
}
void generateRandBeauty()
{
	//生成随机数量的 特殊地形
	int beautyNum = 0, beautyCount = 0;
	srand((unsigned)time(NULL));
	beautyNum = rand() * 100 % 10 + 4;
	int ad1 = 0, ad2 = 0;;
	while (beautyCount <= beautyNum)
	{
		ad1 += 1;
		ad2 -= 1;
		int x, y;
		srand((unsigned)time(NULL) + ad1);
		x = rand() * 321 % MAPX;
		srand((unsigned)time(NULL) + ad2);
		y = rand() * 123 % MAPY;
		if (map[x][y] == 0)
		{
			beauty[x][y] = BEAUTY;
			beautyCount++;
		}
		
	}

}

void printBeauty()
{

	IMAGE beautyI[16];
	loadimage(&beautyI[0], L"./image/grass_boom.jpg");
	loadimage(&beautyI[1], L"./image/forest_boom.jpg");
	loadimage(&beautyI[2], L"./image/ice_boom.jpg");
	loadimage(&beautyI[3], L"./image/sand_boom.jpg");
	loadimage(&beautyI[4], L"./image/nether_boom.jpg");
	loadimage(&beautyI[5], L"./image/tnt_burn.jpg");
	loadimage(&beautyI[6], L"./image/grassland_shining.jpg");
	loadimage(&beautyI[7], L"./image/forest_poison_shining.jpg");
	loadimage(&beautyI[8], L"./image/iceland_poison_shining.jpg");
	loadimage(&beautyI[9], L"./image/sand_poison_shining.jpg");
	loadimage(&beautyI[10], L"./image/nether_poison_shining.jpg");
	loadimage(&beautyI[11], L"./image/dirtBeauty1.jpg");
	loadimage(&beautyI[12], L"./image/forestBeauty1.jpg");
	loadimage(&beautyI[13], L"./image/iceBeauty2.jpg");
	loadimage(&beautyI[14], L"./image/sandBeauty1.jpg");
	loadimage(&beautyI[15], L"./image/netherBeauty1.jpg");
	for (int i = 0; i < MAPX; i++)
	{
		for (int j = 0; j < MAPY; j++)
		{
			if (beauty[i][j] == BOOM && map[i][j] == 0)
			{

				putimage(j * 30, i * 30, &beautyI[scene]);
			}
			if (beauty[i][j] == 9 && map[i][j] == TNT)
			{

				putimage(j * 30, i * 30, &beautyI[5]);
			}
			if (beauty[i][j] == SHINING && map[i][j] == POISON)
			{
				switch (scene)
				{
				case 0:
					putimage(j * 30, i * 30, &beautyI[6]);
					break;
				case 1:
					putimage(j * 30, i * 30, &beautyI[7]);
					break;
				case 2:
					putimage(j * 30, i * 30, &beautyI[8]);
					break;
				case 3:
					putimage(j * 30, i * 30, &beautyI[9]);
					break;
				case 4:
					putimage(j * 30, i * 30, &beautyI[10]);
					break;
				default:
					break;
				}

			}
			if (beauty[i][j] == BEAUTY && map[i][j] == AIR)
			{

					switch (scene)
					{
					case 0:
						putimage(j * 30, i * 30, &beautyI[11]);
						break;
					case 1:
						putimage(j * 30, i * 30, &beautyI[12]);
						break;
					case 2:
						putimage(j * 30, i * 30, &beautyI[13]);
						break;
					case 3:
						putimage(j * 30, i * 30, &beautyI[14]);
						break;
					case 4:
						putimage(j * 30, i * 30, &beautyI[15]);
						break;
					default:
						break;
					}
				
			}
		}
	}
}
void printWord()
{
	IMAGE img;
	loadimage(&img, L"./image/reprintWord.jpg");
	BeginBatchDraw();
	putimage(672, 60, &img);
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(35, 0, _T("华文行楷"));
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(35, 0, _T("华文行楷"));


	
	foodAndHungry();
	TCHAR s[20],n[20],c[20],d[10];
	//TCHAR clear[] = _T("            ");
	_stprintf(s, _T("总分：%d"), totalScore);
	_stprintf(n, _T("目标得分：%d"), targetScore);
	_stprintf(c, _T("当前得分：%d"), curScore);
	_stprintf(d, _T("药效：%d"), autoRound);
	TCHAR e[] = _T("靠你自己啦！");
	outtextxy(665, 60,  s);
	outtextxy(665, 110, c);

	if (autoRound <=4 && autoRound >0)
	{
		outtextxy(675, 450, d);
	}
	else if(autoRound >= -2 && autoRound <=0)
	{
		gameSpeed = beginSpeed;
		if (autoRound == 0)//有问题
		{
			clearKey();
			directionX[0] = curDirectionX;
			directionY[0] = curDirectionY;
			walkMode = 0;
		}
		outtextxy(675, 450, e);
	Sleep(1000);
		autoRound--;
	}
	if (autoRound == -3)
		autoRound = 5;
	outtextxy(665, 160, n);
	TCHAR dif0[] = _T("难度：初来乍到");
	TCHAR dif1[] = _T("难度：略知一二");
	TCHAR dif2[] = _T("难度：游刃有余");
	switch (difficulty)
	{
	case 0:
		outtextxy(670, 200, dif0);
		break;
	case 1:
		outtextxy(670, 200, dif1);
		break;
	case 2:
		outtextxy(670, 200, dif2);
		break;
	default:
		break;
	}



	RECT r = { 680, 250, 910,550  }; 
	RECT u = { 680,300, 910, 350 };
	//drawtext(_T(" "),totalScore, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	if (result != 0 && result != -1)
		resultp = result;
	switch (resultp)
	{
	case FOOD:
		drawtext(_T("emmm...美味"), &r, DT_WORDBREAK | DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		break;
	case POISON:
		drawtext(_T("这玩意，有毒"), &r, DT_WORDBREAK | DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		break;
	case TNT:
		drawtext(_T("\n/(ㄒoㄒ)/~~ "), &r, DT_WORDBREAK | DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		break;
	case CLEVER:
		drawtext(_T("自动寻路，吃到四个食物或按方向键取消"), &r, DT_WORDBREAK | DT_VCENTER|DT_BOTTOM);
		break;
	case 0:
		drawtext(_T("寻路已取消"), &r, DT_WORDBREAK | DT_CENTER | DT_VCENTER);
		break;
	default:
		break;
	}
	
	if (hungryShow <= 0)//清空不再显示
	{
		hungryTem = 0;
		hungryShow = 4;
	}
	if(hungryStatus != 0)
		hungryTem = hungryStatus;
	switch (hungryTem)
	{
	case 1:
		drawtext(_T("好饿。。"), &u, DT_WORDBREAK | DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		hungryShow--;
		break;
	case 2:
		drawtext(_T("饿死了。"), &u, DT_WORDBREAK | DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		break;
	default:
		break;
	}
	hungryStatus = 0;
	result = -1;
	EndBatchDraw();

}
void restart()
{

	gameSpeed = beginSpeed;
	isSelectDifficulty = 1;
	result = -1;
	resultp = -1;
	scene = 0;
	hungryTem = 0;
	
	
	for (int i = 0; i < maxHug; i++)
		hungryIc[i] = 0;
	hungry = maxHug;
	hungryRound = hungrySpeed;
	eatNum = 0, len = 0, printLength = 0, ad = 0, process = 0, eatWhat = 0;
	mciSendString(_T("close music"), NULL, 0, NULL);//关闭音乐
	for (int i = 0; i < MAPX; i++)
		for (int j = 0; j < MAPY; j++)
		{
			if (beauty[i][j] == BOOM || beauty[i][j] == BEAUTY)
				beauty[i][j] = AIR;
		}
	

	/*
	删除这一盘的蛇
	
	*/
	snake * del = head->next;
	while (del != NULL)
	{
		free(del->previous);
		del = del->next;
	}
	clearKey();
	foodCount = 0;
	poisonCount = 0;
	tntCount = 0;
	gameStatus = 1;
	head = NULL;
	tail = NULL;
	isSelectDifficulty = 1;
	result = 0;
	for (int i = 0; i < foodNum; i++)
	{
		foodGroup[i].status = 0;
		foodGroup[i].foodLife = 0;
		foodGroup[i].foodY = 0;
		foodGroup[i].foodX = 0;
	}
	for (int i = 0; i < tntNum; i++)
	{
		tntGroup[i].status = 0;
		tntGroup[i].tntLife = 0;
		tntGroup[i].poisonY = 0;
		tntGroup[i].poisonX = 0;
	}
	for (int i = 0; i < poisonNum; i++)
	{
		poisonGroup[i].status = 0;
		poisonGroup[i].posionLife = 0;
		poisonGroup[i].poisonY = 0;
		poisonGroup[i].poisonX = 0;
	}
	totalScore = 0;
	curScore = 0;
}

void rankList()//退出游戏时进行保存，在那里进行排序
{
	char* temp;
	char* rankName[10], *ranktotalScore[10];
	int compare[10] = { 0 };

	//initgraph(1000, 600);
	IMAGE rank;
	loadimage(&rank, L"./image/ranklist.jpg");
	putimage(0, 0, &rank);
	FILE *stream;
	char line[20];
	char n = '\n';
	TCHAR showName[20], showtotalScore[20];
	char* div = "#";
	while (1)
	{
		if (kbhit())
		{
			char get = getch();
			if (get == 8)
			{
				PlaySound(TEXT("./music/return.wav"), NULL, SND_FILENAME | SND_ASYNC);
				get = 0;
				longjmp(buf, 1);

			}
		}
		else {
			if ((stream = fopen("./data/rank.txt", "r")) != NULL)
			{
				setbkmode(TRANSPARENT);
				settextcolor(LIGHTBLUE);
				settextstyle(50, 0, _T("Bauhaus 93"));
				int x = 70;
				int y = 200;
				int c = 0, co = 0;
				while (fgets(line, 20, stream) != NULL)//整行读取   用#来分隔名字与分数
				{

					temp = strtok(line,"#");
					while (temp != NULL)
					{
						if (c == 0)
						{
							rankName[co] = temp;

						}
						else if (c == 1)
						{
							ranktotalScore[co] = temp;
						}
						temp = strtok(NULL, div);
						c++;
						if (c == 2)
							c = 0;
					}

					MultiByteToWideChar(CP_ACP, 0, rankName[co], -1, showName, 100);//转换char[]为TCHAR[]
					MultiByteToWideChar(CP_ACP, 0, ranktotalScore[co], -1, showtotalScore, 100);//转换char[]为TCHAR[]
					if (co <= 4)
					{
						outtextxy(x, y, showName);
						outtextxy(x + 270, y, showtotalScore);
					}
					else
					{
						if (co == 5)
							y = 200;
						outtextxy(x + 500, y, showName);
						outtextxy(x + 740, y, showtotalScore);
					}
					y += 70;

					co++;
				}
				fclose(stream);
			}
		}
	}
}
void saveData()
{
	int flag = 0;
	int compare[10] = { 0 };
	char* readName[10], *readtotalScore[10], *temp, *div = "#";//
	for (int i = 0; i < 10; i++)
	{
		readName[i] = (char*)calloc(sizeof(char) * 10, 1);
		readtotalScore[i] = (char*)calloc(sizeof(char) * 10, 1);
	}
	FILE* stream;
	int c = 0, co = 0;
	char* writeName[10], *writetotalScore[10];
	char* line = (char*)calloc(sizeof(char) * 20, 1);
	//排行榜相关操作，读取文件中所有数据，利用插入排序
	if ((stream = fopen("./data/rank.txt", "r")) != NULL)
	{

		while (fgets(line, 20, stream) != NULL)
		{
			temp = (char*)calloc(sizeof(char) * 10, 1);//获得一个新的空间
			temp = strtok(line, div);//取#前面一串

			while (temp != NULL)
			{
				if (c == 0)
				{

					readName[co] = temp;
					temp = (char*)calloc(sizeof(char) * 10, 1);
				}
				else if (c == 1)
				{
					readtotalScore[co] = temp;
					compare[co] = atoi(temp);//将字符串转为int
				}
				temp = strtok(NULL, div);
				c++;
				if (c == 2) {
					c = 0;
					co++;
				}

			}

			line = (char*)calloc(sizeof(char) * 20, 1);  //！！！！一定要为字符串分配新的储存空间
		}

		if (co <= 9)//如果排行榜没有满,直接在后面加
		{
			co++;
			char * tempName, *temptotalScore;
			char * write = (char*)calloc(sizeof(char) * 20 + 4, 1);
			tempName = (char*)calloc(sizeof(char) * 10 + 4, 1);
			temptotalScore = (char*)calloc(sizeof(char) * 10 + 4, 1);

			//排序
			for (int i = 0; i < co; i++)
			{
				writeName[i] = (char*)calloc(sizeof(char) * 10, 1);
				writetotalScore[i] = (char*)calloc(sizeof(char) * 10, 1);
				if (compare[i] >= totalScore && flag == 0)
				{
					writeName[i] = readName[i];
					writetotalScore[i] = readtotalScore[i];
				}
				else if (compare[i] < totalScore && flag == 0)//找到第一个比当前分数底的记录时
				{
					char* change = "\n";
					flag = 1;
					tempName = readName[i];
					temptotalScore = readtotalScore[i];
					writeName[i] = playerName;
					itoa(totalScore, writetotalScore[i], 10);//这一句有？？
					strcat(writetotalScore[i], change);
				}
				else if (flag == 1)
				{
					writeName[i] = tempName; //等于上一项的
					writetotalScore[i] = temptotalScore;
					tempName = readName[i];
					temptotalScore = readtotalScore[i];
				}
			}
		}
		else
		{

			int count = 0;
			char len[10];
			char * tempName, *temptotalScore;
			char * write = (char*)calloc(strlen(len) + strlen(len) + 4, 1);
			tempName = (char*)calloc(strlen(len) + 4, 1);
			temptotalScore = (char*)calloc(strlen(len) + 4, 1);

			//排序
			for (int i = 0; i < 10; i++)
			{
				writeName[i] = (char*)calloc(sizeof(char) * 10, 1);
				writetotalScore[i] = (char*)calloc(sizeof(char) * 10, 1);
				if (compare[i] >= totalScore && flag == 0)
				{

					count++;
					writeName[i] = readName[i];
					writetotalScore[i] = readtotalScore[i];
				}
				else if (compare[i] < totalScore && flag == 0)//找到第一个比当前分数底的记录时
				{
					char* change = "\n";
					flag = 1;
					tempName = readName[i];
					temptotalScore = readtotalScore[i];

					writeName[i] = playerName;
					itoa(totalScore, writetotalScore[i], 10);//这一句有？？
					strcat(writetotalScore[i], change);
				}
				else if (flag == 1)
				{


					writeName[i] = tempName; //等于上一项的
					writetotalScore[i] = temptotalScore;
					tempName = readName[i];
					temptotalScore = readtotalScore[i];

				}
			}

		}//执行不下去
		fclose(stream);
		//以上应该没什么问题

	}

	errno_t err = 0;
	//储存
	if (flag == 1) {//记录有变动

		FILE *save;
		if ((save = fopen("./data/rank.txt", "w")) != NULL)
		{


			char change[2] = "\n";
			char len[10];
			//write = strcat(playerName,div);
			for (int i = 0; i < co; i++) {
				char * write = (char*)calloc(strlen(len) + strlen(len) + strlen(div) + 2, 1);
				strcpy(write, writeName[i]);   //为什么要这样写啊，不能直接拼接
				strcat(write, div);
				strcat(write, writetotalScore[i]);
				//strcat(write, change);
				fputs(write, save);
			}
			fclose(save);
		}
	}

}
//需要储存的内容，当前地图，分数，蛇的各节坐标，方向，行走模式，难度     但是食物等东西不存了
void saveGame()
{
	FILE *saveStream;
	if ((saveStream = fopen("./data/save.txt", "w")) != NULL)
	{
		char* writeScene, *writeDifficulty, *writetotalScore, *writeDx, *writeDy, *writeMode, *writeName,*writecurScore;
		char* div = "#";
		char* writeLine = (char*)calloc(sizeof(char) * 80, 1);
		//格式 地图#行走模式#难度#分数#当前方向#姓名
		writeScene = (char*)calloc(sizeof(char) * 3, 1);
		writeDifficulty = (char*)calloc(sizeof(char) * 3, 1);
		writetotalScore = (char*)calloc(sizeof(char) * 10, 1);
		writeDx = (char*)calloc(sizeof(char) * 3, 1);
		writeDy = (char*)calloc(sizeof(char) * 3, 1);
		writeMode = (char*)calloc(sizeof(char) * 3, 1);
		writecurScore = (char*)calloc(sizeof(char) * 10, 1);

		itoa(scene, writeScene, 10);
		itoa(walkMode, writeMode, 10);
		itoa(totalScore, writetotalScore, 10);
		itoa(curScore, writecurScore, 10);
		itoa(difficulty, writeDifficulty, 10);
		itoa(directionX[0], writeDx, 10);
		itoa(directionY[0], writeDy, 10);
		strcpy(writeLine, writeScene);
		strcat(writeLine, div);
		strcat(writeLine, writeMode);
		strcat(writeLine, div);
		strcat(writeLine, writeDifficulty);
		strcat(writeLine, div);
		strcat(writeLine, writetotalScore);
		strcat(writeLine, div);
		strcat(writeLine, writeDx);
		strcat(writeLine, div);
		strcat(writeLine, writeDy);
		strcat(writeLine, div);
		strcat(writeLine, writecurScore);
		fputs(writeLine, saveStream);
		fputs("\n", saveStream);
		//记录蛇的坐标headX#headY#bodyX#bodyY#tailX#tailY
		snake* saveSnake = head;
		writeLine = (char*)calloc(sizeof(char) * 80, 1);
		while (saveSnake != NULL)
		{
			char* writeSnakeX = (char*)calloc(sizeof(char) * 4, 1);
			char* writeSnakeY = (char*)calloc(sizeof(char) * 4, 1);
			itoa(saveSnake->positionX, writeSnakeX, 10);
			itoa(saveSnake->positionY, writeSnakeY, 10);
			strcat(writeLine, writeSnakeX);
			strcat(writeLine, div);
			strcat(writeLine, writeSnakeY);
			strcat(writeLine, div);
			saveSnake = saveSnake->next;
		}
		fputs(writeLine, saveStream);
		fclose(saveStream);
	}
}
void loadGame()
{
	eatWhat = FOOD;
	//clearKey();
	FILE *loadStream;
	char* readLine = (char*)calloc(sizeof(char) * 80, 1);
	char* temp = (char*)calloc(sizeof(char) * 10, 1);//获得一个新的空间
	if ((loadStream = fopen("./data/save.txt", "r")) != NULL)
	{
		int LineCount = 0;//行计数
		int ColCount = 0;//列计数
		while (fgets(readLine, 80, loadStream) != NULL)
		{
			if (LineCount == 0) {//载入第一行信息
				LineCount++;
				temp = strtok(readLine, "#");//取#前面一串

				while (temp != NULL)
				{

					switch (ColCount)
					{
					case 0://scene
						scene = atoi(temp);
						break;
					case 1://mode
						walkMode = atoi(temp);
						break;
					case 2:
						difficulty = atoi(temp);
						break;
					case 3:
						totalScore = atoi(temp);
						break;
					case 4:
						directionX[0] = atoi(temp);
						break;
					case 5:
						directionY[0] = atoi(temp);
						break;
					case 6:
						curScore = atoi(temp);//读取储存游戏时，关卡内得分
						break;
					default:
						break;
					}

					temp = strtok(NULL, "#");

					ColCount++;

				}

			}
			else
			{
				int round = 0, num = 0;
				//读取蛇

				temp = (char*)calloc(sizeof(char) * 10, 1);
				temp = strtok(readLine, "#");//取#前面一串

				snake* cur, *prv;
				while (temp != NULL)
				{

					if (round == 0)//加载x坐标
					{
						round++;
						if (num == 0)//蛇头部分x
						{

							head = (snake*)calloc(sizeof(snake), 1);
							prv = head;
							head->positionX = atoi(temp);
						}
						else
						{

							cur = (snake*)calloc(sizeof(snake), 1);

							cur->positionX = atoi(temp);
							prv->next = cur;
							//有问题？？

							cur->previous = prv;

						}
					}
					else if (round == 1)
					{
						round = 0;
						if (num == 0)
						{
							head->positionY = atoi(temp);
							num++;
						}
						else//当不是第一节的时候
						{
							cur->next = NULL;
							cur->positionY = atoi(temp);
							num++;
							prv = cur;
							tail = cur;
						}
					}
					temp = strtok(NULL, "#");

				}
				snake* snakeP = head;
			}
			LineCount = 1;
		}

	}
}
void upgradeProcess()
{	
	up = ::CreateThread(NULL, 0, drawProcess, NULL, 0, NULL);
	
	if (curScore >= targetScore) {//当前关卡内得分达到目标
		
		if (scene < 4) {
			curScore = targetScore;
			printWord();
			setbkmode(TRANSPARENT);
			settextcolor(BLACK);
			settextstyle(35, 0, _T("华文行楷"));
			TCHAR s[] = _T("恭喜你，达成目标");
			outtextxy(665, 250, s);
			mciSendString(_T("close music"), NULL, 0, NULL);//关闭音乐
			mciSendString(_T("open ./music/compm.mp3 alias vic"), NULL, 0, NULL);//打开文件
			mciSendString(_T("play vic"), NULL, 0, NULL);//重复播放
			Sleep(6000);//主线程停一下，让进度条画完。。
		}
		else if (scene == 4)//最后一关通关了。。
		{
			gameFinish();
		}
	}

}

DWORD WINAPI drawProcess(LPVOID lpParameter)
{
	int startPoi;//清除的起点
	len = 600 / (targetScore / 100);//没吃到一个食物要增加到的长度------吃到毒草或是炸弹也要有响应
	ad = len / 3;//ad越来越少，进度条缓慢打印
	if (eatWhat == FOOD ) {
		startPoi = 0;
		printLength = curScore * 600 / targetScore;//需要打印到的长度 
	}
	else if (eatWhat == TNT)
	{
		startPoi = printLength;
		printLength /= 2;
	}
	else if (eatWhat == POISON)
	{
		startPoi = printLength;
		printLength = curScore * 600 / targetScore;//需要打印到的长度 
	}
	//第一次绘制len的一半 
	//每次得分调用，绘制   独立线程
	if (eatWhat == FOOD) {//加载地图要能打出来
		eatWhat = 0;
		while (process < printLength){
			process += ad;
			ad -= 12;
			if (ad <= 0)
				ad = len / 5;
			if (process >= printLength)
				process = len;
			setfillcolor(GREEN);
			solidrectangle(startPoi, 603, process, 620);
			startPoi = process;
			Sleep(50);
		} 
		eatWhat = 0;
	}
	else if (eatWhat == POISON || eatWhat == TNT)//从当前进度清除到上一级
	{
		eatWhat = 0;
		do {
			process -= ad;
			ad -= 5;
			if (ad <= 0)
				ad = len / 7;
			if (process < printLength)
				process = len;
			setfillcolor(GREEN);
			clearrectangle(startPoi, 603, process, 620);
			Sleep(100);
		} while (process > printLength);
	}
	
	ExitThread(0);
	return 0;

}

void upgrade()//升级后重新加载界面到新地图
{

	if (curScore >= targetScore)
	{
		autoRound = -3;
		foodCount = 0;
		poisonCount = 0;
		tntCount = 0;
		for (int i = 0; i < foodNum; i++)
		{
			foodGroup[i].status = 0;
		}
		for (int i = 0; i < poisonNum; i++)
		{
			poisonGroup[i].status = 0;
		}
		for (int i = 0; i < tntNum; i++)
		{
			tntGroup[i].status = 0;
		}

		
		clearKey();
		directionX[0] = -1;
		directionY[0] = 0;

		printLength = 0;
		process = 0;
		curScore = 0;//关卡得分变为0 总得分不变
				  //重新加载地图
		scene++;
		head = NULL;
		tail = NULL;
		longjmp(upg, 1);
	}
}


void foodAndHungry()//饥饿系统，不吃东西就会饿死。。
{	
	IMAGE hungryI[3];
	loadimage(&hungryI[0], L"./image/hungry_full.jpg");
	loadimage(&hungryI[1], L"./image/hungry_half.jpg");
	loadimage(&hungryI[2], L"./image/hungry_empty.jpg");
	if (hungry == 0) {
		PlaySound(TEXT("./music/hug.wav"), NULL, SND_FILENAME | SND_ASYNC);
		hungry = maxHug;//清除掉一节之后，满饱食度---图标展示
		for (int i = 0; i < maxHug; i++)
			hungryIc[i] = 0;
	}
	hungryRound--;//round回合掉一点饱食
	if (hungryRound == (hungrySpeed) / 2) //只剩下一半，马上就要减少饱食度
	{
		hungryIc[hungry - 1] = 1;
	}
	else if (hungryRound == 0)
	{
		
		hungry--;//图标要展示出来
		hungryIc[hungry] = 2;//空了
		hungryRound = hungrySpeed;
		if (hungry == 0) {//饱食度降至0
			hungryStatus = 1;//饥饿
			delTail();               //删除一段，播放音效，重置,展示一轮的全空饱食度图标？--到judge处删除
			snakeLength--;
			if (snakeLength == 1)
				hungryStatus = 2;//饿死~_~
		}
	}

	//打印饥饿值
	for (int i = 0; i < maxHug; i++)
	{
		int j = hungryIc[i];//应该打印哪张图片
		putimage(670 + 35 * i, 500, &hungryI[j]);
	}

}
DWORD WINAPI hungryMsg(LPVOID lpParameter)
{
	
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	settextstyle(35, 0, _T("华文行楷"));
	if (hungryStatus == 1) {
		for (int i = 0; i < 4; i++)
		{
			TCHAR s[] = _T("好饿呀！");
			outtextxy(675, 320, s);
		}
	}
	else if(hungryStatus == 2)
	{
		for (int i = 0; i < 4; i++) {
			TCHAR s[] = _T("饿死啦！");
			outtextxy(675, 320, s);
			Sleep(2000);
		}
	}
	//真正删除尾巴后再重置
	hungryStatus = 0;
	ExitThread(0);
}
void showStart()
{
	IMAGE startI[2];
	loadimage(&startI[0], L"./image/START1.jpg");
	loadimage(&startI[1], L"./image/START2.jpg");
	int i = 0;
	
		while (1)
		{
			if (!kbhit()) {
				if (i == 2)
					i = 0;
				putimage(0, 0, &startI[i]);
				Sleep(300);
				i++;
			}
			else
			{
				PlaySound(TEXT("./music/gameStart.wav"), NULL, SND_FILENAME | SND_ASYNC);
				Sleep(1200);
				break;
			}
		}
	
}

void gameFinish()
{
	int choose = 0;
	IMAGE finishImg[2];
	loadimage(&finishImg[0], L"./image/finishContinue.jpg");
	loadimage(&finishImg[1], L"./image/finishExit.jpg");
	mciSendString(_T("close music"), NULL, 0, NULL);//关闭音乐
	PlaySound(TEXT("./music/finish.wav"), NULL, SND_FILENAME | SND_ASYNC);
	TerminateThread(drawProcess, 0);
	Sleep(2000);
	clearrectangle(0, 603, 600, 620);
	process = 0;
	printLength = 0;
	putimage(0, 0, &finishImg[choose]);
	while (1)
	{
		if (kbhit())
		{
			char get = getch();
			if (get == -32)
			{
				get = getch();
				switch (get)
				{
				case KEYDOWN:
					PlaySound(TEXT("./music/select.wav"), NULL, SND_FILENAME | SND_ASYNC);
					Sleep(100);
					choose += 1;
					if (choose == 2)
						choose = 0;
					break;
				case KEYUP:

					PlaySound(TEXT("./music/select.wav"), NULL, SND_FILENAME | SND_ASYNC);
					Sleep(100);
					choose -= 1;

					if (choose == -1)
						choose = 1;
					break;
				default:
					break;
				}
				putimage(0, 0, &finishImg[choose]);
			}
			else if (get == 13)
			{
				saveData();
				PlaySound(TEXT("./music/确认.wav"), NULL, SND_FILENAME | SND_ASYNC);
				Sleep(500);
				switch (choose)
				{
				case 0:
					isUp = 0;
					longjmp(con, 1);
					break;
				case 1:
					longjmp(ove, 1);
					break;
				default:
					break;
				}
				break;
			}
			isUp = 0;//不再打印进度条
			mciSendString(_T("open ./music/nether.mp3 alias music"), NULL, 0, NULL);
			//游戏暂停
			//打印图片进行选择
		}
	}
}