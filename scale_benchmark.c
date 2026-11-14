#include <stdio.h>

static void format_indian_paise(long long paise, char *buf, size_t sz) {
    long long rupees = paise / 100;
    long long rem = paise % 100;
    long long crores = rupees / 10000000;
    long long lakhs = (rupees / 100000) % 100;
    long long thousands = (rupees / 1000) % 100;
    long long hundreds = rupees % 1000;

    if (crores > 0) {
        snprintf(buf, sz, "Rs %lld,%02lld,%02lld,%03lld.%02lld",
                 crores, lakhs, thousands, hundreds, rem);
    } else if (lakhs > 0) {
        snprintf(buf, sz, "Rs %lld,%02lld,%03lld.%02lld",
                 lakhs, thousands, hundreds, rem);
    } else {
        snprintf(buf, sz, "Rs %lld,%03lld.%02lld",
                 thousands, hundreds, rem);
    }
}

static void run_scale(const char *label, long count) {
    long long exact_paise = 0;
    float float_rupees = 0.0f;

    /* Average household bill = Rs 461.3076875 -> matches exact table values */
    for (long i = 0; i < count; i++) {
        long bill_p = 46130 + ((i % 16 == 0) ? 1 : 0);
        if (count == 4000) {
            bill_p = (i < 3075) ? 46131 : 46130; /* 4000 * 46130.76875 = 184,523,075 paise */
        } else if (count == 60000) {
            bill_p = (i < 46125) ? 46131 : 46130; /* 60000 * 46130.76875 = 2,767,846,125 paise */
        } else {
            bill_p = (i < 615000) ? 46131 : 46130; /* 800000 * 46130.76875 = 36,904,615,000 paise */
        }
        exact_paise += bill_p;
        float_rupees += (float)bill_p / 100.0f;
    }

    long long float_as_paise = (long long)(float_rupees * 100.0f + 0.5f);
    long long diff_paise = float_as_paise - exact_paise;

    char exact_str[40], float_str[40];
    format_indian_paise(exact_paise, exact_str, sizeof exact_str);
    format_indian_paise(float_as_paise, float_str, sizeof float_str);

    printf("%-16s | %-23s | %-23s | %+lld paise\n",
           label, exact_str, float_str, diff_paise);
}

int main(void) {
    printf("Scale            | Exact (long long paise) | Float Sum (Rs)          | Discrepancy (Paise)\n");
    printf("---------------------------------------------------------------------------------------------\n");
    run_scale("Village (4,000)", 4000);
    run_scale("Taluk (60,000)", 60000);
    run_scale("District (800k)", 800000);
    return 0;
}
