#include "auth.h"
#include <stdio.h>
#include <string.h>

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
        printf("Error: could not create users file.\n");
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

// add this to auth.c, below initializeAuthFile()

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
                return 1;
            } else {
                return 2;
            }
        }
    }

    fclose(fp);
    return 0;  /* no matching record found */
}