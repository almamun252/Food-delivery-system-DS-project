#ifndef USER_H
#define USER_H

#define MAX_USERS 100

typedef struct
{
    char name[50];
    char phone[20];
    char password[50];
} User;

extern User users[MAX_USERS];
extern int userCount;

void loadUsers();
void saveUsers();
void createAccount();
int login();

#endif