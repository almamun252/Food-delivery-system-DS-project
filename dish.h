#ifndef DISH_H
#define DISH_H

#define MAX_DISHES 100

typedef struct
{
    char name[50];
    char restaurant[50];
    int price;
} Dish;

extern Dish dishes[MAX_DISHES];
extern int dishCount;

void loadDishes();
void addDish();
void deleteDish();
void viewDishes();

#endif