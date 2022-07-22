#include <iostream>

#include "game.h"

int main() {
	Game game = Game();

	std::cout << "CHESS GAME\n";
	std::cout << "Pieces: (0) pawn, (1) bishop, (2) knight, (3) rook, (4) queen, (5) king\n";

	while (true) {
		std::cout << "New turn\n";
		std::cout << "Introduce piece to move: ";
		unsigned int pt{};
		std::cin >> pt;

		if ((pt <= 5) && (pt >= 0)) {
			std::cout << "Starting square: ";
			unsigned int from{};
			std::cin >> from;

			std::cout << "final square: ";
			unsigned int to{};
			std::cin >> to;

			game.makeMove(static_cast<Utils::enumPieces>(pt), from, to);
		} else {
			std::cout << "Invalid input. Try again\n";
		}
	};

	/* game.makeMove(Utils::enumPieces::knight, 6, 21); */
	/* game.makeMove(Utils::enumPieces::pawn, 48, 32); */
	/* game.makeMove(Utils::enumPieces::knight, 21, 36); */
	/* game.makeMove(Utils::enumPieces::pawn, 32, 24); */
	/* game.makeMove(Utils::enumPieces::knight, 36, 53); */

	return 0;
}
