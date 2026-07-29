#include "inventory.h"
#include <stdio.h>

void viewLowStockMedicines(void) {

    FILE *fp = fopen(MEDICINES_FILE, "rb");
    if (fp == NULL) {
        printf("\nNo medicines found. Please add some first.\n");
        return;
    }

    Medicine m;
    int count = 0;

    printf("\n----- LOW STOCK MEDICINES (Quantity <= %d) -----\n", LOW_STOCK_THRESHOLD);
    printf("%-5s %-20s %-15s %-10s %-10s\n",
           "ID", "Name", "Category", "Price", "Qty");
    printf("----------------------------------------------------------\n");

    while (fread(&m, sizeof(Medicine), 1, fp) == 1) {
        if (checkLowStock(m)) {
            printf("%-5d %-20s %-15s %-10.2f %-10d\n",
                   m.id, m.name, m.category, m.price, m.quantity);
            count++;
        }
    }

    fclose(fp);

    if (count == 0) {
        printf("No medicines are currently low on stock.\n");
    } else {
        printf("\nTotal low stock medicines: %d\n", count);
    }
}

int checkLowStock(Medicine m) {
    if (m.quantity <= LOW_STOCK_THRESHOLD) {
        return 1;
    }
    return 0;
}
