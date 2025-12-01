#include "utils.h"
#include <cstdlib>

#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
#else
    #include <termios.h>
    #include <unistd.h>
    #include <fcntl.h>
#endif

// Hàm hỗ trợ cross-platform
#ifdef _WIN32
    void clearScreen() { system("cls"); }
    void sleep(int ms) { Sleep(ms); }
    bool kbhit() { return _kbhit() != 0; }
    char getch() { return _getch(); }
#else
    void clearScreen() { system("clear"); }
    void sleep(int ms) { usleep(ms * 1000); }
    
    static struct termios old_termios, new_termios;
    static bool initialized = false;
    static char input_buffer = 0;
    static bool has_input = false;
    
    void initTermios() {
        // Lưu trạng thái terminal hiện tại nếu chưa được khởi tạo
        if (!initialized) {
            tcgetattr(STDIN_FILENO, &old_termios);
            initialized = true;
        }
        
        // Thiết lập chế độ raw mode cho terminal
        new_termios = old_termios;
        new_termios.c_lflag &= ~(ICANON | ECHO | ISIG);  // Tắt canonical mode, echo và signal
        new_termios.c_iflag &= ~(IXON | ICRNL);  // Tắt flow control và CR to NL
        new_termios.c_cc[VMIN] = 0;   // Không đợi ký tự
        new_termios.c_cc[VTIME] = 0;  // Không timeout
        
        // Áp dụng cài đặt mới
        tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
        
        // Thiết lập non-blocking mode
        fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
    }
    
    void resetTermios() {
        if (initialized) {
            // Khôi phục trạng thái terminal ban đầu
            tcsetattr(STDIN_FILENO, TCSAFLUSH, &old_termios);
            fcntl(STDIN_FILENO, F_SETFL, 0);  // Tắt non-blocking mode
        }
    }
    
    bool kbhit() {
        initTermios();
        if (has_input) {
            return true;
        }
        char ch;
        int nread = read(STDIN_FILENO, &ch, 1);
        if (nread > 0) {
            input_buffer = ch;
            has_input = true;
            return true;
        }
        return false;
    }
    
    char getch() {
        initTermios();
        // Nếu đã có input từ trước, trả về và xóa buffer
        if (has_input) {
            has_input = false;
            return input_buffer;
        }
        
        // Đọc input (non-blocking)
        char ch = 0;
        int nread = read(STDIN_FILENO, &ch, 1);
        
        // Nếu không có input, trả về giá trị không ảnh hưởng đến game
        if (nread <= 0) {
            return -1;  // Trả về giá trị không phải là phím điều khiển
        }
        
        return ch;
    }
#endif

