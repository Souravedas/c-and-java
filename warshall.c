#include <stdio.h>

int main() {
    int V;
    printf("Enter the number of vertices: ");
    scanf("%d", &V);

    int graph[V][V];
    int reach[V][V];

    printf("Enter the adjacency matrix:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            scanf("%d", &graph[i][j]);
        }
    }
   

    // Initialize the reach matrix with the given graph
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            reach[i][j] = graph[i][j];
        }
    }

    // Apply Warshall's algorithm to compute transitive closure
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                reach[i][j] = reach[i][j] || (reach[i][k] && reach[k][j]);
            }
        }
    }

    // Print the transitive closure matrix
       printf("Transitive Closure of the graph:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            printf("%d ", reach[i][j]);
        }
        printf("\n");
    }

    return 0;
}
