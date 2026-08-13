#ifndef SALES_H
#define SALES_H

#include "medicine.h"

/* ---------- Constants ---------- */
#define SALES_FILE "data/sales.dat"
#define MAX_TRANSACTION_ID 8   /* "TXN001" + null terminator, room to grow */
#define MAX_DATE 12           /* "Aug-14-2026" + null terminator */

/* ---------- Sale Structure ---------- */
typedef struct {
    char transactionId[MAX_TRANSACTION_ID];
    int medicineId;
    char medicineName[MAX_NAME];
    int quantitySold;
    float unitPrice;
    float totalAmount;
    char date[MAX_DATE];
    char username[MAX_USERNAME];
} Sale;

/* ---------- Public Function Prototypes ---------- */

void salesMenu(void);
/* Sells a medicine: finds it by ID, checks stock is sufficient, reduces quantity in medicines.dat, records the sale in sales.dat, and warns if stock becomes low afterward. */
void sellMedicine(void);

void generateTransactionId(char *outId);
void getCurrentDate(char *outDate);

#endif
