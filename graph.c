#include "graph.h"
#include "location.h"
#include <limits.h>
#include <stdio.h>

#define MAX 20
#define INF 9999

int graph[MAX][MAX];

/* Load graph edges from graph.txt */
void loadGraph()
{
FILE *fp = fopen("graph.txt","r");


if(fp == NULL)
{
    printf("graph.txt not found\n");
    return;
}

/* Initialize graph matrix */

for(int i=0;i<MAX;i++)
    for(int j=0;j<MAX;j++)
        graph[i][j] = 0;

int u,v,w;

while(fscanf(fp,"%d %d %d",&u,&v,&w) == 3)
{
    if(u < locationCount && v < locationCount)
    {
        graph[u][v] = w;
        graph[v][u] = w;
    }
}

fclose(fp);


}

/* Find minimum distance node */
int minDist(int dist[], int visited[])
{
int min = INT_MAX;
int min_index = -1;


for(int i=0;i<locationCount;i++)
{
    if(!visited[i] && dist[i] < min)
    {
        min = dist[i];
        min_index = i;
    }
}

return min_index;


}

/* Dijkstra shortest path */
void dijkstra(int src,int dist[])
{
int visited[MAX];


for(int i=0;i<locationCount;i++)
{
    dist[i] = INF;
    visited[i] = 0;
}

if(src < 0 || src >= locationCount)
    return;

dist[src] = 0;

for(int c=0;c<locationCount-1;c++)
{
    int u = minDist(dist,visited);

    if(u == -1)
        break;

    visited[u] = 1;

    for(int v=0;v<locationCount;v++)
    {
        if(!visited[v] &&
           graph[u][v] &&
           dist[u] + graph[u][v] < dist[v])
        {
            dist[v] = dist[u] + graph[u][v];
        }
    }
}


}

/* Return shortest distance between two nodes */
int getDistance(int src,int dest)
{
int dist[MAX];


if(src < 0 || dest < 0 ||
   src >= locationCount || dest >= locationCount)
{
    return INF;
}

dijkstra(src,dist);

return dist[dest];


}
