#include <iostream>
#include "GameMap.h"
#include "Food.h"
#include "Snake.h"
#include "WinConsoleTools.h"
#include <conio.h> 
#include <string>
#include <utility>
using namespace std;

void PrintGameMap(const GameMap& game_map);
void ResetGameMap(const GameMap& game_map);
void PrintFood(const Food & food);
void RemoveFood(const Food& food);
void PrintSnake(const Snake& snake);
std::pair<int,int> GameRun(const GameMap & game_map, int base_refresh_rate, int hardness_level, int level_up_threshold, int highest_level);
void PrintFeedback(std::pair<int, int> final_performance, const int heighest_level);

int main()
{   
    // Setup the basic parameters. Variable names are self-explained.
    const int kGameMapWidth = 100;
    const int kGameMapHeight = 40;
    const int kLevelUpThreshold = 5;
    const int kHighestHardnessLevel = 5;
    const int kBaseRefreshRate = 100;
    // Hardness is defined in the following way:
    // We refresh the frames $(hardness_level+1) times every $(kBaseRefreshRate) milliseconds.
    
    // Initialize a console window as the game interface
    std::string window_size_command = "mode con cols=" + std::to_string(kGameMapWidth+4) + " lines=" + std::to_string(kGameMapHeight+8);
    system(window_size_command.c_str());
    MoveCenter();

    // Initialize and show the map
    GameMap game_map(kGameMapWidth, kGameMapHeight);
    PrintGameMap(game_map);

    // Print the info line at the bottom of the map
    MoveCursor(0, game_map.get_height());
    std::cout << "Your Score:  ";
    std::cout << "             ";
    std::cout << "Your level:  /" << kLevelUpThreshold;
    std::cout << "             ";
    std::cout << "[Earn " << kLevelUpThreshold << " points to level up!]";
    MoveCursor(0, game_map.get_height()+2);
    std::cout << "Press Keys: 'w'--up  's'--down  'a'--left  'd'--right";


    bool start_new_game = true;
    while (start_new_game) {
 
        // Get the harness level from the user 
        int hardness_level = 0;
        MoveCursor(2, 1);
        std::cout << "Specify the level you want to start with.";
        MoveCursor(2, 2);
        std::cout << "Enter a number among 0-" << kHighestHardnessLevel;
        std::wcout << "[0-Easy, " << kHighestHardnessLevel << "-Hard]";
        MoveCursor(2, 3);
        std::cout << "Your Choice:";
        ShowCursor(); // The cursor was hidden due to the last call of GameRun() function
        std::cin >> hardness_level;

        bool valid_input = false;
        while (!valid_input) {
            if (hardness_level < 0 || hardness_level > kHighestHardnessLevel) {
                MoveCursor(2, 5);
                std::cout << std::string(game_map.get_height() - 4, ' ');

                MoveCursor(2, 3);
                std::cout << std::string(game_map.get_height() - 4, ' ');
                MoveCursor(2, 3);
                std::cout << "Invalid Input" << std::endl;

                MoveCursor(2, 4);
                std::cout << std::string(game_map.get_height() - 4, ' ');
                MoveCursor(2, 4);
                std::cout << "Please enter a number between 0-" << kHighestHardnessLevel << ":" << std::endl;
                MoveCursor(2, 5);
                std::cin >> hardness_level;
            }
            else {
                valid_input = true;
            }
        }
        ResetGameMap(game_map);
        
        std::pair<int, int> final_performance = {};
        
        final_performance = GameRun(game_map,
                                    kBaseRefreshRate,
                                    hardness_level,
                                    kLevelUpThreshold,
                                    kHighestHardnessLevel);

        // Give the player feedback, based on the player's performance 
        PrintFeedback(final_performance, kHighestHardnessLevel);
        
        // Ask if the player wants a new game
        MoveCursor(2, 4);
        std::cout << "Press 'x' to exit. Press any other key to start a new game";
        char temp_char = ' ';
        MoveCursor(2, 5);
        temp_char = _getch();
        if (temp_char == 'x') start_new_game = false;

        // Clear the map for a new game.
        ResetGameMap(game_map);
    }

    return 0;
}


void PrintFood(const Food& food) {
    const Coordinate& food_position = food.get_position();
    MoveCursor(food_position.cor_x, food_position.cor_y);
    std::cout << food.get_icon();
}

void RemoveFood(const Food& food) {
    const Coordinate& food_position = food.get_position();
    MoveCursor(food_position.cor_x, food_position.cor_y);
    std::cout << ' ';
}

void PrintSnake(const Snake& snake) {
    // Draw the new head
    const Coordinate& cur_head = snake.get_head();
    MoveCursor(cur_head.cor_x, cur_head.cor_y);
    std::cout << snake.get_head_symbol();

    // Update the symbol at the old head (to a body symbol)
    const Coordinate& prev_head = snake.get_prev_head();
    MoveCursor(prev_head.cor_x, prev_head.cor_y);
    std::cout << snake.get_body_symbol();
    
    // Erase the old tail
    Coordinate prev_tail = snake.get_prev_tail();
    MoveCursor(prev_tail.cor_x, prev_tail.cor_y);
    std::cout << ' ';
}


void ResetGameMap(const GameMap& game_map) {
    for (int i = 1; i <= game_map.get_height() - 2; i++) {
        MoveCursor(2, i);
        std::cout << std::string(game_map.get_width() - 4, ' ');
    }
    PrintGameMap(game_map);
}

void PrintGameMap(const GameMap& game_map) {
    const int& width = game_map.get_width();
    const int& height = game_map.get_height();
    int i = 0;
    MoveCursor(0, 0 );
    for (i = 0; i < width; i += 2) std::cout << "¡ö"; 
    MoveCursor(0, 1 );
    for (i = 1; i < height; ++i) std::cout << "¡ö" << std::endl;
    for (i = 1; i < height; ++i) {
        MoveCursor(width - 2, i);
        std::cout << "¡ö";
    }
    MoveCursor(0, height - 1 );
    for (i = 0; i < width; i += 2) std::cout << "¡ö";
}


std::pair<int, int> GameRun(const GameMap & game_map, int base_refresh_rate, int hardness_level, int level_up_threshold, int highest_level) {
    
    int game_map_width = game_map.get_width();
    int game_map_height = game_map.get_height();

    int current_score = 0;

    // Hide the console cursor
    HideCursor();

    // Initialize and show the snake
    Snake snake(Coordinate({ game_map.get_width() / 2, game_map.get_height() / 2 }));
    PrintSnake(snake);

    // Initialize and show the food. 
    // (Keep generating a new food until it does not overlap with the snake)
    Food food = Food(game_map.get_width(), game_map.get_height());
    while (snake.OnSnake(food.get_position())) {
        food = Food(game_map.get_width(), game_map.get_height());
    }
    PrintFood(food);

    char new_direction; // take the direction for movement from the user
    while (snake.IsAlive()) {
        if (_kbhit()) {
            new_direction = _getch();
            snake.set_direction(new_direction);
        }
        snake.Move();
        PrintSnake(snake);

        // If snake hits the wall, kill it.
        const Coordinate& cur_head_pos = snake.get_head();
        if (cur_head_pos.cor_x == 0 ||
            cur_head_pos.cor_x == game_map.get_width() - 2 ||
            cur_head_pos.cor_y == 0 ||
            cur_head_pos.cor_y == game_map.get_height() - 1) {
            snake.Killed();
        }

        // If the snake eats the food: 
        if (cur_head_pos == food.get_position()) {
            // Grow the body by 1.
            snake.Grow();

            // Remove the old food and generate a new food.
            RemoveFood(food);
            food = Food(game_map.get_width(), game_map.get_height());
            while (snake.OnSnake(food.get_position())) {
                food = Food(game_map.get_width(), game_map.get_height());
            }
            PrintFood(food);

            // increase the score by 1
            current_score++;

            // check if hardness need to be updated
            // Update the hardness level onece the level_up_threshhold is acheived
            if (current_score == level_up_threshold) {
                current_score = 0;
                hardness_level++;
            }
        }

        // Update the score and level infomation.
        MoveCursor(0, game_map_height);
        std::cout << "Your Score: " << current_score;
        std::cout << "             ";
        std::cout << "Your level: " << hardness_level;

        // stop if the highest level are achieved
        if (hardness_level > highest_level) {
            break;
        }
        
        // Refresh the console frame based on current harness leve
        // We refresh it twice often when the snake is moving horizontally, 
        // to cancel the effect that the console cell is a imperfect square whose width is shorter than the height
        int refresh_rate = base_refresh_rate / (hardness_level + 1);
        Pause(refresh_rate);
        const char& cur_direction = snake.get_direction();
        if (cur_direction == 'U' || cur_direction == 'D') {
            Pause(refresh_rate);
        }
    }

    // Reset the map before exiting 
    // (Bacause feedback info will be later shown on the map)
    ResetGameMap(game_map);

    // Return the palyer's final score and level achieved.
    return std::pair<int, int>{current_score, hardness_level};
}


void PrintFeedback(std::pair<int,int> final_performance, const int heighest_level) {
    if (final_performance.second > heighest_level) {
        MoveCursor(2, 1);
        std::cout << "Professional Player. You crack the game!";
    }
    else {
        MoveCursor(2, 1);
        std::cout << "The snake is died now...";
        MoveCursor(2, 2);
        std::cout << "your final score is: " << final_performance.first;
        MoveCursor(2, 3);
        std::cout << "your final level is: " << final_performance.second;
    }
}