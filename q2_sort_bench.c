#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1000

typedef struct {
    long cmp;
    long swp;
} Metrics;

Metrics bubble_sort(int a[], int n) {
    Metrics m = {0, 0};
    for (int i = 0; i < n - 1; i++) {
        int swapped = 0;
        for (int j = 0; j < n - 1 - i; j++) {
            m.cmp++;
            if (a[j] > a[j + 1]) {
                int tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
                m.swp++;
                swapped = 1;
            }
        }
        if (!swapped) break;
    }
    return m;
}

Metrics selection_sort(int a[], int n) {
    Metrics m = {0, 0};
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            m.cmp++;
            if (a[j] < a[min_idx]) min_idx = j;
        }
        if (min_idx != i) {
            int tmp = a[i];
            a[i] = a[min_idx];
            a[min_idx] = tmp;
            m.swp++;
        }
    }
    return m;
}

Metrics insertion_sort(int a[], int n) {
    Metrics m = {0, 0};
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;
        while (j >= 0) {
            m.cmp++;
            if (a[j] > key) {
                a[j + 1] = a[j];
                m.swp++;
                j--;
            } else {
                break;
            }
        }
        a[j + 1] = key;
    }
    return m;
}

void run_case(const char *label, const int base[], int n) {
    int buf[N];

    memcpy(buf, base, n * sizeof(int));
    Metrics mb = bubble_sort(buf, n);

    memcpy(buf, base, n * sizeof(int));
    Metrics ms = selection_sort(buf, n);

    memcpy(buf, base, n * sizeof(int));
    Metrics mi = insertion_sort(buf, n);

    printf("%-14s | %7ld / %-7ld | %7ld / %-7ld | %7ld / %-7ld\n",
           label, mb.cmp, mb.swp, ms.cmp, ms.swp, mi.cmp, mi.swp);
}

int main(void) {
    int arr[N];

    printf("Input Order    | Bubble (Cmp/Swp)  | Selection (Cmp/Swp)| Insertion (Cmp/Swp)\n");
    printf("----------------------------------------------------------------------------\n");

    /* 1. Already Sorted */
    for (int i = 0; i < N; i++) arr[i] = 1000 + i;
    run_case("Already Sorted", arr, N);

    /* 2. Nearly Sorted (20 late registrations at the end) */
    for (int i = 0; i < N - 1; i++) arr[i] = 1000 + i + 1;
    arr[N - 1] = 1000 + (N - 21);
    run_case("Nearly Sorted", arr, N);

    /* 3. Random Order */
    srand(42);
    for (int i = 0; i < N; i++) arr[i] = 1000 + rand() % 9000;
    run_case("Random Order", arr, N);

    /* 4. Reverse Sorted */
    for (int i = 0; i < N; i++) arr[i] = 1000 + (N - i);
    run_case("Reverse Sorted", arr, N);

    return 0;
}
