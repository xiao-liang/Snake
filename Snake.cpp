#include"Snake.h"
#include"WinConsoleTools.h"

Snake::Snake(const Coordinate& init_position, const char head_symbol, const char body_symbol) : head_symbol_(head_symbol), body_symbol_(body_symbol) {
	// Initialize the snake of length 2, with its head up
	direction_ = 'U';
	is_alive_ = true;
	snake_.push_back(init_position);
	snake_.push_back(Coordinate({ init_position.cor_x,  init_position.cor_y+1 }));
	
	// Initialize the previous position of the snake 1 spot below the actual position.
	prev_head_ = Coordinate({ init_position.cor_x,  init_position.cor_y + 1 });
	prev_tail_ = Coordinate({ init_position.cor_x,  init_position.cor_y + 2 });
}


bool Snake::OnSnake(Coordinate position) const {
	for (const Coordinate & pos : snake_) {
		if (pos == position) {
			return true;
		}
	}
	return false;
}

void Snake::Move() {
	prev_head_ = snake_.front();
	Coordinate new_head = prev_head_;
	switch (direction_) {
	case 'U':
		new_head.cor_y--;
		break;
	case 'D':
		new_head.cor_y++;
		break;
	case 'L':
		new_head.cor_x -= 1;
		break;
	case 'R':
		new_head.cor_x += 1;
		break;
	}

	snake_.push_front(new_head);
	prev_tail_ = snake_.back();
	snake_.pop_back();

	std::list<Coordinate>::iterator it = ++snake_.begin();
	while (it != snake_.end()) {
		if (new_head == (*it)) {
			is_alive_ = false;
			return;
		}
		it++;
	}
}

void Snake::set_direction(char new_direction) {
	switch (new_direction) {
	case 'w':
		new_direction = 'U';
		break;
	case 's':
		new_direction = 'D';
		break;
	case 'a':
		new_direction = 'L';
		break;
	case 'd':
		new_direction = 'R';
		break;
	default:
		return;
	}

	switch (direction_) {
	case 'U':
		if (new_direction == 'D') return;
		break;
	case 'D':
		if (new_direction == 'U') return;
		break;
	case 'L':
		if (new_direction == 'R') return;
		break;
	case 'R':
		if (new_direction == 'L') return;
		break;
	}

	direction_ = new_direction;
}




const bool Snake::IsAlive() const {
	return is_alive_;
}

void Snake::Killed() {
	is_alive_ = false;
}

void Snake::Grow() {
	prev_tail_ = snake_.back();
	Coordinate new_tail = prev_tail_;
	switch (direction_) {
	case 'U':
		new_tail.cor_y++;
		break;
	case 'D':
		new_tail.cor_y--;
		break;
	case 'L':
		new_tail.cor_x++;
		break;
	case 'R':
		new_tail.cor_x--;
		break;
	}
	snake_.push_back(new_tail);
}
