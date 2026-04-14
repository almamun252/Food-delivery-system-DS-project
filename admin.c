#include <stdio.h>
#include <string.h>
#include "admin.h"
#include "restaurant.h"
#include "dish.h"
#include "rider.h"

#define ADMIN_USER "admin"
#define ADMIN_PASS "12345"

int adminLogin()
{
char user[50], pass[50];


printf("\n===== ADMIN LOGIN =====\n");

printf("Username: ");
scanf("%s", user);

printf("Password: ");
scanf("%s", pass);

if(strcmp(user, ADMIN_USER) == 0 && strcmp(pass, ADMIN_PASS) == 0)
{
    printf("Login Successful\n");
    return 1;
}

printf("Invalid credentials\n");
return 0;


}

void adminMenu()
{
int choice;


while(1)
{
    printf("\n===== ADMIN PANEL =====\n");
    printf("1 Add Restaurant\n");
    printf("2 Remove Restaurant\n");
    printf("3 View Restaurants\n");
    printf("4 Change Restaurant Location\n");
    printf("5 Add Dish\n");
    printf("6 Delete Dish\n");
    printf("7 View Dishes\n");
    printf("8 Add Rider\n");
    printf("9 View Riders\n");
    printf("10 Logout\n");

    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    switch(choice)
    {
        case 1:
            addRestaurant();
            break;

        case 2:
            removeRestaurant();
            break;

        case 3:
            viewRestaurants();
            break;

        case 4:
        changeRestaurantLocation();
        break;

        case 5:
            addDish();
            break;

        case 6:
            deleteDish();
            break;

        case 7:
            viewDishes();
            break;

        case 8:
            addRider();
            break;

        case 9:
            viewRiders();
            break;

        case 10:
            printf("Logging out from admin panel...\n");
            return;

        default:
            printf("Invalid choice. Try again.\n");
    }
}


}
