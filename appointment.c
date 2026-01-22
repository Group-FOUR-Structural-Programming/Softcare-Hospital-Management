#include <stdio.h>
#include "appointment.h"

void scheduleAppointment() {
    struct Appointment a;
    printf("\n--- Schedule Appointment ---\n");
    printf("Enter patient name: ");
    scanf("%s", a.patientName);
    printf("Enter date (dd/mm/yyyy): ");
    scanf("%s", a.date);
    printf("Enter time (hh:mm): ");
    scanf("%s", a.time);
    printf("Enter doctor: ");
    scanf("%s", a.doctor);
    FILE *fp = fopen("appointments.txt", "a");
    if (fp) {
        fprintf(fp, "%s %s %s %s\n", a.patientName, a.date, a.time, a.doctor);
        fclose(fp);
        printf("Appointment scheduled.\n");
    } else {
        printf("Error saving appointment.\n");
    }
}
