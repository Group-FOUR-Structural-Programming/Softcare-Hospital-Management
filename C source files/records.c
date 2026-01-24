#include <stdio.h>
#include "records.h"
#include "patient.h"

void viewRecords() {
    FILE *fp = fopen("patients.txt", "r");
    if (fp) {
        struct Patient p;
        printf("\n--- Patient Records ---\n");
        while (fscanf(fp, "%s %d %s %s", p.name, &p.age, p.gender, p.contact) != EOF) {
            printf("Name: %s, Age: %d, Gender: %s, Contact: %s\n", p.name, p.age, p.gender, p.contact);
        }
        fclose(fp);
    } else {
        printf("No records found.\n");
    }
}
