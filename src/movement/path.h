#ifndef CHESS_PATH_H
#define CHESS_PATH_H

#include <vector>
#include "../utils/utils.h"
#include "player.h"
#include "board.h"
#include "move.h"

class Path {
private:
    Player& player;
    Board& board;
    Move& move;

    std::vector<Utils::enumSquare> calculateVerticalMovement();

    std::vector<Utils::enumSquare> calculateHorizontalMovement();

    std::vector<Utils::enumSquare> calculateDiagonalMovement();
public:
    Path(Player& pj, Board& board, Move& movement) : player(pj), board(board), move(movement) {

    }

    std::vector<Utils::enumSquare> calculatePath();
};

#endif //CHESS_PATH_H
