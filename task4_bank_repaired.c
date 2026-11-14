#include <stdio.h>

struct account {
    int number;
    double balance;
};

void addInterest(struct account *a, double rate, int print_addr) {
    if (print_addr) {
        printf("addInterest() ptr = %p (Same address!)\n", (void *)a);
    }
    a->balance += a->balance * rate;
}

int main(void) {
    struct account list[3] = {
        {101, 5000.00},
        {102, 12000.00},
        {103, 800.00}
    };

    printf("main() &list[0] = %p | ", (void *)&list[0]);
    for (int i = 0; i < 3; i++) {
        addInterest(&list[i], 0.04, i == 0);
    }

    for (int i = 0; i < 3; i++) {
        struct account *p = &list[i];
        printf("%d %.2f\n", p->number, p->balance);
    }
    return 0;
}
