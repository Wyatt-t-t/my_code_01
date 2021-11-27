#pragma once
#include<graphics.h>
#include<iostream>
using namespace std;
class Map
{
public:
	Map();
	~Map();
	void Draw_map();
	
private:
	RECT p_title;
	RECT p_score;
	RECT p_len;
	RECT p_diff;

};
