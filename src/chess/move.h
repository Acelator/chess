#ifndef MOVE_H
#define MOVE_H
#include <cstdint>

#include "helpers.h"

// divide by 8 + 1 to obtain rank
// mod 8 + 1 to obtain col

typedef uint8_t square;

// TODO: ENCODE SPECIAL MOVES
class Move {
public:
    Move(square from, square to, Player ply);

    square getFrom() const { return from; }

    square getTo() const { return to; }
    Player getPlayer() const { return playerMoving; }

private:
    square from;
    square to;
    Player playerMoving;
};


#endif //MOVE_H
