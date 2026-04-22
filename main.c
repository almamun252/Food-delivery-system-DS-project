//gcc *.c -o foodapp
//.\foodapp.exe 

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
    printf("4 View Top Rated Restaurants\n"); 
    printf("5 View Food Menu\n");

    if(loggedIn)
    {
        printf("6 Order Food\n");
        printf("7 Rate Restaurant\n");
        printf("8 Order History\n");
        printf("9 Logout\n");
    }

    if(!loggedIn)
    {
        printf("10 Admin Login\n");
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
            showTopRestaurants();   
                break;
        case 5:
            viewDishes();
            break;

        case 6:
            if(loggedIn)
                orderFood();
            else
                printf("Login required\n");
            break;
            
        case 7:
            if(loggedIn)
                rateRestaurant();
            else
                printf("Login required\n");
            break;

        case 8:
            if(loggedIn)
                showHistory();
            else
                printf("Login required\n");
            break;

        case 9:
            if(loggedIn)
            {
                loggedIn = 0;
                printf("Logged out\n");
            }
            break;

        case 10:
            if(!loggedIn)
            {
                if(adminLogin())
                    adminMenu();
            }
            break;

        case 0:
            printf("Exiting program...\n");
            return 0;

        default:
            printf("Invalid option\n");
    }
}


}
