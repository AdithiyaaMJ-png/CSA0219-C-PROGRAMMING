#include <stdio.h>

#define MAX_MONTHS 360

int main(void) {
    double balance = 10000.00;
    double monthly_rate = 0.02;
    double emi = 2000.00;
    double total_interest = 0.0;
    int month = 0;

    printf("Month | Opening (Rs) | Interest (Rs) | Payment (Rs) | Closing (Rs)\n");
    printf("------------------------------------------------------------------\n");

    while (balance > 0.005) {
        month++;
        if (month > MAX_MONTHS) {
            printf("Error: Monthly repayment insufficient to amortize principal within 30-year limit.\n");
            break;
        }
        double opening = balance;
        double interest = opening * monthly_rate;
        double payment = emi;

        if (opening + interest <= emi) {
            payment = opening + interest;
            balance = 0.0;
        } else {
            balance = opening + interest - payment;
        }
        total_interest += interest;

        printf("%5d | %12.2f | %13.2f | %12.2f | %12.2f\n",
               month, opening, interest, payment, balance);
    }

    printf("Total Months: %d | Total Interest Paid: Rs %.2f\n", month, total_interest);
    return 0;
}
