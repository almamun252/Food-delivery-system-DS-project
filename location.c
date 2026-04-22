#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "location.h"


Location *locations = NULL;
int locationCount = 0;
int locationCapacity = 0;

void loadLocations()
{
    FILE *fp = fopen("locations.txt","r");

    if(fp == NULL)
    {
        printf("locations.txt not found\n");
        return;
    }

    char tempName[50];
    
    
    while(fgets(tempName, 50, fp))
    {
        
        tempName[strcspn(tempName, "\n")] = 0;

        
        if(locationCount >= locationCapacity)
        {
            locationCapacity = (locationCapacity == 0) ? 5 : locationCapacity * 2;
            locations = (Location*)realloc(locations, locationCapacity * sizeof(Location));
            
            if(locations == NULL)
            {
                printf("Memory allocation failed for locations!\n");
                fclose(fp);
                return;
            }
        }

        strcpy(locations[locationCount].name, tempName);
        locationCount++;
    }

    fclose(fp);
}

void viewLocations()
{
    printf("\n===== DELIVERY LOCATION =====\n");

    if(locationCount <= 1)
    {
        printf("No locations available\n");
        return;
    }

    for(int i=1; i<locationCount; i++)
        printf("%d %s\n", i, locations[i].name);

    printf("0 Back\n");
}