#include "path.h"

std::vector<Utils::enumSquare> Path::calculatePath() {
    auto pt = move.getPieceType();
    std::vector<Utils::enumSquare> path{};

    // Determine the file of the starting and final square
    int startingFile = move.obtainFileFromSquare(move.getFrom());
    int finalFile{move.obtainFileFromSquare(move.getTo())};

    // Determine the rank of the starting and final square
    auto startingRank = move.obtainRankFromSquare(move.getFrom());
    auto finalRank = move.obtainRankFromSquare(move.getTo());

    switch (pt) {
        case (Utils::enumPieces::pawn): {
            if (move.isCapture() || move.isEnPassant()) {
                auto diagonalVector{calculateDiagonalMovement()};
                if (diagonalVector.empty()) {
                    throw -1;
                }
                return diagonalVector;
            }

            auto verticalVector{calculateVerticalMovement()};
            if (verticalVector.empty() || verticalVector.size() > 2) {
                // Pawn is trying to move further away than 2 squares
                throw -1;
            } else if (verticalVector.size() == 1) {
                return verticalVector;
            } else {
                // Double pawn push
                // En passant can be performed by the other player in his next turn
                if (((move.obtainRankFromSquare(move.getFrom()) == 2) && (player.getPlayerColor() == Utils::Color::whitePLayer)) ||
                    ((move.obtainRankFromSquare(move.getFrom()) == 7) && (player.getPlayerColor() == Utils::Color::blackPlayer))) {
                    board.newEnPassantOpportunity(startingFile);
                    return verticalVector;
                } else {
                    // Pawn isn't in the initial position, so the double push isn't possible
                    throw -1;
                }
            }
        }
        case (Utils::enumPieces::bishop): {
            auto diagonalVector{calculateDiagonalMovement()};

            if (diagonalVector.empty()) {
                throw -1;
            }
            return diagonalVector;
        }
        case (Utils::enumPieces::rook): {
            auto horizontalVector{calculateHorizontalMovement()};
            auto verticalVector{calculateVerticalMovement()};

            if (horizontalVector.empty() && verticalVector.empty()) {
                throw -1;
            } else if (horizontalVector.empty()) {
                return verticalVector;
            } else if (verticalVector.empty()) {
                return horizontalVector;
            }
            break;
        }
        case (Utils::enumPieces::knight): {
            // Knight always moves three squares
            if ((std::abs(startingRank - finalRank) + std::abs(startingFile - finalFile)) != 3) {
                // knight is trying to move further away than three squares
                throw -1;
            } else if ((startingFile == finalFile) || (startingRank == finalRank)) {
                // Knight is trying to move three squares in straight line
                throw -1;
            }

            // move is valid
            path.push_back(static_cast<Utils::enumSquare>(move.getTo()));
            return path;
        }
        case (Utils::enumPieces::queen): {
            auto horizontalVector{calculateHorizontalMovement()};
            auto verticalVector{calculateVerticalMovement()};
            auto diagonalVector{calculateDiagonalMovement()};

            if (!horizontalVector.empty()) {
                for (const auto &i: horizontalVector) {
                    path.push_back(i);
                }
            } else if (!verticalVector.empty()) {
                for (const auto &i: verticalVector) {
                    path.push_back(i);
                }
            } else if (!diagonalVector.empty()) {
                for (const auto &i: diagonalVector) {
                    path.push_back(i);
                }
            }
            break;
        }
        case (Utils::enumPieces::king): {
            auto horizontalVector{calculateHorizontalMovement()};
            auto verticalVector{calculateVerticalMovement()};
            auto diagonalVector{calculateDiagonalMovement()};

            if (!horizontalVector.empty()) {
                for (const auto &i: horizontalVector) {
                    path.push_back(i);
                }
            } else if (!verticalVector.empty()) {
                for (const auto &i: verticalVector) {
                    path.push_back(i);
                }
            } else if (!diagonalVector.empty()) {
                for (const auto &i: diagonalVector) {
                    path.push_back(i);
                }
            }

            if (path.size() > 1) {
                throw -1;
            }
            break;
        }
    }
    return path;
}

std::vector<Utils::enumSquare> Path::calculateVerticalMovement() {
    std::vector<Utils::enumSquare> path{};

    // Determine the file of the starting and final square
    int startingFile = move.obtainFileFromSquare(move.getFrom());
    int finalFile{move.obtainFileFromSquare(move.getTo())};

    // Piece isn't moving vertically
    if (startingFile != finalFile) {
        return path;
    }

    if (move.getFrom() > move.getTo()) {
        // south
        for (int i{move.getFrom() - 8}; i >= move.getTo(); i -= 8) {
            path.push_back(static_cast<Utils::enumSquare>(i));
        }
    } else {
        // north
        for (int i{move.getFrom() + 8}; i <= move.getTo(); i += 8) {
            path.push_back(static_cast<Utils::enumSquare>(i));
        }
    }
    return path;
}

std::vector<Utils::enumSquare> Path::calculateHorizontalMovement() {
    std::vector<Utils::enumSquare> path{};

    // Determine the rank of the starting and final square
    auto startingRank = move.obtainRankFromSquare(move.getFrom());
    auto finalRank = move.obtainRankFromSquare(move.getTo());

    // Piece isn't moving horizontally
    if (startingRank != finalRank) {
        return path;
    }

    if (move.getFrom() > move.getTo()) {
        // west
        for (int i{move.getFrom() - 1}; i >= move.getTo(); i--) {
            path.push_back(static_cast<Utils::enumSquare>(i));
        }
    } else {
        // east
        for (int i{move.getFrom() + 1}; i <= move.getTo(); i++) {
            path.push_back(static_cast<Utils::enumSquare>(i));
        }
    }
    return path;
}

std::vector<Utils::enumSquare> Path::calculateDiagonalMovement() {
    std::vector<Utils::enumSquare> path{};

    if ((std::abs(move.getFrom() - move.getTo()) % 9) == 0) {
        if (move.getFrom() > move.getTo()) {
            // noEa
            for (int i{move.getFrom() - 9}; i >= move.getTo(); i -= 9) {
                path.push_back(static_cast<Utils::enumSquare>(i));
            }
        } else {
            // soWe
            for (int i{move.getFrom() + 9}; i <= move.getTo(); i += 9) {
                path.push_back(static_cast<Utils::enumSquare>(i));
            }
        }
    } else if ((std::abs(move.getFrom() - move.getTo()) % 7) == 0) {
        if (move.getFrom() > move.getTo()) {
            // noWe
            for (int i{move.getFrom() - 7}; i >= move.getTo(); i -= 7) {
                path.push_back(static_cast<Utils::enumSquare>(i));
            }
        } else {
            // soEa
            for (int i{move.getFrom() + 7}; i <= move.getTo(); i += 7) {
                path.push_back(static_cast<Utils::enumSquare>(i));
            }
        }
    }
    return path;
}