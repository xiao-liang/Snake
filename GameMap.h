#ifndef SNAKE_GAMEMAP_H_
#define SNAKE_GAMEMAP_H_
class GameMap
{
private:
	int height_;
	int width_;
public:
	GameMap(const int width, const int height);
	const int& get_height() const { return height_; }
	const int& get_width() const { return width_; }
};
#endif 


