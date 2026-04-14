#ifndef RIDER_H
#define RIDER_H

#define MAX_RIDERS 20

typedef struct
{
    char name[50];
    char phone[20];
    int node;   
} Rider;

extern Rider riders[MAX_RIDERS];
extern int riderCount;

void loadRiders();
void addRider();
void viewRiders();

#endif