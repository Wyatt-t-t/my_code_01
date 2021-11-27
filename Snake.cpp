#include<iostream>
#include<graphics.h>
#include<list>
#include<string>
#include"Snake.h"

using namespace std;

Snake::Snake(int Difficulty)
{
	Node body(10, 12);
	Node head(11, 12);				//Ĭ�ϵ�����body
	this->head_x = 11;
	this->head_y = 12;				//����ͷ���λ��
	this->Head.push_back(body);		//��ӽ��
	this->Head.push_front(head);

	_continue = 1;					//�����ж�����Ϊ1��������ͣ���ز˵�����
	this->s_score = 0;				//���÷���
	this->direction = 'R';			//���÷���Ϊ �� 'R'
	this->len_body = 2;				//�������峤��
	this->difficulty = Difficulty;	//�����Ѷȣ��Ѷ�Ĭ��Ϊ0�����������и���

	ifstream MAXSCORE;				//���ļ�����ȡ��¼��Ϣ
	MAXSCORE.open("MAXSCORE.txt", ios::in);
	if (MAXSCORE.is_open())
	{
		MAXSCORE >> this->Max_score[0];//��ģʽ
		MAXSCORE >> this->Max_score[1];//����ģʽ
	}
	else
	{
		this->Max_score[0] = 0;		//δ����ֵΪ0
		this->Max_score[1] = 0;
	}

	MAXSCORE.close();
}

Snake::~Snake()
{
	if (s_score >= Max_score[difficulty])		//�˳�ʱ������¼��Ϣ�������ļ���
	{
		ofstream MAXSCORE;			
		MAXSCORE.open("MAXSCORE.txt", ios::out);
		MAXSCORE << Max_score[0] << ' ' << Max_score[1];
		MAXSCORE.close();
	}
}


void Snake::draw_snake()						//��������
{
	for (list<Node>::iterator it = Head.begin(); it != Head.end(); it++)
	{
		it->draw_body();	
	}
	this->print_text();							//ͬʱ��ӡ�ҿ���Ϣ


}	
void Snake::Change_head()						//�ı�ͷλ��
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

void Snake::Update_direction()					//�ı䷽��ͬʱ��ȡ��ͣ����
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


void Snake::Snake_move(Food &food)				//���ƶ������ж��Ƿ�Ե�ʳ����Ե����򳤶ȣ�����++
{
	this->Update_direction();	//�ķ���
	this->Change_head();		//��ͷλ��

	if (!this->difficulty)		//ʵ�ּ�ģʽ��ǽ
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
		outtextxy(500, 160, "��ģʽ(�ɴ�ǽ)");
		break;
	case 1:
		outtextxy(500, 160, "����ģʽ");
		break;
	}
			
	if (s_score >= Max_score[difficulty])
	{
		Max_score[difficulty] = s_score;
	}
	
	outtextxy(510, 290, to_string(Max_score[0]).c_str());//��Ҫ�������н��ַ�����Ϊ������
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

bool Snake::is_body()									//�ж�ͷ�Ƿ���������
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
bool Snake::is_wall()									//�����Ѷ�������
{
	if (this->difficulty)	//1 ����ǽ 0 ��ǽ
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
	outtextxy(110, 230, "�밴��������ز˵�...");
	this->print_text();
	this->_continue = 0;


}

void Snake::pause()
{

	setlinecolor(BLACK);
	rectangle(100, 170, 300, 280);
	outtextxy(172, 190, "PAUSE!");
	outtextxy(140, 230, "�˵�");
	outtextxy(220, 230, "����");

	rectangle(135, 225, 178, 252);		//�˵���
	rectangle(215, 225, 258, 252);		//���ؿ�



	this->print_text();
	EndBatchDraw();
	ExMessage _pause;
	while (true)
	{
		_pause = getmessage();
		if (_pause.lbutton)
		{
			if (135 <= _pause.x && _pause.x <= 178 && _pause.y >= 225 && _pause.y <= 252)		//�˵�
			{
				setfillcolor(LIGHTGRAY);
				fillrectangle(135, 225, 178, 252);
				Sleep(100);
				setfillcolor(WHITE);
				this->_continue = 0;
				break;
				
			}
			else if (215 <= _pause.x && _pause.x <= 258 && _pause.y >= 225 && _pause.y <= 252)	//����
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