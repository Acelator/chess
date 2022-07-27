#ifndef CHESS_GAME_H
#define CHESS_GAME_H

// Make sure libraries are only compiled once
#include "utils/utils.h"

#include "board.h"
#include "move.h"

#include "utils/moveValidator.h"
#include "player.h"

class Game {
private:
    Player white;
    Player black;
    Board m_board{};

    int halfTurnCount{1};
    int fiftyMoveCount{0};
    bool currentTurn{};

    void newHalfTurn(Move &move);

    void determineMovementType(Move &move);

public:
    Game() : white(Utils::Color::whitePLayer), black(Utils::Color::blackPlayer) {
        // White starts
        currentTurn = true;
    }

    // Return the player that has the current turn
    Player &getCurrentPlayer();

    Player &getNextPlayer();

    // Allow "to" to be expressed in chess notation (ej. f4)
    U64 makeMove(Utils::enumPieces pt, std::uint_fast8_t from, std::uint_fast8_t to);
};

#endif
