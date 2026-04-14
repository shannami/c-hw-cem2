#include "graph.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool testOneCapital(void)
{
    Graph* graph = createGraph(3);

    addEdge(graph, 0, 1, 3);
    addEdge(graph, 1, 2, 2);

    int capitals[] = { 0 };

    int* country = distributionByCountry(graph, capitals, 1);

    bool result = (country[0] == 0 && country[1] == 0 && country[2] == 0);

    free(country);
    freeGraph(graph);

    return result;
}

bool testTwoCapitals(void)
{
    Graph* graph = createGraph(4);

    addEdge(graph, 1, 0, 1);
    addEdge(graph, 1, 2, 1);
    addEdge(graph, 3, 2, 1);

    int capitals[] = { 0, 3 };

    int* country = distributionByCountry(graph, capitals, 2);

    bool result = (country[0] == 0 && country[1] == 0 && country[2] == 1 && country[3] == 1);

    free(country);
    freeGraph(graph);

    return result;
}

bool testWeighted(void)
{
    Graph* graph = createGraph(4);

    addEdge(graph, 0, 1, 1);
    addEdge(graph, 1, 2, 10);
    addEdge(graph, 0, 2, 5);
    addEdge(graph, 2, 3, 1);

    int capitals[] = { 0, 3 };

    int* country = distributionByCountry(graph, capitals, 2);

    bool result = (country[0] == 0 && country[1] == 0 && country[2] == 1 && country[3] == 1);

    free(country);
    freeGraph(graph);

    return result;
}

bool testSingleCity(void)
{
    Graph* graph = createGraph(1);

    int capitals[] = { 0 };

    int* country = distributionByCountry(graph, capitals, 1);

    bool result = (country[0] == 0);

    free(country);
    freeGraph(graph);

    return result;
}

int main(int argc, char* argv[])
{
    if (argc > 1 && strcmp(argv[1], "--test") == 0) {

        if (!testOneCapital() || !testTwoCapitals() || !testWeighted() || !testSingleCity()) {

            printf("Tests failed\n");
            return 1;
        }

        printf("All tests passed\n");
        return 0;
    }

    return 0;
}