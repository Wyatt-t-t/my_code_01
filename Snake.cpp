#include<iostream>
#include<graphics.h>
#include<list>
#include<string>
#include"Snake.h"

using namespace std;

Snake::Snake(int Difficulty)
{
	Node body(10, 12);
	Node head(11, 12);				//默认的两个body
	this->head_x = 11;
	this->head_y = 12;				//设置头结点位置
	this->Head.push_back(body);		//添加结点
	this->Head.push_front(head);

	_continue = 1;					//设置判断条件为1，用于暂停返回菜单操作
	this->s_score = 0;				//设置分数
	this->direction = 'R';			//设置方向为 右 'R'
	this->len_body = 2;				//设置身体长度
	this->difficulty = Difficulty;	//设置难度，难度默认为0，可在设置中更改

	ifstream MAXSCORE;				//打开文件，获取记录信息
	MAXSCORE.open("MAXSCORE.txt", ios::in);
	if (MAXSCORE.is_open())
	{
		MAXSCORE >> this->Max_score[0];//简单模式
		MAXSCORE >> this->Max_score[1];//困难模式
	}
	else
	{
		this->Max_score[0] = 0;		//未打开则赋值为0
		this->Max_score[1] = 0;
	}

	MAXSCORE.close();
}

Snake::~Snake()
{
	if (s_score >= Max_score[difficulty])		//退出时，将记录信息保存在文件中
	{
		ofstream MAXSCORE;			
		MAXSCORE.open("MAXSCORE.txt", ios::out);
		MAXSCORE << Max_score[0] << ' ' << Max_score[1];
		MAXSCORE.close();
	}
}


void Snake::draw_snake()						//画蛇身体
{
	for (list<Node>::iterator it = Head.begin(); it != Head.end(); it++)
	{
		it->draw_body();	
	}
	this->print_text();							//同时打印右框信息


}	
void Snake::Change_head()						//改变头位置
{
	switch (this->direction)
	{
	case 'U':
		head_y--;
		break;
	case 'D':
		head_y++;
		break;
	case 'L':
		head_x--;
		break;
	case 'R':
		head_x++;
		break;
	}
}

void Snake::Update_direction()					//改变方向，同时获取暂停操作
{

	if (_kbhit())
	{
		char key;
		key = _getch();
		switch (key)
		{
		case 'w':
		case 'W':
			if(direction != 'D')
			this->direction = 'U';
			break;
		case 's':
		case 'S':
			if (direction != 'U')
			this->direction = 'D';
			break;
		case 'a':
		case 'A':
			if (direction != 'R')
			this->direction = 'L';
			break;
		case 'd':
		case 'D':
			if (direction != 'L')
			this->direction = 'R';
			break;
		case 'p':
		case 'P':
			this->pause();
			break;
		default:
			break;
		}
	}
}


void Snake::Snake_move(Food &food)				//蛇移动，并判断是否吃到食物，若吃到，则长度，分数++
{
	this->Update_direction();	//改方向
	this->Change_head();		//改头位置

	if (!this->difficulty)		//实现简单模式穿墙
	{
		if (head_x == 21)						
		{
			head_x = 0;
		}

		else if (head_x == 0)
		{
			head_x = 20;
		}
		else if (head_y == 25)
		{
			head_y = 1;
		}
		else if (head_y == 0)
		{
			head_y = 25;
		}
	}

	if (head_x != Head.begin()->n_x || head_y != Head.begin()->n_y)
	{
		Node point(head_x, head_y);
		
		Head.push_front(point);
		if (growth(food))
		{
			Head.pop_back();
		}
		
	}
}

void Snake::print_text()
{
	outtextxy(500, 80, to_string(s_score).c_str());
	outtextxy(500, 120, to_string(len_body).c_str());
	switch (difficulty)
	{
	case 0:
		outtextxy(500, 160, "简单模式(可穿墙)");
		break;
	case 1:
		outtextxy(500, 160, "困难模式");
		break;
	}
			
	if (s_score >= Max_score[difficulty])
	{
		Max_score[difficulty] = s_score;
	}
	
	outtextxy(510, 290, to_string(Max_score[0]).c_str());//需要在设置中将字符集设为允许多个
	outtextxy(510, 330, to_string(Max_score[1]).c_str());

	
}

bool Snake::growth(Food& food)
{
	if (this->head_x == food.f_x && this->head_y == food.f_y)
	{
		food.is_eaten = 1;
		this->len_body++;
		this->s_score++;
		return 0;
	}
	return 1;
}

bool Snake::is_body()									//判断头是否碰到身体
{
	list<Node>::iterator it = Head.begin();
	for (it++; it != Head.end(); it++)
	{
		if (head_x == it->n_x && head_y == it->n_y)
		{
			return 1;
		}
		
	}
	return 0;
}
bool Snake::is_wall()									//根据难度来返回
{
	if (this->difficulty)	//1 不穿墙 0 穿墙
	{
		if (head_x == 21 || head_x == 0 || head_y == 0 || head_y == 25)
		{
			return 1;
		}
		else
			return 0;
	}
	else
	{
		return 0;
	}
}
bool Snake::is_defeat()
{
	if (is_body() || is_wall())
		return 1;
	else
		return 0;
}


void Snake::game_over()
{
	setlinecolor(BLACK);
	rectangle(100, 170, 300, 280);
	outtextxy(155, 190, "YOU LOST!");
	outtextxy(110, 230, "请按任意键返回菜单...");
	this->print_text();
	this->_continue = 0;


}

void Snake::pause()
{

	setlinecolor(BLACK);
	rectangle(100, 170, 300, 280);
	outtextxy(172, 190, "PAUSE!");
	outtextxy(140, 230, "菜单");
	outtextxy(220, 230, "返回");

	rectangle(135, 225, 178, 252);		//菜单框
	rectangle(215, 225, 258, 252);		//返回框



	this->print_text();
	EndBatchDraw();
	ExMessage _pause;
	while (true)
	{
		_pause = getmessage();
		if (_pause.lbutton)
		{
			if (135 <= _pause.x && _pause.x <= 178 && _pause.y >= 225 && _pause.y <= 252)		//菜单
			{
				setfillcolor(LIGHTGRAY);
				fillrectangle(135, 225, 178, 252);
				Sleep(100);
				setfillcolor(WHITE);
				this->_continue = 0;
				break;
				
			}
			else if (215 <= _pause.x && _pause.x <= 258 && _pause.y >= 225 && _pause.y <= 252)	//返回
			{
				setfillcolor(LIGHTGRAY);
				fillrectangle(215, 225, 258, 252);
				Sleep(100);
				setfillcolor(WHITE);
				break;
			}
		}
	}

}