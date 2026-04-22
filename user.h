#ifndef USER_H
#define USER_H

typedef struct
{
    char name[50];
    char phone[20];
    char password[50];
} User;


extern User *users;
extern int userCount;
extern int userCapacity;

void loadUsers();
void saveUsers();
void createAccount();
int login();

#endif