#ifndef UTILS_H
#define UTILS_H

// Hàm hỗ trợ cross-platform
void clearScreen();
void sleep(int ms);
bool kbhit();
char getch();

#ifdef _WIN32
    // Windows không cần thêm gì
#else
    // Unix/Linux/macOS
    void initTermios();
    void resetTermios();
#endif

#endif // UTILS_H

