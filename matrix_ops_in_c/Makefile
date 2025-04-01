# Compiler and flags
CC = gcc
CFLAGS = -std=c17 -Wall -Wextra -pedantic -g

# Executable names
EXECUTABLE = Sparse
LIST_TEST = ListTest
MATRIX_TEST = MatrixTest

# Source files
SRC = Sparse.c Matrix.c List.c
OBJ = $(SRC:.c=.o)

# Test files
LIST_TEST_SRC = ListTest.c List.c
LIST_TEST_OBJ = $(LIST_TEST_SRC:.c=.o)

MATRIX_TEST_SRC = MatrixTest.c Matrix.c List.c
MATRIX_TEST_OBJ = $(MATRIX_TEST_SRC:.c=.o)

# Default rule (builds Sparse)
all: $(EXECUTABLE)

# Rule for compiling Sparse
$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(OBJ)

# Explicit compilation rules
Sparse.o: Sparse.c Matrix.h List.h
	$(CC) $(CFLAGS) -c Sparse.c

Matrix.o: Matrix.c Matrix.h List.h
	$(CC) $(CFLAGS) -c Matrix.c

List.o: List.c List.h
	$(CC) $(CFLAGS) -c List.c

# Rule for compiling ListTest
$(LIST_TEST): $(LIST_TEST_OBJ)
	$(CC) $(CFLAGS) -o $(LIST_TEST) $(LIST_TEST_OBJ)

# Rule for compiling MatrixTest
$(MATRIX_TEST): $(MATRIX_TEST_OBJ)
	$(CC) $(CFLAGS) -o $(MATRIX_TEST) $(MATRIX_TEST_OBJ)

# Compile .c files into .o files (general rule)
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# Clean rule to remove generated files
clean:
	rm -f $(EXECUTABLE) $(LIST_TEST) $(MATRIX_TEST) $(OBJ) $(LIST_TEST_OBJ) $(MATRIX_TEST_OBJ)