#include <stdio.h>
#include <stdint.h>
#include <limits.h>

#define SLAB1_UNITS        100U
#define SLAB2_UNITS        200U
#define RATE1_PAISE        0LL
#define RATE2_PAISE        225LL
#define RATE3_PAISE        450LL
#define FIXED_CHARGE_PAISE 5000LL
#define MAX_MONTHLY_UNITS  5000U

typedef uint16_t meter_t;

unsigned int calc_consumption(meter_t prev, meter_t curr) {
    return (meter_t)(curr - prev);
}

long long compute_bill_paise(unsigned int units) {
    long long paise = FIXED_CHARGE_PAISE;
    if (units > SLAB2_UNITS) {
        paise += (long long)(units - SLAB2_UNITS) * RATE3_PAISE;
        paise += (long long)(SLAB2_UNITS - SLAB1_UNITS) * RATE2_PAISE;
    } else if (units > SLAB1_UNITS) {
        paise += (long long)(units - SLAB1_UNITS) * RATE2_PAISE;
    }
    return paise;
}

int main(void) {
    int n;
    long long grand_total_paise = 0;

    printf("Enter number of households: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        fprintf(stderr, "Error: Invalid household count.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        unsigned int hh_id;
        long prev_in, curr_in;
        if (scanf("%u %ld %ld", &hh_id, &prev_in, &curr_in) != 3) {
            fprintf(stderr, "Error: Non-numeric input at record %d.\n", i + 1);
            return 1;
        }
        if (prev_in < 0 || curr_in < 0 || prev_in > 65535 || curr_in > 65535) {
            fprintf(stderr, "Error: Reading out of 16-bit meter range [0..65535].\n");
            continue;
        }
        unsigned int units = calc_consumption((meter_t)prev_in, (meter_t)curr_in);
        if (units > MAX_MONTHLY_UNITS) {
            fprintf(stderr, "Error: Implausible consumption (%u units) for HH %u.\n", units, hh_id);
            continue;
        }
        long long bill = compute_bill_paise(units);
        grand_total_paise += bill;
        printf("HH #%04u | Units: %4u | Fixed: Rs 50.00 | Energy: Rs %lld.%02lld | Total: Rs %lld.%02lld\n",
               hh_id, units, (bill - FIXED_CHARGE_PAISE) / 100, (bill - FIXED_CHARGE_PAISE) % 100,
               bill / 100, bill % 100);
    }

    printf("------------------------------------------------------------------------\n");
    printf("Batch Grand Total: Rs %lld.%02lld\n", grand_total_paise / 100, grand_total_paise % 100);
    return 0;
}
