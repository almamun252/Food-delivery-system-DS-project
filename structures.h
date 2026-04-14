
#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct Restaurant{
    int id;
    char name[50];
    float rating;
}Restaurant;

typedef struct FoodNode{
    char name[50];
    int price;
    struct FoodNode *left;
    struct FoodNode *right;
}FoodNode;

typedef struct Order{
    int id;
    char food[50];
    int price;
    struct Order *next;
}Order;

typedef struct Heap{
    int orderID;
    int priority;
}Heap;

#endif
