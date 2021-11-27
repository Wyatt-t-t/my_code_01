#pragma once
#include<iostream>
#include"Snake.h"
#include"Map.h"
#include<Windows.h>

using namespace std;

class Game
{
public:
	Game();
	~Game();
	void start_interface();			//开始页面
	void game_start();				//游戏开始
	void config();					//设置

	int judge(int x, int y);		//判断鼠标点击位置进入以上三个选项

private:
	bool GAME_DIFFICULTY;			//游戏难度 0 简单；1 困难
};