#pragma once

#include <cstddef>
#include <cstdint>

#include "Board.hpp"

class MoveReceiver {
  public:
    static inline uint64_t nodes;

    template<class BoardStatus>
    static void KingMove(const Board& board, size_t from, size_t to) {
        Board newBoard = board;
        newBoard.movePiece(from, to);
        nodes++;
    }
};
