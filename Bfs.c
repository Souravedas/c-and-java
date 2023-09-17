
#include<stdio.h>
#include<stdlib.h>

int matrix[10][10], n, visited[10];


void create()
{
    int i, j;
    printf("\nEnter the number of the vertices: \n");
    scanf("%d", &n);

    printf("\nEnter the adjacency matrix: \n");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            scanf("%d", &matrix[i][j]);
        }
    }
    printf("\nValues entered.\n");
}


void bfs()
{
    int start, j, i;
    int front = -1, rear = -1, queue[n];
    printf("\nEnter the starting vertex: ");
    scanf("%d", &start);

    start = start - 1;

    queue[++rear] = start;
    visited[start] = 1;

    printf("\nThe reachable vertices are: \n");
    while(front != rear)
    {
        j = queue[++front];
        for(i = 0; i < n; i++)
        {
            if(matrix[i][j] == 1 && visited[i] == 0)
            {
                queue[++rear] = i;
                visited[i] = 1;
                printf("\n%d", i+1);
            }
        }
    }
    printf("\n");
}

int main()
{
    int choice, i;
    
    do
    {
        
        printf("\n1. Create graph.");
        printf("\n2. BFS Traversal.");
        printf("\n3. Exit.");
        printf("\nEnter your choice: \n");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1: 
                create();
                    break;
            case 2: 
                for(i = 0; i < n; i++)
                {
                    visited[i] = 0;
                }
                bfs();
                    break;
            case 3: 
                choice = 3;
                    break;
            default: 
                printf("\nInvalid option.\n");
        }
    } while (choice != 3);

    return 0;
}