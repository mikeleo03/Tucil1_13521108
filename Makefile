CC = g++
TARGET = main

all:
	$(CC) -o $(TARGET) src/solver.c

clean:
	rm $(TARGET)