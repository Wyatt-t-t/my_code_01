#include"Map.h"


Map::Map()
{
	settextstyle(17, 0, "����");
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
	drawtext(_T("###  WYATT��̰����  ###"), &p_title, DT_CENTER);
	drawtext(_T("�÷֣�"), &p_score, DT_LEFT);
	drawtext(_T("�߳���"), &p_len, DT_LEFT);
	drawtext(_T("�Ѷȣ�"), &p_diff, DT_LEFT);
	outtextxy(430, 250, "��߼�¼:");			//��Ҫ�������н��ַ�����Ϊ������
	outtextxy(450, 290, "�򵥣�");
	outtextxy(450, 330, "���ѣ�");
	outtextxy(430, 400, "�������WASD");
	outtextxy(430, 435, "��ͣ���� P");

}

