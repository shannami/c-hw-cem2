#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n = 0;
    int m = 0;
    printf("введите число городов и число дорог:\n");
    scanf("%d %d", &n, &m);

    Graph* graph = createGraph(n);

    printf("введите %d дорог в формате: from to len \n", m);

    for (int i = 0; i < m; i++) {
        int a = 0, b = 0, len = 0;
        scanf("%d %d %d", &a, &b, &len);
        a--;
        b--;
        addEdge(graph, a, b, len);
        addEdge(graph, b, a, len);
    }

    int k = 0;
    printf("введите кол-во столиц:\n");
    scanf("%d", &k);

    int* capitals = malloc(k * sizeof(int));
    printf("введите номера столиц:\n");
    for (int i = 0; i < k; i++) {
        scanf("%d", &capitals[i]);
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

    free(country);
    free(capitals);
    freeGraph(graph);

    return 0;
}
