#include <iostream>

#include "game.h"

int main() {
	Game game = Game();

	game.makeMove(Utils::enumPieces::knight, 6, 21);
	game.makeMove(Utils::enumPieces::bishop, 61, 47);
	game.makeMove(Utils::enumPieces::rook, 7, 55);
	game.makeMove(Utils::enumPieces::pawn, 48, 32);
	game.makeMove(Utils::enumPieces::queen, 4, 3);
	game.makeMove(Utils::enumPieces::king, 60, 56);

	return 0;
}
