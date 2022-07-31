#include "attackVector.h"

U64 calculateInitialAttackVector(Player &pj, Board &board) {
    U64 playerBoard = board.getAllPiecesOfAGivenPlayer(pj);
    U64 attackVector{};
    Utils::enumPieces pt{};

    for (int i{0}; i <= 63; i++) {
        if (((playerBoard >> i) & 1) != 0) {
            //There is a piece in that position

            // First we determine the type of the piece
            if (((board.getPieceSet(Utils::enumPieces::pawn) >> i) & 1) != 0) {
                pt = Utils::enumPieces::pawn;
            } else if (((board.getPieceSet(Utils::enumPieces::rook) >> i) & 1) != 0) {
                pt = Utils::enumPieces::rook;
            } else if (((board.getPieceSet(Utils::enumPieces::knight) >> i) & 1) != 0) {
                pt = Utils::enumPieces::knight;
            } else if (((board.getPieceSet(Utils::enumPieces::bishop) >> i) & 1) != 0) {
                pt = Utils::enumPieces::bishop;
            } else if (((board.getPieceSet(Utils::enumPieces::queen) >> i) & 1) != 0) {
                pt = Utils::enumPieces::queen;
            } else if (((board.getPieceSet(Utils::enumPieces::king) >> i) & 1) != 0) {
                pt = Utils::enumPieces::king;
            } else {
                break;
            }

            // TODO: Take into account pawns, they don't eat to the square they are move to
            if (pt == Utils::enumPieces::pawn) {
                auto moves = getAttackOfPawn(pj, board, static_cast<Utils::enumSquare>(i));
                for (const auto &square: moves) {
                    attackVector |= (static_cast<U64>(0x1) << square);
                }
            } else {
                auto moves = getAllPossibleMovesOfAPiece(pj, board, pt, static_cast<Utils::enumSquare>(i));
                for (const auto &square: moves) {
                    attackVector |= (static_cast<U64>(0x1) << square);
                }
            }
        } else if (((playerBoard >> i) == 0)) {
            // There is no pieces left
            break;
        } else {
            continue;
        }
    }
    return attackVector;
}

// TODO: Implement
//U64 updateAttackVector(Player &pj, Board &board, Move &move) {
//    U64 attackVector{board.getPlayerAttackVector(pj)};
//    if (move.getPieceType() == Utils::enumPieces::pawn) {
//        // Delete the attacks of the piece to move in its old position
//        auto moves = getAttackOfPawn(pj, board, static_cast<Utils::enumSquare>(move.getFrom()));
//        for (const auto &square: moves) {
//            attackVector ^= (static_cast<U64>(0x1) << square);
//        }
//        // Update the attack of the piece to move in its new position
//        auto newMoves = getAttackOfPawn(pj, board, static_cast<Utils::enumSquare>(move.getTo()));
//        for (const auto &square: newMoves) {
//            attackVector &= (static_cast<U64>(0x1) << square);
//        }
//    } else {
//        // Delete the attacks of the piece to move in its old position
//        auto moves = getAllPossibleMovesOfAPiece(pj, board, move.getPieceType(), static_cast<Utils::enumSquare>(move.getFrom()));
//        for (const auto &square: moves) {
//            attackVector ^= (static_cast<U64>(0x1) << square);
//        }
//    }
//    // Update the attack of the piece to move in its new position
//    auto newMoves = getAllPossibleMovesOfAPiece(pj, board, move.getPieceType(), static_cast<Utils::enumSquare>(move.getFrom()));
//    for (const auto &square: newMoves) {
//        attackVector &= (static_cast<U64>(0x1) << square);
//    }
//
//    return attackVector;
//}
