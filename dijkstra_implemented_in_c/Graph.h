#pragma once
#include <stdio.h>   // For FILE operations
#include <stdbool.h> // For boolean types like 'true' and 'false'
#include <stdlib.h>
#include "List.h"
#define NIL -1      // Represents an undefined parent in DFS
#define UNDEF -2    // Represents an undefined discovery/finish time
typedef struct GraphObj
{
    // size n+1 for ease of access
    List *adj_list;
    char *colors;
    int *parent_table;
    int *distances; // from source to i
    int* discovery;
    int* finish;

    int num_edges;    // size
    int num_vertices; // order
    int source;       // by BFS
} GraphObj;

typedef struct GraphObj *Graph;
Graph newGraph(int n);
void freeGraph(Graph *pG);

int getParent(Graph G, int u);
int getOrder(Graph G); // num_v
int getSize(Graph G);  // num_e
int getDiscover(Graph G, int v);
int getFinish(Graph G, int v);
void makeNull(Graph G);
void addEdge(Graph G, int u, int v); // u->v and v->u
void addArc(Graph G, int u, int v);  // adds u->v
void visit(Graph G, int v, int *time, List S);
void DFS(Graph G, List S);
void printGraph(FILE *out, Graph G);
Graph transpose(Graph G);