#include <immintrin.h>

#include <cmath>
#include <cstddef>
#include <iomanip>
#include <iostream>

#include "Bitboard.hpp"
#include "Lookup.hpp"

auto main(int argc, char* argv[]) -> int {
    std::cout << "// white\n";
    for (int sq = 0; sq < 64; sq++) {
        Bitboard mask = 0ull;
        Bitboard sq_bb = 1ull << (sq);
        const size_t file = lookup::file(sq);
        const size_t rank = lookup::rank(sq);

        if (file >= 1 && rank <= 6)
            mask |= sq_bb << 7;

        if (file <= 6 && rank <= 6)
            mask |= sq_bb << 9;

        std::cout << "0x" << std::setw(16) << std::setfill('0') << std::hex << mask.value << ",\n";
    }
    std::cout << "// black\n";
    for (int sq = 0; sq < 64; sq++) {
        Bitboard mask = 0ull;
        Bitboard sq_bb = 1ull << (sq);
        const size_t file = lookup::file(sq);
        const size_t rank = lookup::rank(sq);

        if (file <= 6 && rank >= 1)
            mask |= sq_bb >> 7;

        if (file >= 1 && rank >= 1)
            mask |= sq_bb << 9;

        std::cout << "0x" << std::setw(16) << std::setfill('0') << std::hex << mask.value << ",\n";
    }

    return 0;
}
