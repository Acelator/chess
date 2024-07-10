#include "board.h"

#include <memory>

// TODO: IMPROVE
Board::Board() {
    playerBoard[static_cast<int>(Player::White)] = 0x000000000000ffff;
    playerBoard[static_cast<int>(Player::Black)] = 0x000000000000ffff;

    piecesBoard[static_cast<int>(Pieces::Pawn)] = 0x00ff00000000ff00;
    piecesBoard[static_cast<int>(Pieces::Knight)] = 0x4200000000000042;
    piecesBoard[static_cast<int>(Pieces::Bishop)] = 0x2400000000000024;
    piecesBoard[static_cast<int>(Pieces::Rook)] = 0x8100000000000081;
    piecesBoard[static_cast<int>(Pieces::Queen)] = 0x1000000000000008;
    piecesBoard[static_cast<int>(Pieces::King)] = 0x800000000000010;

    playerToMove = Player::White;
    whitePlayerRightToCastle = true;
    blackPlayerRightToCastle = true;

    halfwayClock = 0;
}

uint64_t Board::getPlayerBoard(Player ply) const {
    return playerBoard[static_cast<int>(ply)];
}

uint64_t Board::getPieceBoard(Pieces pc) const {
    return piecesBoard[static_cast<int>(pc)];
}

uint64_t Board::getPiecesBoardOfAGivenPlayer(Player ply, Pieces pc) const {
    return getPieceBoard(pc) & getPlayerBoard(ply);
}

Board Board::simulateMove(const Move &move) const {
    // MAKE MORE EFICIENT
    auto board = *this;
    auto pc = pieceOnSquare(move.getFrom());

    auto plyBoard = board.getPlayerBoard(move.getPlayer());
    auto pcBoard = board.getPieceBoard(pc);

    board.playerBoard[static_cast<int>(move.getPlayer())] = (plyBoard ^ (1 << move.getFrom()) ^ (1 << move.getTo()));
    board.piecesBoard[static_cast<int>(pc)] = (pcBoard ^ (1 << move.getFrom()) ^ (1 << move.getTo()));

    std::cout << board.playerBoard[static_cast<int>(pc)];

    return board;
}

// TODO: CHECK IF MOVE IS VALID
void Board::updateBoard(const Move &move) {
    auto pc = pieceOnSquare(move.getFrom());

    auto plyBoard = getPlayerBoard(move.getPlayer());
    auto pcBoard = getPieceBoard(pc);

    playerBoard[static_cast<int>(move.getPlayer())] = (plyBoard ^ (1 << move.getFrom()) ^ (1 << move.getTo()));
    piecesBoard[static_cast<int>(pc)] = (pcBoard ^ (1 << move.getFrom()) ^ (1 << move.getTo()));
}

Pieces Board::pieceOnSquare(square sq) const {
    for (int i{0}; i < 6; i++) {
        auto pcBoard = (getPieceBoard(static_cast<Pieces>(i)) >> sq) & 1;
        if (pcBoard == 1) return static_cast<Pieces>(i);
    }
    // WE SHOULD NEVER REACH HERE
    // return Pieces::Pawn;

    std::cout << "NO PIECE ON SQUARE\n";
}

bool Board::validateMove(const Move &move) {
    // isCheckMate and all that stuff to be implemented

    auto pc = pieceOnSquare(move.getFrom());
    switch (pc) {
        case Pieces::Pawn:
            break;
        case Pieces::Knight:
            break;
        case Pieces::Bishop:
            break;
        case Pieces::Rook:
            break;
        case Pieces::Queen:
            break;
        case Pieces::King:
            break;
    }

    return true;
}
