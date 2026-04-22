#include "graph.h"
#include "location.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h> 

#define MAX 20
#define INF 9999


typedef struct AdjListNode {
    int dest;
    int weight;
    struct AdjListNode* next;
} AdjListNode;


AdjListNode* graph[MAX];


void initGraph()
{
    for (int i = 0; i < MAX; i++) {
        graph[i] = NULL;
    }
}


void addEdge(int src, int dest, int weight)
{
    
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = graph[src];
    graph[src] = newNode;

    
    newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->dest = src;
    newNode->weight = weight;
    newNode->next = graph[dest];
    graph[dest] = newNode;
}


void loadGraph()
{
    FILE *fp = fopen("graph.txt", "r");

    if (fp == NULL)
    {
        printf("graph.txt not found\n");
        return;
    }

    initGraph();

    int u, v, w;

    while (fscanf(fp, "%d %d %d", &u, &v, &w) == 3)
    {
        if (u < locationCount && v < locationCount)
        {
            addEdge(u, v, w);
        }
    }

    fclose(fp);
}




int minDist(int dist[], int visited[])
{
    int min = INT_MAX;
    int min_index = -1;

    for (int i = 0; i < locationCount; i++)
    {
        if (!visited[i] && dist[i] <= min)
        {
            min = dist[i];
            min_index = i;
        }
    }

    return min_index;
}


void dijkstra(int src, int dist[])
{
    int visited[MAX];

    for (int i = 0; i < locationCount; i++)
    {
        dist[i] = INF;
        visited[i] = 0;
    }

    if (src < 0 || src >= locationCount)
        return;

    dist[src] = 0;

    for (int c = 0; c < locationCount - 1; c++)
    {
        int u = minDist(dist, visited);

        if (u == -1)
            break;

        visited[u] = 1;

        
        AdjListNode* temp = graph[u];
        
        while (temp != NULL)
        {
            int v = temp->dest;
            int weight = temp->weight;

            if (!visited[v] && dist[u] != INF && dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight;
            }
            
            temp = temp->next;
        }
    }
}


int getDistance(int src, int dest)
{
    int dist[MAX];

    if (src < 0 || dest < 0 ||
        src >= locationCount || dest >= locationCount)
    {
        return INF;
    }

    dijkstra(src, dist);

    return dist[dest];
}