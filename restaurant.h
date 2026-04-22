#ifndef RESTAURANT_H
#define RESTAURANT_H

typedef struct
{
    char name[50];
    int node;
    int ratingSum;
    int ratingCount;

} Restaurant;


extern Restaurant *restaurants;
extern int restaurantCount;
extern int restaurantCapacity;

void loadRestaurants();
void saveRestaurants();
void addRestaurant();
void removeRestaurant();
void viewRestaurants();
void rateRestaurant();
void changeRestaurantLocation();
void showTopRestaurants();

#endif