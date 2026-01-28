#include <stdio.h>
#include <string.h>
#include "billing.h"
#include "patient.h"
#include "login.h"

void billingMenu() {
    char patientName[50];
    float amountPaid;
    printf("\n--- Billing ---\n");
    printf("Enter patient name: ");
    scanf("%s", patientName);
    printf("Enter amount paid: ");
    scanf("%f", &amountPaid);

    FILE *fp = fopen("patients.txt", "r");
    FILE *temp = fopen("temp_patients.txt", "w");
    if (fp && temp) {
        struct Patient p;
        int found = 0;
        while (fscanf(fp, "%s %d %s %s %s %s %f", p.name, &p.age, p.gender, p.contact, p.username, p.password, &p.totalDueCharges) != EOF) {
            if (strcmp(p.name, patientName) == 0) {
                found = 1;
                float previousBalance = p.totalDueCharges;
                p.totalDueCharges -= amountPaid;
                if (p.totalDueCharges < 0) {
                    p.totalDueCharges = 0; // Prevent negative
                }
                printf("Payment processed. Remaining due: %.2f\n", p.totalDueCharges);
                
                // Log transaction to billing.txt with staff member
                FILE *billing_fp = fopen("billing.txt", "a");
                if (billing_fp) {
                    fprintf(billing_fp, "%s %s %.2f %.2f %.2f\n", currentUsername, patientName, amountPaid, previousBalance, p.totalDueCharges);
                    fclose(billing_fp);
                }
            }
            fprintf(temp, "%s %d %s %s %s %s %.2f\n", p.name, p.age, p.gender, p.contact, p.username, p.password, p.totalDueCharges);
        }
        fclose(fp);
        fclose(temp);
        remove("patients.txt");
        rename("temp_patients.txt", "patients.txt");
        if (!found) {
            printf("Patient doesn't exist.\n");
        }
    } else {
        printf("Error accessing patient records.\n");
    }
}

void viewBillingRecords() {
    FILE *fp = fopen("billing.txt", "r");
    if (fp) {
        printf("\n--- Billing Records ---\n");
        printf("%-15s %-15s %-10s %-12s %-12s\n", "Staff", "Patient", "Amount", "Previous", "New Balance");
        printf("------------------------------------------------------------------\n");
        char staff[50], patient[50];
        float amount, prev, new;
        while (fscanf(fp, "%s %s %f %f %f", staff, patient, &amount, &prev, &new) != EOF) {
            printf("%-15s %-15s $%-9.2f $%-11.2f $%-11.2f\n", staff, patient, amount, prev, new);
        }
        fclose(fp);
    } else {
        printf("No billing records found.\n");
    }
}
