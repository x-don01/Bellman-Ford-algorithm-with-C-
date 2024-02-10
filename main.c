#include <stdio.h>
#include <limits.h>
#include <string.h>

#define MAX_VERTICES 7
#define MAX_EDGES 12

struct Edge {
    int src, dst, wt;
};

void printPath(int parent[], int j, char cities[MAX_VERTICES][20]) {
    if (parent[j] == -1)
        return;

    printPath(parent, parent[j], cities);
    printf(" -> %s", cities[j]);
}

void bellmanFord(struct Edge Edges[MAX_EDGES], int numVertices, char cities[MAX_VERTICES][20]) {
    int parent[MAX_VERTICES];
    int value[MAX_VERTICES];

    // Initialisation
    for (int i = 0; i < MAX_VERTICES; i++) {
        parent[i] = -1;
        value[i] = INT_MAX;
    }

    parent[0] = -1;
    value[0] = 0;

    int updated;
    for (int i = 0; i < numVertices - 1; i++) {
        updated = 0;
        for (int j = 0; j < MAX_EDGES; j++) {
            int U = Edges[j].src;
            int V = Edges[j].dst;
            int wt = Edges[j].wt;

            if (value[U] != INT_MAX && value[U] + wt < value[V]) {
                value[V] = value[U] + wt;
                parent[V] = U;
                updated = 1;
            }
        }

        if (updated == 0)
            break;

        for (int j = 0; j < MAX_EDGES; j++) {
            int U = Edges[j].src;
            int V = Edges[j].dst;
            int wt = Edges[j].wt;

            if (value[U] != INT_MAX && value[U] + wt < value[V]) {
                printf("Le graphe a un cycle negatif\n");
                return;
            }
        }
    }

    // Print Shortest Path Graph
    for (int i = 1; i < numVertices; i++) {
        printf("Shortest distance from %s to %s is %d.\n", cities[0], cities[i], value[i]);
        printf("Path: %s", cities[0]);
        printPath(parent, i, cities);
        printf("\n");
    }
}


int main() {
    int V,E;
    char cities[MAX_VERTICES][20] = {"drissia", "bni makada", "marjane val ffleuri", "branes", "mershan", "iberia", "palaza toro"};

    printf("saisi le nombre de sommets :");
    scanf("%d", &V);
    printf("saisi le nombre d'arc : ");
    scanf("%d", &E);

    if (E > MAX_EDGES) {
        printf("Error: Number of edges exceeds the maximum limit.\n");
        return 1;
    }

    struct Edge Edges[E];

    // saisir edges
    int src, dst, wt;
    printf("saisi la source, la destination (indices) et le poids pour chaque arc :\n");
    for (int i = 0; i < E; i++) {
        printf("Edge %d: \n", i + 1);
        printf("source : ");
        scanf("%d", &src);
        printf("destination : ");
        scanf("%d", &dst);
        printf("poids : ");
        scanf("%d", &wt);

        Edges[i].src = src;
        Edges[i].dst = dst;
        Edges[i].wt = wt;
    }

    printf("------------------------------------------------------------------------------------------\n");
    printf("voici les noms des zones :\n");
    for (int i = 0; i < MAX_VERTICES; i++) {
        printf(" %d/ %s \n", i + 1, cities[i]);
    }
    printf("\n\n\n voici les plus court chemins :\n\n");

    bellmanFord(Edges, V, cities);
    return 0;
}





/*
{{0,4,-10,8,999,999,999},
 {999,0,-16,999,14,999,999},
 {999,999,0,999,8,6,999},
 {999,999,2,0,999,8,999},
 {999,999,999,999,0,-2,10},
 {999,999,999,999,999,0,14},
 {999,999,999,999,999,999,0}
} */
