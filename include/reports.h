#ifndef REPORTS_H
#define REPORTS_H

/* ---------- Public Function Prototypes ---------- */

/* Displays the Reports menu and routes to the correct report below. Called from main.c's hub menu. */
void reportsMenu(void);

/* Reads medicines.dat and prints every medicine with its current stock level. */
void generateInventoryReport(void);

/* Reads sales.dat and prints every past sale with full transaction details. */
void generateSalesReport(void);

/* Reads medicines.dat and prints only medicines at or below LOW_STOCK_THRESHOLD. Reuses checkLowStock() from inventory.c. */
void generateLowStockReport(void);

#endif
