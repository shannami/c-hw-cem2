#pragma once
#include <stdio.h>

typedef struct Eghe Eghe;
typedef struct Vertex Vertex;
typedef struct Graph Graph;
/*cоздает граф с заданным количеством вершин n*/
Graph* createGraph(int n);
/*добавляет ребро в граф */
void addEdge(Graph* g, int from, int to, int len);
/*распределение городов между k государствами*/
int* distributionByCountry(Graph* graph, int* capitals, int k);
/*освобождает память занятую графом*/
void freeGraph(Graph* g);
