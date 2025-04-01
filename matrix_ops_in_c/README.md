CSE 101 - Programming Assignment 4 (PA4)
Sparse Matrix Calculator

Overview
--------
This program implements a sparse matrix calculator that efficiently performs matrix 
operations on large, sparse matrices using an array-of-lists representation. Each 
row of the matrix is represented as a list of (column, value) pairs, ensuring memory 
efficiency for sparse matrices.

The program reads two matrices A and B from an input file, performs various 
operations, and outputs the results to an output file in the required format.

Files Included
--------------
- Sparse.c - The main program that reads matrices from a file, computes operations, and writes the output.
- Matrix.c - Implements the Matrix ADT, including functions for matrix arithmetic.
- Matrix.h - Header file for Matrix.c.
- List.c - Implements the List ADT, a doubly linked list modified to store void* elements.
- List.h - Header file for List.c.
- ListTest.c - A test file for verifying the List ADT.
- MatrixTest.c - A test file for verifying the Matrix ADT.
- Makefile - Automates compilation, linking, and cleanup.

Compilation & Execution
-----------------------
Compile All Files:
    make
This compiles all necessary .c files and produces the executable Sparse.

Run the Sparse Matrix Program:
    ./Sparse <input file> <output file>
Example:
    ./Sparse input.txt output.txt
This reads input.txt, processes matrix operations, and writes results to output.txt.

Run ListTest:
    make ListTest
    ./ListTest
Verifies that the List ADT works correctly.

Run MatrixTest:
    make MatrixTest
    ./MatrixTest
Verifies that the Matrix ADT functions correctly.

Clean Compiled Files:
    make clean
Removes object files and executables.

Matrix Operations Implemented
-----------------------------
The program computes the following matrix operations:
- A and B (prints original matrices)
- Scalar multiplication (1.5 * A)
- Sum (A + B, A + A)
- Difference (B - A, A - A)
- Transpose (Transpose(A))
- Matrix multiplication (A * B, B * B)

Input File Format
-----------------
- The first line contains three integers:
    n a b  -> Matrix size n, nonzero entries in A (a), nonzero entries in B (b).
- The next a lines contain row col value for A.
- A blank line separates A and B.
- The next b lines contain row col value for B.

Example Input File (input.txt)
------------------------------
3 9 5

1 1 1.0
1 2 2.0
1 3 3.0
2 1 4.0
2 2 5.0
2 3 6.0
3 1 7.0
3 2 8.0
3 3 9.0

1 1 1.0
1 3 1.0
3 1 1.0
3 2 1.0
3 3 1.0

Output File Format
------------------
- Each matrix operation is printed in the required format.
- Empty matrices are not printed.

Example Output File (output.txt)
--------------------------------
A has 9 non-zero entries:
1: (1, 1.0) (2, 2.0) (3, 3.0)  
2: (1, 4.0) (2, 5.0) (3, 6.0)  
3: (1, 7.0) (2, 8.0) (3, 9.0)  

B has 5 non-zero entries:
1: (1, 1.0) (3, 1.0)  
3: (1, 1.0) (2, 1.0) (3, 1.0)  

(1.5)*A =
1: (1, 1.5) (2, 3.0) (3, 4.5)  
2: (1, 6.0) (2, 7.5) (3, 9.0)  
3: (1, 10.5) (2, 12.0) (3, 13.5)  

A+B =
1: (1, 2.0) (2, 2.0) (3, 4.0)  
2: (1, 4.0) (2, 5.0) (3, 6.0)  
3: (1, 8.0) (2, 9.0) (3, 10.0)  

A+A =
1: (1, 2.0) (2, 4.0) (3, 6.0)  
2: (1, 8.0) (2, 10.0) (3, 12.0)  
3: (1, 14.0) (2, 16.0) (3, 18.0)  

B-A =
1: (2, -2.0) (3, -2.0)  
2: (1, -4.0) (2, -5.0) (3, -6.0)  
3: (1, -6.0) (2, -7.0) (3, -8.0)  

A-A =

Transpose(A) =
1: (1, 1.0) (2, 4.0) (3, 7.0)  
2: (1, 2.0) (2, 5.0) (3, 8.0)  
3: (1, 3.0) (2, 6.0) (3, 9.0)  

A*B =
1: (1, 4.0) (2, 3.0) (3, 4.0)  
2: (1, 10.0) (2, 6.0) (3, 10.0)  
3: (1, 16.0) (2, 9.0) (3, 16.0)  

B*B =
1: (1, 2.0) (2, 1.0) (3, 2.0)  
3: (1, 2.0) (2, 1.0) (3, 2.0)  

Memory Management
-----------------
- All dynamically allocated memory is properly freed.
- No memory leaks due to proper freeMatrix() and freeList() calls.

Error Handling
--------------
- Checks for incorrect command-line arguments.
- Validates input file readability.
- Handles invalid matrix sizes and entries.

Author
------
CSE 101 Student  
University of California, Santa Cruz  