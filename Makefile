CC=g++
SRC_DIR=src
SRC_FILES=$(SRC_DIR)/*.cpp
INCL_FILES=$(SRC_DIR)/*.hpp
LIBS=-lraylib
TARGET=main
CFLAGS=-Wall -Werror -Wextra -Wpedantic
STYLE=GNU

all: clean format $(TARGET) test

no-test: clean $(TARGET)

$(TARGET): 
	$(CC) $(SRC_FILES) -o $(TARGET) $(LIBS) $(CFLAGS) #-I./$(SRC_DIR)

test: $(TARGET)
	valgrind --leak-check=yes ./$(TARGET)

clean:
	-@rm $(TARGET) 2>/dev/null || true

format: 
	clang-format -style=$(STYLE) -i $(SRC_FILES) #$(INCL_FILES)
