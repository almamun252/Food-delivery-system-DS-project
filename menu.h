
#ifndef MENU_H
#define MENU_H
#include "structures.h"

FoodNode* insertFood(FoodNode*,char[],int);
FoodNode* createFood(char[],int);
void showMenu(FoodNode*);
void searchFood(FoodNode*,char[]);
void addFood(FoodNode**);
int getFoodPrice(FoodNode*, char[]);

#endif
