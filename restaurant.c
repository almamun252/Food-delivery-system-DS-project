#include <stdio.h>
#include <stdlib.h>  
#include <string.h>
#include "restaurant.h"
#include "location.h"



Restaurant *restaurants = NULL; 
int restaurantCount = 0;
int restaurantCapacity = 0;     



typedef struct
{
    char name[50];
    float rating;
} HeapNode;



void swapHeap(HeapNode *a, HeapNode *b)
{
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyDown(HeapNode *heap, int heapSize, int i)
{
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if(left < heapSize && heap[left].rating > heap[largest].rating)
        largest = left;

    if(right < heapSize && heap[right].rating > heap[largest].rating)
        largest = right;

    if(largest != i)
    {
        swapHeap(&heap[i], &heap[largest]);
        heapifyDown(heap, heapSize, largest);
    }
}

void insertHeap(HeapNode *heap, int *heapSize, char name[], float rating)
{
    int i = *heapSize;

    strcpy(heap[i].name, name);
    heap[i].rating = rating;

    (*heapSize)++;

    while(i != 0 && heap[(i-1)/2].rating < heap[i].rating)
    {
        swapHeap(&heap[i], &heap[(i-1)/2]);
        i = (i-1)/2;
    }
}

HeapNode extractMax(HeapNode *heap, int *heapSize)
{
    HeapNode root = heap[0];

    heap[0] = heap[*heapSize-1];
    (*heapSize)--;

    heapifyDown(heap, *heapSize, 0);

    return root;
}



void loadRestaurants()
{
    FILE *fp = fopen("restaurants.txt","r");

    if(fp == NULL)
    {
        printf("restaurants.txt not found\n");
        return;
    }

    restaurantCount = 0;

    char name[50];
    int node;
    int sum, count;

    while(fscanf(fp,"%[^|]|%d|%d|%d\n",name,&node,&sum,&count) == 4)
    {
        
        if (restaurantCount >= restaurantCapacity)
        {
            restaurantCapacity = (restaurantCapacity == 0) ? 5 : restaurantCapacity * 2;
            restaurants = (Restaurant*)realloc(restaurants, restaurantCapacity * sizeof(Restaurant));
            
            if (restaurants == NULL) {
                printf("Memory Allocation Failed during loading!\n");
                fclose(fp);
                return;
            }
        }

        strcpy(restaurants[restaurantCount].name,name);
        restaurants[restaurantCount].node = node;

        restaurants[restaurantCount].ratingSum = sum;
        restaurants[restaurantCount].ratingCount = count;

        restaurantCount++;
    }

    fclose(fp);
}



void saveRestaurants()
{
    FILE *fp = fopen("restaurants.txt","w");

    if(fp == NULL)
        return;

    for(int i=0;i<restaurantCount;i++)
    {
        fprintf(fp,"%s|%d|%d|%d\n",
                restaurants[i].name,
                restaurants[i].node,
                restaurants[i].ratingSum,
                restaurants[i].ratingCount);
    }

    fclose(fp);
}



void addRestaurant()
{

    if (restaurantCount >= restaurantCapacity)
    {
        restaurantCapacity = (restaurantCapacity == 0) ? 5 : restaurantCapacity * 2;
        restaurants = (Restaurant*)realloc(restaurants, restaurantCapacity * sizeof(Restaurant));
        
        if (restaurants == NULL) {
            printf("Memory Allocation Failed! Cannot add restaurant.\n");
            return;
        }
    }

    char name[50];

    printf("\n===== ADD RESTAURANT =====\n");

    printf("Enter restaurant name: ");
    scanf(" %[^\n]", name);

    for(int i=0;i<restaurantCount;i++)
    {
        if(strcmp(restaurants[i].name,name) == 0)
        {
            printf("Restaurant already exists\n");
            return;
        }
    }

    if(locationCount == 0)
    {
        printf("Location list empty\n");
        return;
    }

    printf("\nSelect Restaurant Location\n");

    for(int i=0;i<locationCount;i++)
        printf("%d. %s\n", i, locations[i].name);

    int loc;

    printf("Enter location node: ");
    scanf("%d",&loc);

    if(loc < 0 || loc >= locationCount)
    {
        printf("Invalid location\n");
        return;
    }

    strcpy(restaurants[restaurantCount].name,name);
    restaurants[restaurantCount].node = loc;

    restaurants[restaurantCount].ratingSum = 0;
    restaurants[restaurantCount].ratingCount = 0;

    restaurantCount++;

    saveRestaurants();

    printf("Restaurant added successfully\n");
}



void removeRestaurant()
{
    char name[50];
    int found = -1;

    if(restaurantCount == 0)
    {
        printf("No restaurants available\n");
        return;
    }

    printf("Enter restaurant name to remove: ");
    scanf(" %[^\n]", name);

    for(int i=0;i<restaurantCount;i++)
    {
        if(strcmp(restaurants[i].name,name) == 0)
        {
            found = i;
            break;
        }
    }

    if(found == -1)
    {
        printf("Restaurant not found\n");
        return;
    }

    for(int i=found;i<restaurantCount-1;i++)
        restaurants[i] = restaurants[i+1];

    restaurantCount--;

    saveRestaurants();

    printf("Restaurant removed successfully\n");
}



void viewRestaurants()
{
    printf("\n===== RESTAURANTS =====\n");

    if(restaurantCount == 0)
    {
        printf("No restaurants available\n");
        return;
    }

    for(int i=0;i<restaurantCount;i++)
    {
        float avg = 0;

        if(restaurants[i].ratingCount > 0)
        {
            avg = (float)restaurants[i].ratingSum /
                  restaurants[i].ratingCount;
        }

        printf("%d. %-15s | Location: %-15s | Rating: %.1f\n",
               i+1,
               restaurants[i].name,
               locations[restaurants[i].node].name,
               avg);
    }
}



void rateRestaurant()
{
    if(restaurantCount == 0)
    {
        printf("No restaurants available\n");
        return;
    }

    printf("\n===== RATE RESTAURANT =====\n");

    for(int i=0;i<restaurantCount;i++)
    {
        float avg = 0;

        if(restaurants[i].ratingCount > 0)
        {
            avg = (float)restaurants[i].ratingSum /
                  restaurants[i].ratingCount;
        }

        printf("%d. %s (Rating %.1f)\n",
               i+1,
               restaurants[i].name,
               avg);
    }

    int choice;

    printf("Select restaurant: ");
    scanf("%d",&choice);

    if(choice < 1 || choice > restaurantCount)
    {
        printf("Invalid choice\n");
        return;
    }

    int rating;

    printf("Give rating (1-5): ");
    scanf("%d",&rating);

    if(rating < 1 || rating > 5)
    {
        printf("Invalid rating\n");
        return;
    }

    restaurants[choice-1].ratingSum += rating;
    restaurants[choice-1].ratingCount++;

    saveRestaurants();

    printf("Rating submitted successfully\n");
}



void showTopRestaurants()
{
    if(restaurantCount == 0)
    {
        printf("No restaurants available\n");
        return;
    }

    
    HeapNode *dynamicHeap = (HeapNode*)malloc(restaurantCount * sizeof(HeapNode));
    if (dynamicHeap == NULL) {
        printf("Memory allocation failed for Heap!\n");
        return;
    }
    
    int currentHeapSize = 0;

    for(int i=0;i<restaurantCount;i++)
    {
        float avg = 0;

        if(restaurants[i].ratingCount > 0)
        {
            avg = (float)restaurants[i].ratingSum /
                  restaurants[i].ratingCount;
        }

        
        insertHeap(dynamicHeap, &currentHeapSize, restaurants[i].name, avg);
    }

    printf("\n===== TOP RATED RESTAURANTS =====\n");

    int limit = 3;
    if(limit > currentHeapSize)
        limit = currentHeapSize;

    for(int i=0;i<limit;i++)
    {
        HeapNode top = extractMax(dynamicHeap, &currentHeapSize);

        printf("%d. %s (Rating %.1f)\n",
               i+1,
               top.name,
               top.rating);
    }

    
    free(dynamicHeap);
}


void changeRestaurantLocation()
{
    if(restaurantCount == 0)
    {
        printf("No restaurants available\n");
        return;
    }

    printf("\n===== CHANGE RESTAURANT LOCATION =====\n");

    for(int i=0;i<restaurantCount;i++)
    {
        printf("%d. %s (%s)\n",
               i+1,
               restaurants[i].name,
               locations[restaurants[i].node].name);
    }

    int choice;

    printf("Select restaurant: ");
    scanf("%d",&choice);

    if(choice < 1 || choice > restaurantCount)
    {
        printf("Invalid choice\n");
        return;
    }

    printf("\nAvailable Locations\n");

    for(int i=0;i<locationCount;i++)
        printf("%d. %s\n",i,locations[i].name);

    int loc;

    printf("Enter new location node: ");
    scanf("%d",&loc);

    if(loc < 0 || loc >= locationCount)
    {
        printf("Invalid location\n");
        return;
    }

    restaurants[choice-1].node = loc;

    saveRestaurants();

    printf("Restaurant location updated successfully\n");
}