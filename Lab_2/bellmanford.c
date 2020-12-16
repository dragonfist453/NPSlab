#include<stdio.h>
#include<stdlib.h>
#define max 10
#define inf 999
void BellmanFord(int A[max][max], int *d, int *p, int n) {
    int i,u,v;
    for(i=1;i<n;i++) {
        for(u=0;u<n;u++) {
            for(v=0;v<n;v++) {
                if(d[v] > d[u] + A[u][v]) {
                    d[v] = d[u] + A[u][v];
                    p[v] = u;
                }
            }
        }
    }
    for(u=0;u<n;u++) {
        for(v=0;v<n;v++) {
            if(d[v] > d[u] + A[u][v]) {
                printf("Negative edge found. Exiting!\n");
                exit(0);
            }
        }
    }
}

int main() {
    int A[max][max],n;
    int *d = malloc(sizeof(int) * max);
    int *p = malloc(sizeof(int) * max);
    printf("Enter the no. of vertices : ");
    scanf("%d", &n);
    printf("Enter the adjacency matrix\n");
    int i,j;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            scanf("%d", &A[i][j]);
    
    int src,dest;
    printf("Enter source and destination vertices: \n");
    scanf("%d %d", &src,&dest);
    
    printf("\n");
    int source;
    for(source = 0;source<n;source++) {
        if(source == src) {
            for(i=0;i<n;i++) {
                d[i] = inf;
                p[i] = -1;
            }
            d[source] = 0;
            BellmanFord(A, d, p, n);
            printf("\n");
            printf("Router %d\n", source);
            for(i=0;i<n;i++){
                if(i == dest) {
                    if(i != source){
                        j = i;
                        while(p[j] != -1){
                            printf("%d<-",j);
                            j = p[j];
                        }
                    }
                    printf("%d\tCost %d\n",source,d[i]);
                }
            }
        }
    }

    return 0;
}