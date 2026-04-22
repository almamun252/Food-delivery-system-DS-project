#ifndef LOCATION_H
#define LOCATION_H

typedef struct
{
    char name[50];
} Location;


extern Location *locations;
extern int locationCount;
extern int locationCapacity;

void loadLocations();
void viewLocations();

void loadGraph();
int getDistance(int src,int dest);

#endif