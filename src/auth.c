#include "auth.h"
#include <stdio.h>
#include <string.h>

char currentUserRole = '\0';

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
    strcpy(admin.username, "admin");
    strcpy(admin.password, "admin123");
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
