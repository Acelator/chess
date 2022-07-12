#include "board.h"

U64 Board::getCompleteBoard() {
	return this->m_playerSet[Utils::Color::whitePLayer] | this->m_pieces[Utils::Color::blackPlayer];
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
