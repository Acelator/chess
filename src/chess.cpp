#include <iostream>

#include "game.h"

int main() {
	Game game = Game();

	game.makeMove(Utils::enumPieces::pawn, 15, 22, Utils::flagsType::quietMove);

	return 0;
}
