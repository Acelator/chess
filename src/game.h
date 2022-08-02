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
    // White starts
    bool m_currentTurn{true};

    Players players;
    Board m_board{};

    int m_halfTurnCount{1};
    int m_fiftyMoveCount{0};

    void newHalfTurn(Move &move);

public:
    // TODO: Initialize attack vector when starting the game
    Game() : m_currentTurn(true), players(m_currentTurn) {
        auto whiteAttackVector = calculateInitialAttackVector(players.getWhitePlayer(), m_board);
        this->m_board.saveAttackVector(players.getWhitePlayer(), whiteAttackVector);

        auto blackAttackVector = calculateInitialAttackVector(players.getBlackPlayer(), m_board);
        this->m_board.saveAttackVector(players.getBlackPlayer(), blackAttackVector);
    }

    // Allow "to" to be expressed in algebraic notation
    U64 makeMove(Utils::enumPieces pt, std::uint_fast8_t from, std::uint_fast8_t to);
};

#endif
