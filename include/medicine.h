#ifndef MEDICINE_H
#define MEDICINE_H

/* ---------- Constants ---------- */
#define MAX_NAME 51       /* 50 characters + null terminator */
#define MAX_GENERIC 51    /* 50 characters + null terminator */
#define MAX_CATEGORY 31   /* 30 characters + null terminator */

#define MEDICINES_FILE "data/medicines.dat"

/* ---------- Medicine Structure ---------- */
typedef struct {
    int id;
    char name[MAX_NAME];
    char genericName[MAX_GENERIC];
    char category[MAX_CATEGORY];   /* e.g. Tablet, Capsule, Syrup */
    float price;
    int quantity;
} Medicine;

/* ---------- Public Function Prototypes ---------- */

void medicineMenu(void);

void addMedicine(void);
void viewAllMedicines(void);
void searchMedicine(void);
void updateMedicine(void);
void deleteMedicine(void);

/* Lets the user find a medicine by ID or by (partial) name.
   If multiple medicines match a name search, lists them and asks the user to confirm by entering the exact ID.
   Returns the resolved medicine ID, or -1 if none was found or the user cancelled. Used by updateMedicine(), deleteMedicine(), and sellMedicine() in sales.c. */
int resolveMedicineId(void);

#endif
