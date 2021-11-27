#include<iostream>
#include"Node.h"
using namespace std;

Node::Node(int x, int y)
{
	this->n_x = x;
	this->n_y = y;
}

Node::~Node()
{
	
}

void Node::draw_body()
{
	setfillcolor(LIGHTGRAY);
	if (n_x <= 20 && n_x > 0 && n_y <= 24 && n_y > 0)
	{
		solidrectangle(20 * n_x - 20, 20 * n_y - 20, 20 * n_x, 20 * n_y);
	}
}
