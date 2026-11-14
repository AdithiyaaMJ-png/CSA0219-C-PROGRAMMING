#include <stdio.h>

int next_token_static(void) {
    static int token = 1000;
    return ++token;
}

int next_token_auto(void) {
    auto int token = 1000;
    return ++token;
}

int main(void) {
    printf("static: %d %d %d\n", next_token_static(), next_token_static(), next_token_static());
    printf("auto: %d %d %d\n", next_token_auto(), next_token_auto(), next_token_auto());
    printf("Single printf unspecified order example: %d %d %d\n",
           next_token_static(), next_token_static(), next_token_static());
    return 0;
}
