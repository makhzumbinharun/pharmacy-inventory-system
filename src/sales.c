#include "sales.h"
#include "inventory.h"
#include <stdio.h>
#include <string.h>

void salesMenu(void) {
    int choice;
    int running = 1;

    while (running) {
        printf("\n--------- SALES MANAGEMENT ---------\n");
        printf("1. Sell Medicine\n");
        printf("2. Back to Main Menu\n");
        printf("-------------------------------------\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            choice = -1;
        }

        switch (choice) {
            case 1: sellMedicine(); break;
            case 2: running = 0; break;
            default: printf("\nInvalid choice. Please try again.\n");
        }
    }
}

void sellMedicine(void) {

    FILE *fp = fopen(MEDICINES_FILE, "r+b");
    if (fp == NULL) {
        printf("\nNo medicines found. Please add some first.\n");
        return;
    }

    int searchId;
    printf("\nEnter Medicine ID to sell: ");
    scanf("%d", &searchId);

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

    printf("Medicine: %s | Available Stock: %d | Price: %.2f\n",
           m.name, m.quantity, m.price);

    int qtyToSell;
    printf("Enter quantity to sell: ");
    scanf("%d", &qtyToSell);

    if (qtyToSell <= 0) {
        printf("Invalid quantity.\n");
        fclose(fp);
        return;
    }

    if (qtyToSell > m.quantity) {
        printf("Not enough stock. Only %d units available.\n", m.quantity);
        fclose(fp);
        return;
    }

    /* Reduce stock and write it back in place */
    m.quantity -= qtyToSell;
    fseek(fp, -(long)sizeof(Medicine), SEEK_CUR);
    fwrite(&m, sizeof(Medicine), 1, fp);
    fclose(fp);

    /* Record the transaction */
    Sale s;
    s.medicineId = m.id;
    strcpy(s.medicineName, m.name);
    s.quantitySold = qtyToSell;
    s.totalPrice = qtyToSell * m.price;

    FILE *salesFp = fopen(SALES_FILE, "ab");
    if (salesFp == NULL) {
        printf("Warning: sale completed but could not be recorded in sales log.\n");
    } else {
        fwrite(&s, sizeof(Sale), 1, salesFp);
        fclose(salesFp);
    }

    printf("\nSale successful. %d unit(s) of %s sold for %.2f total.\n",
           qtyToSell, m.name, s.totalPrice);

    if (checkLowStock(m)) {
        printf("Warning: %s is now low on stock (%d remaining).\n",
               m.name, m.quantity);
    }
}
