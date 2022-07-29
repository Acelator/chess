#include "path.h"

std::vector<Utils::enumSquare> Path::calculatePath() {
    auto pt = move.getPieceType();
    std::vector<Utils::enumSquare> path{};

    // Determine the file of the starting and final square
    int startingFile = obtainFileFromSquare(move.getFrom());
    int finalFile{obtainFileFromSquare(move.getTo())};

    // Determine the rank of the starting and final square
    auto startingRank = obtainRankFromSquare(move.getFrom());
    auto finalRank = obtainRankFromSquare(move.getTo());

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
                if (((obtainRankFromSquare(move.getFrom()) == 2) && (player.getPlayerColor() == Utils::Color::whitePLayer)) ||
                    ((obtainRankFromSquare(move.getFrom()) == 7) && (player.getPlayerColor() == Utils::Color::blackPlayer))) {
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
        case (Utils::enumPieces::queen):
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
            if ((path.size() > 1) && pt == Utils::enumPieces::king) {
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
    int startingFile = obtainFileFromSquare(move.getFrom());
    int finalFile{obtainFileFromSquare(move.getTo())};

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
    auto startingRank = obtainRankFromSquare(move.getFrom());
    auto finalRank = obtainRankFromSquare(move.getTo());

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

    if (obtainRankFromSquare(move.getFrom()) == obtainRankFromSquare(move.getTo())) {
        return path;
    }
    if ((std::abs(move.getFrom() - move.getTo()) % 9) == 0) {
        if (move.getFrom() > move.getTo()) {
            // soWe
            if (obtainFileFromSquare(move.getFrom()) == 1) {
                return path;
            }
            for (int i{move.getFrom() - 9}; i >= move.getTo(); i -= 9) {
                path.push_back(static_cast<Utils::enumSquare>(i));
            }
        } else {
            // noEa
            if (obtainRankFromSquare(move.getFrom()) == 8) {
                return path;
            }
            for (int i{move.getFrom() + 9}; i <= move.getTo(); i += 9) {
                path.push_back(static_cast<Utils::enumSquare>(i));
            }
        }
    } else if ((std::abs(move.getFrom() - move.getTo()) % 7) == 0) {
        if (move.getFrom() > move.getTo()) {
            // noWe
            if (obtainRankFromSquare(move.getFrom()) == 1) {
                return path;
            }
            for (int i{move.getFrom() - 7}; i >= move.getTo(); i -= 7) {
                path.push_back(static_cast<Utils::enumSquare>(i));
            }
        } else {
            // soEa
            if (obtainFileFromSquare(move.getFrom()) == 8) {
                return path;
            }
            for (int i{move.getFrom() + 7}; i <= move.getTo(); i += 7) {
                path.push_back(static_cast<Utils::enumSquare>(i));
            }
        }
    }
    return path;
}