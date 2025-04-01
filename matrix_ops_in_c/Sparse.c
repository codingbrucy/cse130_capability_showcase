#include <stdio.h>
#include <stdlib.h>
#include "Matrix.h"

int main(int argc, char* argv[]) {
    // Check for correct number of arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Open input file
    FILE* in = fopen(argv[1], "r");
    if (in == NULL) {
        fprintf(stderr, "Error: Cannot open input file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    // Open output file
    FILE* out = fopen(argv[2], "w");
    if (out == NULL) {
        fprintf(stderr, "Error: Cannot open output file %s\n", argv[2]);
        fclose(in);
        exit(EXIT_FAILURE);
    }

    // Read first line (matrix size, number of non-zero entries in A and B)
    int n, a, b;
    fscanf(in, "%d %d %d", &n, &a, &b);

    // Create matrices A and B
    Matrix A = newMatrix(n);
    Matrix B = newMatrix(n);

    // Read A's nonzero entries
    for (int i = 0; i < a; i++) {
        int row, col;
        double val;
        fscanf(in, "%d %d %lf", &row, &col, &val);
        changeEntry(A, row, col, val);
    }

    // Skip blank line
    fgetc(in);

    // Read B's nonzero entries
    for (int i = 0; i < b; i++) {
        int row, col;
        double val;
        fscanf(in, "%d %d %lf", &row, &col, &val);
        changeEntry(B, row, col, val);
    }

    // Print matrices to output file
    fprintf(out, "A has %d non-zero entries:\n", NNZ(A));
    printMatrix(out, A);
    fprintf(out, "\n");

    fprintf(out, "B has %d non-zero entries:\n", NNZ(B));
    printMatrix(out, B);
    fprintf(out, "\n");

    // Perform matrix operations
    Matrix C;

    // (1.5) * A
    C = scalarMult(1.5, A);
    fprintf(out, "(1.5)*A =\n");
    printMatrix(out, C);
    fprintf(out, "\n");
    freeMatrix(&C);

    // A + B
    C = sum(A, B);
    fprintf(out, "A+B =\n");
    printMatrix(out, C);
    fprintf(out, "\n");
    freeMatrix(&C);

    // A + A
    C = sum(A, A);
    fprintf(out, "A+A =\n");
    printMatrix(out, C);
    fprintf(out, "\n");
    freeMatrix(&C);

    // B - A
    C = diff(B, A);
    fprintf(out, "B-A =\n");
    printMatrix(out, C);
    fprintf(out, "\n");
    freeMatrix(&C);

    // A - A (should be empty)
    C = diff(A, A);
    fprintf(out, "A-A =\n");
    printMatrix(out, C);
    fprintf(out, "\n");
    freeMatrix(&C);

    // Transpose of A
    C = transpose(A);
    fprintf(out, "Transpose(A) =\n");
    printMatrix(out, C);
    fprintf(out, "\n");
    freeMatrix(&C);

    // A * B
    C = product(A, B);
    fprintf(out, "A*B =\n");
    printMatrix(out, C);
    fprintf(out, "\n");
    freeMatrix(&C);

    // B * B
    C = product(B, B);
    fprintf(out, "B*B =\n");
    printMatrix(out, C);
    fprintf(out, "\n");
    freeMatrix(&C);

    // Cleanup
    freeMatrix(&A);
    freeMatrix(&B);
    fclose(in);
    fclose(out);

    return 0;
}