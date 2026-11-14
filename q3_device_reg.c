#include <stdio.h>

enum { LIGHT = 0, FAN = 1, AC = 2, HEATER = 3, PUMP = 4 };

unsigned char switch_on(unsigned char reg, int dev)  { return reg | (1U << dev); }
unsigned char switch_off(unsigned char reg, int dev) { return reg & ~(1U << dev); }
unsigned char toggle(unsigned char reg, int dev)     { return reg ^ (1U << dev); }
int is_on(unsigned char reg, int dev)                { return (reg >> dev) & 1U; }

int count_on(unsigned char reg) {
    int c = 0;
    for (int i = 0; i < 8; i++) c += (reg >> i) & 1U;
    return c;
}

void show(unsigned char reg) {
    for (int bit = 7; bit >= 0; bit--) putchar(((reg >> bit) & 1U) ? '1' : '0');
    putchar('\n');
}

int main(void) {
    unsigned char reg = 0;
    reg = switch_on(reg, LIGHT);
    reg = switch_on(reg, AC);
    show(reg);
    reg = toggle(reg, FAN);
    reg = switch_off(reg, LIGHT);
    show(reg);
    printf("AC is %s, PUMP is %s (Active devices: %d)\n",
           is_on(reg, AC) ? "ON" : "OFF", is_on(reg, PUMP) ? "ON" : "OFF", count_on(reg));
    return 0;
}
