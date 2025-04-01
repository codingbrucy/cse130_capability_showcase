#include "Graph.h"
#include <string.h>

Graph newGraph(int n) {
    Graph G = malloc(sizeof(GraphObj));
    G->num_vertices = n;
    G->num_edges = 0;
    G->source = -1; // No source initially (for BFS)

    G->adj_list = calloc(n + 1, sizeof(List));
    G->colors = calloc(n + 1, sizeof(char)); // Using char* for colors
    G->parent_table = calloc(n + 1, sizeof(int));
    G->distances = calloc(n + 1, sizeof(int));
    G->discovery = calloc(n + 1, sizeof(int));
    G->finish = calloc(n + 1, sizeof(int));

for (int i = 1; i <= n; i++) {
        G->adj_list[i] = newList();
        G->colors[i] = 'W';  // WHITE (unvisited)
        G->parent_table[i] = NIL; // No parent initially
        G->distances[i] = UNDEF;  // Undefined for BFS
        G->discovery[i] = UNDEF;  // Undefined discovery time
        G->finish[i] = UNDEF;     // Undefined finish time
    }
    
    return G;
}

void freeGraph(Graph* pG) {
    if (pG != NULL && *pG != NULL) {
        for (int i = 1; i <= (*pG)->num_vertices; i++) {
            freeList(&((*pG)->adj_list[i]));  // Free each adjacency list
        }
        free((*pG)->adj_list);
        free((*pG)->colors);
        free((*pG)->parent_table);
        free((*pG)->distances);
        free((*pG)->discovery);
        free((*pG)->finish);
        free(*pG);
        *pG = NULL;
    }
}
int getParent(Graph G, int u) {
    if (u < 1 || u > G->num_vertices) {
        fprintf(stderr, "getParent() error: vertex %d out of range\n", u);
        exit(EXIT_FAILURE);
    }
    return G->parent_table[u];
}
int getOrder(Graph G)
{
    return G->num_vertices;
}
int getSize(Graph G)
{
    return G->num_edges;
}
/*** Manipulation procedures ***/

void makeNull(Graph G)
{
    if (G == NULL)
    {
        fprintf(stderr, "Graph Error: calling makeNull() on NULL Graph reference\n");
        return;
    }

    // Delete all edges
    for (int i = 1; i <= G->num_vertices; i++)
    {
        clear(G->adj_list[i]);
    }
    G->num_edges = 0;
}
void addEdge(Graph G, int u, int v)
{
    if (G == NULL)
    {
        fprintf(stderr, "Graph Error: calling addEdge() on NULL Graph reference\n");
        return;
    }
    if (u < 0 || u > G->num_vertices || v < 0 || v > G->num_vertices)
    {
        fprintf(stderr, "Graph Error: calling addEdge() with invalid vertices %d, %d\n", u, v);
        return;
    }

    insertInOrder(G->adj_list[u], v); // Add v to adjacency list of u
    insertInOrder(G->adj_list[v], u);
    G->num_edges += 1;
}
void addArc(Graph G, int u, int v)
{
    if (G == NULL)
    {
        fprintf(stderr, "Graph Error: calling addArc() on NULL Graph reference\n");
        return;
    }
    if (u < 0 || u > G->num_vertices || v < 0 || v > G->num_vertices)
    {
        fprintf(stderr, "Graph Error: calling addArc() with invalid vertices %d, %d\n", u, v);
        return;
    }

    insertInOrder(G->adj_list[u], v); // Add v to adjacency list of u
    G->num_edges += 1;
}
void printGraph(FILE *out, Graph G)
{
    if (G == NULL)
    {
        fprintf(stderr, "Graph Error: calling printGraph() on NULL Graph reference\n");
        return;
    }
    if (out == NULL)
    {
        fprintf(stderr, "File Error: calling printGraph() with NULL FILE pointer\n");
        return;
    }
    for (int i = 1; i <= G->num_vertices; i++)
    {                                   // Assuming 1-based indexing for vertices
        fprintf(out, "%d: ", i);        // Print the vertex label
        printList(out, G->adj_list[i]); // Print the adjacency list for the vertex
        // fprintf(out, "\n");             // Newline after each vertex's list
    }
}

void visit(Graph G, int v, int *time, List S) {
    G->discovery[v] = ++(*time);  // Set discovery time
    G->colors[v] = 'G'; // GRAY (processing)

    for (moveFront(G->adj_list[v]); index(G->adj_list[v]) >= 0; moveNext(G->adj_list[v])) {
        int neighbor = get(G->adj_list[v]);
        if (G->colors[neighbor] == 'W') {  // WHITE means unvisited
            G->parent_table[neighbor] = v;
            visit(G, neighbor, time, S);
        }
    }

    G->colors[v] = 'B'; // BLACK (finished)
    G->finish[v] = ++(*time);  // Set finish time
    append(S, v); // Append so that last finished nodes are at the back
}

void DFS(Graph G, List S) {
    if (length(S) != G->num_vertices) {
        fprintf(stderr, "DFS error: List length must match number of vertices.\n");
        exit(EXIT_FAILURE);
    }

    // Reset all attributes
    for (int i = 1; i <= G->num_vertices; i++) {
        G->colors[i] = 'W';  // WHITE
        G->parent_table[i] = NIL;
        G->discovery[i] = UNDEF;
        G->finish[i] = UNDEF;
    }

    int time = 0;

    // Step 1: Use S to determine DFS order, but modify it directly
    List temp = copyList(S); // Copy since we're modifying S
    clear(S);  // Now safe to clear S before storing finish times

    moveFront(temp);
    while (index(temp) >= 0) { // Process in the given order
        int v = get(temp);
        if (G->colors[v] == 'W') {
            visit(G, v, &time, S);
        }
        moveNext(temp);
    }
    freeList(&temp); // Cleanup copied list
}

Graph transpose(Graph G) {
    Graph GT = newGraph(G->num_vertices); // Create new empty graph with same order

    for (int u = 1; u <= G->num_vertices; u++) {
        for (moveFront(G->adj_list[u]); index(G->adj_list[u]) >= 0; moveNext(G->adj_list[u])) {
            int v = get(G->adj_list[u]);
            addArc(GT, v, u); // Reverse the edge direction
        }
    }
    
    return GT; // Return transposed graph
}
int getDiscover(Graph G, int u) {
    if (u < 1 || u > G->num_vertices) {
        fprintf(stderr, "getDiscover() error: vertex %d out of range\n", u);
        exit(EXIT_FAILURE);
    }
    return G->discovery[u];
}
int getFinish(Graph G, int u) {
    if (u < 1 || u > G->num_vertices) {
        fprintf(stderr, "getFinish() error: vertex %d out of range\n", u);
        exit(EXIT_FAILURE);
    }
    return G->finish[u];
}