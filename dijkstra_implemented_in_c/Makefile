# Makefile for PA3
CC = gcc
CFLAGS = -std=c17 -Wall -Wextra -Wpedantic -g

# Executables
EXECUTABLES = FindComponents GraphTest

# Object files
OBJFILES = Graph.o List.o

# Compile and link FindComponents
FindComponents: FindComponents.o $(OBJFILES)
	$(CC) $(CFLAGS) -o FindComponents FindComponents.o $(OBJFILES)

# Compile and link GraphTest
GraphTest: GraphTest.o $(OBJFILES)
	$(CC) $(CFLAGS) -o GraphTest GraphTest.o $(OBJFILES)

# Compile individual C files
Graph.o: Graph.c Graph.h List.h
	$(CC) $(CFLAGS) -c Graph.c

List.o: List.c List.h
	$(CC) $(CFLAGS) -c List.c

FindComponents.o: FindComponents.c Graph.h List.h
	$(CC) $(CFLAGS) -c FindComponents.c

GraphTest.o: GraphTest.c Graph.h List.h
	$(CC) $(CFLAGS) -c GraphTest.c

# Clean up compiled files
clean:
	rm -f $(EXECUTABLES) *.o