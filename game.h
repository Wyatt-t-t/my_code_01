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
	void start_interface();			//��ʼҳ��
	void game_start();				//��Ϸ��ʼ
	void config();					//����

	int judge(int x, int y);		//�ж������λ�ý�����������ѡ��

private:
	bool GAME_DIFFICULTY;			//��Ϸ�Ѷ� 0 �򵥣�1 ����
};