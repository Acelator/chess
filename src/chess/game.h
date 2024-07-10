#ifndef GAME_H
#define GAME_H

#include "helpers.h"
#include "board.h"
#include "move.h"

#include <vector>


class Game {
public:
    Game();

    ~Game();

private:
    Board *currentBoard;
    std::vector<Move *> moves;
    int numberOfMoves{};
    Player sideToMove{};

    // Board &const getCurrentBoard() const;

    Player getPlayerToMove() const { return this->sideToMove; };

    // maybe return new board
    void makeMove(Move &move);

    // TODO: Reconsider static
    static void isMoveValid(Move &move);
};

#endif //GAME_H
