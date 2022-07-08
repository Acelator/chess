#include <iostream>
#include "player.h"
#include "board.h"

int main() {
	Board board = Board();
	std::cout << std::hex << board.getPieceSet(Utils::enumPieces::white);

	return 0;
}
