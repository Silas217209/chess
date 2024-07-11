#pragma once

#include "Bitboard.hpp"

// 56 57 58 59 60 61 62 63
// 48 49 50 51 52 53 54 55
// 40 41 42 43 44 45 46 47
// 32 33 34 35 36 37 38 39
// 24 25 26 27 28 29 30 31
// 16 17 18 19 20 21 22 23
// 08 09 10 11 12 13 14 15
// 00 01 02 03 04 05 06 07
//
// ♜ ♞ ♝ ♛ ♚ ♝ ♞ ♜
// ♟︎ ♟︎ ♟︎ ♟︎ ♟︎ ♟︎ ♟︎ ♟︎
// · · · · · · · ·
// · · · · · · · ·
// · · · · · · · ·
// · · · · · · · ·
// ♙ ♙ ♙ ♙ ♙ ♙ ♙ ♙
// ♖ ♘ ♗ ♕ ♔ ♗ ♘ ♖
class Board {
  public:
    const Bitboard white;
    const Bitboard black;
    const Bitboard occ;

    const Bitboard w_king;
    const Bitboard b_king;
    const Bitboard w_queen;
    const Bitboard b_queen;
    const Bitboard w_rooks;
    const Bitboard b_rooks;
    const Bitboard w_bishops;
    const Bitboard b_bishops;
    const Bitboard w_knights;
    const Bitboard b_knights;
    const Bitboard w_pawns;
    const Bitboard b_pawns;

    constexpr auto show_board() const -> std::string;

    template<bool is_white>
    constexpr auto enemy_or_empty() const -> Bitboard;

    constexpr Board(
        Bitboard w_king,
        Bitboard b_king,
        Bitboard w_queen,
        Bitboard b_queen,
        Bitboard w_rooks,
        Bitboard b_rooks,
        Bitboard w_bishops,
        Bitboard b_bishops,
        Bitboard w_knights,
        Bitboard b_knights,
        Bitboard w_pawns,
        Bitboard b_pawns
    ) :
        white(w_king | w_queen | w_rooks | w_bishops | w_knights | w_pawns),
        black(b_king | b_queen | b_rooks | b_bishops | b_knights | b_pawns),
        occ(white | black),
        w_king(w_king),
        b_king(b_king),
        w_queen(w_queen),
        b_queen(b_queen),
        w_rooks(w_rooks),
        b_rooks(b_rooks),
        w_bishops(w_bishops),
        b_bishops(b_bishops),
        w_knights(w_knights),
        b_knights(b_knights),
        w_pawns(w_pawns),
        b_pawns(b_pawns) {}

    constexpr Board() :
        w_king(0x10),
        w_queen(0x8),
        w_rooks(0x81),
        w_bishops(0x24),
        w_knights(0x42),
        w_pawns(0xFF00),
        b_king(0x1000000000000000),
        b_queen(0x800000000000000),
        b_rooks(0x8100000000000000),
        b_bishops(0x2400000000000000),
        b_knights(0x4200000000000000),
        b_pawns(0xFF000000000000),
        white(0xFFFF),
        black(0xFFFF000000000000),
        occ(0xFFFF00000000FFFF) {}
};

constexpr auto Board::show_board() const -> std::string {
    std::string result = "";
    for (int rank = 7; rank >= 0; rank--) {
        for (int file = 0; file < 8; file++) {
            Bitboard curr_field = Bitboard(1) << (rank * 8 + file);

            if (curr_field & w_king) {
                result.append("♔ ");
            } else if (curr_field & w_queen) {
                result.append("♕ ");
            } else if (curr_field & w_rooks) {
                result.append("♖ ");
            } else if (curr_field & w_bishops) {
                result.append("♗ ");
            } else if (curr_field & w_knights) {
                result.append("♘ ");
            } else if (curr_field & w_pawns) {
                result.append("♙ ");
            } else if (curr_field & b_king) {
                result.append("♚ ");
            } else if (curr_field & b_queen) {
                result.append("♛ ");
            } else if (curr_field & b_rooks) {
                result.append("♜ ");
            } else if (curr_field & b_bishops) {
                result.append("♝ ");
            } else if (curr_field & b_knights) {
                result.append("♞ ");
            } else if (curr_field & b_pawns) {
                result.append("♟︎ ");
            } else {
                result.append("· ");
            }
        }
        result.append("\n");
    }

    return result;
}

template<bool is_white>
constexpr auto Board::enemy_or_empty() const -> Bitboard {
    if constexpr (is_white) {
        return ~white;
    }
    return ~black;
}
