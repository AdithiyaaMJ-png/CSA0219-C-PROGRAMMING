#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 100

typedef struct { int day, month, year; } Date;
typedef struct { int systolic, diastolic; } BloodPressure;

typedef struct {
    char name[40];
    int age;
    char phone[16];     /* 10 digits + country code + '\0' */
    BloodPressure bp;
    Date visitDate;
} Patient;

int addPatient(Patient list[], int *count, const Patient *p) {
    if (*count >= MAX_PATIENTS) return 0; /* Prevents buffer overflow */
    list[*count] = *p;
    (*count)++;
    return 1;
}
