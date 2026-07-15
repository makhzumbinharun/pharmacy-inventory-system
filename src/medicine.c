#include "medicine.h"
#include "auth.h"
#include <stdio.h>
#include <string.h>

void medicineMenu(void) {
    int choice;
    int running = 1;

    while (running) {
        printf("\n------- MEDICINE MANAGEMENT -------\n");
        printf("1. Add Medicine\n");
        printf("2. View All Medicines\n");
        printf("3. Search Medicine\n");
        printf("4. Update Medicine\n");
        printf("5. Delete Medicine\n");
        printf("6. Back to Main Menu\n");
        printf("------------------------------------\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            choice = -1;
        }

        switch (choice) {
            case 1: addMedicine(); break;
            case 2: viewAllMedicines(); break;
            case 3: searchMedicine(); break;
            case 4: updateMedicine(); break;
            case 5: deleteMedicine(); break;
            case 6: running = 0; break;
            default: printf("\nInvalid choice. Please try again.\n");
        }
    }
}

void addMedicine(void) {

    if (currentUserRole == 'S') {
        char adminPass[MAX_PASSWORD];
        printf("\nStaff must enter Admin password to add medicine.\n");
        printf("Admin password: ");
        scanf("%s", adminPass);

        if (!verifyAdminPassword(adminPass)) {
            printf("Incorrect admin password. Add medicine cancelled.\n");
            return;
        }
    }

    Medicine m;

    printf("\n--- Add New Medicine ---\n");
    printf("Medicine ID: ");
    scanf("%d", &m.id);
    printf("Name: ");
    scanf("%s", m.name);
    printf("Category: ");
    scanf("%s", m.category);
    printf("Price: ");
    scanf("%f", &m.price);
    printf("Quantity: ");
    scanf("%d", &m.quantity);

    FILE *fp = fopen(MEDICINES_FILE, "ab");
    if (fp == NULL) {
        perror("fopen failed");
        return;
    }

    fwrite(&m, sizeof(Medicine), 1, fp);
    fclose(fp);

    printf("\nMedicine added successfully.\n");
}

void viewAllMedicines(void) {

    FILE *fp = fopen(MEDICINES_FILE, "rb");
    if (fp == NULL) {
        printf("\nNo medicines found. Please add some first.\n");
        return;
    }

    Medicine m;
    int count = 0;

    printf("\n%-5s %-20s %-15s %-10s %-10s\n",
           "ID", "Name", "Category", "Price", "Qty");
    printf("----------------------------------------------------------\n");

    while (fread(&m, sizeof(Medicine), 1, fp) == 1) {
        printf("%-5d %-20s %-15s %-10.2f %-10d\n",
               m.id, m.name, m.category, m.price, m.quantity);
        count++;
    }

    fclose(fp);

    if (count == 0) {
        printf("No medicine records found.\n");
    } else {
        printf("\nTotal medicines: %d\n", count);
    }
}

void searchMedicine(void) {

    FILE *fp = fopen(MEDICINES_FILE, "rb");
    if (fp == NULL) {
        printf("\nNo medicines found. Please add some first.\n");
        return;
    }

    int choice;
    printf("\nSearch by:\n");
    printf("1. Medicine ID\n");
    printf("2. Medicine Name\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    Medicine m;
    int found = 0;

    printf("\n%-5s %-20s %-15s %-10s %-10s\n",
           "ID", "Name", "Category", "Price", "Qty");
    printf("----------------------------------------------------------\n");

    if (choice == 1) {
        int searchId;
        printf("Enter Medicine ID: ");
        scanf("%d", &searchId);

        while (fread(&m, sizeof(Medicine), 1, fp) == 1) {
            if (m.id == searchId) {
                printf("%-5d %-20s %-15s %-10.2f %-10d\n",
                       m.id, m.name, m.category, m.price, m.quantity);
                found = 1;
                break;   /* IDs are unique, no need to keep searching */
            }
        }

    } else if (choice == 2) {
        char searchName[MAX_NAME];
        printf("Enter Medicine Name (or part of it): ");
        scanf("%s", searchName);

        while (fread(&m, sizeof(Medicine), 1, fp) == 1) {
            if (strstr(m.name, searchName) != NULL) {
                printf("%-5d %-20s %-15s %-10.2f %-10d\n",
                       m.id, m.name, m.category, m.price, m.quantity);
                found = 1;
                /* no break - a name search may match multiple records */
            }
        }

    } else {
        printf("Invalid choice.\n");
        fclose(fp);
        return;
    }

    fclose(fp);

    if (!found) {
        printf("No matching medicine found.\n");
    }
}

void updateMedicine(void) {
    printf("\n[Update Medicine] - Under development.\n");
}

void deleteMedicine(void) {
    printf("\n[Delete Medicine] - Under development.\n");
}
