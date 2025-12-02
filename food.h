#ifndef FOOD_H
#define FOOD_H

#include "point.h"
#include "constants.h"

// Lớp Food: Quản lý vị trí mồi và tạo mồi mới
class Food {
private:
    Point position;

public:
    Food();
    void generateNewPosition();
    Point getPosition() const;
    bool isEaten(const Point& snakeHead) const;
};

#endif // FOOD_H

