#ifndef CHESS_MOVE_VALIDATOR_H
#define CHESS_MOVE_VALIDATOR_H

#include <vector>

#include "../board.h"
#include "move.h"
#include "../utils/utils.h"
#include "path.h"

// This class should not update the board
class MoveValidator {
private:
    Board &board;
    Move &move;
    Player &player;

public:
    MoveValidator(Board &currentBoard, Move &movement, Player &player) : board(currentBoard), move(movement), player(player) {};

    // Save is a param that allows us to know if the current move that is validated should update the board to pass along check and en passant info.
    bool validate(bool save = false);

    bool isPlayerInCheck();

    static bool isCastleValid();
};

#endif
