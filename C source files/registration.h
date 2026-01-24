#ifndef REGISTRATION_H
#define REGISTRATION_H

struct User {
    char username[50];
    char password[50];
    char role[50];
};

void startRegistration();

#endif