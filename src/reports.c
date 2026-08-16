#include "utils.h"
#include "reports.h"
#include "medicine.h"
#include "inventory.h"
#include "sales.h"
#include <stdio.h>

void reportsMenu(void) {
    int choice;
    int running = 1;

    while (running) {
        clearScreen();
        printf("\n----------- REPORTS -----------\n");
        printf("1. Inventory Report\n");
        printf("2. Sales Report\n");
        printf("3. Low Stock Report\n");
        printf("4. Back to Main Menu\n");
        printf("--------------------------------\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            choice = -1;
        }

        switch (choice) {
            case 1: generateInventoryReport(); pauseScreen(); break;
            case 2: generateSalesReport(); pauseScreen(); break;
            case 3: generateLowStockReport(); pauseScreen(); break;
            case 4: running = 0; break;
            default:
                printf("\nInvalid choice. Please try again.\n");
                pauseScreen();
        }
    }
}


void generateInventoryReport(void) {
    printf("\n============ INVENTORY REPORT ============\n");
    viewAllMedicines();   /* reuse - identical behavior needed */
}

void generateLowStockReport(void) {
    printf("\n============ LOW STOCK REPORT ============\n");
    viewLowStockMedicines();   /* reuse - identical behavior needed */
}

void generateSalesReport(void) {

    FILE *fp = fopen(SALES_FILE, "rb");
    if (fp == NULL) {
        printf("\nNo sales records found yet.\n");
        return;
    }

    Sale s;
    int count = 0;
    float totalRevenue = 0.0f;

    printf("\n============================================================================\n");
    printf("                              SALES REPORT\n");
    printf("============================================================================\n");
    printf("%-8s %-6s %-18s %-5s %-10s %-10s %-12s %-12s\n",
           "TxnID", "MedID", "Medicine", "Qty", "Unit Price", "Total", "Date", "Seller");
    printf("----------------------------------------------------------------------------\n");

    while (fread(&s, sizeof(Sale), 1, fp) == 1) {
        printf("%-8s %-6d %-18s %-5d %-10.2f %-10.2f %-12s %-12s\n",
               s.transactionId, s.medicineId, s.medicineName, s.quantitySold,
               s.unitPrice, s.totalAmount, s.date, s.username);
        count++;
        totalRevenue += s.totalAmount;
    }

    fclose(fp);

    printf("----------------------------------------------------------------------------\n");

    if (count == 0) {
        printf("No sales records found.\n");
    } else {
        printf("Total Transactions: %d\n", count);
        printf("Total Revenue: %.2f\n", totalRevenue);
    }

    printf("============================================================================\n");
}
