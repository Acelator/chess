#include "moveValidator.h"

bool MoveValidator::validate() {
    if (move.getFrom() == move.getTo()) {
        return false;
    }

    // Check if the piece is in the starting position
    U64 pieceBoardOfCurrentPlayer{this->board.getPieceSetOfAGivenPlayer(move.getPieceType(), player)};

    U64 piece = (static_cast<U64>(1) << move.getFrom());
    bool isPieceThere = ((piece & pieceBoardOfCurrentPlayer) != 0);

    if (move.isCastle()) {
        if (this->isCastleValid()) {

        } else {
            return false;
        }
    }

    if (!isPieceThere) {
        // The piece is not there
        // TODO: Add exception
        return false;
    }

    // MoveValidator.isCheck();
    std::vector<Utils::enumSquare> path{};
    Path pathCalculator = Path(player, board, move);
    try {
        path = pathCalculator.calculatePath();
    } catch (int x) {
        // TODO: Document possible exceptions
        if (x == -1) {
            return false;
        }
    }
    // Represents the path that the piece follow
    U64 movementBoard{};
    for (const auto &i: path) {
        if (move.isCapture() && (i == path.back())) {
            break;
        }
        U64 currentSquare = (static_cast<U64>(1) << i);
        movementBoard = (movementBoard | currentSquare);
    }

    std::cout << "complete: " << movementBoard << '\n';
    auto completeBoard{this->board.getCompleteBoard()};

    // No piece intersect during the movement
    if ((completeBoard & movementBoard) == 0) {
        if (!this->isPlayerInCheck()) {
            return true;
        }
    }
    return false;
}

bool MoveValidator::isCastleValid() {
    return false;
}

bool MoveValidator::isPlayerInCheck() {
    U64 attackVector{this->board.getOtherPlayerAttackVector(this->player)};

    // Determine king bitboard
    U64 playerBitboard{board.getAllPiecesOfAGivenPlayer(this->player)};
    U64 kingsBitboard{board.getPieceSet(Utils::enumPieces::king)};
    U64 kingBitboard{playerBitboard & kingsBitboard};

    return ((attackVector & kingBitboard) != 0);
}

