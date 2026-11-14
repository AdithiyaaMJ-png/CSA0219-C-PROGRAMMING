/* billing.c */
#include <stdio.h>
#include "billing.h"

unsigned int calc_consumption(meter_t prev, meter_t curr) {
    unsigned int units = (meter_t)(curr - prev);
    int rollover = (curr < prev) ? 1 : 0;
    DBG_PRINT("prev=%u, curr=%u, rollover=%d, units=%u", prev, curr, rollover, units);
    return units;
}

long compute_bill(unsigned int units) {
    long s1_units = 0, s2_units = 0, s3_units = 0;

    if (units > SLAB2_UNITS) {
        s1_units = SLAB1_UNITS;
        s2_units = SLAB2_UNITS - SLAB1_UNITS;
        s3_units = units - SLAB2_UNITS;
    } else if (units > SLAB1_UNITS) {
        s1_units = SLAB1_UNITS;
        s2_units = units - SLAB1_UNITS;
    } else {
        s1_units = units;
    }

    long s1_paise = s1_units * RATE1_PAISE;
    long s2_paise = s2_units * RATE2_PAISE;
    long s3_paise = s3_units * RATE3_PAISE;

    DBG_PRINT("slab1=%ld(%ldp), slab2=%ld(%ldp), slab3=%ld(%ldp), fixed=%ldp",
              s1_units, s1_paise, s2_units, s2_paise, s3_units, s3_paise, FIXED_CHARGE_PAISE);

    return FIXED_CHARGE_PAISE + s1_paise + s2_paise + s3_paise;
}
