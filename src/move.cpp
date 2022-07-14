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

int Move::mapIntFromLERFnotation(std::uint_fast8_t square) {
	float division = (static_cast<float>(square) / 8);
	return std::ceil(division); 
}

