#ifndef CHESS_MOVE_GENERATOR_H
#define CHESS_MOVE_GENERATOR_H

#include <vector>

#include "../player.h"
#include "../board.h"
#include "../utils/utils.h"

// Delete need to introduce piece type
std::vector<Utils::enumSquare> getAllPossibleMoves(Player& pj, Board& board, Utils::enumPieces pt, Utils::enumSquare from);

#endif //CHESS_MOVE_GENERATOR_H
