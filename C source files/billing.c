#include <stdio.h>
#include <string.h>
#include "billing.h"
#include "patient.h"

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
                p.totalDueCharges -= amountPaid;
                if (p.totalDueCharges < 0) {
                    p.totalDueCharges = 0; // Prevent negative
                }
                printf("Payment processed. Remaining due: %.2f\n", p.totalDueCharges);
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
