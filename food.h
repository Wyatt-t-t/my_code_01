#pragma once
#include"Snake.h"

class Food
{
	friend class Snake;
public:
	Food();
	~Food();
	
	void update_food(Snake& sss);

	void place_food(Snake& sss);
	bool is_repeat(Snake &sss);
	void Ch_eaten();
private:
	int f_x;
	int f_y;
	bool is_eaten;
};