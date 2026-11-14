#include <stdio.h>

int main(void) {
    double price = 250.0;
    int qty = 5, senior = 1, count = 10;

    /* Buggy expression without brackets */
    double buggy_total = price * qty - price * qty * 15 / 100 * senior + price * qty * 5 / 100;
    double buggy_net   = buggy_total > 1000 ? buggy_total - 50 : buggy_total;

    /* Corrected readable calculation using intermediate variables & brackets */
    double gross       = price * qty;
    double discount    = senior ? (gross * 0.15) : 0.0;
    double taxable_amt = gross - discount;
    double gst         = taxable_amt * 0.05;
    double fixed_total = taxable_amt + gst;
    double fixed_net   = (fixed_total > 1000.0) ? (fixed_total - 50.0) : fixed_total;

    printf("Buggy Total : Rs %.2f | Buggy Net : Rs %.2f\n", buggy_total, buggy_net);
    printf("Fixed Total : Rs %.2f | Fixed Net : Rs %.2f\n", fixed_total, fixed_net);
    return 0;
}
