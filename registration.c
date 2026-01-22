#include <stdio.h>
#include <string.h>
#include "registration.h"

void startRegistration() {
    struct User user;
    printf("\n--- User Registration ---\n");
    printf("Enter username(use one name): ");
    scanf("%s", user.username);
    printf("Enter password: ");
    scanf("%s", user.password);
    printf("Enter role (admin/doctor/nurse): ");
    scanf("%s", user.role);
    if (strcmp(user.role, "admin") == 0) {
        char secret[50];
        printf("Enter admin secret password: ");
        scanf("%s", secret);
        if (strcmp(secret, "ADMINPASS") != 0) {
            printf("Invalid admin password. Registration failed.\n");
            return;
        }
    }
    FILE *fp = fopen("users.txt", "a");
    if (fp) {
        fprintf(fp, "%s %s %s\n", user.username, user.password, user.role);
        fclose(fp);
        printf("Registration successful.\n");
    } else {
        printf("Error saving user.\n");
    }
}