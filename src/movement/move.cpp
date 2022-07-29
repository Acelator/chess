#include "move.h"

// Getters
std::uint_fast8_t Move::getTo() const {
    return this->to;
}

std::uint_fast8_t Move::getFrom() const {
    return this->from;
}

Utils::enumPieces Move::getPieceType() const {
    return this->pt;
}

Utils::enumPieces Move::getPieceToPromoteTo() const {
    return this->pieceToPromoteTo;
}

// Utility
bool Move::isCapture() const {
    return this->capture;
}

bool Move::isCastle() const {
    return this->castle;
}

bool Move::isPromotion() const {
    return this->promotion;
}

bool Move::isEnPassant() const {
    return this->enPassant;
}

void Move::setUpFlags(bool isCastle, bool isCapture, bool isEnPassant) {
    this->castle = isCastle;
    this->capture = isCapture;
    this->enPassant = isEnPassant;
}

int obtainFileFromSquare(std::uint_fast8_t square) {
    float division = (static_cast<float>(square) / 8);
    double integer{};
    float decimal = std::modf(division, &integer);
    if (decimal == 0) {
        return 1;
    }

    int count{1};
    for (float i{0.125}; i < 1; i += 0.125) {
        if (i == decimal) {
            count++;
            return count;
        } else {
            count++;
        }
    }
    return 0;
}

int obtainRankFromSquare(std::uint_fast8_t square) {
    float division = (static_cast<float>(square) / 8);
    if (std::ceil(division) == division) {
        // number is whole
        return division + 1;
    }
    return std::ceil(division);
}
