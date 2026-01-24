#ifndef STAFF_H
#define STAFF_H

struct Staff {
    char name[50];
    char role[50];
    char contact[20];
    char username[50];
    char password[50];
};

void manageStaff();

#endif
