//
// Created by sohai on 8/13/2023.
//


#include "patient.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void admin_view();
void add_patient();
static void add_patient_logic(patient *newPatient);
patient *get_patient_by_id(s32 id);
void edit_patient();
patient *delete_patient_by_id(u32 id);
void delete_patient_reservations(patient *tmp);
void delete_patient();
void available_slots();
void reserve_slot();
void cancel_reservation();
void launch_system();
void view_patients();
void scanChar(pu8 ptr);

patient *head = NULL;
patient *tail = NULL;


/// ========================================= HELPER FUNCTIONS ========================================
void choice() {
    printf("Enter your choice :");
}

void separator() {
    printf("---------------------------------------------\n");
}

void admin_or_exit() {
    printf("0. Exit the program\n"
           "1. Back to admin view\n"
    );
}

bool isEmpty() {
    return head == NULL;
}

void invalid() {
    printf("Invalid input, try again :");
}

// DYNAMIC ALLOCATING TO NEW PATIENT OBJECT
patient *newPatientObject() {
    return (patient *) malloc(sizeof(patient));
}

// TAKES A POINTER TO VOID FUNCTION AND DISPLAYS 3 OPTIONS { EXIT , BACK TO ADMIN VIEW , FUNCTION THAT PASSED }
void selecting(void(*func)()) {
    u8 selector;
    separator();
    choice();
    while (true) {
        scanChar(&selector);
        if (selector == 0) return;
        else if (selector == 1)return admin_view();
        else if (selector == 2 && func != NULL) return func();
        else invalid();
    }
}

// ========================================= HELPER FUNCTIONS ========================================


/// ===================================== VALIDATION FUNCTIONS ========================================
static bool idChecker(s32 id) {
    patient *tmp = head;
    while (tmp != NULL) {
        if (tmp->id == id)
            return false;
        tmp = tmp->next;
    }
    return true;
}

static bool ageChecker(u8 age) {
    return (age > 0) && (age <= 150);

}

static bool genderChecker(u8 gender) {
    return (gender == 0) || (gender == 1);
}

void scanInt(ps32 ptr) {
    while (!scanf("%d", ptr)) {
        invalid();
        fflush(stdin);
    }
}

void scanShort(ps16 ptr) {
    while (!scanf("%hi", ptr)) {
        invalid();
        fflush(stdin);
    }
}

void scanChar(pu8 ptr) {
    while (!scanf("%u", ptr)) {
        invalid();
        fflush(stdin);
    }
}

void scan_id(patient *newPatient) {
    scanInt(&newPatient->id);
    while (newPatient->id <= 0) {
        printf("ID must be greater than zero, try another one :");
        scanInt(&newPatient->id);
    }
    while (!idChecker(newPatient->id)) {
        printf("This ID is already used try another one :");
        scanInt(&newPatient->id);
        while (newPatient->id <= 0) {
            printf("ID must be greater than zero, try another one :");
            scanInt(&newPatient->id);
        }
    }
}

void scan_age(patient *newPatient) {
    scanChar(&newPatient->age);
    while (!ageChecker(newPatient->age)) {
        printf("Please enter a valid age :");
        scanChar(&newPatient->age);
    }
}

void scan_gender(patient *newPatient) {
    printf("Genders :\n");
    printf("0. Male\n"
           "1. Female\n"
    );
    printf("Choose your gender :");
    scanShort(&newPatient->gender);
    while (!genderChecker(newPatient->gender)) {
        printf("Please enter a valid gender :");
        scanShort(&newPatient->gender);
    }
}
// ===================================== VALIDATION FUNCTIONS ========================================


/// =========================================== ADMIN VIEW ============================================
// JUST DISPLAY FUNCTIONS THAT ADMIN CAN SELECT AMONG THEM.
void admin_view() {
    separator();
    printf("1. Add patient\n"
           "2. Edit patient\n"
           "3. Delete patient\n"
           "4. Reserve a slot\n"
           "5. Cancel reservation\n"
           "6. View patients\n"
           "7. Exit admin mode\n"
    );
    separator();
    choice();
    while (true) {
        u8 selector;
        scanChar(&selector);
        switch (selector) {
            case 1:
                return add_patient();
            case 2:
                return edit_patient();
            case 3:
                return delete_patient();
            case 4:
                return reserve_slot();
            case 5:
                return cancel_reservation();
            case 6:
                return view_patients();
            case 7:
                return launch_system();
            default:
                invalid();
                break;
        }
    }
}
// =========================================== ADMIN VIEW ============================================


/// ======================================= ADDITION FUNCTION =========================================
// ASKING ADMIN TO ENTER PATIENT'S DATA __ WITH HANDLING REPEATED IDS
// OPTIONS AFTER ADDITION -> { ADD ANOTHER PATIENT }
void add_patient() {
    separator();
    patient *newPatient = newPatientObject();
    printf("Enter patient's data :\n");
    printf("ID :");
    scan_id(newPatient);
    printf("Name :");
    getchar();
    gets(newPatient->name);
    printf("Age :");
    scan_age(newPatient);
    separator();
    scan_gender(newPatient);
    add_patient_logic(newPatient);
    separator();
    admin_or_exit();
    printf("2. Add another patient\n");
    selecting(add_patient);
}

// LOGIC THAT HANDLES THE LIST OF PATIENTS AFTER GETTING PATIENT DATA
static void add_patient_logic(patient *newPatient) {
    patient *tmp = tail;
    tail = newPatient;
    newPatient->next = NULL;
    if (!isEmpty()) tmp->next = newPatient;
    if (isEmpty()) head = newPatient;
}
// ======================================= ADDITION FUNCTION =========================================


/// ======================================= EDITION FUNCTION =========================================
// EDITS PATIENT BY IT'S ID __ WITH HANDLING THE EXISTENCE OF THAT ID
// OPTIONS AFTER EDITION -> { EDIT ANOTHER ATTRIBUTE FOR THE SAME PATIENT _OR_ EDIT ANOTHER PATIENT'S DATA }
void edit_patient() {
    separator();
    s32 id;
    printf("Enter patient ID :");
    scanInt(&id);
    patient *ptr = get_patient_by_id(id);
    if (ptr == NULL) {
        printf("Can't find such an id, try another one\n");
        return edit_patient();
    }
    printf("{ %s , %d years old , %s }\n", ptr->name, ptr->age, genders[ptr->gender]);
    printf("0. Name\n"
           "1. Age\n"
           "2. Gender\n"
    );
    u8 selector, checker = 1;
    while (checker) {
        checker = 1;
        separator();
        printf("Which attribute you wanna edit :");
        scanChar(&selector);
//        separator();
        switch (selector) {
            case 0:
                printf("Enter new name :");
                getchar();
                gets(ptr->name);
                break;
            case 1:
                printf("Enter new age :");
                scan_age(ptr);
                break;
            case 2:
                scan_gender(ptr);
                break;
            default:
                invalid();
                checker = 2;
                break;
        }
        if (checker == 2)
            printf("\n");

        else {
            separator();
            admin_or_exit();
            printf("2. Edit another attribute\n"
                   "3. Edit another patient\n"
            );
            separator();
            choice();
            bool checker2 = true;
            while (checker2) {
                u8 selector;
                scanChar(&selector);
                switch (selector) {
                    case 0:
                        return;
                    case 1:
                        return admin_view();
                    case 2:
                        checker2 = false;
                        break;
                    case 3:
                        return edit_patient();
                    default:
                        invalid();
                        break;
                }
            }
        }
    }
}

patient *get_patient_by_id(s32 id) {
    patient *tmp = head;
    while (tmp != NULL) {
        if (tmp->id == id)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}
// ======================================= EDITION FUNCTION =========================================


/// ====================================== DELETION FUNCTION =========================================
// DELETES PATIENT BY IT'S ID __ WITH HANDLING THE EXISTENCE OF THAT ID _AND_ IF PATIENT HAS RESERVATIONS
// DISPLAYS PATIENT'S DATA THEN ASK THE ADMIN FOR CONFIRMATION
// OPTIONS AFTER DELETION -> { DELETE ANOTHER PATIENT }
void delete_patient() {
    separator();
    s32 id;
    printf("Enter patient's id :");
    scanInt(&id);
    patient *prev = NULL;
    patient *tmp = NULL;
    if (!isEmpty()) {
        if (head->id == id) tmp = head;
        else prev = delete_patient_by_id(id);

    }
    if (prev == NULL && tmp == NULL) {
        printf("Can't find such an id, try another one\n");
        return delete_patient();
    }
    separator();
    tmp == NULL ?
    printf("{ %s , %d years old , %s }\n", prev->next->name, prev->next->age, genders[prev->next->gender]) :
    printf("{ %s , %d years old , %s }\n", tmp->name, tmp->age, genders[tmp->gender]);
    printf("Wanna delete this patient ?\n"
           "0. Delete\n"
           "1. Cancel\n"
    );
    separator();
    choice();
    u8 selector;
    scanChar(&selector);
    while (selector != 1 && selector != 0) {
        invalid();
        scanChar(&selector);
    };
    if (selector) return admin_view();

// HANDLING 3 CASES OF DELETION { HEAD , MID , TAIL }
    if (tmp != NULL) {
        if (head == tail) {
            head = NULL;
            tail = NULL;
        } else {
            head = head->next;
        }
    } else {
        tmp = prev->next;
        if (prev->next == tail) {
            tail = prev;
            tail->next = NULL;
        } else {
            prev->next = prev->next->next;
        }
    }


    delete_patient_reservations(tmp);

    free(tmp);
    separator();
    admin_or_exit();
    printf("2. Delete another patient\n"
    );
    selecting(delete_patient);
}

// CHECKING IF ID EXISTS AND RETURNING POINTER TO THE PREVIOUS PATIENT
patient *delete_patient_by_id(u32 id) {
    patient *tmp = head;
    while (tmp->next != NULL) {
        if (tmp->next->id == id)
            return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

// HANDLING 3 CASES OF DELETION { HEAD , MID , TAIL }
//static void delete_patient_logic(patient **tmp, patient **prev) {
//    if (*tmp != NULL) {
//        if (head == tail) {
//            head = NULL;
//            tail = NULL;
//        } else {
//            head = head->next;
//        }
//    } else {
//        *tmp = (*prev)->next;
//        if ((*prev)->next == tail) {
//            tail = (*prev);
//            tail->next = NULL;
//        } else {
//            (*prev)->next = (*prev)->next->next;
//        }
//    }
//}

//DELETING THE RESERVATIONS FOR THIS PATIENT IF EXIST
void delete_patient_reservations(patient *tmp) {
    for (int i = 0; i < SLOTS_NUM; ++i)
        if (reservation[i] == tmp) reservation[i] = NULL;
}
// ====================================== DELETION FUNCTION =========================================

/// ====================================== RESERVE FUNCTION =========================================
// RESERVES SLOTS FOR PATIENTS BY THERE IDS __ SHOWS AVAILABLE SLOTS FIRST
// OPTIONS AFTER RESERVATION -> { RESERVE ANOTHER SLOT }
void reserve_slot() {
    separator();
    available_slots();
    separator();
    printf("Choose the slot you want :");
    u8 selector;
    scanChar(&selector);
    while (selector > SLOTS_NUM || selector < 1 || reservation[selector - 1] != NULL) {
        invalid();
        scanChar(&selector);
    }
    printf("Enter the patient ID :");
    s32 id;
    patient *ptr = NULL;
    while (ptr == NULL) {
        scanInt(&id);
        ptr = get_patient_by_id(id);
        if (ptr == NULL)
            printf("Can't find such an id, try another one :");
    }
    reservation[selector - 1] = ptr;
    separator();
    printf("( %s ) is reserved for { %s , %d years old }\n", slots[selector - 1], ptr->name, ptr->age);
    separator();
    admin_or_exit();
    printf("2. Reserve another slot\n");
    selecting(reserve_slot);
}

// CHECK IF THERE ARE SLOTS AVAILABLE AND DISPLAY THEM TO MAKE ADMIN RESERVING FROM THEM
void available_slots() {
    u8 checker = 0;
    for (int i = 0; i < SLOTS_NUM; ++i)
        if (reservation[i] == NULL) {
            if (checker == 0)
                printf("Available slots are :\n");
            printf("%d.  %s\n", i + 1, slots[i]);
            checker++;
        }
    if (checker == 0) {
        printf("There are no slots available\n");
        return admin_view();
    };
}
// ====================================== RESERVE FUNCTION =========================================

/// =============================== CANCEL RESERVATION FUNCTION ====================================
// TAKES A PATIENT'S ID AND DISPLAY ALL RESERVATIONS FOR THIS PATIENT WITH CONFIRMATION MESSAGE TO CANCEL IT
// OPTIONS AFTER CANCELLING -> { RESERVE ANOTHER SLOT }
void cancel_reservation() {
    separator();
    printf("Enter the patient ID :");
    s32 id;
    patient *ptr = NULL;
    while (ptr == NULL) {
        scanInt(&id);
        ptr = get_patient_by_id(id);
        if (ptr == NULL)
            printf("Can't find such an id, try another one :");
    }
    u8 index = 0, selector;
    for (int i = 0; i < SLOTS_NUM; ++i)
        if (reservation[i] == ptr) {
            index++;
            separator();
            printf("This patient reserves ( %s ) slot :\n", slots[i]);
            printf("0. Cancel reservation\n"
                   "1. Keep it\n");
            separator();
            choice();
            scanChar(&selector);
            while (selector != 0 && selector != 1) {
                invalid();
                scanChar(&selector);
            }
            if (!selector) reservation[i] = NULL;
        }
    if (index == 0) printf("There are no reservations for this patient\n");
    separator();
    admin_or_exit();
    printf("2. Cancel another reservation\n");
    selecting(cancel_reservation);
}
// =============================== CANCEL RESERVATION FUNCTION ====================================

/// ============================ DISPLAY PATIENTS' DATA FUNCTION ==================================
void view_patients() {
    separator();
    patient *tmp = head;
    int index = 1;
    while (tmp != NULL) {
        printf("%d. %d --> { %s , %d years old , %s }\n", index, tmp->id, tmp->name, tmp->age,
               genders[tmp->gender]);
        index++;
        tmp = tmp->next;
    }
    if (index == 1) printf("There are no patients yet\n");
    separator();
    admin_or_exit();
    selecting(NULL);
}
// ============================ DISPLAY PATIENTS' DATA FUNCTION ==================================

