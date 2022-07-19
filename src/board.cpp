#include "board.h"

U64 Board::getCompleteBoard() {
	return this->m_playerSet[Utils::Color::whitePLayer] | this->m_playerSet[Utils::Color::blackPlayer];
}

U64 Board::getPieceSet(Utils::enumPieces pt) {
	return this->m_pieces[pt];
}

U64 Board::getPieceSetOfAGivenPlayer(Utils::enumPieces pt, Player &pj) {
	return this->m_pieces[pt] & this->m_playerSet[pj.getPlayerColor()];
}

U64 Board::getAllPiecesOfAGivenPlayer(Player &pj) {
	return this->m_playerSet[pj.getPlayerColor()];
}

void Board::updateBoard(Move& move, Player pj) {
	U64 startingPieceBitboard = static_cast<unsigned long>(0x1) << move.getFrom();
	U64 finalPieceBitboard = static_cast<unsigned long>(0x1) << move.getTo();

	// Update player board
	U64 playerBoard{this->getAllPiecesOfAGivenPlayer(pj)}; 
	U64 piecesBoard{this->getPieceSet(move.getPieceType())};

	// Delete from the starting position the piece moved
	playerBoard ^= startingPieceBitboard;
	piecesBoard ^= startingPieceBitboard;

	// input the new piece position
	playerBoard |= finalPieceBitboard;
	piecesBoard |= finalPieceBitboard;

	std::cout << "Player: " << playerBoard << '\n';
	std::cout << "Piece: " << piecesBoard << '\n';

	// Save it
	this->m_playerSet[pj.getPlayerColor()] = playerBoard;
	this->m_pieces[move.getPieceType()] = piecesBoard;
}

U64 Board::mirrorHorizontal (U64 x) {
   const U64 k1 = U64(0x5555555555555555);
   const U64 k2 = U64(0x3333333333333333);
   const U64 k4 = U64(0x0f0f0f0f0f0f0f0f);
   x = ((x >> 1) & k1) | ((x & k1) << 1);
   x = ((x >> 2) & k2) | ((x & k2) << 2);
   x = ((x >> 4) & k4) | ((x & k4) << 4);
   return x;
}

std::ostream& operator<<(std::ostream &os, Board& board) {
	U64 bitboard{board.mirrorHorizontal(board.getCompleteBoard())};
	os << "Board expresed as int: " << board.getCompleteBoard() << '\n';
	os << '|';

	int border{56};
	for (int i{63}; i >= 0; i--) {
		if(((bitboard & (static_cast<unsigned long>(0x1) << i)) != 0)) {
			os << " X " << '|';
		} else {
			os << "   " << '|';
		}
		if (i == 0) {
			break;
		}
		if (i == border) {
			os << '\n' << '|';
			border -= 8;
		}
	}
	return os;
}
