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
int sum,count;

while(fscanf(fp,"%[^|]|%d|%d|%d\n",name,&node,&sum,&count) == 4)
{
    strcpy(restaurants[restaurantCount].name,name);
    restaurants[restaurantCount].node = node;

    restaurants[restaurantCount].ratingSum = sum;
    restaurants[restaurantCount].ratingCount = count;

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
    fprintf(fp,"%s|%d|%d|%d\n",
            restaurants[i].name,
            restaurants[i].node,
            restaurants[i].ratingSum,
            restaurants[i].ratingCount);
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
    restaurants[i] = restaurants[i+1];

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
    float avg = 0;

    if(restaurants[i].ratingCount > 0)
        avg = (float)restaurants[i].ratingSum /
              restaurants[i].ratingCount;

    printf("%d. %-15s | Location: %-15s | Rating: %.1f\n",
           i+1,
           restaurants[i].name,
           locations[restaurants[i].node].name,
           avg);
}


}

/* ---------- RATE RESTAURANT ---------- */

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
        avg = (float)restaurants[i].ratingSum /
              restaurants[i].ratingCount;

    printf("%d. %s (Rating: %.1f)\n",
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
