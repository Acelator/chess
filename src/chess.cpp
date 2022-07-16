#include <iostream>

#include "game.h"

int main() {
	Game game = Game();

	game.makeMove(Utils::enumPieces::bishop, 5, 26, Utils::flagsType::quietMove);
	game.makeMove(Utils::enumPieces::bishop, 61, 16, Utils::flagsType::quietMove);
	game.makeMove(Utils::enumPieces::pawn, 15, 31, Utils::flagsType::quietMove);

	return 0;
}
