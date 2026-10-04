#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
    SMART CITY MANAGEMENT SYSTEM
    Data Structures Used:
    1. Linked List - Citizen Management
    2. Queue       - Emergency Management
    3. Stack       - Undo Operations
    4. Graph       - City Roads
    5. Tree        - City Structure
*/

/* =========================================================
   LINKED LIST - CITIZEN MANAGEMENT
   ========================================================= */

struct Citizen {
    int id;
    char name[50];
    struct Citizen *next;
};

struct Citizen *head = NULL;

void addCitizen(void)
{
    struct Citizen *newCitizen;

    newCitizen = (struct Citizen *)malloc(sizeof(struct Citizen));

    if (newCitizen == NULL) {
        printf("\nMemory allocation failed!\n");
        return;
    }

    printf("\nEnter Citizen ID: ");
    scanf("%d", &newCitizen->id);

    printf("Enter Citizen Name: ");
    scanf(" %49[^\n]", newCitizen->name);

    newCitizen->next = head;
    head = newCitizen;

    printf("Citizen added successfully!\n");
}

void displayCitizens(void)
{
    struct Citizen *temp = head;

    if (temp == NULL) {
        printf("\nNo citizen records found.\n");
        return;
    }

    printf("\n========== CITIZEN RECORDS ==========\n");

    while (temp != NULL) {
        printf("ID: %d | Name: %s\n", temp->id, temp->name);
        temp = temp->next;
    }

    printf("=====================================\n");
}

/* =========================================================
   QUEUE - EMERGENCY MANAGEMENT
   ========================================================= */

#define MAX_EMERGENCIES 10

char emergency[MAX_EMERGENCIES][100];
int front = 0;
int rear = -1;

void addEmergency(void)
{
    if (rear == MAX_EMERGENCIES - 1) {
        printf("\nEmergency queue is full.\n");
        return;
    }

    rear++;

    printf("\nEnter Emergency/Problem: ");
    scanf(" %99[^\n]", emergency[rear]);

    printf("Emergency added to queue successfully!\n");
}

void handleEmergency(void)
{
    if (front > rear) {
        printf("\nNo emergency requests.\n");
        return;
    }

    printf("\nHandling Emergency: %s\n", emergency[front]);
    front++;

    printf("Emergency handled successfully!\n");
}

/* =========================================================
   STACK - UNDO OPERATION
   ========================================================= */

#define MAX_ACTIONS 10

char actions[MAX_ACTIONS][100];
int top = -1;

void addAction(void)
{
    if (top == MAX_ACTIONS - 1) {
        printf("\nStack is full.\n");
        return;
    }

    top++;

    printf("\nEnter Action: ");
    scanf(" %99[^\n]", actions[top]);

    printf("Action added successfully!\n");
}

void undoAction(void)
{
    if (top == -1) {
        printf("\nNothing to undo.\n");
        return;
    }

    printf("\nUndo Action: %s\n", actions[top]);
    top--;

    printf("Action undone successfully!\n");
}

/* =========================================================
   GRAPH - CITY ROADS
   ========================================================= */

#define AREAS 5

int graph[AREAS][AREAS] = {0};

void addRoad(void)
{
    int a, b;

    printf("\nEnter Area Numbers (0-4): ");
    scanf("%d %d", &a, &b);

    if (a < 0 || a >= AREAS || b < 0 || b >= AREAS) {
        printf("Invalid area number!\n");
        return;
    }

    if (a == b) {
        printf("A road cannot connect an area to itself.\n");
        return;
    }

    graph[a][b] = 1;
    graph[b][a] = 1;

    printf("Road added successfully!\n");
}

void showRoads(void)
{
    int i, j;
    int found = 0;

    printf("\n========== CITY ROADS ==========\n");

    for (i = 0; i < AREAS; i++) {
        for (j = i + 1; j < AREAS; j++) {
            if (graph[i][j] == 1) {
                printf("Area %d <--> Area %d\n", i, j);
                found = 1;
            }
        }
    }

    if (!found) {
        printf("No roads have been added yet.\n");
    }

    printf("================================\n");
}

/* =========================================================
   TREE - CITY STRUCTURE
   ========================================================= */

struct Tree {
    char name[50];
    struct Tree *left;
    struct Tree *right;
};

struct Tree *createNode(const char *name)
{
    struct Tree *node;

    node = (struct Tree *)malloc(sizeof(struct Tree));

    if (node == NULL) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }

    strcpy(node->name, name);
    node->left = NULL;
    node->right = NULL;

    return node;
}

void displayTree(struct Tree *root, int level)
{
    int i;

    if (root == NULL) {
        return;
    }

    for (i = 0; i < level; i++) {
        printf("   ");
    }

    printf("|-- %s\n", root->name);

    displayTree(root->left, level + 1);
    displayTree(root->right, level + 1);
}

void freeTree(struct Tree *root)
{
    if (root == NULL) {
        return;
    }

    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

/* =========================================================
   MAIN FUNCTION
   ========================================================= */

int main(void)
{
    struct Tree *city;
    int choice;

    /* Create the city tree */
    city = createNode("Smart City");

    city->left = createNode("Area A");
    city->right = createNode("Area B");

    city->left->left = createNode("Building 1");
    city->left->right = createNode("Building 2");

    city->right->left = createNode("Building 3");
    city->right->right = createNode("Building 4");

    /* Main Menu */
    do {
        printf("\n\n");
        printf("============================================\n");
        printf("       SMART CITY MANAGEMENT SYSTEM\n");
        printf("============================================\n");
        printf("1. Add Citizen\n");
        printf("2. Display Citizens\n");
        printf("3. Add Emergency\n");
        printf("4. Handle Emergency\n");
        printf("5. Add Action\n");
        printf("6. Undo Action\n");
        printf("7. Add Road\n");
        printf("8. Show Roads\n");
        printf("9. Display City Structure\n");
        printf("0. Exit\n");
        printf("============================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addCitizen();
                break;

            case 2:
                displayCitizens();
                break;

            case 3:
                addEmergency();
                break;

            case 4:
                handleEmergency();
                break;

            case 5:
                addAction();
                break;

            case 6:
                undoAction();
                break;

            case 7:
                addRoad();
                break;

            case 8:
                showRoads();
                break;

            case 9:
                printf("\n========== CITY STRUCTURE ==========\n");
                displayTree(city, 0);
                printf("=====================================\n");
                break;

            case 0:
                printf("\nThank you!\n");
                printf("Smart City Management System\n");
                break;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }

    } while (choice != 0);

    /* Free dynamically allocated memory */
    while (head != NULL) {
        struct Citizen *temp = head;
        head = head->next;
        free(temp);
    }

    freeTree(city);

    return 0;
}
