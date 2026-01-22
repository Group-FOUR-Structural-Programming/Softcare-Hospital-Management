#ifndef APPOINTMENT_H
#define APPOINTMENT_H

struct Appointment {
    char patientName[50];
    char date[20];
    char time[10];
    char doctor[50];
};

void scheduleAppointment();

#endif
