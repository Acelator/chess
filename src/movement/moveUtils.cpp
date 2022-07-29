#include "moveUtils.h"

std::vector<Utils::enumSquare> getAllPossibleMovesOfAPiece(Player &pj, Board &board, Utils::enumPieces pt, Utils::enumSquare from) {
    std::vector<Utils::enumSquare> moves{};
//    U64 pieceBitboard{static_cast<U64>(0x1) << from};
//    U64 playerBitboard{board.getAllPiecesOfAGivenPlayer(pj)};

    switch (pt) {
        case Utils::enumPieces::pawn: {
            // Max amount of possible moves are four
            if (pj.getPlayerColor() == Utils::Color::whitePLayer) {
                for (int i{0}; i < 4; i++) {
                    int to{};
                    if (i == 0) {
                        to = static_cast<Utils::enumSquare>(from + 8);
                    } else if (i == 1) {
                        to = static_cast<Utils::enumSquare>(from + 16);
                    } else if (i == 2) {
                        to = static_cast<Utils::enumSquare>(from + 9);
                    } else if (i == 3) {
                        to = static_cast<Utils::enumSquare>(from + 7);
                    }
                    if (to > 63 || to < 0) {
                        // Square is outside the board
                        continue;
                    }
                    Move move = Move(pt, pj, from, to);
                    determineMovementType(pj, board, move);
                    MoveValidator validator = MoveValidator(board, move, pj);
                    if (validator.validate()) {
                        moves.push_back(static_cast<Utils::enumSquare>(to));
                    }
                }
            } else {
                for (int i{0}; i < 4; i++) {
                    int to{};
                    if (i == 0) {
                        to = static_cast<Utils::enumSquare>(from - 8);
                    } else if (i == 1) {
                        to = static_cast<Utils::enumSquare>(from - 16);
                    } else if (i == 2) {
                        to = static_cast<Utils::enumSquare>(from - 9);
                    } else if (i == 3) {
                        to = static_cast<Utils::enumSquare>(from - 7);
                    }
                    if (to > 63 || to < 0) {
                        // Square is outside the board
                        continue;
                    }
                    Move move = Move(pt, pj, from, to);
                    determineMovementType(pj, board, move);
                    MoveValidator validator = MoveValidator(board, move, pj);
                    if (validator.validate()) {
                        moves.push_back(static_cast<Utils::enumSquare>(to));
                    }
                }
            }
            // Check En passant
            if (board.getEnPassantAllowedFile() != 0) {
                // En passant is possible
                if ((board.getEnPassantAllowedFile() - obtainFileFromSquare(from)) == 1) {
                    if (pj.getPlayerColor() == Utils::Color::whitePLayer) {
                        int to{from + 9};
                        Move move = Move(pt, pj, from, to);
                        determineMovementType(pj, board, move);
                        MoveValidator validator = MoveValidator(board, move, pj);
                        if (validator.validate()) {
                            moves.push_back(static_cast<Utils::enumSquare>(to));
                        }
                    } else {
                        int to{from - 7};
                        Move move = Move(pt, pj, from, to);
                        determineMovementType(pj, board, move);
                        MoveValidator validator = MoveValidator(board, move, pj);
                        if (validator.validate()) {
                            moves.push_back(static_cast<Utils::enumSquare>(to));
                        }
                    }
                } else if ((board.getEnPassantAllowedFile() - obtainFileFromSquare(from)) == -1) {
                    if (pj.getPlayerColor() == Utils::Color::whitePLayer) {
                        int to{from + 7};
                        Move move = Move(pt, pj, from, to);
                        determineMovementType(pj, board, move);
                        MoveValidator validator = MoveValidator(board, move, pj);
                        if (validator.validate()) {
                            moves.push_back(static_cast<Utils::enumSquare>(to));
                        }
                    } else {
                        int to{from - 9};
                        Move move = Move(pt, pj, from, to);
                        determineMovementType(pj, board, move);
                        MoveValidator validator = MoveValidator(board, move, pj);
                        if (validator.validate()) {
                            moves.push_back(static_cast<Utils::enumSquare>(to));
                        }
                    }
                }
            }
            break;
        }
        case Utils::enumPieces::bishop: {
            // SoEa
            for (int i{from - 7};; i -= 7) {
                if (i > 63 || i < 0) {
                    // Square is outside the board
                    break;
                }

                Move move = Move(pt, pj, from, i);
                determineMovementType(pj, board, move);
                MoveValidator validator = MoveValidator(board, move, pj);
                if (validator.validate()) {
                    moves.push_back(static_cast<Utils::enumSquare>(i));
                } else {
                    break;
                }

                if ((obtainFileFromSquare(i) == 1) || (obtainFileFromSquare(i) == 8)
                    || (obtainRankFromSquare(i) == 1) || (obtainRankFromSquare(i) == 8)) {
                    break;
                }
            }

            // noWe
            for (int i{from + 7};; i += 7) {
                if (i > 63 || i < 0) {
                    // Square is outside the board
                    break;
                }

                Move move = Move(pt, pj, from, i);
                determineMovementType(pj, board, move);
                MoveValidator validator = MoveValidator(board, move, pj);
                if (validator.validate()) {
                    moves.push_back(static_cast<Utils::enumSquare>(i));
                } else {
                    break;
                }

                if ((obtainFileFromSquare(i) == 1) || (obtainFileFromSquare(i) == 8)
                    || (obtainRankFromSquare(i) == 1) || (obtainRankFromSquare(i) == 8)) {
                    break;
                }
            }

            // noEa
            for (int i{from + 9};; i += 9) {
                if (i > 63 || i < 0) {
                    // Square is outside the board
                    break;
                }
                Move move = Move(pt, pj, from, i);
                determineMovementType(pj, board, move);
                MoveValidator validator = MoveValidator(board, move, pj);
                if (validator.validate()) {
                    moves.push_back(static_cast<Utils::enumSquare>(i));
                } else {
                    break;
                }

                if ((obtainFileFromSquare(i) == 1) || (obtainFileFromSquare(i) == 8)
                    || (obtainRankFromSquare(i) == 1) || (obtainRankFromSquare(i) == 8)) {
                    break;
                }
            }

            // soWe
            for (int i{from - 9};; i -= 9) {
                if (i > 63 || i < 0) {
                    // Square is outside the board
                    break;
                }
                Move move = Move(pt, pj, from, i);
                determineMovementType(pj, board, move);
                MoveValidator validator = MoveValidator(board, move, pj);
                if (validator.validate()) {
                    moves.push_back(static_cast<Utils::enumSquare>(i));
                } else {
                    break;
                }

                if ((obtainFileFromSquare(i) == 1) || (obtainFileFromSquare(i) == 8)
                    || (obtainRankFromSquare(i) == 1) || (obtainRankFromSquare(i) == 8)) {
                    break;
                }
            }
            break;
        }
        case Utils::enumPieces::knight: {
            // Max amount of movement is eight
            for (int i{0}; i < 8; i++) {
                int to{};
                if (i == 0) {
                    to = static_cast<Utils::enumSquare>(from + 17);
                } else if (i == 1) {
                    to = static_cast<Utils::enumSquare>(from - 17);
                } else if (i == 2) {
                    to = static_cast<Utils::enumSquare>(from + 15);
                } else if (i == 3) {
                    to = static_cast<Utils::enumSquare>(from - 15);
                } else if (i == 4) {
                    to = static_cast<Utils::enumSquare>(from + 10);
                } else if (i == 5) {
                    to = static_cast<Utils::enumSquare>(from - 10);
                } else if (i == 6) {
                    to = static_cast<Utils::enumSquare>(from + 6);
                } else if (i == 7) {
                    to = static_cast<Utils::enumSquare>(from - 6);
                }
                if (to > 63 || to < 0) {
                    // Square is outside the board
                    continue;
                }
                Move move = Move(pt, pj, from, to);
                determineMovementType(pj, board, move);
                MoveValidator validator = MoveValidator(board, move, pj);
                if (validator.validate()) {
                    moves.push_back(static_cast<Utils::enumSquare>(to));
                }
            }
            break;
        }
        case Utils::enumPieces::rook: {
            // north
            for (int i{from + 8};; i += 8) {
                if (i > 63 || i < 0) {
                    // Square is outside the board
                    break;
                }

                Move move = Move(pt, pj, from, i);
                determineMovementType(pj, board, move);
                MoveValidator validator = MoveValidator(board, move, pj);
                if (validator.validate()) {
                    moves.push_back(static_cast<Utils::enumSquare>(i));
                } else {
                    break;
                }
            }

            // south
            for (int i{from - 8};; i -= 8) {
                if (i > 63 || i < 0) {
                    // Square is outside the board
                    break;
                }

                Move move = Move(pt, pj, from, i);
                determineMovementType(pj, board, move);
                MoveValidator validator = MoveValidator(board, move, pj);
                if (validator.validate()) {
                    moves.push_back(static_cast<Utils::enumSquare>(i));
                } else {
                    break;
                }
            }

            // east
            for (int i{from + 1};; i += 1) {
                if (i > 63 || i < 0) {
                    // Square is outside the board
                    break;
                }
                Move move = Move(pt, pj, from, i);
                determineMovementType(pj, board, move);
                MoveValidator validator = MoveValidator(board, move, pj);
                if (validator.validate()) {
                    moves.push_back(static_cast<Utils::enumSquare>(i));
                } else {
                    break;
                }
            }

            // west
            for (int i{from - 1};; i -= 1) {
                if (i > 63 || i < 0) {
                    // Square is outside the board
                    break;
                }
                Move move = Move(pt, pj, from, i);
                determineMovementType(pj, board, move);
                MoveValidator validator = MoveValidator(board, move, pj);
                if (validator.validate()) {
                    moves.push_back(static_cast<Utils::enumSquare>(i));
                } else {
                    break;
                }
            }
            break;
        }
        case Utils::enumPieces::queen: {
            // north
            for (int i{from + 8};; i += 8) {
                if (i > 63 || i < 0) {
                    // Square is outside the board
                    break;
                }

                Move move = Move(pt, pj, from, i);
                determineMovementType(pj, board, move);
                MoveValidator validator = MoveValidator(board, move, pj);
                if (validator.validate()) {
                    moves.push_back(static_cast<Utils::enumSquare>(i));
                } else {
                    break;
                }
            }

            // south
            for (int i{from - 8};; i -= 8) {
                if (i > 63 || i < 0) {
                    // Square is outside the board
                    break;
                }

                Move move = Move(pt, pj, from, i);
                determineMovementType(pj, board, move);
                MoveValidator validator = MoveValidator(board, move, pj);
                if (validator.validate()) {
                    moves.push_back(static_cast<Utils::enumSquare>(i));
                } else {
                    break;
                }
            }

            // east
            for (int i{from + 1};; i += 1) {
                if (i > 63 || i < 0) {
                    // Square is outside the board
                    break;
                }
                Move move = Move(pt, pj, from, i);
                determineMovementType(pj, board, move);
                MoveValidator validator = MoveValidator(board, move, pj);
                if (validator.validate()) {
                    moves.push_back(static_cast<Utils::enumSquare>(i));
                } else {
                    break;
                }
            }

            // west
            for (int i{from - 1};; i -= 1) {
                if (i > 63 || i < 0) {
                    // Square is outside the board
                    break;
                }
                Move move = Move(pt, pj, from, i);
                determineMovementType(pj, board, move);
                MoveValidator validator = MoveValidator(board, move, pj);
                if (validator.validate()) {
                    moves.push_back(static_cast<Utils::enumSquare>(i));
                } else {
                    break;
                }
            }

            // SoEa
            for (int i{from - 7};; i -= 7) {
                if (i > 63 || i < 0) {
                    // Square is outside the board
                    break;
                }

                Move move = Move(pt, pj, from, i);
                determineMovementType(pj, board, move);
                MoveValidator validator = MoveValidator(board, move, pj);
                if (validator.validate()) {
                    moves.push_back(static_cast<Utils::enumSquare>(i));
                } else {
                    break;
                }

                if ((obtainFileFromSquare(i) == 1) || (obtainFileFromSquare(i) == 8)
                    || (obtainRankFromSquare(i) == 1) || (obtainRankFromSquare(i) == 8)) {
                    break;
                }
            }

            // noWe
            for (int i{from + 7};; i += 7) {
                if (i > 63 || i < 0) {
                    // Square is outside the board
                    break;
                }

                Move move = Move(pt, pj, from, i);
                determineMovementType(pj, board, move);
                MoveValidator validator = MoveValidator(board, move, pj);
                if (validator.validate()) {
                    moves.push_back(static_cast<Utils::enumSquare>(i));
                } else {
                    break;
                }

                if ((obtainFileFromSquare(i) == 1) || (obtainFileFromSquare(i) == 8)
                    || (obtainRankFromSquare(i) == 1) || (obtainRankFromSquare(i) == 8)) {
                    break;
                }
            }

            // noEa
            for (int i{from + 9};; i += 9) {
                if (i > 63 || i < 0) {
                    // Square is outside the board
                    break;
                }
                Move move = Move(pt, pj, from, i);
                determineMovementType(pj, board, move);
                MoveValidator validator = MoveValidator(board, move, pj);
                if (validator.validate()) {
                    moves.push_back(static_cast<Utils::enumSquare>(i));
                } else {
                    break;
                }

                if ((obtainFileFromSquare(i) == 1) || (obtainFileFromSquare(i) == 8)
                    || (obtainRankFromSquare(i) == 1) || (obtainRankFromSquare(i) == 8)) {
                    break;
                }
            }

            // soWe
            for (int i{from - 9};; i -= 9) {
                if (i > 63 || i < 0) {
                    // Square is outside the board
                    break;
                }
                Move move = Move(pt, pj, from, i);
                determineMovementType(pj, board, move);
                MoveValidator validator = MoveValidator(board, move, pj);
                if (validator.validate()) {
                    moves.push_back(static_cast<Utils::enumSquare>(i));
                } else {
                    break;
                }

                if ((obtainFileFromSquare(i) == 1) || (obtainFileFromSquare(i) == 8)
                    || (obtainRankFromSquare(i) == 1) || (obtainRankFromSquare(i) == 8)) {
                    break;
                }
            }
            break;
        }
        case Utils::enumPieces::king: {
            for (int i{0}; i < 8; i++) {
                int to{};
                if (i == 0) {
                    to = static_cast<Utils::enumSquare>(from + 8);
                } else if (i == 1) {
                    to = static_cast<Utils::enumSquare>(from + 7);
                } else if (i == 2) {
                    to = static_cast<Utils::enumSquare>(from - 1);
                } else if (i == 3) {
                    to = static_cast<Utils::enumSquare>(from - 9);
                } else if (i == 4) {
                    to = static_cast<Utils::enumSquare>(from - 8);
                } else if (i == 5) {
                    to = static_cast<Utils::enumSquare>(from + -7);
                } else if (i == 6) {
                    to = static_cast<Utils::enumSquare>(from + 1);
                } else if (i == 7) {
                    to = static_cast<Utils::enumSquare>(from + 9);
                }

                if (to > 63 || to < 0) {
                    // Square is outside the board
                    continue;
                }
                Move move = Move(pt, pj, from, to);
                determineMovementType(pj, board, move);
                MoveValidator validator = MoveValidator(board, move, pj);
                if (validator.validate()) {
                    moves.push_back(static_cast<Utils::enumSquare>(to));
                }
            }
            break;
        }
    }
    return moves;
}

void determineMovementType(Player &currentPlayer, Board &board, Move &move) {
    auto pt = move.getPieceType();

    bool capture{false};
    bool castle{false};
    bool enPassant{false};

    // Get a bitboard of the current player
    U64 currentPlayerBoard = board.getAllPiecesOfAGivenPlayer(currentPlayer);
    U64 otherPlayerBoard = (currentPlayerBoard ^ board.getCompleteBoard());

    U64 toSquare = static_cast<std::uint_fast64_t>(1) << move.getTo();

    // Determine if is castle
    // Right now we aren't able to support both sides independently
    if (currentPlayer.canPlayerCastle()) {
        if ((pt == Utils::enumPieces::rook) || (pt == Utils::enumPieces::king)) {
            if (pt == Utils::enumPieces::rook) {
                // The piece must be moved to the king
                U64 bitboardOfKings{board.getPieceSet(Utils::enumPieces::king)};
                U64 kingBitboard{bitboardOfKings & currentPlayerBoard};

                if ((toSquare & kingBitboard) != 0) {
                    castle = true;
                }
            } else {
                // King
                // The piece must be moved to the rook
                U64 bitboardOfRooks{board.getPieceSet(Utils::enumPieces::rook)};
                U64 rookBitboard{bitboardOfRooks & currentPlayerBoard};

                if ((toSquare & rookBitboard) != 0) {
                    castle = true;
                }
            }
        }
    }

    // Determine if is capture
    if ((toSquare & otherPlayerBoard) != 0) {
        capture = true;
    }

    // Determine if is en Passant
    if ((board.getEnPassantAllowedFile() != 0) && (move.getPieceType() == Utils::enumPieces::pawn)) {
        if (capture) {
            board.restartEnPassant();
        } else if (obtainFileFromSquare(move.getTo()) == board.getEnPassantAllowedFile()) {
            enPassant = true;
        }
    } else if (board.getEnPassantAllowedFile() != 0) {
        board.restartEnPassant();
    }

    move.setUpFlags(castle, capture, enPassant);
}
