#include <stdio.h>
#include <stdlib.h> 
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
        if(dishCount >= dishCapacity)
        {
            dishCapacity = (dishCapacity == 0) ? 5 : dishCapacity * 2;
            dishes = (Dish*)realloc(dishes, dishCapacity * sizeof(Dish));
            
            if(dishes == NULL)
            {
                printf("Memory allocation failed for dishes in loadData!\n");
                fclose(fp);
                return;
            }
        }

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
            
            if(restaurantCount >= restaurantCapacity)
            {
                restaurantCapacity = (restaurantCapacity == 0) ? 5 : restaurantCapacity * 2;
                restaurants = (Restaurant*)realloc(restaurants, restaurantCapacity * sizeof(Restaurant));
                
                if(restaurants == NULL)
                {
                    printf("Memory allocation failed for restaurants in loadData!\n");
                    fclose(fp);
                    return;
                }
            }

            strcpy(restaurants[restaurantCount].name, rest);
            restaurants[restaurantCount].node = 0;

            restaurantCount++;
        }
    }

    fclose(fp);
}