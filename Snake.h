#ifndef SNAKE_SNAKE_H_
#define SNAKE_SNAKE_H_
#include<list>
#include<iostream>
#include"Coordinate.h"
class Snake
{
	const char head_symbol_;
	const char body_symbol_;
	char direction_;
	Coordinate prev_head_;
	Coordinate prev_tail_;
	std::list<Coordinate> snake_;
	bool is_alive_;
public:
	Snake(const Coordinate & init_position, const char head_symbol = 'O', const char body_symbol = '+');
	const char& get_head_symbol() const { return head_symbol_; }
	const char& get_body_symbol() const { return body_symbol_; }
	const Coordinate& get_head() const { return snake_.front(); }
	const Coordinate& get_tail() const { return snake_.back(); }
	const Coordinate& get_prev_head() const { return prev_head_; }
	const Coordinate& get_prev_tail() const { return prev_tail_; }
	const char& get_direction() const { return direction_; }

	bool OnSnake(Coordinate position) const;
	
	void Move();
	void set_direction(char new_direction);
	const bool IsAlive() const;
	void Killed();
	void Grow();
};
#endif
