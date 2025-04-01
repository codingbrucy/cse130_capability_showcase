#include <stdio.h>
#include <stdlib.h>
#include "List.h"

// Define Entry struct for testing
typedef struct EntryObj {
    int column;
    double value;
} EntryObj;

typedef EntryObj* Entry;

// Function to create a new Entry
Entry newEntry(int col, double val) {
    Entry E = malloc(sizeof(EntryObj));
    E->column = col;
    E->value = val;
    return E;
}

// Function to print an Entry
void printEntry(Entry E) {
    if (E != NULL) {
        printf("(%d, %.1f) ", E->column, E->value);
    }
}

// Test function for List ADT
int main() {
    printf("=== Testing List ADT ===\n");

    List L = newList();

    // Append & Prepend Test
    printf("\nAppending entries...\n");
    append(L, newEntry(1, 1.1));
    append(L, newEntry(2, 2.2));
    append(L, newEntry(3, 3.3));
    
    printf("Prepending entries...\n");
    prepend(L, newEntry(0, 0.0));

    // Print List
    printf("List after append/prepend: ");
    moveFront(L);
    while (index(L) >= 0) {
        printEntry((Entry)get(L));
        moveNext(L);
    }
    printf("\n");

    // Cursor Movement Test
    printf("\nMoving cursor...\n");
    moveFront(L);
    printf("Cursor at front: ");
    printEntry((Entry)get(L));
    printf("\n");

    moveBack(L);
    printf("Cursor at back: ");
    printEntry((Entry)get(L));
    printf("\n");

    movePrev(L);
    printf("Cursor moved prev: ");
    printEntry((Entry)get(L));
    printf("\n");

    moveNext(L);
    printf("Cursor moved next: ");
    printEntry((Entry)get(L));
    printf("\n");

    // Insert Before & After Test
    printf("\nInserting before & after cursor...\n");
    moveFront(L);
    moveNext(L);
    insertBefore(L, newEntry(5, 5.5));
    insertAfter(L, newEntry(6, 6.6));

    // Print updated List
    printf("List after insertions: ");
    moveFront(L);
    while (index(L) >= 0) {
        printEntry((Entry)get(L));
        moveNext(L);
    }
    printf("\n");

    // Deletion Test
    printf("\nDeleting front, back, and cursor...\n");
    deleteFront(L);
    deleteBack(L);

    moveFront(L);
    moveNext(L);
    delete(L);

    // Print final List
    printf("List after deletions: ");
    moveFront(L);
    while (index(L) >= 0) {
        printEntry((Entry)get(L));
        moveNext(L);
    }
    printf("\n");

    // Freeing Memory
    printf("\nFreeing list...\n");
    freeList(&L);

    printf("=== List ADT Test Completed Successfully ===\n");
    return 0;
}