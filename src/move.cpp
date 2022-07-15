#include "move.h"

bool Move::isCapture() {
	std::cout << "Color: "<<  pj.getPlayerColor() <<'\n';
	return ((this->flags >> 2) == 1) ? true : false;
};

bool Move::isPromotion() {
	return ((this->flags >> 3) == 1) ? true : false;
};

std::uint_fast8_t Move::getTo() {
	return this->to;
}

std::uint_fast8_t Move::getFrom() {
	return this->from;
}

Utils::flagsType Move::getFlags() {
	return this->flags;
}

Utils::enumPieces Move::getPieceType() {
	return this->pt;
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
