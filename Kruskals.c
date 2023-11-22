#include <stdio.h>
#include <stdlib.h>


int find(int parent[], int i) {
    if (parent[i] != i)
        parent[i] = find(parent, parent[i]);
    return parent[i];
}


void Union(int parent[], int rank[], int x, int y) {
    int xroot = find(parent, x);
    int yroot = find(parent, y);

    if (rank[xroot] < rank[yroot])
        parent[xroot] = yroot;
    else if (rank[xroot] > rank[yroot])
        parent[yroot] = xroot;
    else {
        parent[yroot] = xroot;
        rank[xroot]++;
    }
}

int main() {
    int V, E;

 
    printf("Enter the number of vertices: ");
    scanf("%d", &V);
    printf("Enter the number of edges: ");
    scanf("%d", &E);

    int parent[V];
    int rank[V];

  
    for (int i = 0; i < V; i++) {
        parent[i] = i;
        rank[i] = 0;
    }

    int graph[E][3];

   
    for (int i = 0; i < E; i++) {
        printf("Enter edge %d (src dest weight): ", i + 1);
        scanf("%d %d %d", &graph[i][0], &graph[i][1], &graph[i][2]);
    }

    int result[V - 1];
    int e = 0; 
    int totalCost = 0;

  
    for (int i = 0; i < E - 1; i++) {
        for (int j = 0; j < E - i - 1; j++) {
            if (graph[j][2] > graph[j + 1][2]) {
                
                for (int k = 0; k < 3; k++) {
                    int temp = graph[j][k];
                    graph[j][k] = graph[j + 1][k];
                    graph[j + 1][k] = temp;
                }
            }
        }
    }

   
    for (int i = 0; i < E && e < V - 1; i++) {
        int x = find(parent, graph[i][0]);
        int y = find(parent, graph[i][1]);

    
        if (x != y) {
            result[e++] = i;
            Union(parent, rank, x, y);
             totalCost += graph[i][2];
        }
       
    }

   
    printf("Edges in the constructed MST:\n");
    for (int i = 0; i < V - 1; i++)
        printf("%d -- %d == %d\n", graph[result[i]][0], graph[result[i]][1], graph[result[i]][2]);
        
        
    printf("Total cost of the minimum spanning tree: %d\n", totalCost);

    return 0;
}
