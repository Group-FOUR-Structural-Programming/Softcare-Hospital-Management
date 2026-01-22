#include <stdio.h>
#include "registration.h"
#include "login.h"
#include "patient.h"
#include "records.h"
#include "appointment.h"
#include "profile.h"
#include "staff.h"

void homeMenu() {
    int choice;

    do {
        printf("\n=== SMARTCARE HOSPITAL MANAGEMENT ===\n");
        printf("1. Register Patient\n");
        printf("2. View Records\n");
        printf("3. Schedule Appointment\n");
        printf("4. User Profile\n");
        printf("5. Manage Staff\n");
        printf("0. Exit\n");
        printf("Choose option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerPatient();
                break;
            case 2:
                viewRecords();
                break;
            case 3:
                scheduleAppointment();
                break;
            case 4:
                userProfileMenu();
                break;
            case 5:
                manageStaff();
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
