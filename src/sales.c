#include "utils.h"
#include "sales.h"
#include "inventory.h"
#include "auth.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

void salesMenu(void) {
    int choice;
    int running = 1;

    while (running) {
        clearScreen();
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
            case 1: sellMedicine(); pauseScreen(); break;
            case 2: running = 0; break;
            default:
                printf("\nInvalid choice. Please try again.\n");
                pauseScreen();
        }
    }
}

/* Generates the next transaction ID by counting existing records in sales.dat. Returns e.g. "TXN001", "TXN002"... */
void generateTransactionId(char *outId) {

    FILE *fp = fopen(SALES_FILE, "rb");
    int recordCount = 0;

    if (fp != NULL) {
        fseek(fp, 0, SEEK_END);
        long fileSize = ftell(fp);
        recordCount = fileSize / sizeof(Sale);
        fclose(fp);
    }

    sprintf(outId, "TXN%03d", recordCount + 1);
}

/* Fills outDate with today's date in "Aug-14-2026" format. */
void getCurrentDate(char *outDate) {
    time_t now = time(NULL);
    struct tm *localTime = localtime(&now);
    strftime(outDate, MAX_DATE, "%b-%d-%Y", localTime);
}

void sellMedicine(void) {

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

    printf("Medicine: %s | Available Stock: %d | Unit Price: %.2f\n",
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

    /* Build the sale record */
    Sale s;

    generateTransactionId(s.transactionId);
    s.medicineId = m.id;
    strcpy(s.medicineName, m.name);
    s.quantitySold = qtyToSell;
    s.unitPrice = m.price;
    s.totalAmount = qtyToSell * m.price;
    getCurrentDate(s.date);
    strcpy(s.username, currentUsername);

    FILE *salesFp = fopen(SALES_FILE, "ab");
    if (salesFp == NULL) {
        printf("Warning: sale completed but could not be recorded in sales log.\n");
    } else {
        fwrite(&s, sizeof(Sale), 1, salesFp);
        fclose(salesFp);
    }

    printf("\nSale successful. Transaction ID: %s\n", s.transactionId);
    printf("%d unit(s) of %s sold for %.2f total. Date: %s\n",
           qtyToSell, m.name, s.totalAmount, s.date);

    if (checkLowStock(m)) {
        printf("Warning: %s is now low on stock (%d remaining).\n",
               m.name, m.quantity);
    }
}
