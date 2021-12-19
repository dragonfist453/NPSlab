#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int mat[10][10], p[10], nodes, dist[10];

void bellmanFord(int source)
{
    int u, v, i;
    for (i = 1; i < nodes; i++)
    {
        for (u = 0; u < nodes; u++)
        {
            for (v = 0; v < nodes; v++)
            {
                if (dist[v] > dist[u] + mat[u][v])
                {
                    dist[v] = dist[u] + mat[u][v];
                    p[v] = u;
                }
            }
        }
    }
    for (u = 0; u < nodes; u++)
    {
        for (v = 0; v < nodes; v++)
        {
            if (dist[v] > dist[u] + mat[u][v])
            {
                printf("Negative edge cycle\n");
                exit(0);
            }
        }
    }
}

int main()
{
    int i, j, source;
    printf("Enter number of nodes\n");
    scanf("%d", &nodes);
    printf("Enter the adjancency matrix\n");
    for (i = 0; i < nodes; i++)
    {
        for (j = 0; j < nodes; j++)
        {
            scanf("%d", &mat[i][j]);
        }
    }

    for (source = 0; source < nodes; source++)
    {
        for (i = 0; i < 9; i++)
        {
            dist[i] = 999;
            p[i] = -1;
        }
        // printf("Enter the source vertex\n");
        // scanf("%d", &source);
        dist[source] = 0;
        bellmanFord(source);

        printf("ROUTER-%d\n\n", source);

        for (i = 0; i < nodes; i++)
        {
            if (i != source)
            {
                j = i;
                while (p[j] != -1)
                {
                    printf("%d <- ", j);
                    j = p[j];
                }
            }
            printf("%d\tCost %d\n\n", source, dist[i]);
        }
    }
    return 0;
}
