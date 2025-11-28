# Trò chơi Rắn ăn mồi (Snake Game)

## Mô tả

Đây là một trò chơi cổ điển "Rắn ăn mồi" được phát triển bằng ngôn ngữ C++. Người chơi điều khiển một con rắn di chuyển trên màn hình để ăn các mồi và tăng độ dài. Trò chơi kết thúc khi rắn va chạm vào tường hoặc vào chính cơ thể của nó.

## Tính năng

- ✅ Điều khiển rắn bằng các phím chữ hoặc mũi tên (W A S D | ↑ ↓ ← →)
- ✅ Rắn tăng độ dài khi ăn mồi
- ✅ Điểm số tăng dần theo số mồi đã ăn
- ✅ Phát hiện va chạm với tường và cơ thể
- ✅ Mồi xuất hiện ngẫu nhiên trên màn hình
- ✅ **Chọn độ khó** khi bắt đầu game (Dễ, Trung bình, Khó)
- ✅ **Chơi lại** sau khi game over (nhấn 'r')
- ✅ Giao diện console đơn giản và dễ sử dụng

## Yêu cầu hệ thống

- **Hệ điều hành**: Windows, Linux, hoặc macOS
- **Trình biên dịch**: GCC (MinGW trên Windows) hoặc Clang
- **C++ Standard**: C++11 trở lên
- **Thư viện**: Có thể sử dụng thư viện chuẩn hoặc các thư viện như:
  - `<iostream>` - Nhập/xuất
  - `<conio.h>` (Windows) hoặc `<termios.h>` (Linux/macOS) - Điều khiển bàn phím
  - `<cstdlib>` - Hàm ngẫu nhiên và điều khiển màn hình
  - `<ctime>` - Tạo số ngẫu nhiên

## Cài đặt và Biên dịch

### Sử dụng Makefile (Khuyến nghị)

```bash
# Biên dịch
make

# Chạy game
make run

# Dọn dẹp file build
make clean
```

### Biên dịch thủ công

#### Trên Windows (sử dụng MinGW)

```bash
g++ -o snake_game.exe snake_game.cpp -std=c++11
```

#### Trên Linux/macOS

```bash
g++ -o snake_game snake_game.cpp -std=c++11
# hoặc
clang++ -o snake_game snake_game.cpp -std=c++11
```

## Cách chơi

1. Biên dịch và chạy chương trình:
   ```bash
   make
   ./snake_game  # hoặc snake_game.exe trên Windows
   ```

2. **Chọn độ khó** khi bắt đầu:
   - **1 - Dễ**: Tốc độ 250ms (chậm, phù hợp cho người mới)
   - **2 - Trung bình**: Tốc độ 150ms (vừa phải)
   - **3 - Khó**: Tốc độ 80ms (nhanh, thử thách)

3. Sử dụng các phím để điều khiển hướng di chuyển của rắn:
   - **WASD**: W (lên), S (xuống), A (trái), D (phải)
   - **Phím mũi tên**: ↑ ↓ ← → (hỗ trợ trên cả Windows và Unix)
   - **Q hoặc ESC**: Thoát game (khi đang chơi)

4. Ăn mồi (ký tự `*`) để tăng điểm và độ dài rắn
5. Tránh va chạm vào tường (ký tự `#`) hoặc vào chính cơ thể của rắn
6. Sau khi game over:
   - **R**: Chơi lại với cùng độ khó
   - **Q hoặc ESC**: Thoát game
7. Mục tiêu: Đạt điểm số cao nhất có thể!

## Cấu trúc dự án

```
SS004.8-Snake-Game/
├── README.md           # Tài liệu hướng dẫn
├── snake_game.cpp      # File mã nguồn chính
├── Makefile            # (Tùy chọn) File build tự động
└── .gitignore          # (Tùy chọn) File loại trừ Git
```

## Cấu trúc mã nguồn

Code được tổ chức thành các lớp và thành phần chính:

- **Point struct**: Cấu trúc điểm (x, y) để biểu diễn vị trí
- **Snake Class**: Quản lý vị trí, di chuyển và tăng trưởng của rắn
- **Food Class**: Quản lý vị trí mồi và tạo mồi mới
- **Game Class**: 
  - Game Loop: Vòng lặp chính của trò chơi
  - Game Board: Quản lý màn hình và hiển thị
  - Input Handler: Xử lý đầu vào từ bàn phím (hỗ trợ cross-platform)
  - Collision Detection: Phát hiện va chạm với tường và cơ thể
  - Difficulty Selection: Menu chọn độ khó khi bắt đầu
  - Game Speed Control: Điều chỉnh tốc độ game dựa trên độ khó
- **Cross-platform support**: Hỗ trợ cả Windows và Unix (Linux/macOS)

## Độ khó

Game hỗ trợ 3 mức độ khó khác nhau:

| Độ khó | Tốc độ | Mô tả |
|--------|--------|-------|
| **Dễ** | 250ms | Tốc độ chậm, phù hợp cho người mới bắt đầu |
| **Trung bình** | 150ms | Tốc độ vừa phải, cân bằng giữa thử thách và dễ chơi |
| **Khó** | 80ms | Tốc độ nhanh, đòi hỏi phản xạ và kỹ năng cao |

Bạn có thể chọn độ khó khi bắt đầu game và chơi lại với cùng độ khó đã chọn.

## Các tính năng có thể mở rộng

- [x] Thêm mức độ khó (Easy, Medium, Hard) ✅
- [ ] Thêm tường chướng ngại vật
- [ ] Lưu điểm cao nhất (High Score)
- [ ] Thêm âm thanh và hiệu ứng
- [ ] Giao diện đồ họa với thư viện như SDL2 hoặc SFML
- [ ] Chế độ chơi hai người
- [ ] Thêm các loại mồi đặc biệt với điểm số khác nhau
- [ ] Thay đổi độ khó trong khi chơi

## Tác giả

Dự án được phát triển như một bài tập thực hành lập trình C++.

## Giấy phép

Dự án này được tạo cho mục đích giáo dục và học tập.

## Ký hiệu trong game

- `O`: Đầu rắn
- `o`: Thân rắn
- `*`: Mồi
- `#`: Tường/khung
- ` `: Khoảng trống

## Lưu ý kỹ thuật

- Code hỗ trợ cross-platform (Windows, Linux, macOS)
- Sử dụng C++11 standard
- Không cần thư viện bên ngoài, chỉ sử dụng thư viện chuẩn
- Trên Unix systems, code tự động xử lý terminal mode để đọc phím không cần Enter

---

**Trạng thái**: Dự án đã có đầy đủ mã nguồn và có thể biên dịch, chạy ngay!

