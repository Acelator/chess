#include <iostream>

#include "game.h"

int main() {
	Game game = Game();

	game.makeMove(Utils::enumPieces::knight, 6, 21);
	game.makeMove(Utils::enumPieces::rook, 56, 63);
	game.makeMove(Utils::enumPieces::bishop, 5, 23);
	game.makeMove(Utils::enumPieces::pawn, 48, 32);
	game.makeMove(Utils::enumPieces::queen, 4, 3);
	game.makeMove(Utils::enumPieces::king, 60, 61);

	return 0;
}
