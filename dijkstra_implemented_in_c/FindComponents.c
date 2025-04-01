#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *in = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "w");
    if (in == NULL || out == NULL) {
        fprintf(stderr, "Error: Unable to open files.\n");
        exit(EXIT_FAILURE);
    }

    // Read number of vertices
    int n;
    fscanf(in, "%d", &n);
    Graph G = newGraph(n);

    // Read edges
    int u, v;
    while (fscanf(in, "%d %d", &u, &v) == 2 && (u != 0 && v != 0)) {
        addArc(G, u, v);
    }

    // Print adjacency list of G
    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);
    fprintf(out, "\n");

    // Step 1: First DFS to compute finish times
    List S = newList();
    for (int i = 1; i <= n; i++) append(S, i); // Fill S with {1, 2, ..., n}
    DFS(G, S); // First DFS pass

    Graph GT = transpose(G);

    List S_reversed = newList();
    moveBack(S);
    while (index(S) >= 0) {
        append(S_reversed, get(S));  // Reverse order into S_reversed
        movePrev(S);
    }

    // Run DFS on GT using S_reversed (this modifies S_reversed)
    DFS(GT, S_reversed);

    List *SCCs = calloc(getOrder(GT) + 1, sizeof(List)); // Array of Lists for SCCs
    int sccCount = 0;

    //
    moveBack(S_reversed);
    while (index(S_reversed) >= 0) {
        int v = get(S_reversed);

        if (getParent(GT, v) == NIL) { // New SCC root found
            sccCount++;
            SCCs[sccCount] = newList();
        }
        append(SCCs[sccCount], v);

        movePrev(S_reversed);
    }
    //

    fprintf(out, "G contains %d strongly connected components:\n", sccCount);
    for (int i = 1; i <= sccCount; i++) {
        fprintf(out, "Component %d: ", i);
        printList(out, SCCs[i]);
        freeList(&SCCs[i]);
    }

    // Cleanup
    free(SCCs);
    freeList(&S);
    freeGraph(&G);
    freeGraph(&GT);
    fclose(in);
    fclose(out);

    return 0;
}