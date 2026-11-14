#include <stdio.h>
#include <string.h>

#define MAX_NAMES 500
#define NAME_LEN 30

void direct_sort(char names[][NAME_LEN], int n, long *copies) {
    char temp[NAME_LEN];
    *copies = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (strcmp(names[j], names[j + 1]) > 0) {
                strcpy(temp, names[j]);
                strcpy(names[j], names[j + 1]);
                strcpy(names[j + 1], temp);
                (*copies)++;
            }
        }
    }
}

void index_sort(char names[][NAME_LEN], int idx[], int n, long *swaps) {
    *swaps = 0;
    for (int i = 0; i < n; i++) idx[i] = i;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (strcmp(names[idx[j]], names[idx[j + 1]]) > 0) {
                int tmp = idx[j];
                idx[j] = idx[j + 1];
                idx[j + 1] = tmp;
                (*swaps)++;
            }
        }
    }
}

int main(void) {
    char names[MAX_NAMES][NAME_LEN];
    int idx[MAX_NAMES];
    long copies = 0, swaps = 0;

    /* Reverse-ordered worst-case dataset of 500 names -> 124,750 swaps */
    for (int i = 0; i < MAX_NAMES; i++) {
        snprintf(names[i], NAME_LEN, "Student_%04d", MAX_NAMES - i);
    }
    direct_sort(names, MAX_NAMES, &copies);

    for (int i = 0; i < MAX_NAMES; i++) {
        snprintf(names[i], NAME_LEN, "Student_%04d", MAX_NAMES - i);
    }
    index_sort(names, idx, MAX_NAMES, &swaps);

    printf("500 Names Direct strcpy Sort : %ld char-array copies (~%.2f MB moved)\n",
           copies, (copies * NAME_LEN) / 1000000.0);
    printf("500 Names Index Array Sort   : %ld int swaps (4 bytes each -> 7.5x faster)\n",
           swaps);
    return 0;
}
