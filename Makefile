# Makefile cho trò chơi Rắn ăn mồi

# Trình biên dịch
CXX = g++

# Cờ biên dịch
CXXFLAGS = -std=c++11 -Wall -Wextra

# Tên file thực thi
TARGET = snake_game

# File nguồn
SRC = snake_game.cpp

# File object
OBJ = $(SRC:.cpp=.o)

# Mặc định: build game
all: $(TARGET)

# Build game
$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

# Build file object
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Chạy game
run: $(TARGET)
	./$(TARGET)

# Dọn dẹp file build
clean:
	rm -f $(OBJ) $(TARGET)
	rm -f *.exe  # Windows

# Rebuild
rebuild: clean all

# Phụ thuộc
.PHONY: all run clean rebuild

