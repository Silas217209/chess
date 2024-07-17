#pragma once

class Game {
  public:
    const bool w_to_move;
    const bool ep_pawn;

    const bool w_castle_q;
    const bool w_castle_k;

    const bool b_castle_q;
    const bool b_castle_k;

    constexpr Game(bool w_to_move, bool ep_pawn, bool w_castle_q, bool w_castle_k, bool b_castle_q, bool b_castle_k) :
        w_to_move(w_to_move),
        ep_pawn(ep_pawn),
        w_castle_q(w_castle_q),
        w_castle_k(w_castle_k),
        b_castle_q(b_castle_q),
        b_castle_k(b_castle_k) {};

    constexpr auto move_king() const -> Game {
        if (w_to_move) {
            return Game(!w_to_move, false, false, false, b_castle_k, b_castle_q);
        }
        return Game(!w_to_move, false, w_castle_k, w_castle_q, false, false);
    }

    constexpr auto double_pawn_push() const -> Game {
        return Game(!w_to_move, true, w_castle_q, w_castle_k, b_castle_q, b_castle_k);
    }

    constexpr auto move_rook_queenside() const -> Game {
        if (w_to_move) {
            return Game(!w_to_move, false, false, w_castle_k, b_castle_q, b_castle_k);
        }
        return Game(!w_to_move, false, w_castle_q, w_castle_k, false, b_castle_k);
    }

    constexpr auto move_rook_kingside() const -> Game {
        if (w_to_move) {
            return Game(!w_to_move, false, w_castle_q, false, b_castle_q, b_castle_k);
        }
        return Game(!w_to_move, false, w_castle_q, w_castle_k, b_castle_q, false);
    }

    constexpr auto move_silent() const -> Game {
        return Game(!w_to_move, false, w_castle_q, w_castle_k, b_castle_q, b_castle_k);
    }
};
