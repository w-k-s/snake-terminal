#------------------------------------------------------------------------------

SOURCE=Snake.cpp main.cpp
OUTPUT=SnakeCLI
INCLUDES=
LIBRARIES=-lcurses
CC=clang++
CCFLAGS=-stdlib=libc++ -std=c++11

#------------------------------------------------------------------------------



all: format $(OUTPUT)

$(OUTPUT): $(SOURCE)

	$(CC) $(CCFLAGS) $(INCLUDES) $(SOURCE) -o$(OUTPUT) $(LIBRARIES)

clean:
	rm -f $(OUTPUT)

format: 
	clang-format -i -style=Webkit $(SOURCE)