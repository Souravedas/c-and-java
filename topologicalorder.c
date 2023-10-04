#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int numVertices, numEdges;
int adjMatrix[MAX][MAX];
int visited[MAX];
int result[MAX];
int index;



void dfs(int v) {
    visited[v] = 1;

    for (int u = 0; u < numVertices; u++) {
        if (adjMatrix[v][u] && !visited[u]) {
            dfs(u);
        }
    }

    result[index] = v;
    index--;
}

int main() {
    printf("Enter the number of vertices and edges: ");
    scanf("%d %d", &numVertices, &numEdges);

    
    for (int i = 0; i < numVertices; i++) {
        visited[i] = 0;
        for (int j = 0; j < numVertices; j++) {
            adjMatrix[i][j] = 0;
        }
    }

    
    printf("Enter the edges (source destination):\n");
    for (int i = 0; i < numEdges; i++) {
        int src, dest;
        scanf("%d %d", &src, &dest);

    

        adjMatrix[src][dest] = 1;
    }


    index = numVertices - 1;

    
    for (int v = 0; v < numVertices; v++) {
        if (!visited[v]) {
            dfs(v);
        }
    }

    
    printf("Topological Order: ");
    for (int i = 0; i < numVertices; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    return 0;
}
