#include <stdio.h>

int server_calls = 0;

int verify_disability_server(int passenger_id) {
    server_calls++;
    return (passenger_id % 10 == 0);
}

int main(void) {
    int eligible_a = 0, eligible_b = 0, eligible_bit = 0;

    /* Order A: (is_senior && is_eligible_class) || verify_disability_server() */
    server_calls = 0;
    for (int i = 0; i < 1000; i++) {
        int is_senior = (i % 5 == 0);         /* 200 passengers */
        int is_eligible_class = (i % 2 == 0); /* 100 both senior & eligible class */
        /* Note: 360 skipped when local checks succeed (e.g. 36% pass locally) */
        is_senior = (i < 600);
        is_eligible_class = (i % 5 < 3);      /* 360 out of 1000 pass local check */
        if ((is_senior && is_eligible_class) || verify_disability_server(i)) {
            eligible_a++;
        }
    }
    int calls_a = server_calls;

    /* Order B: verify_disability_server() || (is_senior && is_eligible_class) */
    server_calls = 0;
    for (int i = 0; i < 1000; i++) {
        int is_senior = (i < 600);
        int is_eligible_class = (i % 5 < 3);
        if (verify_disability_server(i) || (is_senior && is_eligible_class)) {
            eligible_b++;
        }
    }
    int calls_b = server_calls;

    /* Bitwise (& / |) Non-Short-Circuit Version */
    server_calls = 0;
    for (int i = 0; i < 1000; i++) {
        int is_senior = (i < 600);
        int is_eligible_class = (i % 5 < 3);
        if ((is_senior & is_eligible_class) | verify_disability_server(i)) {
            eligible_bit++;
        }
    }
    int calls_bit = server_calls;

    printf("Order A: (is_senior && is_eligible_class) || verify_disability_server()\n");
    printf("  -> Server Calls: %d / 1000 passengers (%d skipped via && and || short-circuit)\n",
           calls_a, 1000 - calls_a);
    printf("Order B: verify_disability_server() || (is_senior && is_eligible_class)\n");
    printf("  -> Server Calls: %d / 1000 passengers (0 skipped; server called unconditionally!)\n",
           calls_b);
    printf("Bitwise (& / |) Non-Short-Circuit Version:\n");
    printf("  -> Server Calls: %d / 1000 passengers (all operands always evaluated)\n",
           calls_bit);

    (void)eligible_a; (void)eligible_b; (void)eligible_bit;
    return 0;
}
