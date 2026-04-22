#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"


FoodNode* createFood(char name[], int price) {

    FoodNode* node = (FoodNode*)malloc(sizeof(FoodNode));
    
    if (node == NULL) {
        printf("Memory allocation failed for new food item!\n");
        return NULL;
    }
    
    strcpy(node->name, name);
    node->price = price;
    node->left = node->right = NULL;
    
    return node;
}


FoodNode* insertFood(FoodNode* root, char name[], int price) {
    if (root == NULL) return createFood(name, price);

    if (strcmp(name, root->name) < 0)
        root->left = insertFood(root->left, name, price);
    else if (strcmp(name, root->name) > 0)
        root->right = insertFood(root->right, name, price);

    return root;
}


void showMenu(FoodNode* root) {
    if (root == NULL) return;
    showMenu(root->left);
    printf("%-15s : %d Tk\n", root->name, root->price);
    showMenu(root->right);
}


void searchFood(FoodNode* root, char name[]) {
    if (root == NULL) {
        printf("Food not found\n");
        return;
    }

    int cmp = strcmp(name, root->name);

    if (cmp == 0)
        printf("Found: %s - %d Tk\n", root->name, root->price);
    else if (cmp < 0)
        searchFood(root->left, name);
    else
        searchFood(root->right, name);
}


void addFood(FoodNode **menu) {
    char name[50];
    int price;

    printf("Food name: ");
    scanf(" %[^\n]", name);

    printf("Price: ");
    scanf("%d", &price);

    *menu = insertFood(*menu, name, price);

    printf("Food added successfully\n");
}


int getFoodPrice(FoodNode* root, char name[]) {
    if (root == NULL)
        return -1;

    int cmp = strcmp(name, root->name);

    if (cmp == 0)
        return root->price;
    else if (cmp < 0)
        return getFoodPrice(root->left, name);
    else
        return getFoodPrice(root->right, name);
}


void freeMenu(FoodNode* root) {
    if (root == NULL) return;
    
    freeMenu(root->left);
    freeMenu(root->right);
    
    free(root);
}