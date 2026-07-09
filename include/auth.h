#ifndef AUTH_H
#define AUTH_H

/* ---------- Constants ---------- */
#define MAX_USERNAME 21   /* 20 characters + null terminator */
#define MAX_PASSWORD 21   /* 20 characters + null terminator */

#define USERS_FILE "data/users.dat"

/* Default admin account created automatically on first run
   if users.dat does not exist yet:
       username: admin
       password: admin123
   (Team should change this password after first login in a
   real deployment, but for this project it stays fixed.) */

/* ---------- User Structure ---------- */
typedef struct {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char role;   /* 'A' = Admin, 'S' = Staff */
} User;

/* ---------- Public Function Prototypes ---------- */

/* Makes sure users.dat exists. If it doesn't, creates it
   and writes the default admin account into it. */
void initializeAuthFile(void);

/* Checks username/password against users.dat.
   Returns:
     0 -> login failed (wrong username or password)
     1 -> success, logged in as Admin
     2 -> success, logged in as Staff
*/
int authenticateUser(const char *username, const char *password);

#endif