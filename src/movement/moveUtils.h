#ifndef CHESS_MOVE_UTILS_H
#define CHESS_MOVE_UTILS_H

#include <vector>
#include <cmath>

#include "../player.h"
#include "../board.h"
#include "../utils/utils.h"
#include "path.h"
#include "moveValidator.h"
#include "move.h"

void determineMovementType(Player &currentPlayer, Board &board, Move &move);

// Delete need to introduce piece type
//std::vector<Utils::enumSquare> getAllPossibleMoves(Player &pj, Board &board);

std::vector<Utils::enumSquare> getAllPossibleMovesOfAPiece(Player &pj, Board &board, Utils::enumPieces pt, Utils::enumSquare from);

std::vector<Utils::enumSquare> getAttackOfPawn(Player &pj, Board &board, Utils::enumSquare from);

#endif //CHESS_MOVE_UTILS_H
