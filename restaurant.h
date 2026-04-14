#ifndef RESTAURANT_H
#define RESTAURANT_H

#define MAX_RESTAURANTS 20

typedef struct
{
    char name[50];
    int node;
} Restaurant;

extern Restaurant restaurants[MAX_RESTAURANTS];
extern int restaurantCount;

void loadRestaurants();
void addRestaurant();
void removeRestaurant();
void viewRestaurants();
void changeRestaurantLocation();

#endif