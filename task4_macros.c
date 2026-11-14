#include <stdio.h>

#define RUPEES_TO_PAISE(rs) ((long)((rs) * 100.0 + 0.5))
#define MAX(a, b)           (((a) > (b)) ? (a) : (b))
#define MIN(a, b)           (((a) < (b)) ? (a) : (b))
#define SQUARE(x)           ((x) * (x))

int main(void) {
    int a = 4, i = 5, j = 3;

    printf("SQUARE(a + 1) = %d\n", SQUARE(a + 1));
    printf("MAX(120, 350) = %d\n", MAX(120, 350));
    printf("Paise for Rs 162.50 = %ld\n", RUPEES_TO_PAISE(162.50));

    /* Pitfall demo: double evaluation */
    int m = MAX(i++, j);
    printf("After MAX(i++, j): m = %d, i = %d (incremented twice!)\n", m, i);
    return 0;
}
