#ifndef SNAKE_H
#define SNAKE_H

#include "point.h"
#include "constants.h"
#include <vector>

// Lớp Snake: Quản lý vị trí, di chuyển và tăng trưởng của rắn
class Snake {
private:
    std::vector<Point> body;
    char direction;  // 'U', 'D', 'L', 'R'
    bool grow;

public:
    Snake();
    void move();
    void changeDirection(char newDir);
    void setGrow();
    Point getHead() const;
    std::vector<Point> getBody() const;
    bool checkCollision() const;
    int getLength() const;
};

#endif // SNAKE_H

