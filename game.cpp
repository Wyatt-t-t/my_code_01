#include"game.h"

Game::Game()
{
	this->GAME_DIFFICULTY = 0;						//默认为简单
}
Game::~Game()
{

}
void Game::start_interface()						//开始页面
{
	//initgraph(640, 480, SHOWCONSOLE);		//带控制台的窗口
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
		rectangle(42, 47, 602, 142);		//名字框
		rectangle(44, 49, 604, 144);
		rectangle(46, 51, 606, 146);
		settextstyle(70, 0, "黑体");
		outtextxy(55, 60, "贪吃蛇大作战1.0");

		settextcolor(BLACK);
		settextstyle(20, 0, "等线");

		outtextxy(280, 200, "开始游戏");		//开始游戏
		rectangle(270, 195, 365, 225);
		rectangle(268, 193, 363, 223);

		outtextxy(300, 270, "设置");			//设置
		rectangle(270, 265, 365, 295);
		rectangle(268, 263, 363, 293);

		outtextxy(300, 340, "退出");			//退出
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
				fillrectangle(270, 195, 365, 225);		//点击效果 
				Sleep(200);
				setfillcolor(WHITE);
				fillrectangle(270, 195, 365, 225);
				outtextxy(280, 200, "开始游戏");
				Sleep(100);
				game_start();		//进入游戏
				break;
			case 2:
				setfillcolor(LIGHTGRAY);
				fillrectangle(270, 265, 365, 295);		//点击效果 
				Sleep(200);
				setfillcolor(WHITE);
				fillrectangle(270, 265, 365, 295);
				outtextxy(300, 270, "设置");
				Sleep(100);
				this->config();		//进入设置
				break;
			case 3:
				setfillcolor(LIGHTGRAY);
				fillrectangle(270, 335, 365, 365);		//点击效果 
				Sleep(200);
				exit(0);
			default:
				break;
			}
		}	
	}
}

int Game::judge(int x, int y)			//判断鼠标点击
{
	if (270 <= x && x <= 365)
	{
		if (195 <= y && y <= 225)
			return 1;	//开始游戏
		else if (265 <= y && y <= 295)
			return 2;	//设置
		else if (335 <= y && y <= 365)
			return 3;	//退出
	}
		
	return 0;
}

//1 不穿墙 0 穿墙 
void Game::game_start()
{

	Snake wyatt(this->GAME_DIFFICULTY);
	Map map;
	Food food;
	while (wyatt._continue)
	{
		BeginBatchDraw();			//批量绘图
		cleardevice();
		map.Draw_map();
		food.place_food(wyatt);
		if (wyatt.is_defeat())
		{
			wyatt.game_over();
			EndBatchDraw();			//结束批量绘图
			system("pause");
			break;
		}

		wyatt.Snake_move(food);
		wyatt.draw_snake();
		
		EndBatchDraw();				//结束批量绘图
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
		outtextxy(70, 60, "返回");
		outtextxy(180, 140, "难度：");
		outtextxy(180, 230, "音量：");
		outtextxy(180, 320, "速度：");



		rectangle(60, 55, 115, 85);
		rectangle(62, 57, 117, 87);		//返回键框

		rectangle(255, 135, 330, 165);	//难度框
		rectangle(253, 132, 328, 162);

		rectangle(245, 225, 350, 255);	//音量框
		rectangle(247, 227, 352, 257);

		rectangle(240, 315, 365, 345);	//速度框
		rectangle(242, 317, 367, 347);

		switch (this->GAME_DIFFICULTY)		//难度
		{
		case 0:
			outtextxy(275, 140, "简单");
			break;
		case 1:
			outtextxy(275, 140, "困难");
			break;
		}
		switch (voluem)		//音量
		{
		case 0:
			outtextxy(255, 232, "没错你聋了");
			break;
		case 1:
			outtextxy(255, 232, "你真的聋了");
			break;
		}
		switch (speed)		//速度
		{
		case 0:
			outtextxy(247, 320, "跑一样的速度");
			break;
		case 1:
			outtextxy(247, 320, "飞一样地速度");
			break;
		}
		EndBatchDraw();
		box = getmessage(EM_MOUSE);
		if(box.lbutton)
			if (255 <= box.x && box.x <= 330 && box.y >= 132 && box.y <= 165)		//难度
			{
				setfillcolor(LIGHTGRAY);
				fillrectangle(255, 135, 330, 165);
				//Sleep(100);
				setfillcolor(WHITE);
				fillrectangle(255, 135, 330, 165);
				this->GAME_DIFFICULTY = !this->GAME_DIFFICULTY;//切换选项
			}
			else if (60 <= box.x && box.x <= 255 && box.y >= 55 && box.y <= 135)	//返回
			{
				setfillcolor(LIGHTGRAY);
				fillrectangle(60, 55, 115, 85);
				Sleep(100);
				setfillcolor(WHITE);
				break;
			}
			else if (245 <= box.x && box.x <= 352 && box.y >= 225 && box.y <= 257)	//音量
			{
				setfillcolor(LIGHTGRAY);
				fillrectangle(245, 225, 350, 255);
				Sleep(100);
				setfillcolor(WHITE);
				fillrectangle(245, 225, 350, 255);
				voluem = !voluem;//切换选项
			}
			else if (240 <= box.x && box.x <= 367 && box.y >= 315 && box.y <= 347)	//速度
			{
				setfillcolor(LIGHTGRAY);
				fillrectangle(240, 315, 365, 345);
				Sleep(100);
				setfillcolor(WHITE);
				fillrectangle(240, 315, 365, 345);
				speed = !speed;//切换选项
			}


	}


}






