//
// Created by sohai on 8/14/2023.
//

#include <stdio.h>
#include "string.h"
#include "std_type.h"
#include "patient.h"
#define PASS "1234"

void check_pass();
void separator();
void choice();
void scanChar();
void invalid();
void user_view();
void admin_view();

char *slots[] = {
        "2     -->   2:30",
        "2:30  -->   3",
        "3     -->   3:30",
        "4     -->   4:30",
        "4:30  -->   5",
};

char *genders[] = {
        "Male",
        "Female"
};

// ARRAY OF POINTERS TO PATIENT
// WHEN A PATIENT POINTER ASSIGNED TO INDEX 0 FOR EXAMPLE THAT MEANS :
// THIS PATIENT RESERVED FIRST SLOT  --> ( slots [index] )
patient *reservation[SLOTS_NUM] = {NULL};

/// ========================================= HELPER FUNCTION ========================================
void welcome() {
    separator();
    printf("--------------- W E L C O M E ---------------\n");
}



/// ========================================= LAUNCH FUNCTION ========================================
// CHOOSING BETWEEN ADMIN MODE _AND_ USER MODE
void launch_system() {
    separator();
    printf("0. Admin mode\n"
           "1. User mode\n");
    separator();
    choice();
    u8 selector;
    scanChar(&selector);
    while (selector != 0 && selector != 1) {
        invalid();
        scanChar(&selector);
    }
    if (!selector) return check_pass();
    welcome();
    return user_view();
}

/// ========================================= PASS FUNCTION ========================================
// CHECKING ADMIN PASSWORD FOR 3 TIMES MAXIMUM __ IF IT CORRECT DISPLAY ADMIN VIEW THEN
void check_pass() {
    separator();
    char pass[20];
    u8 trials = 3;
    printf("Enter admin password :");
    getchar();
    do {
        if (trials == 1) printf("Incorrect password, %d trial remaining :", trials);
        else if (trials < 3) printf("Incorrect password, %d trials remaining :", trials);
        gets(pass);
        if (strcmp(pass, PASS) == 0) {
            welcome();
            return admin_view();
        };
    } while (--trials);
    separator();
    printf("No more trials\n");
    separator();
    return;
}

