#ifndef INVENTORY_H
#define INVENTORY_H

#include "medicine.h"

/* ---------- Constants ---------- */
#define LOW_STOCK_THRESHOLD 3

/* ---------- Public Function Prototypes ---------- */

/* Scans medicines.dat and prints only medicines whose quantity is at or below LOW_STOCK_THRESHOLD. */
void viewLowStockMedicines(void);

/* Checks a single Medicine record and returns:
     1 -> quantity is at or below the threshold (low stock)
     0 -> quantity is fine
   Used by Sales Management after a sale reduces stock. */
int checkLowStock(Medicine m);

#endif
