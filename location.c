#include <stdio.h>
#include <string.h>
#include "location.h"

Location locations[MAX_LOCATIONS];
int locationCount = 0;

void loadLocations()
{
    FILE *fp = fopen("locations.txt","r");

    if(fp == NULL)
    {
        printf("locations.txt not found\n");
        return;
    }

    while(fgets(locations[locationCount].name,50,fp))
    {
        locations[locationCount].name[strcspn(locations[locationCount].name,"\n")] = 0;
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

    for(int i=1;i<locationCount;i++)
        printf("%d %s\n",i,locations[i].name);

    printf("0 Back\n");
}