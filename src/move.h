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

	Utils::enumPieces pieceToPromoteTo{};

	bool promotion{false};
	bool castle;
	bool capture;
	bool enPassant{false};

public:
	// Allow to update "to" and "from" after initilization???
	Move(Utils::enumPieces piece, Player &player, std::uint_fast8_t origin, std::uint_fast8_t destination) : pt(piece), pj(player), from(origin), to(destination)
	{

	}

	Move(Utils::enumPieces piece, Player &player, std::uint_fast8_t origin, std::uint_fast8_t destination, Utils::enumPieces promotion) : pt(piece), pj(player), from(origin), to(destination), pieceToPromoteTo{promotion}
	{
		this->promotion = true;
	}

	// Return string (Ex. A1 or 1 (square number)) ??
	std::uint_fast8_t getTo();
	std::uint_fast8_t getFrom();
	Utils::enumPieces getPieceType();
	Utils::enumPieces getPieceToPromoteTo();

	bool isCapture();
	// After we know that castle is impossible don't check again
	bool isCastle();
	bool isPromotion();
	bool isEnPassant();

	void setUpFlags(bool castle, bool capture, bool enPassant);

	// Takes a square in LERF notation and convert it into the number of the file or of the rank
	// TODO: Remove as a member function??
	int obtainRankFromSquare(std::uint_fast8_t square);
	int obtainFileFromSquare(std::uint_fast8_t square);
};

#endif
