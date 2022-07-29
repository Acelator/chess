#ifndef CHESS_ATTACK_VECTOR_H
#define CHESS_ATTACK_VECTOR_H

#include "player.h"
#include "board.h"
#include "movement/move.h"
#include "movement/moveUtils.h"

U64 calculateInitialAttackVector(Player& pj, Board& board);

#endif //CHESS_ATTACK_VECTOR_H
