#include "move.h"

// Getters
std::uint_fast8_t Move::getTo() {
	return this->to;
}

std::uint_fast8_t Move::getFrom() {
	return this->from;
}
Utils::enumPieces Move::getPieceType() {
	return this->pt;
}

Utils::enumPieces Move::getPieceToPromoteTo() {
	return this->pieceToPromoteTo;
}

// Utility
bool Move::isCapture() {
	return this->capture;
};

bool Move::isCastle() {
	return this->castle;
}

bool Move::isPromotion() {
	return this->promotion;
};

bool Move::isEnPassant() {
	return this->enPassant;
}


void Move::setUpFlags(bool castle, bool capture, bool enPassant) {
	this->castle = castle;
	this->capture = capture;
	this->enPassant = enPassant;
}


int Move::obtainFileFromSquare(std::uint_fast8_t square) {
	float division = (static_cast<float>(square) / 8);
	double integer{};
	float decimal = std::modf(division, &integer);	
	if(decimal == 0) {
		return 1;
	}

	int count{1};
	for(float i{0.125}; i < 1; i += 0.125) {
		if(i == decimal) {
			count++;
			return count;
		} else {
			count ++;
		}
	}
	return 0;
}

int Move::obtainRankFromSquare(std::uint_fast8_t square) {
	float division = (static_cast<float>(square) / 8);
	if (std::ceil(division) == division) {
		// number is whole
		return division + 1;
	}
	return std::ceil(division);
}
