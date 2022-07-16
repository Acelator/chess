#include <iostream>

#include "game.h"

int main() {
	Game game = Game();

	game.makeMove(Utils::enumPieces::knight, 6, 21, Utils::flagsType::quietMove);
	game.makeMove(Utils::enumPieces::rook, 56, 63, Utils::flagsType::quietMove);
	game.makeMove(Utils::enumPieces::bishop, 5, 23, Utils::flagsType::quietMove);
	game.makeMove(Utils::enumPieces::pawn, 48, 32, Utils::flagsType::quietMove);

	return 0;
}
