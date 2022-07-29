#include "attackVector.h"

U64 calculateInitialAttackVector(Player &pj, Board &board) {
//    U64 playerBoard = board.getAllPiecesOfAGivenPlayer(pj);
    getAllPossibleMovesOfAPiece(pj, board, Utils::enumPieces::king, static_cast<Utils::enumSquare>(27));
//
    U64 attackVector{};
//    auto moves = getAllPossibleMoves(pj, board);
//    for (const auto& i : moves) {
//        attackVector |= i;
//    }
    // TODO: Take into account pawns, they don't eat to the square they are move if
    return attackVector;
}