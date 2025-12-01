#include "food.h"
#include <cstdlib>
#include <ctime>

Food::Food() {
    generateNewPosition();
}

void Food::generateNewPosition() {
    position.x = rand() % WIDTH;
    position.y = rand() % HEIGHT;
}

Point Food::getPosition() const {
    return position;
}

bool Food::isEaten(const Point& snakeHead) const {
    return position == snakeHead;
}

