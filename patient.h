//
// Created by sohai on 8/13/2023.
//
#ifndef C_LANG_PATIENT_H
#define C_LANG_PATIENT_H

#include "std_type.h"
#include "stdlib.h"
#define SLOTS_NUM 5

extern char *slots[];
extern char *genders[];

typedef struct patient_ {
    s32 id;
    u8 name[50];
    u8 age;
    s16 gender;
    struct patient_ *next;
} patient;

extern patient *reservation[SLOTS_NUM];
#endif //C_LANG_PATIENT_H

