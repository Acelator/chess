#ifndef CHESS_GAME_H
#define CHESS_GAME_H

#include "utils/moveValidator.h"
#include "utils/utils.h"

#include "player.h"
#include "board.h"
#include "move.h"

class Game {
private:
    Player m_white;
    Player m_black;
    Board m_board{};

    int m_halfTurnCount{1};
    int m_fiftyMoveCount{0};
    bool m_currentTurn{};

    void newHalfTurn(Move &move);

    void determineMovementType(Move &move);

public:
    Game() : m_white(Utils::Color::whitePLayer), m_black(Utils::Color::blackPlayer) {
        // White starts
        m_currentTurn = true;
    }

    // Return the player that has the current turn
    Player &getCurrentPlayer();

    Player &getNextPlayer();

    // Allow "to" to be expressed in algebraic notation
    U64 makeMove(Utils::enumPieces pt, std::uint_fast8_t from, std::uint_fast8_t to);
};

#endif
