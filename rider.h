#ifndef RIDER_H
#define RIDER_H

typedef struct
{
    char name[50];
    char phone[20];
    int node;   
} Rider;

extern Rider *riders;
extern int riderCount;
extern int riderCapacity;

void loadRiders();
void addRider();
void viewRiders();

#endif