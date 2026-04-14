#include <stdio.h>
#include "user.h"
#include "admin.h"
#include "restaurant.h"
#include "dish.h"
#include "order.h"
#include "rider.h"
#include "location.h"
#include "graph.h"

int main()
{

loadUsers();
loadLocations();
loadGraph();
loadRestaurants();
loadDishes();
loadRiders();

int loggedIn = 0;


while(1)
{
    printf("\n===== ONLINE FOOD DELIVERY =====\n");

    if(!loggedIn)
    {
        printf("1 Login\n");
        printf("2 Create Account\n");
    }

    printf("3 View Restaurants\n");
    printf("4 View Food Menu\n");

    if(loggedIn)
    {
        printf("5 Order Food\n");
    }

    if(loggedIn)
    {
        printf("6 Rate Restaurant\n");
    }

    if(loggedIn)
    {
        printf("7 Order History\n");
        printf("8 Logout\n");
    }

    if(!loggedIn)
    {
        printf("9 Admin Login\n");
    }

    printf("0 Exit\n");

    int choice;
    printf("Enter choice: ");
    scanf("%d",&choice);

    switch(choice)
    {
        case 1:
            if(!loggedIn)
            {
                if(login())
                    loggedIn = 1;
            }
            break;

        case 2:
            if(!loggedIn)
                createAccount();
            break;

        case 3:
            viewRestaurants();
            break;

        case 4:
            viewDishes();
            break;

        case 5:
            if(loggedIn)
                orderFood();
            else
                printf("Login required\n");
            break;

        case 6:
        if(loggedIn)
            printf("Thanks for rating!\n");
            break;

        case 7:
            if(loggedIn)
                showHistory();
            break;

        case 8:
            loggedIn = 0;
            printf("Logged out\n");
            break;

        case 9:
            if(adminLogin())
            {
                adminMenu();
            }
            break;

        case 0:
            return 0;

        default:
            printf("Invalid option\n");
    }
}


}
