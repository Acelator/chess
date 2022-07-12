#ifndef CHESS_UTILS_H
#define CHESS_UTILS_H

#include <iostream>
#include <cstdint>

using U64 = std::uint_fast64_t;

namespace Utils{
	enum Color {
		whitePLayer,
		blackPlayer
	};

	enum enumPieces {
		pawn,
		bishop,
		knight,
		rook,
		queen,
		king
	};

	enum flagsType{
		quietMove,
		doublePawnPush,
		kingCastle,
		queenCastle,
		capture,
		epCapture,
		knightPromotion,
		bishopPromotion,
		rookPromotion,
		queenPromotion,
		knightPromoAndCapture,
		bishopPromoAndCapture,
		rookPromoAndCapture,
		queenPromoAndCapture
	};

};

#endif
