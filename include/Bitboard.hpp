#pragma once

#include <cstdint>
#include <iostream>
#include <string>

#include "Color.hpp"

class Bitboard {
  public:
    uint64_t value;

    constexpr auto show_bitboard() const -> std::string;

    constexpr auto show_bitbaords(Bitboard other) const -> std::string;

    // Constructor
    constexpr Bitboard(uint64_t value = 0) : value(value) {}

    // clang-format off
    // Arithmetic operators
    constexpr auto operator+(const Bitboard& other) const -> Bitboard { return Bitboard(value + other.value); }
    constexpr auto operator-(const Bitboard& other) const -> Bitboard { return Bitboard(value - other.value); }

    // Bitwise operators
    constexpr auto operator&(const Bitboard& other) const -> Bitboard { return Bitboard(value & other.value); }
    constexpr auto operator|(const Bitboard& other) const -> Bitboard { return Bitboard(value | other.value); }
    constexpr auto operator^(const Bitboard& other) const -> Bitboard { return Bitboard(value ^ other.value); }
    constexpr auto operator~() const -> Bitboard { return Bitboard(~value); }
    constexpr auto operator<<(int shift) const -> Bitboard { return Bitboard(value << shift); }
    constexpr auto operator>>(int shift) const -> Bitboard { return Bitboard(value >> shift); }

    // Compound assignment operators
    constexpr auto operator+=(const Bitboard& other) -> Bitboard& { value += other.value; return *this; }
    constexpr auto operator-=(const Bitboard& other) -> Bitboard& { value -= other.value; return *this; }
    constexpr auto operator&=(const Bitboard& other) -> Bitboard& { value &= other.value; return *this; }
    constexpr auto operator|=(const Bitboard& other) -> Bitboard& { value |= other.value; return *this; }
    constexpr auto operator^=(const Bitboard& other) -> Bitboard& { value ^= other.value; return *this; }
    constexpr auto operator<<=(int shift) -> Bitboard& { value <<= shift; return *this; }
    constexpr auto operator>>=(int shift) -> Bitboard& { value >>= shift; return *this; }

    // Comparison operators
    constexpr auto operator==(const Bitboard& other) const -> bool { return value == other.value; }
    constexpr auto operator!=(const Bitboard& other) const -> bool { return value != other.value; }
    constexpr auto operator<(const Bitboard& other) const -> bool { return value < other.value; }
    constexpr auto operator>(const Bitboard& other) const -> bool { return value > other.value; }
    constexpr auto operator<=(const Bitboard& other) const -> bool { return value <= other.value; }
    constexpr auto operator>=(const Bitboard& other) const -> bool { return value >= other.value; }

    // Conversion operators
    constexpr explicit operator bool() const { return value != 0; }
    constexpr explicit operator uint64_t() const { return value; }

    // clang-format on
};

// constexpr implementation must be in header file
constexpr auto Bitboard::show_bitboard() const -> std::string {
    std::string result = "";
    for (int rank = 7; rank >= 0; rank--) {
        for (int file = 0; file < 8; file++) {
            uint64_t curr_field = 0x1 << (rank * 8 + file);

            if (curr_field & value) {
                result.append("● ");
            } else {
                result.append("○ ");
            }
        }
        result.append("\n");
    }

    return result;
}

constexpr auto Bitboard::show_bitbaords(Bitboard other) const -> std::string {
    std::string result = "";
    for (int rank = 7; rank >= 0; rank--) {
        for (int file = 0; file < 8; file++) {
            Bitboard curr_field = Bitboard(1) << (rank * 8 + file);

            if (curr_field & value && curr_field & other) {
                result.append(green("● "));
            } else if (curr_field & value) {
                result.append(blue("● "));
            } else if (curr_field & other) {
                result.append(red("● "));
            } else {
                result.append("○ ");
            }
        }
        result.append("\n");
    }

    return result;
}
