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
    printf("\n[Search Medicine] - Under development.\n");
}

void updateMedicine(void) {
    printf("\n[Update Medicine] - Under development.\n");
}

void deleteMedicine(void) {
    printf("\n[Delete Medicine] - Under development.\n");
}
