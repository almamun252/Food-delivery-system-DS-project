#include <stdio.h>
#include <string.h>
#include "restaurant.h"
#include "location.h"

Restaurant restaurants[MAX_RESTAURANTS];
int restaurantCount = 0;

/* ---------- LOAD RESTAURANTS ---------- */

void loadRestaurants()
{
FILE *fp = fopen("restaurants.txt","r");


if(fp == NULL)
{
    printf("restaurants.txt not found\n");
    return;
}

char name[50];
int node;

while(fscanf(fp,"%[^|]|%d\n",name,&node) == 2)
{
    strcpy(restaurants[restaurantCount].name,name);
    restaurants[restaurantCount].node = node;

    restaurantCount++;
}

fclose(fp);


}

/* ---------- SAVE RESTAURANTS ---------- */

void saveRestaurants()
{
FILE *fp = fopen("restaurants.txt","w");


if(fp == NULL)
    return;

for(int i=0;i<restaurantCount;i++)
{
    fprintf(fp,"%s|%d\n",
            restaurants[i].name,
            restaurants[i].node);
}

fclose(fp);


}

/* ---------- ADD RESTAURANT ---------- */

void addRestaurant()
{
if(restaurantCount >= MAX_RESTAURANTS)
{
printf("Restaurant list is full\n");
return;
}


char name[50];

printf("\n===== ADD RESTAURANT =====\n");

printf("Enter restaurant name: ");
scanf(" %[^\n]", name);

/* Duplicate check */

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
{
    printf("%d. %s\n", i, locations[i].name);
}

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

restaurantCount++;

saveRestaurants();

printf("Restaurant added successfully\n");


}

/* ---------- REMOVE RESTAURANT ---------- */

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
{
    restaurants[i] = restaurants[i+1];
}

restaurantCount--;

saveRestaurants();

printf("Restaurant removed successfully\n");


}

/* ---------- VIEW RESTAURANTS ---------- */

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
    printf("%d. %-15s | Location: %s\n",
           i+1,
           restaurants[i].name,
           locations[restaurants[i].node].name);
}


}

/* ---------- CHANGE RESTAURANT LOCATION ---------- */

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
{
    printf("%d. %s\n",i,locations[i].name);
}

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
