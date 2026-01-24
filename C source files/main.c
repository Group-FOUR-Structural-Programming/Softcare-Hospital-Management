#include <stdio.h>
#include "registration.h"
#include "login.h"
#include "patient.h"
#include "records.h"
#include "appointment.h"
#include "profile.h"
#include "staff.h"
#include "billing.h"

void homeMenu() {
    int choice;

    do {
        printf("\n=== SMARTCARE HOSPITAL MANAGEMENT ===\n");
        printf("1. Patient Management\n");
        printf("2. Appointment Management\n");
        printf("3. User Profile\n");
        printf("4. Staff Management (Only for admins)\n");
        printf("5. Medical Records\n");
        printf("6. Billing\n");
        printf("0. Exit\n");
        printf("Choose option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                patientManagementMenu();
                break;
            case 2:
                appointmentManagementMenu();
                break;
            case 3:
                userProfileMenu();
                break;
            case 4:
                manageStaff();
                break;
            case 5:
                medicalRecordsMenu();
                break;
            case 6:
                billingMenu();
                break;
            case 0:
                printf("Exiting system...\n");
                break;
            default:
                printf("Invalid option.\n");
        }
    } while (choice != 0);
}

int main() {
    int choice;
    // Main menu loop to allow user to choose login, register, or exit
    do {
        printf("What do you want to do?\n");
        printf("1. Login\n");
        printf("2. Register\n");
        printf("3. Exit\n");
        printf("Choose option: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                loginUser();  // Authenticate user
                homeMenu();   // Show main menu after login
                return 0;
            case 2:
                startRegistration();  // Register new user
                loginUser();          // Login after registration
                homeMenu();
                return 0;
            case 3:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid option. Try again.\n");
        }
    } while (1);  // Infinite loop until valid choice and exit
}
