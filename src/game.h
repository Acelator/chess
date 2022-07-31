#ifndef CHESS_GAME_H
#define CHESS_GAME_H

#include "utils/utils.h"
#include "utils/attackVector.h"
#include "board.h"
#include "player.h"

#include "movement/move.h"
#include "movement/moveValidator.h"
#include "movement/moveUtils.h"

class Game {
private:
    Player m_white;
    Player m_black;
    Board m_board{};

    int m_halfTurnCount{1};
    int m_fiftyMoveCount{0};
    bool m_currentTurn{};

    void newHalfTurn(Move &move);

public:
    // TODO: Initialize attack vector when starting the game
    Game() : m_white(Utils::Color::whitePLayer), m_black(Utils::Color::blackPlayer) {
        // White starts
        m_currentTurn = true;

        auto whiteAttackVector = calculateInitialAttackVector(m_white, m_board);
        this->m_board.saveAttackVector(m_white, whiteAttackVector);

        auto blackAttackVector = calculateInitialAttackVector(m_black, m_board);
        this->m_board.saveAttackVector(m_black, blackAttackVector);
    }

    // Return the player that has the current turn
    Player &getCurrentPlayer();

    Player &getNextPlayer();

    // Allow "to" to be expressed in algebraic notation
    U64 makeMove(Utils::enumPieces pt, std::uint_fast8_t from, std::uint_fast8_t to);
};

#endif
