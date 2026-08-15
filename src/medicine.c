#include "inventory.h"
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
        printf("6. View Low Stock Medicines\n");
        printf("7. Back to Main Menu\n");
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
            case 6: viewLowStockMedicines(); break;
            case 7: running = 0; break;
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

    /* Check for duplicate ID before asking for anything else */
    FILE *checkFp = fopen(MEDICINES_FILE, "rb");
    if (checkFp != NULL) {
        Medicine existing;
        while (fread(&existing, sizeof(Medicine), 1, checkFp) == 1) {
            if (existing.id == m.id) {
                printf("Error: Medicine ID %d already exists. Add cancelled.\n", m.id);
                fclose(checkFp);
                return;
            }
        }
        fclose(checkFp);
    }

    printf("Name (e.g. Finix 20mg): ");
    scanf(" %50[^\n]", m.name);
    printf("Generic Name (e.g. Rabeprazole Sodium): ");
    scanf(" %50[^\n]", m.genericName);
    printf("Category (e.g. Tablet, Capsule, Syrup): ");
    scanf(" %30[^\n]", m.category);
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

    printf("\n%-5s %-18s %-20s %-12s %-10s %-6s\n",
           "ID", "Name", "Generic Name", "Category", "Price", "Qty");
    printf("--------------------------------------------------------------------------\n");

    while (fread(&m, sizeof(Medicine), 1, fp) == 1) {
        printf("%-5d %-18s %-20s %-12s %-10.2f %-6d\n",
               m.id, m.name, m.genericName, m.category, m.price, m.quantity);
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

    printf("\n%-5s %-18s %-20s %-12s %-10s %-6s\n",
           "ID", "Name", "Generic Name", "Category", "Price", "Qty");
    printf("--------------------------------------------------------------------------\n");

    if (choice == 1) {
        int searchId;
        printf("Enter Medicine ID: ");
        scanf("%d", &searchId);

        while (fread(&m, sizeof(Medicine), 1, fp) == 1) {
            if (m.id == searchId) {
                printf("%-5d %-18s %-20s %-12s %-10.2f %-6d\n",
                       m.id, m.name, m.genericName, m.category, m.price, m.quantity);
                found = 1;
                break;
            }
        }

    } else if (choice == 2) {
        char searchName[MAX_NAME];
        printf("Enter Medicine Name (or part of it): ");
        scanf(" %50[^\n]", searchName);

        while (fread(&m, sizeof(Medicine), 1, fp) == 1) {
            if (strstr(m.name, searchName) != NULL) {
                printf("%-5d %-18s %-20s %-12s %-10.2f %-6d\n",
                       m.id, m.name, m.genericName, m.category, m.price, m.quantity);
                found = 1;
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

/* Lets the user find a medicine by ID or by (partial) name.
   Used by updateMedicine(), deleteMedicine(), and sellMedicine(). */
int resolveMedicineId(void) {

    int searchChoice;
    printf("\nFind medicine by:\n");
    printf("1. Medicine ID\n");
    printf("2. Medicine Name\n");
    printf("Enter your choice: ");
    scanf("%d", &searchChoice);

    if (searchChoice == 1) {
        int id;
        printf("Enter Medicine ID: ");
        scanf("%d", &id);
        return id;
    }

    if (searchChoice != 2) {
        printf("Invalid choice.\n");
        return -1;
    }

    char searchName[MAX_NAME];
    printf("Enter Medicine Name (or part of it): ");
    scanf(" %50[^\n]", searchName);

    FILE *fp = fopen(MEDICINES_FILE, "rb");
    if (fp == NULL) {
        printf("No medicines found. Please add some first.\n");
        return -1;
    }

    Medicine matches[100];
    int matchCount = 0;
    Medicine m;

    while (fread(&m, sizeof(Medicine), 1, fp) == 1) {
        if (strstr(m.name, searchName) != NULL && matchCount < 100) {
            matches[matchCount] = m;
            matchCount++;
        }
    }
    fclose(fp);

    if (matchCount == 0) {
        printf("No medicine found matching \"%s\".\n", searchName);
        return -1;
    }

    if (matchCount == 1) {
        return matches[0].id;
    }

    /* Multiple matches - show them, ask the user to pick one */
    printf("\nMultiple medicines matched:\n");
    printf("%-5s %-18s %-6s\n", "ID", "Name", "Qty");
    printf("----------------------------------\n");
    for (int i = 0; i < matchCount; i++) {
        printf("%-5d %-18s %-6d\n",
               matches[i].id, matches[i].name, matches[i].quantity);
    }

    int chosenId;
    printf("Enter the exact Medicine ID from the list above: ");
    scanf("%d", &chosenId);

    for (int i = 0; i < matchCount; i++) {
        if (matches[i].id == chosenId) {
            return chosenId;
        }
    }

    printf("That ID was not in the list. Cancelled.\n");
    return -1;
}

void updateMedicine(void) {

    if (currentUserRole == 'S') {
        char adminPass[MAX_PASSWORD];
        printf("\nStaff must enter Admin password to update medicine.\n");
        printf("Admin password: ");
        scanf("%s", adminPass);

        if (!verifyAdminPassword(adminPass)) {
            printf("Incorrect admin password. Update cancelled.\n");
            return;
        }
    }

    int searchId = resolveMedicineId();
    if (searchId == -1) {
        return;
    }

    FILE *fp = fopen(MEDICINES_FILE, "r+b");
    if (fp == NULL) {
        printf("\nNo medicines found. Please add some first.\n");
        return;
    }

    Medicine m;
    int found = 0;

    while (fread(&m, sizeof(Medicine), 1, fp) == 1) {
        if (m.id == searchId) {
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("No medicine found with that ID.\n");
        fclose(fp);
        return;
    }

    printf("\nCurrent details:\n");
    printf("ID: %d | Name: %s | Generic: %s | Category: %s | Price: %.2f | Quantity: %d\n",
           m.id, m.name, m.genericName, m.category, m.price, m.quantity);

    int fieldChoice;
    printf("\nWhat do you want to update?\n");
    printf("1. Medicine ID\n");
    printf("2. Name\n");
    printf("3. Generic Name\n");
    printf("4. Category\n");
    printf("5. Price\n");
    printf("6. Quantity\n");
    printf("Enter your choice: ");
    scanf("%d", &fieldChoice);

    switch (fieldChoice) {
        case 1: {
            int newId;
            printf("New Medicine ID: ");
            scanf("%d", &newId);

            if (newId == m.id) {
                /* No actual change, skip the duplicate check */
                break;
            }

            /* Check the new ID isn't already used by another medicine.
               We scan a SEPARATE read-only handle here, since fp is positioned mid-file for the eventual fseek/fwrite below, and we don't want to disturb that position. */
            FILE *checkFp = fopen(MEDICINES_FILE, "rb");
            if (checkFp != NULL) {
                Medicine other;
                while (fread(&other, sizeof(Medicine), 1, checkFp) == 1) {
                    if (other.id == newId) {
                        printf("Error: Medicine ID %d is already in use. Update cancelled.\n", newId);
                        fclose(checkFp);
                        fclose(fp);
                        return;
                    }
                }
                fclose(checkFp);
            }

            m.id = newId;
            break;
        }
        case 2:
            printf("New name: ");
            scanf(" %50[^\n]", m.name);
            break;
        case 3:
            printf("New generic name: ");
            scanf(" %50[^\n]", m.genericName);
            break;
        case 4:
            printf("New category: ");
            scanf(" %30[^\n]", m.category);
            break;
        case 5:
            printf("New price: ");
            scanf("%f", &m.price);
            break;
        case 6:
            printf("New quantity: ");
            scanf("%d", &m.quantity);
            break;
        default:
            printf("Invalid choice. Update cancelled.\n");
            fclose(fp);
            return;
    }

    fseek(fp, -(long)sizeof(Medicine), SEEK_CUR);
    fwrite(&m, sizeof(Medicine), 1, fp);

    fclose(fp);
    printf("\nMedicine updated successfully.\n");
}

void deleteMedicine(void) {

    if (currentUserRole == 'S') {
        char adminPass[MAX_PASSWORD];
        printf("\nStaff must enter Admin password to delete medicine.\n");
        printf("Admin password: ");
        scanf("%s", adminPass);

        if (!verifyAdminPassword(adminPass)) {
            printf("Incorrect admin password. Delete cancelled.\n");
            return;
        }
    }

    int searchId = resolveMedicineId();
    if (searchId == -1) {
        return;
    }

    FILE *fp = fopen(MEDICINES_FILE, "rb");
    if (fp == NULL) {
        printf("\nNo medicines found. Please add some first.\n");
        return;
    }

    FILE *tempFp = fopen("data/temp.dat", "wb");
    if (tempFp == NULL) {
        printf("Error: could not create temporary file.\n");
        fclose(fp);
        return;
    }

    Medicine m;
    int found = 0;

    while (fread(&m, sizeof(Medicine), 1, fp) == 1) {
        if (m.id == searchId) {
            found = 1;
            continue;
        }
        fwrite(&m, sizeof(Medicine), 1, tempFp);
    }

    fclose(fp);
    fclose(tempFp);

    if (!found) {
        printf("No medicine found with that ID.\n");
        remove("data/temp.dat");
        return;
    }

    remove(MEDICINES_FILE);
    rename("data/temp.dat", MEDICINES_FILE);

    printf("\nMedicine deleted successfully.\n");
}
