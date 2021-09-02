#include <cstdio>

#include "uint128.hpp"

int main() {

    uint128_t a(10);
    uint128_t b(a);

    printf("a == b %d\n", a == b);
    printf("a != b %d\n", a != b);
    printf("a > b %d\n", a > b);
    printf("a >= b %d\n", a >= b);
    printf("a < b %d\n", a < b);
    printf("a <= b %d\n", a <= b);

    uint128_t c = a & (b + 1);
    printf("c.l %lu c.h %lu a && b %d\n", c.high(), c.low(), a && b);
    return 0;
}
