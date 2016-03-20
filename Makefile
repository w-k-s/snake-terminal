#------------------------------------------------------------------------------

HEADERS=Snake.h SnakeGame.h
SOURCE=Snake.cpp SnakeGame.cpp main.cpp
OUTPUT_DIR=Product/Release
OUTPUT=$(OUTPUT_DIR)/SnakeCLI
INCLUDES=
LIBRARIES=-lcurses
CC=clang++
CCFLAGS=-stdlib=libc++ -std=c++11 -Wunused -Wall

#------------------------------------------------------------------------------

all: format $(OUTPUT)

debug: CCFLAGS += -g 
debug: OUTPUT_DIR=Product/Debug
debug: format $(OUTPUT)

$(OUTPUT): $(HEADERS) $(SOURCE)
	mkdir -p $(OUTPUT_DIR)
	$(CC) $(CCFLAGS) $(INCLUDES) $(SOURCE) -o$(OUTPUT) $(LIBRARIES)

clean:
	rm -f $(OUTPUT)

format: 
	clang-format -i -style=Webkit $(SOURCE)
