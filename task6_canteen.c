#include <stdio.h>
#include <string.h>

typedef struct { int day, month, year; } Date;
typedef struct { int hour, minute; } Time;

enum ItemKind { PACKAGED, COOKED, COMBO };

typedef struct {
    int id;
    char name[40];
    enum ItemKind kind;
    union {
        Date expiry;
        Time prepared;
        int combo_ids[3];
    } details;
    int price_paise;
    int stock;
    int revenue_paise;
} MenuItem;

void record_sale(MenuItem *item, int qty) {
    if (item->stock < qty) {
        printf("[ERR ] Sale rejected: Requested %d x %s, only %d in stock!\n",
               qty, item->name, item->stock);
        return;
    }
    item->stock -= qty;
    int sale_paise = qty * item->price_paise;
    item->revenue_paise += sale_paise;

    if (item->kind == COOKED) {
        printf("[SALE] Sold %d x %s (Cooked @ %02d:%02d) -> Rs %.2f | Remaining stock: %d\n",
               qty, item->name, item->details.prepared.hour, item->details.prepared.minute,
               sale_paise / 100.0, item->stock);
    } else {
        printf("[SALE] Sold %d x %s -> Rs %.2f | Remaining stock: %d\n",
               qty, item->name, sale_paise / 100.0, item->stock);
    }
}

void check_expiry(const MenuItem *item, Date today) {
    if (item->kind == PACKAGED &&
        item->details.expiry.year == today.year &&
        item->details.expiry.month == today.month &&
        (item->details.expiry.day - today.day) <= 2 &&
        (item->details.expiry.day - today.day) >= 0) {
        printf("[WARN] EXPIRY ALERT: %s expires on %02d/%02d/%04d (within 2 days!)\n",
               item->name, item->details.expiry.day, item->details.expiry.month, item->details.expiry.year);
    }
}

void sort_by_revenue(MenuItem items[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int max_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (items[j].revenue_paise > items[max_idx].revenue_paise) {
                max_idx = j;
            }
        }
        if (max_idx != i) {
            MenuItem tmp = items[i];
            items[i] = items[max_idx];
            items[max_idx] = tmp;
        }
    }
}

int main(void) {
    Date today = {12, 11, 2026};
    MenuItem menu[4] = {
        {1, "Masala Dosa", COOKED, {.prepared = {8, 30}}, 5000, 20, 0},
        {2, "Filter Coffee", COOKED, {.prepared = {8, 0}}, 2000, 10, 0},
        {3, "Paneer Wrap", PACKAGED, {.expiry = {14, 11, 2026}}, 6000, 15, 12000},
        {4, "Combo Meal #1 (Dosa + Coffee)", COMBO, {.combo_ids = {1, 2, 0}}, 6000, 10, 48000}
    };

    record_sale(&menu[0], 3);
    record_sale(&menu[1], 25);
    check_expiry(&menu[2], today);

    sort_by_revenue(menu, 4);
    printf("--- Daily Revenue Summary (Sorted Descending) ---\n");
    for (int i = 0; i < 3; i++) {
        const char *label = (menu[i].kind == COOKED) ? " (Cooked)" :
                            (menu[i].kind == PACKAGED) ? " (Packaged)" : "";
        char display_name[60];
        snprintf(display_name, sizeof(display_name), "%s%s", menu[i].name, label);
        printf("%d. %-31s | Revenue: Rs %.2f\n", i + 1, display_name, menu[i].revenue_paise / 100.0);
    }
    return 0;
}
