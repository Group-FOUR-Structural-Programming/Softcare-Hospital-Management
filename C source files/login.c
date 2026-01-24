#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "login.h"
#include "registration.h"
#include "staff.h"

char currentRole[50];
char currentUsername[50];

void loginUser() {
    char username[50], password[50];
    printf("\n--- Login ---\n");
    printf("Enter username(use one name): ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);
    // Authenticate against staff.txt
    FILE *sfp = fopen("staff.txt", "r");
    if (sfp) {
        struct Staff s;
        int foundStaff = 0;
        // staff.txt format: name role contact username password
        while (fscanf(sfp, "%s %s %s %s %s", s.name, s.role, s.contact, s.username, s.password) != EOF) {
            if (strcmp(s.username, username) == 0 && strcmp(s.password, password) == 0) {
                foundStaff = 1;
                break;
            }
        }
        fclose(sfp);
        if (foundStaff) {
            strcpy(currentRole, s.role);
            strcpy(currentUsername, s.username);
            printf("Login successful.\n");
            return;
        } else {
            printf("Invalid credentials.\n");
            exit(0);
        }
    } else {
        printf("No staff registered (staff.txt missing).\n");
        exit(0);
    }
}
