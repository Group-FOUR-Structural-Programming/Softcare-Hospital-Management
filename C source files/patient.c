#include <stdio.h>
#include <string.h>
#include "patient.h"

extern char currentRole[50];

void registerPatient() {
    if (strcmp(currentRole, "admin") != 0 && strcmp(currentRole, "doctor") != 0 && strcmp(currentRole, "nurse") != 0) {
        printf("You don't have permission to access this option.\n");
        return;
    }
    struct Patient p;
    printf("\n--- Register Patient ---\n");
    printf("Enter name: ");
    scanf("%s", p.name);
    if (strlen(p.name) == 0) {
        printf("Invalid name. Name cannot be empty.\n");
        return;
    }
    printf("Enter age: ");
    scanf("%d", &p.age);
    if (p.age < 1 || p.age > 120) {
        printf("Invalid age. Age must be between 1 and 120.\n");
        return;
    }
    printf("Enter gender (Male/Female): ");
    scanf("%s", p.gender);
    if (strcmp(p.gender, "Male") != 0 && strcmp(p.gender, "Female") != 0) {
        printf("Invalid gender. Please enter Male or Female.\n");
        return;
    }
    printf("Enter contact: ");
    scanf("%s", p.contact);
    if (strlen(p.contact) == 0) {
        printf("Invalid contact. Contact cannot be empty.\n");
        return;
    }
    printf("Enter username: ");
    scanf("%s", p.username);
    if (strlen(p.username) == 0) {
        printf("Invalid username. Username cannot be empty.\n");
        return;
    }
    printf("Enter password: ");
    scanf("%s", p.password);
    if (strlen(p.password) == 0) {
        printf("Invalid password. Password cannot be empty.\n");
        return;
    }
    p.totalDueCharges = 0.0; // Initialize to 0
    FILE *fp = fopen("patients.txt", "a");
    if (fp) {
        fprintf(fp, "%s %d %s %s %s %s %.2f\n", p.name, p.age, p.gender, p.contact, p.username, p.password, p.totalDueCharges);
        fclose(fp);
        printf("Patient registered successfully.\n");
    } else {
        printf("Error saving patient.\n");
    }
}
