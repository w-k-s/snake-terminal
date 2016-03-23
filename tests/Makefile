TEST_SRC=PointTestSuite.h
CXXTEST=-I../../cxxtest-4.3 -I../src
OUTPUT_SRC=runner.cpp
OUTPUT_EXEC=runner
CC=clang++
CCFLAGS=-stdlib=libc++ -std=c++11 -Wunused -Wall

all:
	rm -f $(OUTPUT_SRC)
	rm -f $(OUTPUT_EXEC)
	cxxtestgen --error-printer -o $(OUTPUT_SRC) $(TEST_SRC)
	test -s $(OUTPUT_SRC) || { echo "$(OUTPUT_SRC) could not be generated"; exit 1; }
	$(CC) $(CCFLAGS) -o $(OUTPUT_EXEC) $(CXXTEST) $(OUTPUT_SRC)
	test -s $(OUTPUT_EXEC) || { echo "$(OUTPUT_EXEC) executable could not be produced"; exit 1; }
	./$(OUTPUT_EXEC)

