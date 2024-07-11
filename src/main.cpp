#include "Board.hpp"

auto main(int argc, char* argv[]) -> int {
    auto board = Board();

    std::cout << board.show_board() << "\n";

    return 0;
}
