#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

void testGraphBasics() {
    printf("Testing Graph Basics...\n");

    Graph G = newGraph(5);
    addArc(G, 1, 2);
    addArc(G, 2, 3);
    addArc(G, 3, 4);
    addArc(G, 4, 5);
    addArc(G, 5, 1); // Cycle to check SCC

    printf("Adjacency List of G:\n");
    printGraph(stdout, G);

    printf("Order: %d, Size: %d\n", getOrder(G), getSize(G));

    freeGraph(&G);
    printf("Graph Basics Test Passed!\n\n");
}

void testDFS() {
    printf("Testing DFS...\n");

    Graph G = newGraph(5);
    addArc(G, 1, 2);
    addArc(G, 2, 3);
    addArc(G, 3, 4);
    addArc(G, 4, 5);
    addArc(G, 5, 1);

    List S = newList();
    for (int i = 1; i <= 5; i++) append(S, i);
    
    DFS(G, S);

    printf("Discovery Times:\n");
    for (int i = 1; i <= 5; i++)
        printf("Vertex %d: %d\n", i, getDiscover(G, i));

    printf("Finish Times:\n");
    for (int i = 1; i <= 5; i++)
        printf("Vertex %d: %d\n", i, getFinish(G, i));

    freeList(&S);
    freeGraph(&G);
    printf("DFS Test Passed!\n\n");
}

void testTranspose() {
    printf("Testing Transpose...\n");

    Graph G = newGraph(4);
    addArc(G, 1, 2);
    addArc(G, 2, 3);
    addArc(G, 3, 4);
    addArc(G, 4, 1);

    printf("Original Graph:\n");
    printGraph(stdout, G);

    Graph GT = transpose(G);
    printf("Transposed Graph:\n");
    printGraph(stdout, GT);

    freeGraph(&G);
    freeGraph(&GT);
    printf("Transpose Test Passed!\n\n");
}

void testSCC() {
    printf("Testing SCC Extraction...\n");

    Graph G = newGraph(8);
    addArc(G, 1, 2);
    addArc(G, 2, 3);
    addArc(G, 2, 5);
    addArc(G, 2, 6);
    addArc(G, 3, 4);
    addArc(G, 3, 7);
    addArc(G, 4, 3);
    addArc(G, 4, 8);
    addArc(G, 5, 1);
    addArc(G, 5, 6);
    addArc(G, 6, 7);
    addArc(G, 7, 6);
    addArc(G, 7, 8);
    addArc(G, 8, 8);

    List S = newList();
    for (int i = 1; i <= 8; i++) append(S, i);

    DFS(G, S);

    Graph GT = transpose(G);
    DFS(GT, S);

    printf("SCCs Found:\n");
    List SCC = newList();
    moveFront(S);
    while (index(S) >= 0) {
        int v = get(S);
        if (getParent(GT, v) == NIL) {
            if (length(SCC) > 0) {
                printList(stdout, SCC);
                printf("\n");
                clear(SCC);
            }
        }
        append(SCC, v);
        moveNext(S);
    }
    if (length(SCC) > 0) {
        printList(stdout, SCC);
        printf("\n");
    }

    freeList(&S);
    freeList(&SCC);
    freeGraph(&G);
    freeGraph(&GT);
    printf("SCC Test Passed!\n\n");
}

int main() {
    testGraphBasics();
    testDFS();
    testTranspose();
    testSCC();
    return 0;
}