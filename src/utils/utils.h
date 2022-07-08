#ifndef CHESS_UTILS_H
#define CHESS_UTILS_H

#include <cstdint>


using U64 = std::uint_fast64_t;

namespace Utils{
	enum Color {
		whitePLayer,
		blackPlayer
	};

	enum enumPieces {
		white,
		black,
		pawn,
		bishop,
		knight,
		rook,
		queen,
		king
	};
}

#endif
