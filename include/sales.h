#ifndef SALES_H
#define SALES_H

#include "medicine.h"

/* ---------- Constants ---------- */
#define SALES_FILE "data/sales.dat"

/* ---------- Sale Structure ---------- */
typedef struct {
    int medicineId;
    char medicineName[MAX_NAME];
    int quantitySold;
    float totalPrice;
} Sale;

/* ---------- Public Function Prototypes ---------- */

/* Displays the Sales Management menu and routes accordingly.
   Called from main.c after successful login. */
void salesMenu(void);

/* Sells a medicine: finds it by ID, checks stock is sufficient, reduces quantity in medicines.dat, records the sale in sales.dat, and warns if stock becomes low afterward. */
void sellMedicine(void);

#endif
