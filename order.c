#include <stdio.h>
#include <string.h>
#include "restaurant.h"
#include "dish.h"
#include "rider.h"
#include "graph.h"
#include "location.h"

#define MAX_CART 20
#define MAX_QUEUE 50

/* -------- CART ITEM -------- */

typedef struct
{
char restaurant[50];
char dish[50];
int price;
} CartItem;

/* -------- ORDER STRUCT -------- */

typedef struct
{
CartItem items[MAX_CART];
int itemCount;
int location;
int totalBill;
int restaurantNode;
} Order;

/* -------- QUEUE -------- */

Order orderQueue[MAX_QUEUE];
int front = 0;
int rear = -1;

/* -------- CART -------- */

CartItem cart[MAX_CART];
int cartCount = 0;

char orderHistory[50][100];
int orderCount = 0;

/* -------- QUEUE FUNCTIONS -------- */

void enqueueOrder(Order o)
{
if(rear >= MAX_QUEUE-1)
{
printf("Order queue full\n");
return;
}


rear++;
orderQueue[rear] = o;


}

Order dequeueOrder()
{
return orderQueue[front++];
}

int isQueueEmpty()
{
return front > rear;
}

/* -------- FIND BEST RIDER -------- */

int findBestRider(int restaurantNode, int customerNode)
{
int bestRider = -1;
int bestDistance = 9999;


for(int i=0;i<riderCount;i++)
{
    int d1 = getDistance(riders[i].node, restaurantNode);
    int d2 = getDistance(restaurantNode, customerNode);

    int total = d1 + d2;

    if(total < bestDistance)
    {
        bestDistance = total;
        bestRider = i;
    }
}

return bestRider;


}

/* -------- PROCESS ORDER -------- */

void processOrders()
{
while(!isQueueEmpty())
{
Order o = dequeueOrder();


    printf("\n===== PROCESSING ORDER =====\n");

    for(int i=0;i<o.itemCount;i++)
    {
        printf("%s (%s) - %d Tk\n",
               o.items[i].dish,
               o.items[i].restaurant,
               o.items[i].price);
    }

    printf("Total Bill : %d Tk\n", o.totalBill);

    int riderIndex = findBestRider(o.restaurantNode, o.location);

    if(riderIndex != -1)
    {
        printf("\n----- DELIVERY DETAILS -----\n");
        printf("Rider Name : %s\n", riders[riderIndex].name);
        printf("Phone      : %s\n", riders[riderIndex].phone);

        riders[riderIndex].node = o.location;
    }
    else
    {
        printf("No rider available\n");
    }

    if(orderCount < 50)
    {
        sprintf(orderHistory[orderCount],
                "Items:%d | Total:%d Tk",
                o.itemCount,
                o.totalBill);

        orderCount++;
    }

    printf("Order delivered successfully\n");
}


}

/* -------- ORDER FOOD -------- */

void orderFood()
{
int rChoice, dChoice;
int dishIndexes[50];
int count;


cartCount = 0;

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
        if(strcmp(dishes[i].restaurant,
                  restaurants[rChoice-1].name)==0)
        {
            printf("%d. %s (%d Tk)\n",
                   count+1,
                   dishes[i].name,
                   dishes[i].price);

            dishIndexes[count++] = i;
        }
    }

    printf("Enter choice: ");
    scanf("%d",&dChoice);

    if(dChoice < 1 || dChoice > count)
    {
        printf("Invalid dish choice\n");
        continue;
    }

    int selected = dishIndexes[dChoice-1];

    strcpy(cart[cartCount].restaurant,
           dishes[selected].restaurant);

    strcpy(cart[cartCount].dish,
           dishes[selected].name);

    cart[cartCount].price = dishes[selected].price;

    cartCount++;
}

if(cartCount == 0)
    return;

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

int foodTotal = 0;

for(int i=0;i<cartCount;i++)
    foodTotal += cart[i].price;

/* -------- DELIVERY CHARGE -------- */

char usedRestaurants[20][50];
int usedCount = 0;

for(int i=0;i<cartCount;i++)
{
    int found = 0;

    for(int j=0;j<usedCount;j++)
    {
        if(strcmp(usedRestaurants[j], cart[i].restaurant)==0)
        {
            found = 1;
            break;
        }
    }

    if(!found)
    {
        strcpy(usedRestaurants[usedCount], cart[i].restaurant);
        usedCount++;
    }
}

int deliveryCharge = usedCount * 50;

int totalBill = foodTotal + deliveryCharge;

printf("\n----- BILL DETAILS -----\n");
printf("Food Total      : %d Tk\n", foodTotal);
printf("Delivery Charge : %d Tk\n", deliveryCharge);
printf("Total Bill      : %d Tk\n", totalBill);

Order newOrder;

newOrder.itemCount = cartCount;
newOrder.location = loc;
newOrder.totalBill = totalBill;

int restaurantNode = -1;

for(int i=0;i<restaurantCount;i++)
{
    if(strcmp(restaurants[i].name, cart[0].restaurant)==0)
    {
        restaurantNode = restaurants[i].node;
        break;
    }
}

newOrder.restaurantNode = restaurantNode;

for(int i=0;i<cartCount;i++)
    newOrder.items[i] = cart[i];

enqueueOrder(newOrder);

printf("\nOrder added to queue successfully\n");

processOrders();


}

/* -------- HISTORY -------- */

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
