#include <stdio.h>
#include <string.h>
#include "registration.h"
#include "staff.h"

void startRegistration() {
    struct Staff s;
    printf("\n--- Staff Self-Registration ---\n");
    printf("Enter name: ");
    scanf("%s", s.name);
    printf("Enter role (admin/doctor/nurse): ");
    scanf("%s", s.role);
    // Due to the uncontrolled power of System Admins create a secret password to control registration of that role
    if (strcmp(s.role, "admin") == 0) {
        char secret[50];
        printf("Enter admin secret password: ");
        scanf("%s", secret);

        if (strcmp(secret, "ADMINPASS") != 0) {
            printf("Invalid admin password. Registration failed.\n");
            return;
        }
    }
    printf("Enter contact: ");
    scanf("%s", s.contact);
    printf("Enter username: ");
    scanf("%s", s.username);
    printf("Enter password: ");
    scanf("%s", s.password);

    FILE *fp = fopen("staff.txt", "a");
    if (fp) {
        fprintf(fp, "%s %s %s %s %s\n", s.name, s.role, s.contact, s.username, s.password);
        fclose(fp);
        printf("Registration successful. Staff record added to staff.txt.\n");
    } else {
        printf("Error saving staff.\n");
    }
}
