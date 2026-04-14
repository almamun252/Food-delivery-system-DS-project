
#include <stdio.h>
#include <string.h>
#include "user.h"

int login(){

    char username[50],password[50];
    char u[50],p[50];

    FILE *fp=fopen("users.txt","r");

    if(fp==NULL){
        printf("No users found. Create account first.\n");
        return 0;
    }

    printf("Username: ");
    scanf("%s",username);

    printf("Password: ");
    scanf("%s",password);

    while(fscanf(fp,"%s %s",u,p)!=EOF){

        if(strcmp(username,u)==0 && strcmp(password,p)==0){
            fclose(fp);
            printf("Login successful\n");
            return 1;
        }
    }

    fclose(fp);
    printf("Invalid login\n");
    return 0;
}

void createAccount(){

    char u[50],p[50];

    FILE *fp=fopen("users.txt","a");

    printf("New username: ");
    scanf("%s",u);

    printf("New password: ");
    scanf("%s",p);

    fprintf(fp,"%s %s\n",u,p);

    fclose(fp);

    printf("Account created successfully\n");
}
