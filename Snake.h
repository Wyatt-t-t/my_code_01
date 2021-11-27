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
	Snake(int Difficulty);			//���캯����Ĭ�ϳ���Ϊ2��
	~Snake();
	void draw_snake();				//������滭����print�÷֡����ȡ��Ѷȡ���¼����Ϣ
	void Update_direction();		//��ȡ����wasd�����ı����˶�����
	void Change_head();				//�����˶��������ı���ͷλ��
	void Snake_move(Food &food);	//��ͷ����λ�ý����ӣ���growth���ж��Ƿ�ɾ������㣬�Դﵽ�߸������ƶ�
	void print_text();				//print�÷֡����ȡ��Ѷȡ���¼����Ϣ

	bool growth(Food &food);		//�ж��Ƿ�����food
	bool is_defeat();				//�ж��Ƿ�game over
	bool is_body();					//�ж��Ƿ�ͷ��������
	bool is_wall();					//�����Ѷ����ж�ͷ��ǽ�Ƿ�ʧ��


	void game_over();				//��Ϸ������ͼ
	void pause();					//��ͣ��

	bool _continue;					//(��ͣ)�Ƿ�game��������
	


private:
	int head_x;			//ͷλ��
	int head_y;			
	char direction;		//�ƶ�����
	list<Node> Head;	//����


	int s_score;		//�÷�
	int Max_score[2];	//��߼�¼
	int len_body;		//����
	int difficulty;		//1 ����ǽ 0 ��ǽ
	

};

