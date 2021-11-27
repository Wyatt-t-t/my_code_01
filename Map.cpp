#include"Map.h"


Map::Map()
{
	settextstyle(17, 0, "黑体");
	line(400, 0, 400, 480);
	p_title = { 400,30,640,120 };
	p_score = { 450,80,500,150 };
	p_len = { 450,120,500,190 };
	p_diff = { 450,160,500,230 };
}

Map::~Map()
{

}

void Map::Draw_map()
{
	line(400, 0, 400, 480);
	drawtext(_T("###  WYATT的贪吃蛇  ###"), &p_title, DT_CENTER);
	drawtext(_T("得分："), &p_score, DT_LEFT);
	drawtext(_T("蛇长："), &p_len, DT_LEFT);
	drawtext(_T("难度："), &p_diff, DT_LEFT);
	outtextxy(430, 250, "最高记录:");			//需要在设置中将字符集设为允许多个
	outtextxy(450, 290, "简单：");
	outtextxy(450, 330, "困难：");
	outtextxy(430, 400, "方向键：WASD");
	outtextxy(430, 435, "暂停键： P");

}

