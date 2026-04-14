#include <stdio.h>
#include <string.h>
#include "dish.h"
#include "restaurant.h"

void loadData()
{
FILE *fp = fopen("data.txt","r");


if(fp == NULL)
{
    printf("No previous data found. Starting fresh.\n");
    return;
}

char rest[50], dish[50];
int price;

while(fscanf(fp,"%[^|]|%[^|]|%d\n",rest,dish,&price) == 3)
{
    strcpy(dishes[dishCount].name, dish);
    strcpy(dishes[dishCount].restaurant, rest);
    dishes[dishCount].price = price;

    dishCount++;

    int found = 0;

    for(int i=0;i<restaurantCount;i++)
    {
        if(strcmp(restaurants[i].name, rest) == 0)
        {
            found = 1;
            break;
        }
    }

    if(!found)
    {
        strcpy(restaurants[restaurantCount].name, rest);

        /* Default node (later admin can change if needed) */
        restaurants[restaurantCount].node = 0;

        restaurantCount++;
    }
}

fclose(fp);


}
