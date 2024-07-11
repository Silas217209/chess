#include <cstddef>
#include <iomanip>
#include <ios>
#include <iostream>

#include "Bitboard.hpp"
#include "Lookup.hpp"

auto main(int argc, char* argv[]) -> int {
    const size_t square = 63;

    std::cout << lookup::bishop_mask(0).value;

    return 0;

    for (size_t i = 0; i < 64; i++) {
        Bitboard moves = lookup::bishop_mask(i);
        std::cout << "0x" << std::setw(16) << std::setfill('0') << std::hex << moves.value << ",\n";
    }

    return 0;
}
