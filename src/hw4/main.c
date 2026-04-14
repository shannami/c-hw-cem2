#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    FILE* inf = stdin;

    if (argc > 1) {
        inf = fopen(argv[1], "r");
        if (!inf) {
            fprintf(stderr, "файл не открывается");
            return 1;
        }
    }

    int n = 0, m = 0;
    fscanf(inf, "%d %d", &n, &m);

    Graph* graph = createGraph(n);

    for (int i = 0; i < m; i++) {
        int a = 0, b = 0, len = 0;
        fscanf(inf, "%d %d %d", &a, &b, &len);
        a--;
        b--;
        addEdge(graph, a, b, len);
    }

    int k = 0;

    fscanf(inf, "%d", &k);

    int* capitals = malloc(k * sizeof(int));
    for (int i = 0; i < k; i++) {
        fscanf(inf, "%d", &capitals[i]);
        capitals[i]--;
    }

    int* country = distributionByCountry(graph, capitals, k);

    for (int c = 0; c < k; c++) {
        printf("государство %d: ", c + 1);

        for (int i = 0; i < n; i++) {
            if (country[i] == c) {
                printf("%d ", i + 1);
            }
        }
        printf("\n");
    }

    if (inf != stdin)
        fclose(inf);

    free(country);
    free(capitals);
    freeGraph(graph);

    return 0;
}
