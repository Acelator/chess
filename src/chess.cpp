#include <iostream>

#include "game.h"

int main() {
	Game game = Game();

	game.makeMove(Utils::enumPieces::knight, 6, 21);
	game.makeMove(Utils::enumPieces::pawn, 48, 32);
	game.makeMove(Utils::enumPieces::knight, 21, 36);
	game.makeMove(Utils::enumPieces::pawn, 32, 24);
	game.makeMove(Utils::enumPieces::knight, 36, 53);

	return 0;
}
