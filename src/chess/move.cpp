#include "move.h"

Move::Move(square from, square to, Player ply)
    : from(from), to(to), playerMoving(ply) {
}
