#ifndef POINT_H
#define POINT_H

// Cấu trúc điểm (x, y) để biểu diễn vị trí
struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

#endif // POINT_H

