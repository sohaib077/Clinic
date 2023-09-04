//
// Created by sohai on 8/14/2023.
//

#include<stdio.h>
#include"std_type.h"
#include"patient.h"


void patient_record();
void today_reservations();
void separator();
void choice();
void scanChar();
void invalid();
void launch_system();
void scanInt();
patient * get_patient_by_id();


/// ========================================= USER VIEW ========================================
// DISPLAYS FUNCTIONS THAT USER CAN DO

void user_view() {
    separator();
    printf("0.  Patient record\n"
           "1.  Today's reservations\n"
           "2.  Exit user mode\n");
    separator();
    choice();
    u8 selector;
    scanChar(&selector);
    while (selector > 2 && selector < 0) {
        invalid();
        scanChar(&selector);
    }
    if (selector == 0) return patient_record();
    else if (selector == 1) return today_reservations();
    return launch_system();

}


/// ========================================= PATIENT RECORD ========================================
// ASKING FOR ID __AND__ CHECK ITS EXISTENCE BY FUNCTION FROM ADMIN VIEW __ THEN DISPLAY PATIENT'S DATA IF EXISTS

void patient_record() {
    separator();
    printf("Enter patient ID :");
    s32 id;
    scanInt(&id);
    patient *ptr = get_patient_by_id(id);
    if (ptr == NULL) {
        printf("Can't find such an id, try another one\n");
        return patient_record();
    }
    separator();
    printf("Name   :  %s\n", ptr->name);
    printf("Age    :  %d years old\n", ptr->age);
    printf("Gender :  %s\n", genders[ptr->gender]);
    return user_view();

}


/// ========================================= PATIENT RECORD ========================================
// DISPLAYS ALL SLOTS THAT HAS BEEN RESERVED WITH ITS PATIENT'S DATA

void today_reservations() {
    separator();
    u8 checker = 0;
    for (int i = 0; i < SLOTS_NUM; ++i) {
        if (reservation[i] != NULL) {
            printf("( %s ) is reserved for { %s , %d years old }\n", slots[i], reservation[i]->name,
                   reservation[i]->age);
            checker = 1;
        }
    }
    if (!checker) {
        printf("There are no attached reservations yet\n");
    }
    return user_view();
}
