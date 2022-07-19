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
	// Update the board of the specific piece
	//this->m_pieces[pt] = newPtBoard;
	//this->m_playerSet[pj.getPlayerColor()] = move.getUpdatedPlayerBoard();
}

std::ostream& operator<<(std::ostream &os, Board& board) {
	U64 bitboard{board.getCompleteBoard()};
	os << "Board expresed as int: " << bitboard << '\n';
	os << '|';

	int border{7};
	for (int i{0}; i < 64; i++) {
		if(((bitboard & (static_cast<unsigned long>(0x1) << i)) != 0)) {
			os << " X " << '|';
		}
		if (i == 63) {
			break;
		}
		if (i == border) {
			os << '\n' << '|';
			border += 8;
		}
	}
	return os;
} 
