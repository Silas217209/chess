#include <immintrin.h>

#include <bit>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <iostream>

#include "Bitboard.hpp"
#include "Lookup.hpp"

auto main(int argc, char* argv[]) -> int {
    for (size_t square = 0; square < 64; square++) {
        Bitboard mask = lookup::rook_mask[square];

        uint64_t max_blockers = pow(2, std::popcount(mask.value));
        for (size_t i = 0; i < max_blockers; i++) {
            Bitboard blockers = _pdep_u64(i, mask.value);

            // North

        }

        std::cout << max_blockers << "\n";
    }

    return 0;
}
