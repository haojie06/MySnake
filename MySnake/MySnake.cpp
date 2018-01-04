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
//����д��ͷ�ļ���ȥ
//��ԭ��ʳ��Ϊ�Ϲ� ��Ϊ����
int mapSel[6][MAPX][MAPY] = {
{
{ 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 },
{ 1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },//���
{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },//�յ��ڱ���
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
{//ɭ��
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
		{    //��ԭ
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
int maze[MAPX][MAPY] = {0}; //��������
int autoRound = 0;
int step;
int kbhitCount;
int gameStatus;											   //����Ϸ��ʼʱȷ��ͬʱ���ڵ����ʳ������
int score = 0;
int dimageShow = 0; //�յ��˺�ʱ��ʾʱ��
int directionX[50] = { 0 }, directionY[50] = { 0 };
/*
*********
����BFS
*********
*/

struct point { int row, col, predecessor; } queue[1000];
int front = 0, rear = 0;
//���еĲ���
void enqueue(struct point p)//���
{
	queue[rear++] = p;
}

struct point dequeue(void)//���� ��head��ʼ
{
	return queue[front++];//��ʱ����Ҳ������� eg��0 -> 1 �ȷ���front front���Լ�
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
	int foodLife;//����ʱ��
	int status = 0;//�Ƿ��Ѿ���ʳ��
	//int kind; ���� ������չ
};
struct poison
{
	int poisonX;
	int poisonY;
	int posionLife;
	int status;
	//int kind 
};
int difficulty = 0;//�Ѷ�
int scene = 0;//��ͼ


char playerName[20];
int foodCount = 0;//ͳ�����е�ʳ����
int poisonCount = 0;
int foodNum;
int poisonNum;
food * foodGroup;
poison * poisonGroup;
char* key,* autoKey;//����
int isFinish = 1;
snake* head, *tail;
int walkMode = 3;//����ģʽ 0-�ֶ�,1-�Զ� 3_���Զ�
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
void loadKey();//���ؼ��������·��
void clearKey();//������е�·��
void BFS();
void theWall(int dirX,int dirY);//��ֹײǽ--��ÿ���ƶ������
void beforeGame();//��Ϸ��ʼ����
void setting();
int main()
{		
	
//	foodNum = (rand_food_x() *133) % 10 + 14;
	poisonNum = (rand_food_x() * 12) % 10 + 12;
	/*ע�� ȫ���ַ�ʹ��goto���ʱҪ*/
		initgraph(1000, 620);//������С
		HideCursor();
		beforeGame();
		
		setting();//��Ϸ���� �����������ͼѡ���Ѷ�ѡ��
		iniMap();
		iniSnake();
		printMap();//����gotoxy����ʾ���� Ϊʲô����goto�� ��ͼ�ұߣ���


		playGame();

		
  return 0;
}

//��ͼ��ʼ��
void iniMap()
{	//�߿�
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
	//��Ϊͼ�ν�����
	IMAGE img[10];
	if (scene == 0)//ƽ����ԭ
	{
		loadimage(&img[0], L"E:\\store\\source code\\MySnake\\image\\dirt.jpg");//���������
		loadimage(&img[1], L"E:\\store\\source code\\MySnake\\image\\food_apple.jpg");//ƻ��
		loadimage(&img[2], L"E:\\store\\source code\\MySnake\\image\\stone.jpg");//ԭʯ����ǽ
		loadimage(&img[3], L"E:\\store\\source code\\MySnake\\image\\poison_rotton.jpg");//����
		loadimage(&img[4], L"E:\\store\\source code\\MySnake\\image\\furnace.jpg");
		loadimage(&img[5], L"E:\\store\\source code\\MySnake\\image\\stonebrick.jpg");
		
	}
	else if (scene == 1)//ɭ��
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
	{   //����
		loadimage(&img[0], L"E:\\store\\source code\\MySnake\\image\\nether_floor.jpg");
		loadimage(&img[1], L"E:\\store\\source code\\MySnake\\image\\nether_food.jpg");
		loadimage(&img[2], L"E:\\store\\source code\\MySnake\\image\\nether_wall.jpg");
		loadimage(&img[3], L"E:\\store\\source code\\MySnake\\image\\nether_poison.jpg");
		loadimage(&img[4], L"E:\\store\\source code\\MySnake\\image\\furnace.jpg");
		loadimage(&img[5], L"E:\\store\\source code\\MySnake\\image\\stonebrick.jpg");
	}
	//�ƺ�����BUG
	//gotoxy(5, 45);
	//printf("��ǰ�÷֣� %d", score);
	//gotoxy(7, 45);
//	printf("���ʳ������ %d", foodNum);
	int count = 0;
	//���������ӡ������
	snake * cur = head;
	if (head == NULL)
	{
		//printf("ͷָ��Ϊ��");
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

		map[head->positionX][head->positionY] = 6;//��������ͷһ��ֵ

		for (int i = 0; i < MAPX; i++)
		{
			for (int j = 0; j < MAPY; j++)
			{
				switch (map[i][j]) {
				case 0:
					//setfillcolor(BLACK);//�����ֵ��Ӧ������ʱ���ӡ���ɫ��ͬ���߲���ӡ��
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
				case 5://ʳ��
					putimage(j * 30, i * 30, &img[1]);
					break;
				case 6://ͷ
					putimage(j * 30, i * 30, &img[4]);
					break;
				case 7://����
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
		//printf("����ʳ������ %d", foodCount);
		gotoxy(2, 46);
	//	printf("                 ");
		gotoxy(2, 46);
		//printf("���ȣ�%d", count);
	}
}

void iniSnake()
{
	/*���߽��г�ʼ��
	*��ʼ����ΪX��  ��ͷ����������
	*/
	//����˫������

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
	tail = current;//βָ�� ʼ��ָ�������ֵ�һ��
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

//�ߵ��ƶ�,ײǽ�жϣ�
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
	if (result != 1)//���Ե�ʳ��ʱ��ÿ���ƶ���ɾ��β�ڵ�
	{
		delTail();
		if(walkMode == 0)
		if (result == 2)
			delTail();//�Ե��� �ټ���һ��
		result = 0;
	}

	
	Clearer();//������ڵ�ʳ��/������ڵĶ���
	if (dimageShow == 0) {
		gotoxy(21, 8);
		//printf("                                          ");
	}
	else
	{
		dimageShow--;
	}
}


//��Ϸ��ѭ��
void playGame()
{

	 kbhitCount = 0;//ͳ�ư�������
	foodNum = rand_food_y() % 10 + 15;//���ʳ������
	poisonNum = (rand_food_y() * 213) % 10 + 4;//�������
	foodGroup = (food*)calloc(sizeof(food), foodNum);
	poisonGroup = (poison*)calloc(sizeof(poison), poisonNum);
	gameStatus = 1;
	//������������������һϵ��ָ��ķ���
	int directionX[20] = { 0 }, directionY[20] = { 0 };
	//��ʼ��������
	directionX[0] = -1;
	directionY[0] = 0;

	key = (char*)calloc(sizeof(char), 50);//��������������20��
	autoKey = (char*)calloc(sizeof(char), 50);

	for (int i = 0; i < 50; i++) {
		key[i] = 0;
		autoKey[i] = 0;
	}

	
	int step = 0;//�ߵĲ���
	char lastKey;
	while (gameStatus)
	{
		printKey();
		generatePoison();
		generateFood();//����ʳ�Ｐȥ������ʳ��  !!�Ե��ǻ۲� ʳ����������

		if (!kbhit())
		{

			if (walkMode == 1 || walkMode == 3)
			{
				gotoxy(1, 42);
				//printf("AUTO MODE");
				if (autoRound != 0)
				{
					isFinish = 0;//��ִ��BFS
					autoRound--;
				}
				else
					isFinish = 1;

				if ( isFinish) {
					BFS();				//BFS(); ����   ����ֻ����һ�Ρ�����Ȼ����Լ�ײ����
					loadKey();//����-key ��autoKEY תΪ key
					kbhitCount = 0;
					step = 0;
				}
				

	  //����Ĵ��뽫keyת��Ϊ���������
				int compare;//�ȽϵĶ��� ���±�
					if (kbhitCount == 0){//��ʱ�Ƚ϶���Ϊ�Լ�ԭ�е�ֵ�������Ǻ���һ��Ƚ�
						compare = 0;
					}
					else
					{
						compare = kbhitCount - 1;
					}


					if (directionX[compare] == 1)//down   ԭ���ķ�������ʱ���Ͳ�������
					{

						switch (key[kbhitCount])//��ȡ��ǰ����
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
							//�����д����߻���ʧ-û���ƶ���ɾ����β��
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
					if (directionY[compare] == 1)//�����ƶ�
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
		//�� key �������л����� ����ʱ ��ȡ����
		move(directionX[step], directionY[step]);
		//�߹��������һ��������(�ж���ָ���ʱ��)����׼����ȡ��һָ��
		if (step != 0) {
			lastKey = key[step];//?
			key[step] = 0;
		}

		if (walkMode == 1 &&key[step + 1] == 0)//��ȡ��һ������û�а���ʱ   //ײǽ�ж�---------------/////////////���޸�
		{	
			clearKey();
			BFS();
			loadKey();
			//������ǰ����
			//directionX[0] = directionX[step];
			//directionY[0] = directionY[step];
			step = 0;//�ַ��ص�һ������һ�����Ȼ������ֵ
			kbhitCount = 0;//ָ������Ϊ1��
		}
		else if (key[step + 1] == 0)
		{
			directionX[0] = directionX[step];
			directionY[0] = directionY[step];
			step = 0;//�ַ��ص�һ������һ�����Ȼ������ֵ
			kbhitCount = 0;//ָ������Ϊ1��
		}
		else {
			step += 1;
			//kbhitCount++;
		}//��һ�ֻ��Ƕ�ȡ����õ�ָ��

		printMap();
		Sleep(100);
	}
		else//����⵽��������ʱ   ��������������ϴ�������ͬ��������
		{
			if (walkMode == 3 )
			{
				step = 0;
				clearKey();
				walkMode = 0;
			}
				getch();//ȡ�� �����ֵ ��һ����

				key[kbhitCount] = getch();
				//�������ڱ��������ֵ
				int compare;//�ȽϵĶ��� ���±�
				if (kbhitCount == 0) {//��ʱ�Ƚ϶���Ϊ�Լ�ԭ�е�ֵ�������Ǻ���һ��Ƚ�
					compare = 0;
				}
				else
				{
					compare = kbhitCount - 1;
				}
				
				//if (key[kbhitCount] == 'c')
					//walkMode = 1;
				if (directionX[compare] == 1)//down   ԭ���ķ�������ʱ���Ͳ�������
				{

					switch (key[kbhitCount])//��ȡ��ǰ����
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
						//�����д����߻���ʧ-û���ƶ���ɾ����β��
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
				if (directionY[compare] == 1)//�����ƶ�
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
				//printf("%����%d\n", kbhitCount);
			
			/*else if(walkMode == 2)
			{
				kbhitCount--;
				if (kbhitCount == 0)//������������·��ʱ�����ֶ�����
					walkMode = 1;
			}*/
			
		}
		
	}
	system("cls");
	gotoxy(10, 10);
	//printf("GAME OVER");
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
//	gotoxy(24, 0);
//	printf("FOOD NUM:%d", foodNum);
	int x, y;
	x = ((rand() * 133) % (MAPX - 3)) + 2;
	y = ((rand() * 334) % (MAPY - 3)) + 2;
	//printf("%d,%d", x, y);
	int isGenerate = 0;
	//��������ʳ�������
	isGenerate = (rand() * 100) % 10;
	if (isGenerate < 8)
	{
		if (x > 1 && x < MAPX - 2  && y>1 && y < MAPY - 2 && map[x][y] != 1 && foodCount < (foodNum) && map[x][y] != 2 && map[x][y] != 5 && map[x][y] != 6 && map[x][y] != 7)
		{	
			for (int i = 0; i < foodNum; i++) {//��һ��λ�ô���ʳ��
				if (foodGroup[i].status == 0)//��λ�ñ���������ʳ���ʱ��
				{
					foodGroup[i].foodX = x;
					foodGroup[i].foodY = y;
					foodGroup[i].foodLife = (rand_food_x() * 100) % 50 + 50;//ʳ�������
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
	//�������ɵ�����
	isGenerate = (rand() * 100) % 18;
	if (isGenerate < 12)
	{
		if (x > 0 && x < MAPX && y>0 && y < MAPY && map[x][y] != 1 && poisonCount < (poisonNum - 1) && map[x][y] != 2)
		{
			for (int i = 0; i < poisonNum; i++) {//��һ��λ�ô���ʳ��
				if (poisonGroup[i].status == 0)//��λ�ñ���������ʳ���ʱ��
				{
					poisonGroup[i].poisonX = x;
					poisonGroup[i].poisonY = y;
					poisonGroup[i].posionLife = (rand_food_x() * 100) % 22 + 20;//����
					poisonGroup[i].status = 1;
					map[x][y] = 7;
					i = poisonNum;
				}
			}
			poisonCount += 1;

			gotoxy(7, 45);
		//	printf("���϶����� %d", poisonCount);
		}
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
	if (map[x][y] == 5)//ͷ�������ʳ��������غ�
	{
		isFinish = 1;
		for (int i = 0; i < foodNum; i++)
			if (foodGroup[i].foodX == x && foodGroup[i].foodY == y)
			{
				gotoxy(21, 0);
				foodGroup[i].status = 0;
				foodCount -= 1;//�����⣬����������������д�Ե��м�һ�� �������һ������������
				score += 100;
				result = 1;
				return result;

			}
	}

	if (map[x][y] == 7 && walkMode == 0)//ͷ������Ͷ���������غ�
	{
		walkMode = 3;
		for (int i = 0; i < poisonNum; i++)
			if (poisonGroup[i].poisonX == x && poisonGroup[i].poisonY == y)
			{	//�ҵ��Ե�������
				gotoxy(21, 0);
			
				
				//printf("No no no!!      ");
				poisonGroup[i].status = 0;
				poisonCount -= 1;
				score -= 100;
				result = 2;
				return result;

			}
	}
	//ײǽ�ˣ�
	else if (map[x][y] == 1) {
		//if(walkMode == 0)
		gameStatus = 0;

	}

	//ҧ���Լ�


	else if (map[x][y] == 2 && walkMode == 0)//��ͷ��������������غ�
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
			//	printf("����ʹ������ʧȥ��%d��", count);
				dimageShow = 5;
				
	}
			
	
	return result;
}

void Clearer()
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
				foodCount--;
			}
		}
	}

	//���д��ڵĶ�������� -1
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
		printf(" ");//����߹���
		gotoxy(25, 0);
	for (int i = 0; i < 10; i++) {//��ӡָ��
		char k = key[i];
		switch (k)
		{
		case KEYUP:
			printf(" �� ");
			break;

		case KEYDOWN:
			printf(" �� ");
			break;

		case KEYLEFT:
			printf(" �� ");
			break;
		case KEYRIGHT:
			printf(" �� ");
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

void visit(int row, int col)//��һ�����Ե�λ��
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
	//maze[row][col] = 11;//������� ��ֹ�ظ�����
	enqueue(visit_point);
}

void BFS()
{
	int isSearch = 0;
	//���ص�ͼ ��������·��
	for (int i = 0; i < MAPX; i++)
	{
		for (int j = 0; j < MAPY; j++)
		{

			maze[i][j] = map[i][j];//����ͼ����
		}
	}


	//ȷ��Ŀ������   loop
	for (int i = 0; i < foodNum; i++)
	{
		if (foodGroup[i].status == 1) {
			int tarX = foodGroup[i].foodX;
			int tarY = foodGroup[i].foodY;
			maze[tarX][tarY] = 5;//���ϼǺ�--�յ�
		}
	}
	if (foodCount == 0)
	{
		clearKey();
		maze[tail->positionX][tail->positionY] = 5;
	}
		int x, y;
	clean_queue();
	struct point p;//��ʼ��  ��ͷ---------------------------------��ô�ڵڶ���
	gotoxy(10, 42);
	//printf("SNAKE HEAD POI:%d,%d", head->positionX, head->positionY);
	p.col = head->positionY;
	p.row = head->positionX;
	x = head->positionX;
	y = head->positionY;
	p.predecessor = -1;
	enqueue(p);//���,rear --1
	
	
	while (!is_empty()) {//���в�Ϊ�յ�ʱ��ѭ��
		p = dequeue();//���ӣ�p���ڶ��׺�һ??   front----1
		if (maze[p.row][p.col] == 5) {			
			isSearch = 1;
			break;//����Ŀ����ʱ��   maze[p.row][p.col] == 5
		}

		if (p.col + 1 < MAPY - 1 /* right ���Ҳ�ײ�߽�*/
			&& (maze[p.row][p.col + 1] == 0 || maze[p.row][p.col + 1] == 5 || maze[p.row][p.col + 1] == 6) && maze[p.row][p.col + 1] != 1  && maze[p.row][p.col + 1] != 10)//��ͼ����Ҫ������
			visit(p.row, p.col + 1);//visit��һ����

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
	

		if (isSearch == 1)//��������ʳ���ʱ��
		{
			isSearch = 0;

			int keyCount = 49;
			while (p.predecessor != -1) {//�����һ��һֱ�򵽵�һ��
				if (p.row != queue[p.predecessor].row)//������������˸ı�
				{
					if (p.row == (queue[p.predecessor].row - 1))//��������һ�е�����
					{
						autoKey[keyCount] = KEYUP;
					}
					else {
						autoKey[keyCount] = KEYDOWN;
					}
				}

				if (p.col != queue[p.predecessor].col)//������������˸ı�
				{
					if (p.col == (queue[p.predecessor].col - 1))//��������һ�е����
					{
						autoKey[keyCount] = KEYLEFT;//����
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

void clearKey() {  //������а���
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
	//WALKMODE3    �ֶ���ģʽ
	int flag = 0;
	AX = dirX;
	AY = dirY;
	if (map[head->positionX + AX][head->positionY + AY] == 1) {//������һ����λ��	
		if (walkMode == 3)
		{
			//autoRound = 0;
		//	isFinish = 1;//
			clearKey();
			char danger,get;
		    getch();
			danger = getch();//��һ����Ҫײǽ�ֶ����

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
			
			if ((AX == 1 || AX == -1) && flag == 0)//��ǰ�������»�������
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

void beforeGame()//��Ϸ��ʼʱ��ѡ�����
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
			if ((get = getch()) == 13)//���»س�ʱ��ʼ��Ϸ-�Ȳ���
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
	//���е�ͼѡ��  ������ͬ�ĵ���
	//�ºͲ�ԭ
	//����ɭ��
	//�ɺ�ɳĮ
	//���߱�ԭ
	//���˵���
	//�Զ���

	//���г���ѡ��
	putimage(0, 0, &sceneSel[0]);
	while (1)
	{

		if (kbhit)
		{
			char get;
			if ((get = getch()) == 13)//���»س�ʱȷ�ϳ���
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


	//���ص�ͼ
	for (int i = 0; i < MAPX; i++)
		for (int j = 0; j < MAPY; j++)
			map[i][j] = mapSel[scene][i][j];


	//�����Ѷ�ѡ��
	putimage(0, 0, &level[0]);
	while (1)
	{
		
		if (kbhit)
		{
			char get;
			if ((get = getch()) == 13)//���»س�ʱȷ���Ѷ�
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