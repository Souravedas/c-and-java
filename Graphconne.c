#include <stdio.h>
#define MAX_NODES 100

int adjacencyMatrix[MAX_NODES][MAX_NODES];
int visited[MAX_NODES];
void DFS(int vertex, int numNodes) {
    visited[vertex] = 1;
    printf("%d ", vertex);

    for (int i = 0; i < numNodes; ++i) {
        if (adjacencyMatrix[vertex][i] && !visited[i]) {
            DFS(i, numNodes);
        }
    }
}
int isConnected(int numNodes) {
    for (int i = 0; i < numNodes; ++i) {
        if (!visited[i]) {
            DFS(i, numNodes);
            break;
        }
    }
    for (int i = 0; i < numNodes; ++i) {
        if (!visited[i]) {
            return 0; 
        }
    }
    return 1; 
}
int main() {
    int numNodes, numEdges;
    printf("Enter the number of nodes and edges: ");
    scanf("%d %d", &numNodes, &numEdges);

    for (int i = 0; i < numNodes; ++i) {
        visited[i] = 0;
        for (int j = 0; j < numNodes; ++j) {
            adjacencyMatrix[i][j] = 0;
        }
    }
    printf("Enter the edges (src dest):\n");
    for (int i = 0; i < numEdges; ++i) {
        int src, dest;
        scanf("%d %d", &src, &dest);
       adjacencyMatrix[src][dest] = 1;
       adjacencyMatrix[dest][src] = 1;
    }
    for (int i = 0; i < numNodes; ++i) {
        if (!visited[i]) {
            DFS(i, numNodes);
            break;
        }
    }
    for (int i = 0; i < numNodes; ++i) {
        if (!visited[i]) {
            printf("\nThe graph is not connected.\n");
            return 0;
        }
    }

    printf("\nThe graph is connected.\n");

    return 0;
}
