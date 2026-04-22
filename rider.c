#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "rider.h"
#include "location.h"


Rider *riders = NULL;
int riderCount = 0;
int riderCapacity = 0;

void loadRiders()
{
    FILE *fp = fopen("riders.txt","r");

    if(fp == NULL)
        return;

    char tempName[50], tempPhone[20];
    int tempNode;

    while(fscanf(fp,"%[^|]|%[^|]|%d\n", tempName, tempPhone, &tempNode) == 3)
    {
        if(riderCount >= riderCapacity)
        {
            riderCapacity = (riderCapacity == 0) ? 5 : riderCapacity * 2;
            riders = (Rider*)realloc(riders, riderCapacity * sizeof(Rider));
            
            if(riders == NULL)
            {
                printf("Memory allocation failed during loading riders!\n");
                fclose(fp);
                return;
            }
        }

        strcpy(riders[riderCount].name, tempName);
        strcpy(riders[riderCount].phone, tempPhone);
        riders[riderCount].node = tempNode;

        riderCount++;
    }

    fclose(fp);
}

void addRider()
{
  
    if(riderCount >= riderCapacity)
    {
        riderCapacity = (riderCapacity == 0) ? 5 : riderCapacity * 2;
        riders = (Rider*)realloc(riders, riderCapacity * sizeof(Rider));
        
        if(riders == NULL)
        {
            printf("Memory allocation failed! Cannot add rider.\n");
            return;
        }
    }

    printf("\n===== ADD RIDER =====\n");

    printf("Enter rider name: ");
    scanf(" %[^\n]", riders[riderCount].name);

    printf("Enter phone number: ");
    scanf("%s", riders[riderCount].phone);

    if(locationCount <= 1)
    {
        printf("Location list empty\n");
        return;
    }

    printf("\nSelect Rider Location\n");

    for(int i=1; i<locationCount; i++)
        printf("%d. %s\n", i, locations[i].name);

    int loc;

    printf("Enter location choice: ");
    scanf("%d",&loc);

    if(loc < 1 || loc >= locationCount)
    {
        printf("Invalid location\n");
        return;
    }

    riders[riderCount].node = loc;

   
    FILE *fp = fopen("riders.txt","a");

    if(fp != NULL)
    {
        fprintf(fp,"\n%s|%s|%d",
                riders[riderCount].name,
                riders[riderCount].phone,
                riders[riderCount].node);

        fclose(fp);
    }

    riderCount++;

    printf("Rider added successfully\n");
}

void viewRiders()
{
    printf("\n===== RIDER LIST =====\n");

    if(riderCount == 0)
    {
        printf("No riders available\n");
        return;
    }

    for(int i=0; i<riderCount; i++)
    {
        printf("%d. %s (%s) - %s\n",
               i+1,
               riders[i].name,
               riders[i].phone,
               locations[riders[i].node].name);
    }
}