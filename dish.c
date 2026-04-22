#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "dish.h"
#include "restaurant.h"


Dish *dishes = NULL;
int dishCount = 0;
int dishCapacity = 0;



void loadDishes()
{
    FILE *fp = fopen("dishes.txt","r");

    if(fp == NULL)
    {
        printf("dishes.txt not found\n");
        return;
    }
    
    dishCount = 0;

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
                printf("Memory allocation failed during loading dishes!\n");
                fclose(fp);
                return;
            }
        }

        strcpy(dishes[dishCount].restaurant,rest);
        strcpy(dishes[dishCount].name,dish);
        dishes[dishCount].price = price;

        dishCount++;
    }

    fclose(fp);
}



void saveDishes()
{
    FILE *fp = fopen("dishes.txt","w");

    if(fp == NULL)
        return;

    for(int i=0;i<dishCount;i++)
    {
        fprintf(fp,"%s|%s|%d\n",
                dishes[i].restaurant,
                dishes[i].name,
                dishes[i].price);
    }

    fclose(fp);
}



void addDish()
{
    int choice;

    if(restaurantCount == 0)
    {
        printf("No restaurants available. Add restaurant first.\n");
        return;
    }

    
    if(dishCount >= dishCapacity)
    {
        dishCapacity = (dishCapacity == 0) ? 5 : dishCapacity * 2;
        dishes = (Dish*)realloc(dishes, dishCapacity * sizeof(Dish));
        
        if(dishes == NULL)
        {
            printf("Memory allocation failed! Cannot add dish.\n");
            return;
        }
    }

    printf("\n===== ADD NEW DISH =====\n");

    printf("Enter dish name: ");
    scanf(" %[^\n]", dishes[dishCount].name);

    printf("\nSelect Restaurant\n");

    for(int i=0;i<restaurantCount;i++)
    {
        printf("%d. %s\n", i+1, restaurants[i].name);
    }

    printf("Enter choice: ");
    scanf("%d",&choice);

    if(choice < 1 || choice > restaurantCount)
    {
        printf("Invalid restaurant choice\n");
        return;
    }

    strcpy(dishes[dishCount].restaurant, restaurants[choice-1].name);

    printf("Enter price (Tk): ");
    scanf("%d",&dishes[dishCount].price);

    dishCount++;

    saveDishes();

    printf("Dish added successfully\n");
}


void deleteDish()
{
    char name[50];
    int found = -1;

    if(dishCount == 0)
    {
        printf("No dishes available\n");
        return;
    }

    printf("\n===== DELETE DISH =====\n");

    printf("Enter dish name to delete: ");
    scanf(" %[^\n]", name);

    for(int i=0;i<dishCount;i++)
    {
        if(strcmp(dishes[i].name,name) == 0)
        {
            found = i;
            break;
        }
    }

    if(found == -1)
    {
        printf("Dish not found\n");
        return;
    }

    for(int i=found;i<dishCount-1;i++)
    {
        dishes[i] = dishes[i+1];
    }

    dishCount--;

    saveDishes();

    printf("Dish deleted successfully\n");
}



void viewDishes()
{
    printf("\n===== FOOD MENU =====\n");

    if(dishCount == 0)
    {
        printf("No dishes available\n");
        return;
    }

    for(int i=0;i<dishCount;i++)
    {
        printf("%d. %-15s | %4d Tk | %s\n",
               i+1,
               dishes[i].name,
               dishes[i].price,
               dishes[i].restaurant);
    }
}