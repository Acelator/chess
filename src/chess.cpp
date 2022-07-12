#include <iostream>

#include "game.h"

int main() {
	Game game = Game();

	game.makeMove(Utils::enumPieces::rook, 0x80, 0x90, Utils::flagsType::capture);

	return 0;
}
