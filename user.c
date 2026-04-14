#include <stdio.h>
#include <string.h>
#include "user.h"

User users[MAX_USERS];
int userCount = 0;

/* -------- LOAD USERS -------- */

void loadUsers()
{
FILE *fp = fopen("users.txt","r");


if(fp == NULL)
    return;

while(fscanf(fp,"%[^|]|%[^|]|%[^\n]\n",
    users[userCount].name,
    users[userCount].phone,
    users[userCount].password) == 3)
{
    userCount++;
}

fclose(fp);


}

/* -------- SAVE USERS -------- */

void saveUsers()
{
FILE *fp = fopen("users.txt","w");


if(fp == NULL)
    return;

for(int i=0;i<userCount;i++)
{
    fprintf(fp,"%s|%s|%s\n",
        users[i].name,
        users[i].phone,
        users[i].password);
}

fclose(fp);


}

/* -------- CREATE ACCOUNT -------- */

void createAccount()
{
if(userCount >= MAX_USERS)
{
printf("User limit reached\n");
return;
}


printf("\n===== CREATE ACCOUNT =====\n");

printf("Enter username: ");
scanf(" %[^\n]", users[userCount].name);

printf("Enter phone number: ");
scanf("%s", users[userCount].phone);

printf("Enter password: ");
scanf("%s", users[userCount].password);

userCount++;

saveUsers();

printf("Account created successfully\n");


}

/* -------- LOGIN -------- */

int login()
{
char input[50], pass[50];


printf("\n===== LOGIN =====\n");

printf("Enter username or phone: ");
scanf("%s", input);

printf("Enter password: ");
scanf("%s", pass);

for(int i=0;i<userCount;i++)
{
    if((strcmp(users[i].name,input) == 0 ||
        strcmp(users[i].phone,input) == 0) &&
        strcmp(users[i].password,pass) == 0)
    {
        printf("Login successful\n");
        return 1;
    }
}

printf("Invalid credentials\n");
return 0;


}
