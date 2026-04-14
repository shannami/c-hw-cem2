#include "graph.h"
#include <limits.h>
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

    int sizeV = v->size;

    v->edges = realloc(v->edges, (sizeV + 1) * sizeof(Edge));

    v->edges[sizeV].to = to;
    v->edges[sizeV].len = len;

    v->size++;

    Vertex* u = &g->vertices[to];

    int sizeU = u->size;

    u->edges = realloc(u->edges, (sizeU + 1) * sizeof(Edge));

    u->edges[sizeU].to = from;
    u->edges[sizeU].len = len;

    u->size++;
}

int* distributionByCountry(Graph* graph, int* capitals, int k)
{
    int n = graph->n;
    int* country = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++)
        country[i] = -1;

    for (int i = 0; i < k; i++)
        country[capitals[i]] = i;

    int freeCities = n - k;

    while (freeCities > 0) {
        for (int c = 0; c < k; c++) {
            int city = -1;
            int dist = INT_MAX;

            for (int v = 0; v < n; v++) {
                if (country[v] != c)
                    continue;

                for (int i = 0; i < graph->vertices[v].size; i++) {
                    Edge e = graph->vertices[v].edges[i];
                    if (country[e.to] == -1 && e.len < dist) {
                        dist = e.len;
                        city = e.to;
                    }
                }
            }

            if (city != -1) {
                country[city] = c;
                freeCities--;
            }
        }
    }

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
