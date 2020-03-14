#include "Food.h"
#include <ctime>
#include <cstdlib>

Food::Food(const int bound_x, const int bound_y, const char icon) : icon_(icon){
    srand(static_cast<unsigned int>(time(NULL)));
    position_.cor_x = rand() % (bound_x - 4) + 2;
    position_.cor_y = rand() % (bound_y - 4) + 2;
}

const Coordinate& Food::get_position() const {
    return position_;
}

const char& Food::get_icon() const {
    return icon_;
}
