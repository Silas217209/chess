#include <immintrin.h>

#include <array>
#include <bit>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <ios>
#include <iostream>

#include "Bitboard.hpp"
#include "Lookup.hpp"

auto main(int argc, char* argv[]) -> int {
    std::ofstream file;
    file.open("l.hpp");

    file << "#include <array>\n\n";
    file << "const std::array<Bitboard, 102400> rook_mask = {\n";

    std::array<size_t, 64> offsets = {};

    int offset = 0;
    for (size_t square = 0; square < 64; square++) {
        offsets[square] = offset;
        Bitboard mask = lookup::rook_mask[square];

        uint64_t max_blockers = pow(2, std::popcount(mask.value));
        for (size_t i = 0; i < max_blockers; i++) {
            Bitboard blockers = _pdep_u64(i, mask.value);
            Bitboard moves = 0;
            Bitboard start_square = Bitboard(1) << square;

            // North
            {
                Bitboard curr_square = start_square;
                size_t curr_rank = lookup::rank(square);
                while ((curr_square & blockers) == 0 && curr_rank <= 6) {
                    moves |= curr_square;

                    curr_square <<= 8;
                    curr_rank++;
                }
            }
            // South
            {
                Bitboard curr_square = start_square;
                size_t curr_rank = lookup::rank(square);
                while ((curr_square & blockers) == 0 && curr_rank >= 1) {
                    moves |= curr_square;

                    curr_square >>= 8;
                    curr_rank--;
                }
            }

            // East
            {
                Bitboard curr_square = start_square;
                size_t curr_file = lookup::file(square);
                while ((curr_square & blockers) == 0 && curr_file <= 6) {
                    moves |= curr_square;

                    curr_square <<= 1;
                    curr_file++;
                }
            }
            // West
            {
                Bitboard curr_square = start_square;
                size_t curr_file = lookup::file(square);
                while ((curr_square & blockers) == 0 && curr_file >= 1) {
                    moves |= curr_square;

                    curr_square >>= 1;
                    curr_file--;
                }
            }

            moves ^= start_square;
            file << "    0x" << std::hex << std::setw(16) << std::setfill('0') << moves.value << ",\n";
            offset++;
        }
    }
    file << "};";
    file.close();

    for (size_t offset : offsets) {
        std::cout << offset << ",\n";
    }

    return 0;
}
