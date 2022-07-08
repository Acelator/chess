#include "board.h"

U64 Board::getPieceSet(Utils::enumPieces pt) {
	return this->m_pieces[pt];
}

U64 Board::getPawns(Utils::Color color) {
	return this->m_pieces[Utils::enumPieces::pawn] & this-> m_pieces[color];
}

U64  Board::getBishops(Utils::Color color) {
	return this->m_pieces[Utils::enumPieces::bishop] & this-> m_pieces[color]; 
}

U64 Board::getRooks(Utils::Color color) {
	return this->m_pieces[Utils::enumPieces::rook] & this-> m_pieces[color];
}

U64 Board::getQueen(Utils::Color color) {
	return this->m_pieces[Utils::enumPieces::queen] & this-> m_pieces[color];
}

U64 Board::getKing(Utils::Color color) {
	return this->m_pieces[Utils::enumPieces::king] & this-> m_pieces[color];
}
