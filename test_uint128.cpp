#include <cstdio>

#include "uint128.hpp"

int main() {

    uint128_t a(0, 10);
    uint128_t b(a);

    printf("a == b %d\n", a == b);
    printf("a != b %d\n", a != b);
    printf("a > b %d\n", a > b);
    printf("a >= b %d\n", a >= b);
    printf("a < b %d\n", a < b);
    printf("a <= b %d\n", a <= b);

    uint128_t c = a & (b + uint128_t(0, 1));
    b += uint128_t(0, 1);
    printf("c.l %lu c.h %lu\na == b %d\n", c.high(), c.low(), a == b);

    uint128_t d = uint128_t(0x10000ul, 0x123) * uint128_t(2, 1);
    printf("d.h %016lx, d.l %016lx\n", d.high(), d.low());

    uint128_t e = uint128_t(0x21, 0x0) / uint128_t(0x0, 0x2);
    printf("e.h %016lx, e.l %016lx\n", e.high(), e.low());

    return 0;
}
