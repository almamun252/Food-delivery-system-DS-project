#ifndef LOCATION_H
#define LOCATION_H

#define MAX_LOCATIONS 20

typedef struct
{
    char name[50];
} Location;

extern Location locations[MAX_LOCATIONS];
extern int locationCount;

void loadLocations();
void viewLocations();

void loadGraph();
int getDistance(int src,int dest);

#endif