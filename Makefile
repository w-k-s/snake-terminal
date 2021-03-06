#------------------------------------------------------------------------------

HEADERS=$(wildcard src/*.h)
SOURCE=$(wildcard src/*.cpp)
OUTPUT_DIR=target/release
OUTPUT=$(OUTPUT_DIR)/SnakeCLI
INCLUDES=-I../cxxtest-4.3 -I../cmdline/
LIBRARIES=-lcurses
CC=clang++
CCFLAGS=-stdlib=libc++ -std=c++11 -Wunused -Wall

#------------------------------------------------------------------------------

all: format $(OUTPUT)

debug: CCFLAGS += -g 
debug: OUTPUT_DIR=target/debug
debug: format $(OUTPUT)

$(OUTPUT): $(HEADERS) $(SOURCE)
	mkdir -p $(OUTPUT_DIR)
	$(CC) $(CCFLAGS) $(INCLUDES) $(SOURCE) -o$(OUTPUT) $(LIBRARIES)

clean:
	rm -rf $(OUTPUT_DIR)

format: 
	clang-format -i -style=Webkit $(SOURCE) $(HEADERS)

run:
	./target/release/SnakeCLI