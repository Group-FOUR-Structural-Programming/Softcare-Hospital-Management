#include <stdio.h>
#include <string.h>
#include "staff.h"

extern char currentRole[50];

void manageStaff() {
    if (strcmp(currentRole, "admin") != 0) {
        printf("You don't have permission to access this option.\n");
        return;
    }
    int choice;
    do {
        printf("\n--- Manage Staff ---\n");
        printf("1. Add Staff\n");
        printf("2. View Staff\n");
        printf("0. Back\n");
        printf("Choose option: ");
        scanf("%d", &choice);
        if (choice == 1) {
            struct Staff s;
            printf("Enter name: ");
            scanf("%s", s.name);
            printf("Enter role: ");
            scanf("%s", s.role);
            printf("Enter contact: ");
            scanf("%s", s.contact);
            FILE *fp = fopen("staff.txt", "a");
            if (fp) {
                fprintf(fp, "%s %s %s\n", s.name, s.role, s.contact);
                fclose(fp);
                printf("Staff added.\n");
            }
        } else if (choice == 2) {
            FILE *fp = fopen("staff.txt", "r");
            if (fp) {
                struct Staff s;
                printf("\n--- Staff List ---\n");
                while (fscanf(fp, "%s %s %s", s.name, s.role, s.contact) != EOF) {
                    printf("Name: %s, Role: %s, Contact: %s\n", s.name, s.role, s.contact);
                }
                fclose(fp);
            } else {
                printf("No staff found.\n");
            }
        } else if (choice != 0) {
            printf("Invalid option.\n");
        }
    } while (choice != 0);
}
