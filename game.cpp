#include "game.h"
#include <cstdlib>
#include <ctime>

#ifndef _WIN32
    #include <unistd.h>
#endif

using namespace std;

Game::Game() : score(0), gameOver(false), difficulty(EASY), gameSpeed(250), inputProcessed(false) {
    srand(time(0));
    #ifndef _WIN32
        initTermios();
    #endif
}

Game::~Game() {
    #ifndef _WIN32
        resetTermios();
    #endif
}

void Game::draw() {
    clearScreen();

    // Vẽ khung trên
    for (int i = 0; i < WIDTH + 2; i++) {
        cout << "#";
    }
    cout << endl;

    // Vẽ game board
    for (int y = 0; y < HEIGHT; y++) {
        cout << "#";  // Tường trái
        for (int x = 0; x < WIDTH; x++) {
            Point current(x, y);
            bool isSnakeBody = false;
            bool isSnakeHead = false;
            bool isFood = false;

            // Kiểm tra vị trí
            if (current == food.getPosition()) {
                isFood = true;
            } else if (current == snake.getHead()) {
                isSnakeHead = true;
            } else {
                vector<Point> body = snake.getBody();
                for (const Point& p : body) {
                    if (current == p) {
                        isSnakeBody = true;
                        break;
                    }
                }
            }

            // Vẽ ký tự tương ứng
            if (isSnakeHead) {
                cout << "O";
            } else if (isSnakeBody) {
                cout << "o";
            } else if (isFood) {
                cout << "*";
            } else {
                cout << " ";
            }
        }
        cout << "#" << endl;  // Tường phải
    }

    // Vẽ khung dưới
    for (int i = 0; i < WIDTH + 2; i++) {
        cout << "#";
    }
    cout << endl;

    // Hiển thị điểm số
    cout << "Diem so: " << score << endl;
    cout << "Do dai ran: " << snake.getLength() << endl;
    string diffName = "";
    switch (difficulty) {
        case EASY: diffName = "De"; break;
        case MEDIUM: diffName = "Trung binh"; break;
        case HARD: diffName = "Kho"; break;
    }
    cout << "Do kho: " << diffName << endl;
    if (gameOver) {
        cout << "GAME OVER!" << endl;
        cout << "Nhan 'r' de choi lai, 'q' de thoat" << endl;
    } else {
        cout << "Su dung phim WASD hoac mui ten de dieu khien (q de thoat)" << endl;
    }
}

void Game::processInput() {
    // Nếu đã xử lý input trong frame này, không xử lý thêm
    if (inputProcessed || !kbhit()) {
        return;
    }
    
    char input = getch();
    
    // Nếu không có input hợp lệ, thoát
    if (input == -1) {
        return;
    }
    
    inputProcessed = true;  // Đánh dấu đã xử lý input
    
    #ifdef _WIN32
        // Windows: Xử lý phím mũi tên
        if (input == -32 || input == 224) {  // Arrow key prefix
            if (kbhit()) {
                input = getch();
                switch (input) {
                    case 72: snake.changeDirection('U'); break;  // Up
                    case 80: snake.changeDirection('D'); break;  // Down
                    case 75: snake.changeDirection('L'); break;  // Left
                    case 77: snake.changeDirection('R'); break;  // Right
                }
            }
            return;
        }
    #else
        // Linux/macOS: Xử lý phím mũi tên (ANSI escape sequences: ESC [ A/B/C/D)
        if (input == 27) {  // ESC
            // Đọc các ký tự tiếp theo nếu có
            vector<char> sequence;
            sequence.push_back(input);
            
            // Đọc tối đa 3 ký tự với timeout lớn hơn để đảm bảo đọc được đầy đủ
            for (int i = 0; i < 3; i++) {
                usleep(15000);  // 15ms delay - tăng thời gian chờ
                if (kbhit()) {
                    char nextChar = getch();
                    if (nextChar != -1) {  // Chỉ thêm vào nếu là ký tự hợp lệ
                        sequence.push_back(nextChar);
                    }
                } else {
                    break;
                }
            }
            
            // Xử lý chuỗi ESC [ A/B/C/D
            if (sequence.size() >= 3 && sequence[1] == '[') {
                switch (sequence[2]) {
                    case 'A': snake.changeDirection('U'); break;  // Up
                    case 'B': snake.changeDirection('D'); break;  // Down
                    case 'C': snake.changeDirection('R'); break;  // Right
                    case 'D': snake.changeDirection('L'); break;  // Left
                    default: break;  // Không làm gì nếu không phải phím mũi tên
                }
                return;  // Đã xử lý phím mũi tên, thoát
            }
            
            // Nếu chỉ nhận được ESC mà không phải là chuỗi phím mũi tên
            // Chỉ thoát game nếu chắc chắn là phím ESC đơn thuần
            if (sequence.size() == 1) {
                gameOver = true;
            }
            return;
        }
    #endif
    
    // Xử lý phím WASD (cross-platform)
    switch (input) {
        case 'w':
        case 'W': snake.changeDirection('U'); break;
        case 's':
        case 'S': snake.changeDirection('D'); break;
        case 'a':
        case 'A': snake.changeDirection('L'); break;
        case 'd':
        case 'D': snake.changeDirection('R'); break;
        case 'q':
        case 'Q': 
            gameOver = true;
            break;
        case 'r':
        case 'R':
            // Chỉ reset khi game over
            if (gameOver) {
                reset();
            }
            break;
    }
}

void Game::reset() {
    snake = Snake();
    food = Food();
    score = 0;
    gameOver = false;
    inputProcessed = false;
    
    // Đảm bảo terminal mode được thiết lập đúng
    #ifndef _WIN32
        initTermios();
    #endif
}

Difficulty Game::selectDifficulty() {
    clearScreen();
    cout << "========================================" << endl;
    cout << "     TRO CHOI RAN AN MOI" << endl;
    cout << "========================================" << endl;
    cout << endl;
    cout << "Chon do kho:" << endl;
    cout << "  1. De (250ms - Cham)" << endl;
    cout << "  2. Trung binh (150ms - Vua)" << endl;
    cout << "  3. Kho (80ms - Nhanh)" << endl;
    cout << endl;
    cout << "Nhan phim 1, 2 hoac 3 de chon: ";
    
    #ifndef _WIN32
        initTermios();
    #endif
    
    char choice = 0;
    while (choice < '1' || choice > '3') {
        if (kbhit()) {
            choice = getch();
        } else {
            sleep(50);
        }
    }
    
    #ifndef _WIN32
        resetTermios();
    #endif
    
    Difficulty selected = static_cast<Difficulty>(choice - '0');
    
    // Thiết lập tốc độ game dựa trên độ khó
    switch (selected) {
        case EASY:
            gameSpeed = 250;
            break;
        case MEDIUM:
            gameSpeed = 150;
            break;
        case HARD:
            gameSpeed = 80;
            break;
    }
    
    return selected;
}

void Game::run() {
    try {
        // Đảm bảo terminal mode được thiết lập đúng
        #ifndef _WIN32
            initTermios();
        #endif
        
        // Chọn độ khó khi bắt đầu
        difficulty = selectDifficulty();
        
        bool keepPlaying = true;
        
        while (keepPlaying) {
            // Reset game nếu cần
            if (gameOver) {
                reset();
            }
            
            // Vòng lặp game chính
            while (!gameOver) {
                draw();
    
                // Xử lý input (non-blocking)
                processInput();
    
                // Di chuyển rắn
                snake.move();
    
                // Kiểm tra va chạm
                if (snake.checkCollision()) {
                    gameOver = true;
                    draw();
                    break;
                }
    
                // Kiểm tra ăn mồi
                if (food.isEaten(snake.getHead())) {
                    snake.setGrow();
                    score += 10;
                    food.generateNewPosition();
    
                    // Đảm bảo mồi không xuất hiện trên thân rắn
                    vector<Point> body = snake.getBody();
                    bool onSnake = true;
                    while (onSnake) {
                        onSnake = false;
                        for (const Point& p : body) {
                            if (food.getPosition() == p) {
                                food.generateNewPosition();
                                onSnake = true;
                                break;
                            }
                        }
                    }
                }
    
                // Tốc độ game (dựa trên độ khó)
                sleep(gameSpeed);
                
                // Reset biến inputProcessed cho frame tiếp theo
                inputProcessed = false;
            }
    
            // Xử lý sau khi game over
            if (gameOver) {
                bool waitingForInput = true;
                while (waitingForInput) {
                    draw();  // Vẽ lại màn hình để hiển thị thông báo
                    
                    // Đợi đến khi có phím được nhấn
                    while (!kbhit()) {
                        sleep(50);
                    }
                    
                    char input = getch();
                    
                    // Bỏ qua các ký tự không hợp lệ
                    if (input == -1) {
                        continue;
                    }
                    
                    if (input == 'q' || input == 'Q' || input == 27) {
                        keepPlaying = false;
                        waitingForInput = false;
                    } else if (input == 'r' || input == 'R') {
                        // Reset và chơi lại
                        waitingForInput = false;
                        // gameOver sẽ được reset ở đầu vòng lặp
                    }
                }
            }
        }
    }
    catch (...) {
        // Đảm bảo terminal mode được khôi phục nếu có lỗi
        #ifndef _WIN32
            resetTermios();
        #endif
        throw;  // Ném lại ngoại lệ
    }
    
    // Đảm bảo terminal mode được khôi phục khi kết thúc
    #ifndef _WIN32
        resetTermios();
    #endif
}

