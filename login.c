#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "login.h"
#include "registration.h"

char currentRole[50];

void loginUser() {
    char username[50], password[50];
    printf("\n--- Login ---\n");
    printf("Enter username(use one name): ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);
    FILE *fp = fopen("users.txt", "r");
    if (fp) {
        struct User user;
        int found = 0;
        // Loop through all users in the file to find matching credentials
        while (fscanf(fp, "%s %s %s", user.username, user.password, user.role) != EOF) {
            if (strcmp(user.username, username) == 0 && strcmp(user.password, password) == 0) {
                found = 1;
                break;
            }
        }
        fclose(fp);
        if (found) {
            strcpy(currentRole, user.role);  // Store the role of the logged in user
            printf("Login successful.\n");
        } else {
            printf("Invalid credentials.\n");
            exit(0);
        }
    } else {
        printf("No users registered.\n");
        exit(0);
    }
}
