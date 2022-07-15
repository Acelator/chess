#include <iostream>

#include "game.h"

int main() {
	Game game = Game();

	game.makeMove(Utils::enumPieces::pawn, 8, 17, Utils::flagsType::quietMove);
	game.makeMove(Utils::enumPieces::pawn, 55, 39, Utils::flagsType::quietMove);

	return 0;
}
