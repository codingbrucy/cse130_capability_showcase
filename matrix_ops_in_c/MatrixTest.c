#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

// Function to print a matrix to stdout
void printMatrixToStdout(Matrix M) {
    printMatrix(stdout, M);
}

// Main testing function
int main() {
    printf("=== Testing Matrix ADT ===\n\n");

    // Create matrices
    printf("Creating matrices A and B (size 3x3)...\n");
    Matrix A = newMatrix(3);
    Matrix B = newMatrix(3);

    // Insert elements into A
    printf("Modifying A...\n");
    changeEntry(A, 1, 1, 1.0);
    changeEntry(A, 1, 2, 2.0);
    changeEntry(A, 1, 3, 3.0);
    changeEntry(A, 2, 1, 4.0);
    changeEntry(A, 2, 2, 5.0);
    changeEntry(A, 2, 3, 6.0);
    changeEntry(A, 3, 1, 7.0);
    changeEntry(A, 3, 2, 8.0);
    changeEntry(A, 3, 3, 9.0);

    printf("Matrix A:\n");
    printMatrixToStdout(A);

    // Insert elements into B
    printf("\nModifying B...\n");
    changeEntry(B, 1, 1, 1.0);
    changeEntry(B, 1, 3, 1.0);
    changeEntry(B, 3, 1, 1.0);
    changeEntry(B, 3, 2, 1.0);
    changeEntry(B, 3, 3, 1.0);

    printf("Matrix B:\n");
    printMatrixToStdout(B);

    // Scalar multiplication
    printf("\nPerforming scalar multiplication (1.5 * A)...\n");
    Matrix C = scalarMult(1.5, A);
    printMatrixToStdout(C);
    freeMatrix(&C);

    // Sum of A + B
    printf("\nComputing A + B...\n");
    Matrix S = sum(A, B);
    printMatrixToStdout(S);
    freeMatrix(&S);

    // Sum of A + A
    printf("\nComputing A + A...\n");
    Matrix AA = sum(A, A);
    printMatrixToStdout(AA);
    freeMatrix(&AA);

    // Difference B - A
    printf("\nComputing B - A...\n");
    Matrix D = diff(B, A);
    printMatrixToStdout(D);
    freeMatrix(&D);

    // Difference A - A (should be empty)
    printf("\nComputing A - A (should be empty)...\n");
    Matrix Z = diff(A, A);
    printMatrixToStdout(Z);
    freeMatrix(&Z);

    // Transpose of A
    printf("\nComputing Transpose(A)...\n");
    Matrix T = transpose(A);
    printMatrixToStdout(T);
    freeMatrix(&T);

    // Product A * B
    printf("\nComputing A * B...\n");
    Matrix P = product(A, B);
    printMatrixToStdout(P);
    freeMatrix(&P);

    // Product B * B
    printf("\nComputing B * B...\n");
    Matrix BB = product(B, B);
    printMatrixToStdout(BB);
    freeMatrix(&BB);

    // Make A zero and test NNZ
    printf("\nResetting A to zero...\n");
    makeZero(A);
    printMatrixToStdout(A);
    printf("A's NNZ after makeZero: %d\n", NNZ(A));

    // Free all matrices
    printf("\nFreeing all matrices...\n");
    freeMatrix(&A);
    freeMatrix(&B);

    printf("\n=== Matrix ADT Test Completed Successfully ===\n");
    return 0;
}