#include "auth.h"
#include <stdio.h>
#include <string.h>

char currentUserRole = '\0';
char currentUsername[MAX_USERNAME] = "";

void initializeAuthFile(void) {

    FILE *fp = fopen(USERS_FILE, "rb");

    if (fp != NULL) {
        /* File already exists - do nothing, just close and return */
        fclose(fp);
        return;
    }

    /* File doesn't exist yet - create it and write default admin */
    fp = fopen(USERS_FILE, "wb");
    if (fp == NULL) {
        perror("fopen failed");
        return;
    }

    User admin;
    printf("No admin account found. Let's create one.\n");
    printf("Choose an admin username: ");
    scanf("%s", admin.username);
    printf("Choose an admin password: ");
    scanf("%s", admin.password);
    admin.role = 'A';

    fwrite(&admin, sizeof(User), 1, fp);
    fclose(fp);

    printf("Default admin account created.\n");
}

int authenticateUser(const char *username, const char *password) {

    FILE *fp = fopen(USERS_FILE, "rb");
    if (fp == NULL) {
        printf("Error: could not open users file.\n");
        return 0;
    }

    User temp;

    while (fread(&temp, sizeof(User), 1, fp) == 1) {
        if (strcmp(temp.username, username) == 0 &&
            strcmp(temp.password, password) == 0) {

            fclose(fp);

            strcpy(currentUsername, temp.username);
            
            if (temp.role == 'A') {
                currentUserRole = 'A';
                return 1;
            } else {
                currentUserRole = 'S';
                return 2;
            }
        }
    }

    fclose(fp);
    return 0;  /* no matching record found */
}

int verifyAdminPassword(const char *password) {

    FILE *fp = fopen(USERS_FILE, "rb");
    if (fp == NULL) {
        return 0;
    }

    User temp;

    while (fread(&temp, sizeof(User), 1, fp) == 1) {
        if (temp.role == 'A' && strcmp(temp.password, password) == 0) {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

void registerUser(void) {

    if (currentUserRole != 'A') {
        printf("\nOnly Admin can create new user accounts.\n");
        return;
    }

    User newUser;
    char roleInput;

    printf("\n--- Register New User ---\n");
    printf("Username: ");
    scanf("%s", newUser.username);

    /* Check for duplicate username before proceeding */
    FILE *checkFp = fopen(USERS_FILE, "rb");
    if (checkFp != NULL) {
        User existing;
        while (fread(&existing, sizeof(User), 1, checkFp) == 1) {
            if (strcmp(existing.username, newUser.username) == 0) {
                printf("Error: username already exists. Registration cancelled.\n");
                fclose(checkFp);
                return;
            }
        }
        fclose(checkFp);
    }

    printf("Password: ");
    scanf("%s", newUser.password);
    printf("Role (A = Admin, S = Staff): ");
    scanf(" %c", &roleInput);

    if (roleInput != 'A' && roleInput != 'S') {
        printf("Invalid role. User not created.\n");
        return;
    }

    newUser.role = roleInput;

    FILE *fp = fopen(USERS_FILE, "ab");
    if (fp == NULL) {
        printf("Error: could not open users file.\n");
        return;
    }

    fwrite(&newUser, sizeof(User), 1, fp);
    fclose(fp);

    printf("User '%s' registered successfully as %s.\n",
           newUser.username, roleInput == 'A' ? "Admin" : "Staff");
}
