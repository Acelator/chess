#ifndef CHESS_MOVE_H
#define CHESS_MOVE_H

#include "utils/utils.h"

#include "player.h"

class Move
{
private:
	Utils::enumPieces pt;
	Player &pj;
	std::uint_fast8_t from;
	std::uint_fast8_t to;
	Utils::flagsType flags;

public:
	// Allow to update "to" and "from" after initilization???
	Move(Utils::enumPieces piece, Player &player, std::uint_fast8_t origin, std::uint_fast8_t destination, Utils::flagsType movementCode) : pt(piece), pj(player), from(origin), to(destination), flags(movementCode)
	{
	}

	// Return string (Ex. A1 or 1 (square number)) ??
	std::uint_fast8_t getTo();
	std::uint_fast8_t getFrom();
	Utils::flagsType getFlags();
	Utils::enumPieces getPieceType();

	bool isMoveValid();
	bool isCapture();
	bool isPromotion();
};

#endif
