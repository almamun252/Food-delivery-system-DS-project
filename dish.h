#ifndef DISH_H
#define DISH_H

typedef struct
{
    char name[50];
    char restaurant[50];
    int price;
} Dish;


extern Dish *dishes;
extern int dishCount;
extern int dishCapacity;

void loadDishes();
void saveDishes();
void addDish();
void deleteDish();
void viewDishes();

#endif