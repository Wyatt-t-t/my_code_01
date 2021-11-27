#pragma once
#include<graphics.h>
#include<iostream>

using namespace std;


class Node
{
public:
	Node(int x = 0, int y = 0);
	~Node();
	void draw_body();

	int n_x;
	int n_y;
	

};
