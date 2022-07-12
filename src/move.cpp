#include "move.h"
#include "utils/utils.h"

bool Move::isMoveValid() {
	switch (this->flags) {
		case (Utils::flagsType::quietMove) :

			break;
		case (Utils::flagsType::doublePawnPush):
		case (Utils::flagsType::kingCastle):
		case (Utils::flagsType::queenCastle):
		case (Utils::flagsType::capture):
		case (Utils::flagsType::epCapture):
		case (Utils::flagsType::knightPromotion):
		case (Utils::flagsType::bishopPromotion):
		case (Utils::flagsType::rookPromotion):
		case (Utils::flagsType::queenPromotion):
		case (Utils::flagsType::knightPromoAndCapture):
		case (Utils::flagsType::bishopPromoAndCapture):
		case (Utils::flagsType::rookPromoAndCapture):
		case (Utils::flagsType::queenPromoAndCapture):
			break;
	}
	return false;
}

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
