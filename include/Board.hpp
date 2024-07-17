#pragma once

#include <cstddef>

#include "Bitboard.hpp"
#include "Lookup.hpp"

enum class Piece { King, Queen, Rook, Bishop, Knight, Pawn };

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
    const Bitboard w_queens;
    const Bitboard w_rooks;
    const Bitboard w_bishops;
    const Bitboard w_knights;
    const Bitboard w_pawns;

    const Bitboard b_pawns;
    const Bitboard b_king;
    const Bitboard b_queens;
    const Bitboard b_rooks;
    const Bitboard b_bishops;
    const Bitboard b_knights;

    constexpr auto show_board() const -> std::string;

    constexpr Board(
        Bitboard w_king,
        Bitboard w_queens,
        Bitboard w_rooks,
        Bitboard w_bishops,
        Bitboard w_knights,
        Bitboard w_pawns,
        Bitboard b_king,
        Bitboard b_queens,
        Bitboard b_rooks,
        Bitboard b_bishops,
        Bitboard b_knights,
        Bitboard b_pawns
    ) :
        white(w_king | w_queens | w_rooks | w_bishops | w_knights | w_pawns),
        black(b_king | b_queens | b_rooks | b_bishops | b_knights | b_pawns),
        occ(white | black),
        w_king(w_king),
        w_queens(w_queens),
        w_rooks(w_rooks),
        w_bishops(w_bishops),
        w_knights(w_knights),
        w_pawns(w_pawns),
        b_pawns(b_pawns),
        b_king(b_king),
        b_queens(b_queens),
        b_rooks(b_rooks),
        b_bishops(b_bishops),
        b_knights(b_knights) {}

    constexpr Board() :
        white(0xFFFF),
        black(0xFFFF000000000000),
        occ(0xFFFF00000000FFFF),
        w_king(0x10),
        w_queens(0x8),
        w_rooks(0x81),
        w_bishops(0x24),
        w_knights(0x42),
        w_pawns(0xFF00),
        b_pawns(0xFF000000000000),
        b_king(0x1000000000000000),
        b_queens(0x800000000000000),
        b_rooks(0x8100000000000000),
        b_bishops(0x2400000000000000),
        b_knights(0x4200000000000000) {}

    template<bool is_white>
    constexpr auto king_bitboard() const -> Bitboard {
        if constexpr (is_white)
            return w_king;
        return b_king;
    }

    template<bool is_white>
    constexpr auto enemy_knigts() const -> Bitboard {
        if constexpr (is_white)
            return b_knights;
        return w_knights;
    }

    template<bool is_white>
    constexpr auto enemy_rooks() const -> Bitboard {
        if constexpr (is_white)
            return b_rooks;
        return w_rooks;
    }

    template<bool is_white>
    constexpr auto enemy_queens() const -> Bitboard {
        if constexpr (is_white)
            return b_queens;
        return w_queens;
    }

    template<bool is_white>
    constexpr auto enemy_pawns() const -> Bitboard {
        if constexpr (is_white)
            return b_pawns;
        return w_pawns;
    }

    template<bool is_white>
    constexpr auto checkmask() -> Bitboard {
        Bitboard checkmask = 0ull;
        const Bitboard king_bb = king_bitboard<is_white>();
        const size_t king_sq = _tzcnt_u64(king_bb.value);

        // Knight checks
        Bitboard knight_attackers = lookup::knight_moves[king_sq] & enemy_knigts<is_white>();
        if (knight_attackers & enemy_knigts<is_white>())
            checkmask |= knight_attackers;

        // Rook / Queen checks
        // North
        Bitboard north_filter = lookup::get_directions_blockers<lookup::Direction::North>(king_sq);
        Bitboard north_attackers = lookup::get_rook_moves(king_sq, occ | north_filter);
        if (north_attackers & (enemy_rooks<is_white>() | enemy_queens<is_white>()))
            checkmask |= north_attackers;

        // East
        Bitboard east_filter = lookup::get_directions_blockers<lookup::Direction::East>(king_sq);
        Bitboard east_attackers = lookup::get_rook_moves(king_sq, occ | east_filter);
        if (east_attackers & (enemy_rooks<is_white>() | enemy_queens<is_white>()))
            checkmask |= east_attackers;

        // South
        Bitboard south_filter = lookup::get_directions_blockers<lookup::Direction::South>(king_sq);
        Bitboard south_attackers = lookup::get_rook_moves(king_sq, occ | south_filter);
        if (south_attackers & (enemy_rooks<is_white>() | enemy_queens<is_white>()))
            checkmask |= south_attackers;

        // West
        Bitboard west_filter = lookup::get_directions_blockers<lookup::Direction::West>(king_sq);
        Bitboard west_attackers = lookup::get_rook_moves(king_sq, occ | west_filter);
        if (west_attackers & (enemy_rooks<is_white>() | enemy_queens<is_white>()))
            checkmask |= west_attackers;

        // Bishop / Queen checks
        // NorthEast
        Bitboard ne_filter = lookup::get_directions_blockers<lookup::Direction::NorthEast>(king_sq);
        Bitboard ne_attackers = lookup::get_bishop_moves(king_sq, occ | ne_filter);
        if (ne_attackers & (enemy_bishops<is_white>() | enemy_queens<is_white>()))
            checkmask |= ne_attackers;

        // SouthEast
        Bitboard se_filter = lookup::get_directions_blockers<lookup::Direction::SouthEast>(king_sq);
        Bitboard se_attackers = lookup::get_bishop_moves(king_sq, occ | se_filter);
        if (se_attackers & (enemy_bishops<is_white>() | enemy_queens<is_white>()))
            checkmask |= se_attackers;

        // SouthWest
        Bitboard sw_filter = lookup::get_directions_blockers<lookup::Direction::SouthWest>(king_sq);
        Bitboard sw_attackers = lookup::get_bishop_moves(king_sq, occ | sw_filter);
        if (sw_attackers & (enemy_bishops<is_white>() | enemy_queens<is_white>()))
            checkmask |= sw_attackers;

        // NorthWest
        Bitboard nw_filter = lookup::get_directions_blockers<lookup::Direction::NorthWest>(king_sq);
        Bitboard nw_attackers = lookup::get_bishop_moves(king_sq, occ | nw_filter);
        if (nw_attackers & (enemy_bishops<is_white>() | enemy_queens<is_white>()))
            checkmask |= nw_attackers;

        // Pawns
        Bitboard pawn_attackers = lookup::get_pawn_attacks<is_white>(king_sq);
        if ((pawn_attackers & enemy_pawns<is_white>()))
            checkmask |= pawn_attackers;

        return checkmask;
    }

    template<Piece piece, bool is_white>
    constexpr auto move_promote(const Board& current, size_t from, size_t to) -> Board {
        Bitboard from_bb = 1ull << from;
        Bitboard to_bb = 1ull << to;

        Bitboard wk = current.w_king;
        Bitboard wq = current.w_queens;
        Bitboard wr = current.w_rooks;
        Bitboard wb = current.w_bishops;
        Bitboard wn = current.w_knights;
        Bitboard wp = current.w_pawns;

        Bitboard bk = current.b_king;
        Bitboard bq = current.b_queens;
        Bitboard br = current.b_rooks;
        Bitboard bb = current.b_bishops;
        Bitboard bn = current.b_knights;
        Bitboard bp = current.b_pawns;

        if constexpr (is_white) {
            if constexpr (piece == Piece::Queen)
                return Board(wk, wq ^ to_bb, wr, wb, wn, wp ^ from_bb, bk, bq, br, bb, bn, bp);
            if constexpr (piece == Piece::Rook)
                return Board(wk, wq, wr ^ to_bb, wb, wn, wp ^ from_bb, bk, bq, br, bb, bn, bp);
            if constexpr (piece == Piece::Bishop)
                return Board(wk, wq, wr, wb ^ to_bb, wn, wp ^ from_bb, bk, bq, br, bb, bn, bp);
            if constexpr (piece == Piece::Knight)
                return Board(wk, wq, wr, wb, wn ^ to_bb, wp ^ from_bb, bk, bq, br, bb, bn, bp);
        }

        if constexpr (piece == Piece::Queen)
            return Board(wk, wq, wr, wb, wn, wp, bk, bq ^ to_bb, br, bb, bn, bp ^ from_bb);
        if constexpr (piece == Piece::Rook)
            return Board(wk, wq, wr, wb, wn, wp, bk, bq, br ^ to_bb, bb, bn, bp ^ from_bb);
        if constexpr (piece == Piece::Bishop)
            return Board(wk, wq, wr, wb, wn, wp, bk, bq, br, bb ^ to_bb, bn, bp ^ from_bb);
        if constexpr (piece == Piece::Knight)
            return Board(wk, wq, wr, wb, wn, wp, bk, bq, br, bb, bn ^ to_bb, bp ^ from_bb);

        // TODO: handle invalid Promotion better
        return current;
    }
};

constexpr auto Board::show_board() const -> std::string {
    std::string result = "";
    for (int rank = 7; rank >= 0; rank--) {
        for (int file = 0; file < 8; file++) {
            Bitboard curr_field = Bitboard(1) << (rank * 8 + file);

            if (curr_field & w_king) {
                result.append("♔ ");
            } else if (curr_field & w_queens) {
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
            } else if (curr_field & b_queens) {
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
