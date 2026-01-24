#include <stdio.h>
#include "profile.h"

void userProfileMenu() {
    int choice;
    do {
        printf("\n--- User Profile ---\n");
        printf("1. View Profile\n");
        printf("2. Account Settings\n");
        printf("0. Logout\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Profile details...\n");
                break;
            case 2:
                printf("Account settings...\n");
                break;
            case 0:
                printf("Logging out...\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    } while (choice != 0);
}
