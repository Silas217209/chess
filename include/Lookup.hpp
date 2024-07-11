#pragma once

#include <sys/types.h>

#include <array>
#include <cstddef>

#include "Bitboard.hpp"

namespace lookup {
const std::array<Bitboard, 8> rank_bitboards = {
    0x00000000000000FF,
    0x000000000000FF00,
    0x0000000000FF0000,
    0x00000000FF000000,
    0x000000FF00000000,
    0x0000FF0000000000,
    0x00FF000000000000,
    0xFF00000000000000
};

const std::array<Bitboard, 8> file_bitboards = {
    0x0101010101010101,
    0x0202020202020202,
    0x0404040404040404,
    0x0808080808080808,
    0x1010101010101010,
    0x2020202020202020,
    0x4040404040404040,
    0x8080808080808080,
};

constexpr auto file(const size_t square) -> size_t { return square % 8; }

constexpr auto rank(const size_t square) -> size_t { return square / 8; }

constexpr auto knight_moves(const size_t square) -> Bitboard {
    Bitboard curr_square = Bitboard(1) << square;
    Bitboard moves = 0;

    size_t curr_file = file(square);
    size_t curr_rank = rank(square);
    
    // 1 right 2 up
    if (square <= 46) moves |= square << 17;
    // 1 left 2 up
    if (square <= 47) moves |= square << 15;
    // 2 right 1 up
    if (square <= 53) moves |= square << 10;
    // 2 left 1 up
    if (square <= 55) moves |= square << 6;
    // 2 right 1 down
    moves |= square >> 6;
    // 2 left 1 down
    moves |= square << 10;
    // 1 right 2 down
    moves |= square << 15;
    // 1 left 2 down
    moves |= square << 16;

    return moves;
}
}  // namespace lookup
