#ifndef MEDICINE_H
#define MEDICINE_H

/* ---------- Constants ---------- */
#define MAX_NAME 51      /* 50 characters + null terminator */
#define MAX_CATEGORY 31  /* 30 characters + null terminator */

#define MEDICINES_FILE "data/medicines.dat"

/* ---------- Medicine Structure ---------- */
typedef struct {
    int id;
    char name[MAX_NAME];
    char category[MAX_CATEGORY];
    float price;
    int quantity;
} Medicine;

/* ---------- Public Function Prototypes ---------- */

/* Displays the Medicine Management menu and routes to the correct function below. Called from main.c after a successful login. */
void medicineMenu(void);

void addMedicine(void);
void viewAllMedicines(void);
void searchMedicine(void);
void updateMedicine(void);
void deleteMedicine(void);

#endif
