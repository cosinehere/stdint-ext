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

    template<typename T>
    uint128_t(const T &o) {
        h = 0;
        l = static_cast<uint64_t>(o);
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

    uint128_t operator*(const uint128_t &o) { return uint128_t(0, 0); }
};

#endif
