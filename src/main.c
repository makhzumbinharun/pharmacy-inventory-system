#include "auth.h"
#include "medicine.h"
#include <stdio.h>

/* ---------- Function Prototypes ---------- */
/* main.c only needs to know these functions exist.
   Their real implementation will move into separate
   modules later (auth.c, medicine.c, etc.) */
void displayWelcomeScreen();
int  displayMainMenu();
void loginMenu();

int main() {
    initializeAuthFile();
    displayWelcomeScreen();

    int choice;
    int running = 1;

    while (running) {

        choice = displayMainMenu();

        switch (choice) {
            case 1:
                loginMenu();
                break;

            case 2:
                printf("\nThank you for using Pharmacy Inventory Management System.\n");
                printf("Exiting program...\n");
                running = 0;
                break;

            default:
                printf("\nInvalid choice. Please enter 1 or 2.\n");
        }
    }

    return 0;
}

/* ---------- Function Definitions ---------- */

void displayWelcomeScreen() {
    printf("=========================================\n");
    printf("   PHARMACY INVENTORY MANAGEMENT SYSTEM\n");
    printf("=========================================\n");
    printf("Developed by Team Three Knights\n");
    printf("BUBT - Department of CSE\n");
}

int displayMainMenu() {
    int choice;

    printf("\n----------- MAIN MENU -----------\n");
    printf("1. Login\n");
    printf("2. Exit\n");
    printf("----------------------------------\n");
    printf("Enter your choice: ");

    if (scanf("%d", &choice) != 1) {
        /* User typed something that is not a number.
           We must clear it out of the input buffer,
           otherwise the program will loop forever. */
        while (getchar() != '\n');
        return -1;
    }

    return choice;
}

void loginMenu() {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];

    printf("\n[Login]\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    int result = authenticateUser(username, password);

    if (result == 1) {
        printf("\nLogin successful. Welcome, Admin.\n");
        medicineMenu();
    } else if (result == 2) {
        printf("\nLogin successful. Welcome, Staff.\n");
        medicineMenu();
    } else {
        printf("\nLogin failed. Invalid username or password.\n");
    }
}
