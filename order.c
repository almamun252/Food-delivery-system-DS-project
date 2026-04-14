#include <stdio.h>
#include <string.h>
#include "restaurant.h"
#include "dish.h"
#include "rider.h"
#include "graph.h"
#include "location.h"

#define MAX_CART 20

typedef struct
{
char restaurant[50];
char dish[50];
int price;
} CartItem;

CartItem cart[MAX_CART];
int cartCount = 0;

char orderHistory[50][100];
int orderCount = 0;

/* -------- FIND NEAREST RIDER -------- */

int findNearestRider(int loc)
{
int minDist = 9999;
int best = -1;


for(int i=0;i<riderCount;i++)
{
    int d = getDistance(riders[i].node, loc);

    if(d < minDist)
    {
        minDist = d;
        best = i;
    }
}

return best;


}

/* -------- ORDER FOOD -------- */

void orderFood()
{
int rChoice, dChoice;
int dishIndexes[50];
int count;


cartCount = 0;

/* -------- ADD ITEMS TO CART -------- */

while(1)
{
    if(restaurantCount == 0)
    {
        printf("No restaurants available\n");
        return;
    }

    printf("\n===== SELECT RESTAURANT =====\n");

    for(int i=0;i<restaurantCount;i++)
        printf("%d. %s\n",i+1,restaurants[i].name);

    printf("0 Finish Order\n");
    printf("Enter choice: ");
    scanf("%d",&rChoice);

    if(rChoice == 0)
        break;

    if(rChoice < 1 || rChoice > restaurantCount)
    {
        printf("Invalid restaurant choice\n");
        continue;
    }

    printf("\n===== SELECT DISH =====\n");

    count = 0;

    for(int i=0;i<dishCount;i++)
    {
        if(strcmp(dishes[i].restaurant, restaurants[rChoice-1].name) == 0)
        {
            printf("%d. %s (%d Tk)\n",count+1,dishes[i].name,dishes[i].price);
            dishIndexes[count] = i;
            count++;
        }
    }

    if(count == 0)
    {
        printf("No dishes available\n");
        continue;
    }

    printf("Enter choice: ");
    scanf("%d",&dChoice);

    if(dChoice < 1 || dChoice > count)
    {
        printf("Invalid choice\n");
        continue;
    }

    if(cartCount >= MAX_CART)
    {
        printf("Cart full\n");
        break;
    }

    int selected = dishIndexes[dChoice-1];

    strcpy(cart[cartCount].restaurant, dishes[selected].restaurant);
    strcpy(cart[cartCount].dish, dishes[selected].name);
    cart[cartCount].price = dishes[selected].price;

    cartCount++;

    printf("Item added to cart\n");
}

if(cartCount == 0)
{
    printf("No items selected\n");
    return;
}

/* -------- DELIVERY LOCATION -------- */

if(locationCount <= 1)
{
    printf("Location list empty\n");
    return;
}

printf("\n===== DELIVERY LOCATION =====\n");

for(int i=1;i<locationCount;i++)
    printf("%d %s\n",i,locations[i].name);

int loc;

printf("Enter location choice: ");
scanf("%d",&loc);

if(loc < 1 || loc >= locationCount)
{
    printf("Invalid location\n");
    return;
}

/* -------- RECEIPT -------- */

int foodTotal = 0;

printf("\n===== ORDER RECEIPT =====\n");

for(int i=0;i<cartCount;i++)
{
    printf("%s (%s) - %d Tk\n",
           cart[i].dish,
           cart[i].restaurant,
           cart[i].price);

    foodTotal += cart[i].price;
}

/* -------- DELIVERY CHARGE CALCULATION -------- */

int deliveryCharge = 0;

char usedRestaurants[20][50];
int usedCount = 0;
int restaurantCharge[20];

for(int i=0;i<cartCount;i++)
{
    int found = -1;

    for(int j=0;j<usedCount;j++)
    {
        if(strcmp(usedRestaurants[j], cart[i].restaurant) == 0)
        {
            found = j;
            break;
        }
    }

    if(found == -1)
    {
        strcpy(usedRestaurants[usedCount], cart[i].restaurant);

        int restaurantNode = -1;

        for(int r=0;r<restaurantCount;r++)
        {
            if(strcmp(restaurants[r].name, cart[i].restaurant) == 0)
            {
                restaurantNode = restaurants[r].node;
                break;
            }
        }

        int distance = getDistance(restaurantNode, loc);

        int charge;

        /* -------- NEW DELIVERY RULE -------- */

        if(distance <= 3)
            charge = 50;
        else
            charge = 50 + (distance - 3) * 10;

        restaurantCharge[usedCount] = charge;

        deliveryCharge += charge;

        usedCount++;
    }
}

int total = foodTotal + deliveryCharge;

printf("\n----- DELIVERY CHARGES -----\n");

for(int i=0;i<usedCount;i++)
{
    printf("%s : %d Tk\n",
           usedRestaurants[i],
           restaurantCharge[i]);
}

printf("-------------------------------\n");
printf("Food Total      : %d Tk\n", foodTotal);
printf("Delivery Charge : %d Tk\n", deliveryCharge);
printf("Total Bill      : %d Tk\n", total);

/* -------- RIDER ASSIGNMENT -------- */

if(riderCount > 0)
{
    int riderIndex = findNearestRider(loc);

    if(riderIndex != -1)
    {
        printf("\n----- DELIVERY DETAILS -----\n");
        printf("Rider Name      : %s\n", riders[riderIndex].name);
        printf("Phone           : %s\n", riders[riderIndex].phone);

        riders[riderIndex].node = loc;
    }
}

/* -------- SAVE HISTORY -------- */

if(orderCount < 50)
{
    sprintf(orderHistory[orderCount],
            "Items:%d | Total:%d Tk",
            cartCount,
            total);

    orderCount++;
}

printf("\nOrder placed successfully!\n");


}

/* -------- ORDER HISTORY -------- */

void showHistory()
{
printf("\n===== ORDER HISTORY =====\n");


if(orderCount == 0)
{
    printf("No orders yet\n");
    return;
}

for(int i=0;i<orderCount;i++)
    printf("%d. %s\n",i+1,orderHistory[i]);


}
