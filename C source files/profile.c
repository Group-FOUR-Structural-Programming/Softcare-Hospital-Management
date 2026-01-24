#include <stdio.h>
#include <string.h>
#include "profile.h"
#include "login.h"
#include "staff.h"

void userProfileMenu() {
    int choice;
    do {
        printf("\n--- User Profile ---\n");
        printf("1. Profile Details\n");
        printf("2. Change Password\n");
        printf("3. Logout\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Display profile details except password
                {
                    FILE *fp = fopen("staff.txt", "r");
                    if (fp) {
                        struct Staff s;
                        int found = 0;
                        while (fscanf(fp, "%s %s %s %s %s", s.name, s.role, s.contact, s.username, s.password) != EOF) {
                            if (strcmp(s.username, currentUsername) == 0) {
                                printf("\n--- Profile Details ---\n");
                                printf("Name: %s\n", s.name);
                                printf("Role: %s\n", s.role);
                                printf("Contact: %s\n", s.contact);
                                printf("Username: %s\n", s.username);
                                found = 1;
                                break;
                            }
                        }
                        fclose(fp);
                        if (!found) {
                            printf("Profile not found.\n");
                        }
                    } else {
                        printf("Error reading staff file.\n");
                    }
                }
                break;
            case 2:
                // Change password
                {
                    char newPass[50], confirmPass[50];
                    printf("Enter new password: ");
                    scanf("%s", newPass);
                    printf("Confirm new password: ");
                    scanf("%s", confirmPass);
                    if (strcmp(newPass, confirmPass) != 0) {
                        printf("Passwords do not match.\n");
                    } else {
                        // Update password in staff.txt
                        FILE *fp = fopen("staff.txt", "r");
                        FILE *temp = fopen("temp.txt", "w");
                        if (fp && temp) {
                            struct Staff s;
                            while (fscanf(fp, "%s %s %s %s %s", s.name, s.role, s.contact, s.username, s.password) != EOF) {
                                if (strcmp(s.username, currentUsername) == 0) {
                                    strcpy(s.password, newPass);
                                }
                                fprintf(temp, "%s %s %s %s %s\n", s.name, s.role, s.contact, s.username, s.password);
                            }
                            fclose(fp);
                            fclose(temp);
                            remove("staff.txt");
                            rename("temp.txt", "staff.txt");
                            printf("Password changed successfully.\n");
                        } else {
                            printf("Error updating password.\n");
                        }
                    }
                }
                break;
            case 3:
                printf("Logging out...\n");
                return; // Go back to main menu
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 3);
}
