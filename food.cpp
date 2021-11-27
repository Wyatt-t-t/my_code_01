#include"food.h"


Food::Food()
{
	is_eaten = 1;
	f_x = rand() % 20 + 1;
	f_y = rand() % 24 + 1;
}

Food::~Food()
{

}

void Food::update_food(Snake& sss)
{
	srand(time(0));
	f_x = rand() % 20 + 1;
	f_y = rand() % 24 + 1;
	while (is_repeat(sss))
	{
		f_x = rand() % 20 + 1;
		f_y = rand() % 24 + 1;
	}
	is_eaten = 0;
}


void Food::place_food(Snake& sss)
{
	if (is_eaten)
	{
		update_food(sss);
	}
	setfillcolor(DARKGRAY);
	solidrectangle(20 * f_x - 20, 20 * f_y - 20, 20 * f_x, 20 * f_y);
}

bool Food::is_repeat(Snake& sss)
{
	for (list<Node>::iterator it = sss.Head.begin(); it != sss.Head.end(); it++)
	{
		if (f_x == it->n_x && f_y == it->n_y)
		{
			return 1;
		}
	}
	return 0;
}

void Food::Ch_eaten()
{
	this->is_eaten = 1;
}