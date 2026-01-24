#ifndef PATIENT_H
#define PATIENT_H

struct Patient {
    char name[50];
    int age;
    char gender[10];
    char contact[20];
    char username[50];
    char password[50];
    float totalDueCharges;
};

void registerPatient();

#endif
