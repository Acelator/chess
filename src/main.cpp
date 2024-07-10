#include <iostream>
#include "chess/game.h"

int main() {
    Board board{};
    Move move{15, 23, Player::White};
    auto b = board.simulateMove(move);
    std::cout << "Testing\n";
    std::cout << board.getPiecesBoardOfAGivenPlayer(Player::White, Pieces::King) << '\n';
    std::cout << b.getPieceBoard(Pieces::Pawn) << '\n';

    std::cout << "E\n";
    board.updateBoard(move);
    std::cout << board.getPieceBoard(Pieces::Pawn) << '\n';
}
