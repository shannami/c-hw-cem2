#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Edge {
    int to;
    int len;
} Edge;

typedef struct Vertex {
    Edge* edges;
    int size;
} Vertex;

typedef struct Graph {
    Vertex* vertices;
    int n;
} Graph;

Graph* createGraph(int n)
{
    Graph* g = malloc(sizeof(Graph));
    g->n = n;
    g->vertices = malloc(n * sizeof(Vertex));

    for (int i = 0; i < n; i++) {
        g->vertices[i].edges = NULL;
        g->vertices[i].size = 0;
    }

    return g;
}

void addEdge(Graph* g, int from, int to, int len)
{
    Vertex* v = &g->vertices[from];

    int size = v->size;

    v->edges = realloc(v->edges, (size + 1) * sizeof(Edge));

    v->edges[size].to = to;
    v->edges[size].len = len;

    v->size++;
}

int* distributionByCountry(Graph* graph, int* capitals, int k)
{
    int n = graph->n;
    int* d = malloc(sizeof(int) * n);
    int* country = malloc(sizeof(int) * n);
    int* used = calloc(n, sizeof(int));

    for (int i = 0; i < n; i++) {
        d[i] = 1e9;
        country[i] = -1;
    }

    for (int i = 0; i < k; i++) {
        int c = capitals[i];
        d[c] = 0;
        country[c] = i;
    }

    for (int iter = 0; iter < n; iter++) {
        int v = -1;

        for (int i = 0; i < n; i++) {
            if (!used[i] && (v == -1 || d[i] < d[v])) {
                v = i;
            }
        }

        if (v == -1 || d[v] == 1e9)
            break;

        used[v] = 1;

        for (int i = 0; i < graph->vertices[v].size; i++) {
            Edge e = graph->vertices[v].edges[i];

            if (d[v] + e.len < d[e.to]) {
                d[e.to] = d[v] + e.len;
                country[e.to] = country[v];
            }
        }
    }

    free(d);
    free(used);

    return country;
}

void freeGraph(Graph* g)
{
    for (int i = 0; i < g->n; i++) {
        free(g->vertices[i].edges);
    }
    free(g->vertices);
    free(g);
}
