#include "reports.h"
#include "sales.h"
#include "auth.h"
#include "medicine.h"
#include "utils.h"
#include <stdio.h>

/* ---------- Function Prototypes ---------- */
/* Prototypes for main.c's own functions - the actual business logic (auth, medicine, sales, reports) lives in their own modules, included above. */
void displayWelcomeScreen();
int  displayMainMenu();
void loginMenu();

int main() {
    initializeAuthFile();
    displayWelcomeScreen();
    pauseScreen();

    int choice;
    int running = 1;

    while (running) {

        choice = displayMainMenu();

        switch (choice) {
            case 1:
                loginMenu();
                break;

            case 2:
                clearScreen();
                printf("\nThank you for using Pharmacy Inventory Management System.\n");
                printf("Exiting program...\n");
                running = 0;
                break;

            default:
                printf("\nInvalid choice. Please enter 1 or 2.\n");
                pauseScreen();
        }
    }

    return 0;
}

/* ---------- Function Definitions ---------- */

void displayWelcomeScreen() {
    clearScreen();
    printCentered("=========================================");
    printCentered("PHARMACY INVENTORY MANAGEMENT SYSTEM");
    printCentered("=========================================");
    printCentered("Developed by Team Three Knights");
    printCentered("BUBT - Department of CSE");
}

int displayMainMenu() {
    int choice;

    clearScreen();
    printf("\n----------- MAIN MENU -----------\n");
    printf("1. Login\n");
    printf("2. Exit\n");
    printf("----------------------------------\n");
    printf("Enter your choice: ");

    if (scanf("%d", &choice) != 1) {
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

    if (result == 1 || result == 2) {
        printf("\nLogin successful. Welcome, %s.\n", result == 1 ? "Admin" : "Staff");
        pauseScreen();

        int hubChoice;
        int hubRunning = 1;

        while (hubRunning) {
            clearScreen();
            printf("\n----------- DASHBOARD -----------\n");
            printf("1. Medicine Management\n");
            printf("2. Sales Management\n");
            printf("3. Reports\n");
            if (currentUserRole == 'A') {
                printf("4. Register New User\n");
            }
            printf("5. Logout\n");
            printf("----------------------------------\n");
            printf("Enter your choice: ");

            if (scanf("%d", &hubChoice) != 1) {
                while (getchar() != '\n');
                hubChoice = -1;
            }

            switch (hubChoice) {
                case 1: medicineMenu(); break;
                case 2: salesMenu(); break;
                case 3: reportsMenu(); break;
                case 4:
                    if (currentUserRole == 'A') {
                        registerUser();
                    } else {
                        printf("\nInvalid choice. Please try again.\n");
                    }
                    pauseScreen();
                    break;
                case 5: hubRunning = 0; break;
                default:
                    printf("\nInvalid choice. Please try again.\n");
                    pauseScreen();
            }
        }

    } else {
        printf("\nLogin failed. Invalid username or password.\n");
        pauseScreen();
    }
}
