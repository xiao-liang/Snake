#ifndef SNAKE_COORDINATE_H_
#define SNAKE_COORDINATE_H_
struct Coordinate {
	int cor_x;
	int cor_y;
	bool operator==(const Coordinate & position) const { 
		return position.cor_x == cor_x && position.cor_y == cor_y;
	}
};
#endif
