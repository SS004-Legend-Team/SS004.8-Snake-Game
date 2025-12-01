#ifndef GAME_H
#define GAME_H

#include "snake.h"
#include "food.h"
#include "constants.h"
#include "utils.h"
#include <iostream>
#include <vector>
#include <string>

// Lớp Game: Quản lý game loop, hiển thị, input handler, collision detection
class Game {
private:
    Snake snake;
    Food food;
    int score;
    bool gameOver;
    Difficulty difficulty;
    int gameSpeed;  // Tốc độ game (ms)
    bool inputProcessed;  // Cờ đánh dấu đã xử lý input trong frame hiện tại

    void draw();
    void processInput();
    void reset();
    Difficulty selectDifficulty();

public:
    Game();
    ~Game();
    void run();
};

#endif // GAME_H

