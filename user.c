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

/* USERNAME */

printf("Enter username: ");
scanf(" %[^\n]", users[userCount].name);

/* PHONE NUMBER VALIDATION */

char phone[20];
int valid;

while(1)
{
    printf("Enter phone number (11 digits): ");
    scanf("%s", phone);

    valid = 1;

    if(strlen(phone) != 11)
        valid = 0;

    for(int i=0;i<strlen(phone);i++)
    {
        if(phone[i] < '0' || phone[i] > '9')
        {
            valid = 0;
            break;
        }
    }

    if(!valid)
    {
        printf("Invalid phone number. Must be 11 digits.\n");
        continue;
    }

    /* Duplicate check */

    int duplicate = 0;

    for(int i=0;i<userCount;i++)
    {
        if(strcmp(users[i].phone, phone) == 0)
        {
            duplicate = 1;
            break;
        }
    }

    if(duplicate)
    {
        printf("Phone number already registered\n");
        continue;
    }

    break;
}

strcpy(users[userCount].phone, phone);


/* PASSWORD VALIDATION */

char password[50];

while(1)
{
    printf("Enter password (numbers only, min 4 digits): ");
    scanf("%s", password);

    valid = 1;

    if(strlen(password) < 4)
        valid = 0;

    for(int i=0;i<strlen(password);i++)
    {
        if(password[i] < '0' || password[i] > '9')
        {
            valid = 0;
            break;
        }
    }

    if(!valid)
    {
        printf("Invalid password. Only numbers allowed (min 4 digits).\n");
        continue;
    }

    break;
}

strcpy(users[userCount].password, password);

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
