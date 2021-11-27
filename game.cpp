#include"game.h"

Game::Game()
{
	this->GAME_DIFFICULTY = 0;						//Ĭ��Ϊ��
}
Game::~Game()
{

}
void Game::start_interface()						//��ʼҳ��
{
	//initgraph(640, 480, SHOWCONSOLE);		//������̨�Ĵ���
	initgraph(640, 480);
	ExMessage operate;

	while (1)
	{
		
		BeginBatchDraw();
		setbkcolor(WHITE);
		cleardevice();
		setlinecolor(BLACK);
		settextcolor(LIGHTBLUE);

		rectangle(40, 45, 600, 140);
		rectangle(42, 47, 602, 142);		//���ֿ�
		rectangle(44, 49, 604, 144);
		rectangle(46, 51, 606, 146);
		settextstyle(70, 0, "����");
		outtextxy(55, 60, "̰���ߴ���ս1.0");

		settextcolor(BLACK);
		settextstyle(20, 0, "����");

		outtextxy(280, 200, "��ʼ��Ϸ");		//��ʼ��Ϸ
		rectangle(270, 195, 365, 225);
		rectangle(268, 193, 363, 223);

		outtextxy(300, 270, "����");			//����
		rectangle(270, 265, 365, 295);
		rectangle(268, 263, 363, 293);

		outtextxy(300, 340, "�˳�");			//�˳�
		rectangle(270, 335, 365, 365);
		rectangle(268, 333, 363, 363);
		EndBatchDraw();
		operate = getmessage(EM_MOUSE);
		if (operate.lbutton)
		{
			switch (judge(operate.x, operate.y))
			{
			case 1:
				setfillcolor(LIGHTGRAY);
				fillrectangle(270, 195, 365, 225);		//���Ч�� 
				Sleep(200);
				setfillcolor(WHITE);
				fillrectangle(270, 195, 365, 225);
				outtextxy(280, 200, "��ʼ��Ϸ");
				Sleep(100);
				game_start();		//������Ϸ
				break;
			case 2:
				setfillcolor(LIGHTGRAY);
				fillrectangle(270, 265, 365, 295);		//���Ч�� 
				Sleep(200);
				setfillcolor(WHITE);
				fillrectangle(270, 265, 365, 295);
				outtextxy(300, 270, "����");
				Sleep(100);
				this->config();		//��������
				break;
			case 3:
				setfillcolor(LIGHTGRAY);
				fillrectangle(270, 335, 365, 365);		//���Ч�� 
				Sleep(200);
				exit(0);
			default:
				break;
			}
		}	
	}
}

int Game::judge(int x, int y)			//�ж������
{
	if (270 <= x && x <= 365)
	{
		if (195 <= y && y <= 225)
			return 1;	//��ʼ��Ϸ
		else if (265 <= y && y <= 295)
			return 2;	//����
		else if (335 <= y && y <= 365)
			return 3;	//�˳�
	}
		
	return 0;
}

//1 ����ǽ 0 ��ǽ 
void Game::game_start()
{

	Snake wyatt(this->GAME_DIFFICULTY);
	Map map;
	Food food;
	while (wyatt._continue)
	{
		BeginBatchDraw();			//������ͼ
		cleardevice();
		map.Draw_map();
		food.place_food(wyatt);
		if (wyatt.is_defeat())
		{
			wyatt.game_over();
			EndBatchDraw();			//����������ͼ
			system("pause");
			break;
		}

		wyatt.Snake_move(food);
		wyatt.draw_snake();
		
		EndBatchDraw();				//����������ͼ
		Sleep(100);	
	}
}

void Game::config()
{
	ExMessage box;
	bool voluem = 0;
	bool speed = 0;
	while (true)
	{
		BeginBatchDraw();
		cleardevice();
		outtextxy(70, 60, "����");
		outtextxy(180, 140, "�Ѷȣ�");
		outtextxy(180, 230, "������");
		outtextxy(180, 320, "�ٶȣ�");



		rectangle(60, 55, 115, 85);
		rectangle(62, 57, 117, 87);		//���ؼ���

		rectangle(255, 135, 330, 165);	//�Ѷȿ�
		rectangle(253, 132, 328, 162);

		rectangle(245, 225, 350, 255);	//������
		rectangle(247, 227, 352, 257);

		rectangle(240, 315, 365, 345);	//�ٶȿ�
		rectangle(242, 317, 367, 347);

		switch (this->GAME_DIFFICULTY)		//�Ѷ�
		{
		case 0:
			outtextxy(275, 140, "��");
			break;
		case 1:
			outtextxy(275, 140, "����");
			break;
		}
		switch (voluem)		//����
		{
		case 0:
			outtextxy(255, 232, "û��������");
			break;
		case 1:
			outtextxy(255, 232, "���������");
			break;
		}
		switch (speed)		//�ٶ�
		{
		case 0:
			outtextxy(247, 320, "��һ�����ٶ�");
			break;
		case 1:
			outtextxy(247, 320, "��һ�����ٶ�");
			break;
		}
		EndBatchDraw();
		box = getmessage(EM_MOUSE);
		if(box.lbutton)
			if (255 <= box.x && box.x <= 330 && box.y >= 132 && box.y <= 165)		//�Ѷ�
			{
				setfillcolor(LIGHTGRAY);
				fillrectangle(255, 135, 330, 165);
				//Sleep(100);
				setfillcolor(WHITE);
				fillrectangle(255, 135, 330, 165);
				this->GAME_DIFFICULTY = !this->GAME_DIFFICULTY;//�л�ѡ��
			}
			else if (60 <= box.x && box.x <= 255 && box.y >= 55 && box.y <= 135)	//����
			{
				setfillcolor(LIGHTGRAY);
				fillrectangle(60, 55, 115, 85);
				Sleep(100);
				setfillcolor(WHITE);
				break;
			}
			else if (245 <= box.x && box.x <= 352 && box.y >= 225 && box.y <= 257)	//����
			{
				setfillcolor(LIGHTGRAY);
				fillrectangle(245, 225, 350, 255);
				Sleep(100);
				setfillcolor(WHITE);
				fillrectangle(245, 225, 350, 255);
				voluem = !voluem;//�л�ѡ��
			}
			else if (240 <= box.x && box.x <= 367 && box.y >= 315 && box.y <= 347)	//�ٶ�
			{
				setfillcolor(LIGHTGRAY);
				fillrectangle(240, 315, 365, 345);
				Sleep(100);
				setfillcolor(WHITE);
				fillrectangle(240, 315, 365, 345);
				speed = !speed;//�л�ѡ��
			}


	}


}






