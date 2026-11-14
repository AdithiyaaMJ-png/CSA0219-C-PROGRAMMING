#include <stdio.h>

int main(void) {
    /* Task 6: Wrong format specifier demonstration */
    long district_total = 3500000000L;
    printf("Wrong (%%d): %d | Correct (%%ld): %ld\n", (int)district_total, district_total);

    /* Task 7: Three type conversion surprises */
    int units = 150;
    double surprise1 = (units / 100) * 225.0;  /* Integer division: 150/100 -> 1 */
    unsigned int u = 10; int s = -20;
    int surprise2 = (s < u);                   /* Signed -20 converts to huge unsigned -> 0 */
    long big_paise = 3000000000L;
    int surprise3 = (int)big_paise;            /* Narrowing overflow on 32-bit int */

    printf("Surprise 1 (int div): %.2f (expected 337.50)\n", surprise1);
    printf("Surprise 2 (-20 < 10u): %d (expected 1)\n", surprise2);
    printf("Surprise 3 (long->int): %d (overflowed!)\n", surprise3);
    return 0;
}
