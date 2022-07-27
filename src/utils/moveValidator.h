#ifndef CHESS_MOVE_VALIDATOR_H
#define CHESS_MOVE_VALIDATOR_H

#include <vector>

#include "../board.h"
#include "../move.h"
#include "utils.h"

class MoveValidator {
private:
    Board &board;
    Move &move;
    Player &player;

    std::vector<Utils::enumSquare> calculatePath();

    // Functions used by calculatePath()
    std::vector<Utils::enumSquare> calculateVerticalMovement();

    std::vector<Utils::enumSquare> calculateHorizontalMovement();

    std::vector<Utils::enumSquare> calculateDiagonalMovement();

public:
    MoveValidator(Board &currentBoard, Move &movement, Player &player) : board(currentBoard), move(movement), player(player) {};

    bool validate();

    bool isCastleValid();
};

#endif
