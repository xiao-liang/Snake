#ifndef SNAKE_FOOD_H_
#define SNAKE_FOOD_H_
#include"Coordinate.h"
class Food
{	
	Coordinate position_;
	char icon_;
public:
	Food(const int bound_x, const int bound_y, const char food_symbol = '&');
	const Coordinate& get_position() const;
	const char& get_icon() const;
};
#endif

