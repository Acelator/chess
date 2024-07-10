#ifndef BOARD_H
#define BOARD_H

#include "helpers.h"
#include "move.h"

#include <array>
#include <cstdint>

class Board {
public:
    Board();

    ~Board() = default;

    uint64_t getPlayerBoard(Player ply) const;

    uint64_t getPieceBoard(Pieces pc) const;

    uint64_t getPiecesBoardOfAGivenPlayer(Player ply, Pieces pc) const;

    // Return using pointers of something similar
    Board simulateMove(const Move &move) const;

    void updateBoard(const Move &move);

private:
    std::array<uint64_t, 2> playerBoard{};
    std::array<uint64_t, 6> piecesBoard{};

    Player playerToMove;
    int halfwayClock{};
    bool whitePlayerRightToCastle{};
    bool blackPlayerRightToCastle{};

    bool validateMove(const Move &move);

    bool isCheckmate();

    // MAKE EXEPTION FOR WHEN THERE IS NOT A PIECE
    Pieces pieceOnSquare(square sq) const;
};


#endif //BOARD_H
