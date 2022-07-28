#ifndef CHESS_MOVE_VALIDATOR_H
#define CHESS_MOVE_VALIDATOR_H

#include <vector>

#include "../board.h"
#include "move.h"
#include "../utils/utils.h"
#include "path.h"

class MoveValidator {
private:
    Board &board;
    Move &move;
    Player &player;

public:
    MoveValidator(Board &currentBoard, Move &movement, Player &player) : board(currentBoard), move(movement), player(player) {};

    bool validate();

    bool isPlayerInCheck();

    static bool isCastleValid();
};

#endif
