#include "Matrix.h"
Matrix newMatrix(int n) {
    Matrix M = malloc(sizeof(MatrixObj));
    M->size = n;
    M->NNZ = 0;
    M->rows = calloc(n, sizeof(List)); // Array of Lists

    for (int i = 0; i < n; i++) {
        M->rows[i] = newList(); // Each row is a new List
    }
    return M;
}
void freeMatrix(Matrix* pM) {
    if (pM != NULL && *pM != NULL) {
        for (int i = 0; i < (*pM)->size; i++) {
            List row = (*pM)->rows[i];
            freeList(&row); // Free List
        }
        free((*pM)->rows);
        free(*pM);
        *pM = NULL;
    }
}
int size(Matrix M) {
    return (M != NULL) ? M->size : 0;
}
int NNZ(Matrix M) {
    return (M != NULL) ? M->NNZ : 0;
}
int equals(Matrix A, Matrix B) {
    if (A == NULL || B == NULL || A->size != B->size) return 0;

    for (int i = 0; i < A->size; i++) {
        List rowA = A->rows[i];
        List rowB = B->rows[i];

        if (length(rowA) != length(rowB)) return 0; // Different # of entries

        moveFront(rowA);
        moveFront(rowB);
        while (index(rowA) >= 0 && index(rowB) >= 0) {
            Entry eA = (Entry) get(rowA);
            Entry eB = (Entry) get(rowB);

            if (eA->column != eB->column || eA->value != eB->value) return 0;

            moveNext(rowA);
            moveNext(rowB);
        }
    }
    return 1; // Matrices are equal
}

void makeZero(Matrix M) {
    if (M == NULL) return;

    for (int i = 0; i < M->size; i++) {
        List row = M->rows[i];

        // Free each Entry in the row
        moveFront(row);
        while (index(row) >= 0) {
            Entry e = (Entry)get(row);
            free(e); // Free dynamically allocated Entry
            moveNext(row);
        }
        clear(row); // Reset the list after freeing entries
    }
    M->NNZ = 0;
}

void changeEntry(Matrix M, int i, int j, double x) {
    if (M == NULL || i < 1 || i > M->size || j < 1 || j > M->size) return;

    List row = M->rows[i - 1]; // Get the correct row
    moveFront(row);

    while (index(row) >= 0) {
        Entry e = (Entry)get(row);
        if (e->column == j) {
            if (x == 0) {  // Remove entry
                free(e);
                delete(row);
                M->NNZ--;
            } else {  // Update value
                e->value = x;
            }
            return;
        }
        if (e->column > j) break;  // Insert before this point
        moveNext(row);
    }

    if (x != 0) { // Insert new entry in sorted order
        Entry newE = malloc(sizeof(EntryObj));
        newE->column = j;
        newE->value = x;
        if (index(row) >= 0) {
            insertBefore(row, newE); // Insert before cursor
        } else {
            append(row, newE); // Insert at end
        }
        M->NNZ++;
    }
}

Matrix sum(Matrix A, Matrix B) {
    if (A == NULL || B == NULL || A->size != B->size) return NULL;

    Matrix S = newMatrix(A->size);

    for (int i = 0; i < A->size; i++) {
        List rowA = A->rows[i], rowB = B->rows[i], rowS = S->rows[i];

        moveFront(rowA);
        moveFront(rowB);

        while (index(rowA) >= 0 || index(rowB) >= 0) {
            Entry eA = (index(rowA) >= 0) ? (Entry)get(rowA) : NULL;
            Entry eB = (index(rowB) >= 0) ? (Entry)get(rowB) : NULL;

            int colA = eA ? eA->column : __INT_MAX__;
            int colB = eB ? eB->column : __INT_MAX__;

            double sumVal = 0;
            if (colA == colB) {  // Same column, add values
                sumVal = eA->value + eB->value;
                moveNext(rowA);
                moveNext(rowB);
            } else if (colA < colB) {  // Take A's value
                sumVal = eA->value;
                moveNext(rowA);
            } else {  // Take B's value
                sumVal = eB->value;
                moveNext(rowB);
            }

            if (sumVal != 0) {
                Entry newE = malloc(sizeof(EntryObj));
                newE->column = (colA < colB) ? colA : colB;
                newE->value = sumVal;
                append(rowS, newE);
                S->NNZ++;
            }
        }
    }
    return S;
}
Matrix diff(Matrix A, Matrix B) {
    if (A == NULL || B == NULL || A->size != B->size) return NULL;

    Matrix D = newMatrix(A->size);

    for (int i = 0; i < A->size; i++) {
        List rowA = A->rows[i], rowB = B->rows[i], rowD = D->rows[i];

        moveFront(rowA);
        moveFront(rowB);

        while (index(rowA) >= 0 || index(rowB) >= 0) {
            Entry eA = (index(rowA) >= 0) ? (Entry)get(rowA) : NULL;
            Entry eB = (index(rowB) >= 0) ? (Entry)get(rowB) : NULL;

            int colA = eA ? eA->column : __INT_MAX__;
            int colB = eB ? eB->column : __INT_MAX__;

            double diffVal = 0;
            if (colA == colB) {  // Same column, subtract values
                diffVal = eA->value - eB->value;
                moveNext(rowA);
                moveNext(rowB);
            } else if (colA < colB) {  // Take A's value
                diffVal = eA->value;
                moveNext(rowA);
            } else {  // Take -B's value
                diffVal = -eB->value;
                moveNext(rowB);
            }

            if (diffVal != 0) {
                Entry newE = malloc(sizeof(EntryObj));
                newE->column = (colA < colB) ? colA : colB;
                newE->value = diffVal;
                append(rowD, newE);
                D->NNZ++;
            }
        }
    }
    return D;
}
Matrix transpose(Matrix A) {
    if (A == NULL) return NULL;

    Matrix T = newMatrix(A->size);

    for (int i = 0; i < A->size; i++) {
        List rowA = A->rows[i];

        moveFront(rowA);
        while (index(rowA) >= 0) {
            Entry eA = (Entry)get(rowA);

            Entry newE = malloc(sizeof(EntryObj));
            newE->column = i + 1;
            newE->value = eA->value;

            append(T->rows[eA->column - 1], newE); // Add to new row
            T->NNZ++;

            moveNext(rowA);
        }
    }
    return T;
}
double vectorDot(List P, List Q) {
    double sum = 0;

    moveFront(P);
    moveFront(Q);

    while (index(P) >= 0 && index(Q) >= 0) {
        Entry eP = (Entry)get(P);
        Entry eQ = (Entry)get(Q);

        if (eP->column == eQ->column) {
            sum += eP->value * eQ->value;
            moveNext(P);
            moveNext(Q);
        } else if (eP->column < eQ->column) {
            moveNext(P);
        } else {
            moveNext(Q);
        }
    }
    return sum;
}
Matrix product(Matrix A, Matrix B) {
    if (A == NULL || B == NULL || A->size != B->size) return NULL;

    Matrix C = newMatrix(A->size);
    Matrix B_T = transpose(B); // Transpose B for column access

    for (int i = 0; i < A->size; i++) {
        if (length(A->rows[i]) == 0) continue; // Skip zero rows

        for (int j = 0; j < B_T->size; j++) {
            if (length(B_T->rows[j]) == 0) continue; // Skip zero columns

            double dotProduct = vectorDot(A->rows[i], B_T->rows[j]);

            if (dotProduct != 0) {
                Entry newE = malloc(sizeof(EntryObj));
                newE->column = j + 1;
                newE->value = dotProduct;
                append(C->rows[i], newE);
                C->NNZ++;
            }
        }
    }

    freeMatrix(&B_T); // Cleanup transposed matrix
    return C;
}
Matrix scalarMult(double x, Matrix A) {
    if (A == NULL) return NULL;

    Matrix S = newMatrix(A->size);

    if (x == 0) return S; // Return a zero matrix

    for (int i = 0; i < A->size; i++) {
        List rowA = A->rows[i];
        List rowS = S->rows[i];

        moveFront(rowA);
        while (index(rowA) >= 0) {
            Entry eA = (Entry)get(rowA);

            Entry newE = malloc(sizeof(EntryObj));
            newE->column = eA->column;
            newE->value = eA->value * x;

            append(rowS, newE); // Maintain column order
            S->NNZ++;

            moveNext(rowA);
        }
    }
    return S;
}

void printMatrix(FILE* out, Matrix M) {
    if (M == NULL || out == NULL) {
        fprintf(stderr, "Matrix Error: Calling printMatrix() on NULL Matrix or NULL file stream\n");
        return;
    }

    for (int i = 0; i < M->size; i++) {
        List row = M->rows[i];  // Get the list for row (i+1)
        if (length(row) == 0) continue;  // Skip zero rows

        fprintf(out, "%d: ", i + 1);  // Print row index (1-based)

        moveFront(row);  
        while (index(row) >= 0) {
            Entry E = (Entry)get(row);  // Cast void* to Entry*
            fprintf(out, "(%d, %.1f) ", E->column, E->value);  // Print (col, value)
            moveNext(row);
        }
        fprintf(out, "\n");  // New line for next row
    }
}
