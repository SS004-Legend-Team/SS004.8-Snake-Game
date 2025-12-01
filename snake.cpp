#include "snake.h"

Snake::Snake() {
    // Khởi tạo rắn ở giữa màn hình
    body.push_back(Point(WIDTH / 2, HEIGHT / 2));
    direction = 'R';  // Bắt đầu di chuyển sang phải
    grow = false;
}

void Snake::move() {
    Point head = body[0];
    Point newHead = head;

    // Tính toán vị trí đầu mới
    switch (direction) {
        case 'U': newHead.y--; break;
        case 'D': newHead.y++; break;
        case 'L': newHead.x--; break;
        case 'R': newHead.x++; break;
    }

    // Thêm đầu mới
    body.insert(body.begin(), newHead);

    // Nếu không phải lúc lớn lên, xóa đuôi
    if (!grow) {
        body.pop_back();
    } else {
        grow = false;
    }
}

void Snake::changeDirection(char newDir) {
    // Ngăn di chuyển ngược lại
    if ((direction == 'U' && newDir == 'D') ||
        (direction == 'D' && newDir == 'U') ||
        (direction == 'L' && newDir == 'R') ||
        (direction == 'R' && newDir == 'L')) {
        return;
    }
    direction = newDir;
}

void Snake::setGrow() {
    grow = true;
}

Point Snake::getHead() const {
    return body[0];
}

std::vector<Point> Snake::getBody() const {
    return body;
}

bool Snake::checkCollision() const {
    Point head = body[0];

    // Kiểm tra va chạm với tường
    if (head.x < 0 || head.x >= WIDTH || head.y < 0 || head.y >= HEIGHT) {
        return true;
    }

    // Kiểm tra va chạm với cơ thể
    for (size_t i = 1; i < body.size(); i++) {
        if (head == body[i]) {
            return true;
        }
    }

    return false;
}

int Snake::getLength() const {
    return body.size();
}

