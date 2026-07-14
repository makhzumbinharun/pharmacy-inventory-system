#ifndef AUTH_H
#define AUTH_H

/* ---------- Constants ---------- */
#define MAX_USERNAME 21   /* 20 characters + null terminator */
#define MAX_PASSWORD 21   /* 20 characters + null terminator */

#define USERS_FILE "data/users.dat"

/* Default admin account created automatically on first run
   if users.dat does not exist yet:
       username: admin
       password: admin123 */

/* ---------- User Structure ---------- */
typedef struct {
    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char role;   /* 'A' = Admin, 'S' = Staff */
} User;

/* ---------- Public Function Prototypes ---------- */

/* Makes sure users.dat exists. If it doesn't, create it and write the default admin account into it. */
void initializeAuthFile(void);

/* Checks username/password against users.dat.
   Returns:
     0 -> login failed (wrong username or password)
     1 -> success, logged in as Admin
     2 -> success, logged in as Staff
*/
int authenticateUser(const char *username, const char *password);

/* Tracks the role of the currently logged-in user.
   Set by authenticateUser() on successful login.
   'A' = Admin, 'S' = Staff, '\0' = no one logged in yet. */
extern char currentUserRole;

/* Checks a password against every Admin record in users.dat.
   Used when the staff needs an Admin override to Add/Update/Delete. */
int verifyAdminPassword(const char *password);

#endif
