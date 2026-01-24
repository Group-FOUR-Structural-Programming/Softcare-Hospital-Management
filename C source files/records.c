#include <stdio.h>
#include <stdlib.h>
#include "records.h"
#include "patient.h"
#include "appointment.h"

void patientManagementMenu() {
    int choice;
    do {
        printf("\n--- Patient Management ---\n");
        printf("1. Register Patient\n");
        printf("2. View Patient Records\n");
        printf("0. Back\n");
        printf("Choose option: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                registerPatient();
                break;
            case 2:
                viewPatientRecords();
                break;
            case 0:
                break;
            default:
                printf("Invalid option.\n");
        }
    } while (choice != 0);
}

void appointmentManagementMenu() {
    int choice;
    do {
        printf("\n--- Appointment Management ---\n");
        printf("1. Schedule Appointment\n");
        printf("2. View Appointment Records\n");
        printf("0. Back\n");
        printf("Choose option: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                scheduleAppointment();
                break;
            case 2:
                viewAppointmentRecords();
                break;
            case 0:
                break;
            default:
                printf("Invalid option.\n");
        }
    } while (choice != 0);
}

void medicalRecordsMenu() {
    int choice;
    do {
        printf("\n--- Medical Records ---\n");
        printf("1. Add a Medical Record\n");
        printf("2. View All Medical Records\n");
        printf("3. View A Single Patient's Medical Records\n");
        printf("0. Back\n");
        printf("Choose option: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                // Add a medical record: Name, Diagnosis, Treatment, Cost
                {
                    char name[50], diagnosis[100], treatment[100];
                    float cost;
                    printf("Enter patient name: ");
                    scanf("%s", name);
                    printf("Enter diagnosis: ");
                    scanf(" %[^\n]", diagnosis); // Read full line
                    printf("Enter treatment: ");
                    scanf(" %[^\n]", treatment);
                    printf("Enter cost: ");
                    scanf("%f", &cost);
                    FILE *fp = fopen("medical_records.txt", "a");
                    if (fp) {
                        fprintf(fp, "%s|%s|%s|%.2f\n", name, diagnosis, treatment, cost);
                        fclose(fp);
                        printf("Medical record added.\n");

                        // Update patient's total due charges
                        FILE *pfp = fopen("patients.txt", "r");
                        FILE *temp = fopen("temp_patients.txt", "w");
                        if (pfp && temp) {
                            struct Patient p;
                            while (fscanf(pfp, "%s %d %s %s %s %s %f", p.name, &p.age, p.gender, p.contact, p.username, p.password, &p.totalDueCharges) != EOF) {
                                if (strcmp(p.name, name) == 0) {
                                    p.totalDueCharges += cost;
                                }
                                fprintf(temp, "%s %d %s %s %s %s %.2f\n", p.name, p.age, p.gender, p.contact, p.username, p.password, p.totalDueCharges);
                            }
                            fclose(pfp);
                            fclose(temp);
                            remove("patients.txt");
                            rename("temp_patients.txt", "patients.txt");
                        } else {
                            printf("Error updating patient charges.\n");
                        }
                    } else {
                        printf("Error saving record.\n");
                    }
                }
                break;
            case 2:
                // View All Medical Records
                {
                    FILE *fp = fopen("medical_records.txt", "r");
                    if (fp) {
                        char line[300];
                        printf("\n--- All Medical Records ---\n");
                        while (fgets(line, sizeof(line), fp)) {
                            // Parse line: name|diagnosis|treatment|cost
                            char *name = strtok(line, "|");
                            char *diagnosis = strtok(NULL, "|");
                            char *treatment = strtok(NULL, "|");
                            char *costStr = strtok(NULL, "\n");
                            if (name && diagnosis && treatment && costStr) {
                                float cost = atof(costStr);
                                printf("Patient: %s, Diagnosis: %s, Treatment: %s, Cost: %.2f\n", name, diagnosis, treatment, cost);
                            }
                        }
                        fclose(fp);
                    } else {
                        printf("No medical records found.\n");
                    }
                }
                break;
            case 3:
                // View A Single Patient's Medical Records
                {
                    char searchName[50];
                    printf("Enter patient name: ");
                    scanf("%s", searchName);
                    FILE *fp = fopen("medical_records.txt", "r");
                    if (fp) {
                        char line[300];
                        int found = 0;
                        printf("\n--- Medical Records for %s ---\n", searchName);
                        while (fgets(line, sizeof(line), fp)) {
                            char *name = strtok(line, "|");
                            char *diagnosis = strtok(NULL, "|");
                            char *treatment = strtok(NULL, "|");
                            char *costStr = strtok(NULL, "\n");
                            if (name && strcmp(name, searchName) == 0 && diagnosis && treatment && costStr) {
                                float cost = atof(costStr);
                                printf("Diagnosis: %s, Treatment: %s, Cost: %.2f\n", diagnosis, treatment, cost);
                                found = 1;
                            }
                        }
                        if (!found) {
                            printf("No records found for this patient.\n");
                        }
                        fclose(fp);
                    } else {
                        printf("No medical records found.\n");
                    }
                }
                break;
            case 0:
                break;
            default:
                printf("Invalid option.\n");
        }
    } while (choice != 0);
}

void viewRecordsMenu() {
    int choice;
    do {
        printf("\n--- View Records ---\n");
        printf("1. View Patient Records\n");
        printf("2. View Appointment Records\n");
        printf("0. Back\n");
        printf("Choose option: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                viewPatientRecords();
                break;
            case 2:
                viewAppointmentRecords();
                break;
            case 0:
                break;
            default:
                printf("Invalid option.\n");
        }
    } while (choice != 0);
}

void viewPatientRecords() {
    FILE *fp = fopen("patients.txt", "r");
    if (fp) {
        struct Patient p;
        printf("\n--- Patient Records ---\n");
        while (fscanf(fp, "%s %d %s %s %s %s %f", p.name, &p.age, p.gender, p.contact, p.username, p.password, &p.totalDueCharges) != EOF) {
            printf("Name: %s, Age: %d, Gender: %s, Contact: %s, Username: %s, Total Due Charges: %.2f\n", p.name, p.age, p.gender, p.contact, p.username, p.totalDueCharges);
        }
        fclose(fp);
    } else {
        printf("No patient records found.\n");
    }
}

void viewAppointmentRecords() {
    FILE *fp = fopen("appointments.txt", "r");
    if (fp) {
        struct Appointment a;
        printf("\n--- Appointment Records ---\n");
        while (fscanf(fp, "%s %s %s %s", a.patientName, a.date, a.time, a.doctor) != EOF) {
            printf("Patient: %s, Date: %s, Time: %s, Doctor: %s\n", a.patientName, a.date, a.time, a.doctor);
        }
        fclose(fp);
    } else {
        printf("No appointment records found.\n");
    }
}
