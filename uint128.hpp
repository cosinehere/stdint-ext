/**
 * @file uint128.hpp
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2021-09-02
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#ifndef _UINT128_HPP_
#define _UINT128_HPP_

#include <cstdint>

class uint128_t {
private:
    uint64_t h, l;

public:
    uint128_t() = default;

    uint128_t(uint64_t high, uint64_t low) : h(high), l(low) {}

    uint128_t(const uint128_t &o) {
        h = o.h;
        l = o.l;
    }

    uint128_t &operator=(const uint128_t &o) {
        h = o.h;
        l = o.l;
        return *this;
    }

    uint128_t(uint128_t &&o) = default;

    uint128_t &operator=(uint128_t &&o) = default;

    ~uint128_t() = default;

    uint64_t low() { return l; }

    uint64_t high() { return h; }

    bool operator==(const uint128_t &o) const { return (h == o.h && l == o.l); }

    bool operator!=(const uint128_t &o) const { return (h != o.h || l != o.l); }

    bool operator>(const uint128_t &o) const {
        return (h > o.h || (h == o.h && l > o.l));
    }

    bool operator>=(const uint128_t &o) const {
        return (h > o.h || (h == o.h && l >= o.l));
    }

    bool operator<(const uint128_t &o) const {
        return (h < o.h || (h == o.h && l < o.l));
    }

    bool operator<=(const uint128_t &o) const {
        return (h < o.h || (h == o.h && h <= o.l));
    }

    bool operator&&(const uint128_t &o) { return (l || h) && (o.l || o.h); }

    bool operator||(const uint128_t &o) { return (l || h) || (o.l || o.h); }

    bool operator()() { return h || l; }

    uint128_t operator~() { return uint128_t(~h, ~l); }

    uint128_t operator&(const uint128_t &o) {
        return uint128_t(h & o.h, l & o.l);
    }

    uint128_t &operator&=(const uint128_t &o) {
        h &= o.h;
        l &= o.l;
        return *this;
    }

    uint128_t operator|(const uint128_t &o) {
        return uint128_t(h | o.h, l | o.l);
    }

    uint128_t &operator|=(const uint128_t &o) {
        h |= o.h;
        l |= o.l;
        return *this;
    }

    uint128_t operator^(const uint128_t &o) {
        return uint128_t(h ^ o.h, l ^ o.l);
    }

    uint128_t &operator^=(const uint128_t &o) {
        h ^= o.h;
        l ^= o.l;
        return *this;
    }

    uint128_t &operator++() {
        h += (l + 1 < l);
        l += 1;
        return *this;
    }

    uint128_t operator+(const uint128_t &o) {
        return uint128_t(h + o.h + (l + o.l < l), l + o.l);
    }

    uint128_t &operator+=(const uint128_t &o) {
        h += o.h + (o.l + l < l);
        l += o.l;
        return *this;
    }

    uint128_t &operator--() {
        h -= (l < 1);
        l -= 1;
        return *this;
    }

    uint128_t operator-(const uint128_t &o) {
        return uint128_t(h - o.h - (o.l > l), l - o.l);
    }

    uint128_t &operator-=(const uint128_t &o) {
        h -= o.h + (o.l > l);
        l -= o.l;
        return *this;
    }

    uint128_t operator*(const uint128_t &o) {
        uint64_t ll = l & 0xffffffff, lh = (l >> 32) & 0xffffffff;
        uint64_t oll = o.l & 0xffffffff, olh = (o.l >> 32) & 0xffffffff;
        uint64_t tll = ll * oll, tlh = ll * olh + lh * oll;
        uint64_t tc = lh * olh + (tlh >> 32);
        return uint128_t(h * o.l + l * o.h + tc, tll | ((tlh & 0xffffffff) << 32));
    }

    uint128_t operator/(const uint128_t &o) {
        if (!o.h && !o.l) { return uint128_t(0, 0); }
        if (h < o.h || (h == o.h && l < o.l)) { return uint128_t(0, 0); }

        uint128_t ret(0, 0);
        uint128_t dividend(h, l);
        for (uint64_t i = o.zeros() - dividend.zeros(); i > 0 && dividend >=o; --i) {
            uint128_t fraction;
            if (i >= 64) {
                fraction = uint128_t(1ull << (i - 64), 0);
            } else {
                fraction = uint128_t(0, 1ull << i);
            }

            if (dividend >= fraction * o) {
                ret += fraction;
                dividend -= fraction * o;
            }
        }

        return ret;
    }

private:
    const uint32_t zeros() const {
        if (h) {
            return __builtin_clzll(h);
        } else {
            return 64 + __builtin_clzll(l);
        }
    }
};

#endif
