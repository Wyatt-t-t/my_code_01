#pragma once
#include<string>
#include<graphics.h>
#include<list>
#include<iostream>
#include<conio.h>
#include<fstream>
#include"Node.h"
#include"food.h"
using namespace std;

class Snake
{
	friend class Food;
public:
	Snake(int Difficulty);			//构造函数，默认长度为2，
	~Snake();
	void draw_snake();				//将蛇身绘画，并print得分、长度、难度、记录等信息
	void Update_direction();		//获取键盘wasd，并改变蛇运动方向
	void Change_head();				//按照运动方向来改变蛇头位置
	void Snake_move(Food &food);	//将头的新位置结点添加，按growth来判断是否删除最后结点，以达到蛇各结点的移动
	void print_text();				//print得分、长度、难度、记录等信息

	bool growth(Food &food);		//判断是否碰到food
	bool is_defeat();				//判断是否game over
	bool is_body();					//判断是否头碰到身体
	bool is_wall();					//根据难度来判断头碰墙是否失败


	void game_over();				//游戏结束绘图
	void pause();					//暂停键

	bool _continue;					//(暂停)是否game继续进行
	


private:
	int head_x;			//头位置
	int head_y;			
	char direction;		//移动方向
	list<Node> Head;	//蛇身


	int s_score;		//得分
	int Max_score[2];	//最高记录
	int len_body;		//长度
	int difficulty;		//1 不穿墙 0 穿墙
	

};

