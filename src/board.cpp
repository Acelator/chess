#include "board.h"

U64 Board::getCompleteBoard() const {
    return this->m_playerSet[Utils::Color::whitePLayer] | this->m_playerSet[Utils::Color::blackPlayer];
}

U64 Board::getPieceSet(Utils::enumPieces pt) const {
    return this->m_pieces[pt];
}

U64 Board::getPieceSetOfAGivenPlayer(Utils::enumPieces pt, Player &pj) const {
    return this->m_pieces[pt] & this->m_playerSet[pj.getPlayerColor()];
}

U64 Board::getAllPiecesOfAGivenPlayer(Player &pj) const {
    return this->m_playerSet[pj.getPlayerColor()];
}

std::uint_fast8_t Board::getEnPassantAllowedFiles() const {
    return this->enPassantAllowedFile;
}

U64 Board::getPlayerAttackVector(Player &pj) const {
    return this->m_attackVector[pj.getPlayerColor()];
}

U64 Board::getOtherPlayerAttackVector(Player &pj) const {
    if (pj.getPlayerColor() == Utils::Color::whitePLayer) {
        return this->m_attackVector[Utils::Color::blackPlayer];
    } else {
        return this->m_attackVector[Utils::Color::whitePLayer];
    }
}

void Board::saveAttackVector(Player &pj, U64 attackVector) {
    this->m_attackVector[pj.getPlayerColor()] = attackVector;
}

void Board::newEnPassantOpportunity(int file) {
    if ((file <= 8) && (file >= 1)) {
        this->enPassantAllowedFile = file;
    }
}

void Board::restartEnPassant() {
    this->enPassantAllowedFile = 0;
}

// TODO: Pass current player and the next one
// TODO: Implement castle
void Board::updateBoard(Move &move, Player &currentPlayer, Player &nextPlayer) {
    U64 startingPieceBitboard = static_cast<unsigned long>(0x1) << move.getFrom();
    U64 finalPieceBitboard = static_cast<unsigned long>(0x1) << move.getTo();

    // Update the board of the player that is currently moving
    U64 playerBoard{this->getAllPiecesOfAGivenPlayer(currentPlayer)};
    U64 piecesBoard{this->getPieceSet(move.getPieceType())};

    // Delete from the starting position the piece moved
    playerBoard ^= startingPieceBitboard;
    piecesBoard ^= startingPieceBitboard;

    // input the new piece position
    playerBoard |= finalPieceBitboard;

    // Save it
    this->m_playerSet[currentPlayer.getPlayerColor()] = playerBoard;

    if (move.isCapture()) {
        U64 otherPlayerBoard{this->getCompleteBoard() ^ playerBoard};
        nextPlayer.newLostPiece(move.getPieceType());
        this->m_playerSet[nextPlayer.getPlayerColor()] = otherPlayerBoard;
    }

    if (move.isPromotion()) {
        // Save the bitboard of the initial piece without the promoted one
        this->m_pieces[move.getPieceType()] = piecesBoard;

        // Add the new promoted piece to its corresponding bitboard
        U64 promotedPieceBitboard{this->getPieceSet(move.getPieceToPromoteTo())};
        promotedPieceBitboard |= finalPieceBitboard;
        this->m_pieces[move.getPieceToPromoteTo()] = promotedPieceBitboard;

    } else {
        // input the new piece position
        piecesBoard |= finalPieceBitboard;
        this->m_pieces[move.getPieceType()] = piecesBoard;
    }

    if (move.isEnPassant()) {
        U64 otherPlayerBoard{this->getCompleteBoard() ^ playerBoard};

        // input the new piece position
        piecesBoard |= finalPieceBitboard;

        U64 positionOfPieceToEat;
        if (currentPlayer.getPlayerColor() == Utils::Color::whitePLayer) {
            positionOfPieceToEat = finalPieceBitboard >> 8;
        } else {
            positionOfPieceToEat = finalPieceBitboard << 8;
        }

        // Always a pawn
        nextPlayer.newLostPiece(Utils::enumPieces::pawn);

        // Delete the eaten piece
        otherPlayerBoard ^= positionOfPieceToEat;
        piecesBoard ^= positionOfPieceToEat;

        // Saves to the bitboard
        this->m_pieces[move.getPieceType()] = piecesBoard;
        this->m_playerSet[nextPlayer.getPlayerColor()] = otherPlayerBoard;

        this->restartEnPassant();
    }
}

U64 Board::mirrorHorizontal(U64 x) {
    const U64 k1 = U64(0x5555555555555555);
    const U64 k2 = U64(0x3333333333333333);
    const U64 k4 = U64(0x0f0f0f0f0f0f0f0f);
    x = ((x >> 1) & k1) | ((x & k1) << 1);
    x = ((x >> 2) & k2) | ((x & k2) << 2);
    x = ((x >> 4) & k4) | ((x & k4) << 4);
    return x;
}

std::ostream &operator<<(std::ostream &os, Board &board) {
    U64 bitboard{board.mirrorHorizontal(board.getCompleteBoard())};
    os << "Board expressed as int: " << board.getCompleteBoard() << '\n';
    os << '|';

    // Border represents when we should make a break in the current line
    int border{56};
    for (int i{63}; i >= 0; i--) {
        if (((bitboard & (static_cast<unsigned long>(0x1) << i)) != 0)) {
            os << " X " << '|';
        } else {
            os << "   " << '|';
        }
        if (i == 0) {
            break;
        }
        if (i == border) {
            os << '\n' << '|';
            border -= 8;
        }
    }
    return os;
}