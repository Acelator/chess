#include "board.h"

U64 Board::getCompleteBoard() {
	return this->m_pieces[Utils::enumPieces::white] | this->m_pieces[Utils::enumPieces::black];
}

U64 Board::getPieceSet(Utils::enumPieces pt) {
	return this->m_pieces[pt];
}

U64 Board::getPieceSetOfAGivenPlayer(Utils::enumPieces pt, Utils::Color color) {
	return this->m_pieces[pt] & this->m_pieces[color];
}

U64 Board::getALlPiecesOfAGivenPlayer(Utils::Color color) {
	if(Utils::Color::whitePLayer == color) {
		return this->m_pieces[Utils::enumPieces::white];
	} else {
		return this->m_pieces[Utils::enumPieces::black];
	}
}

U64 Board::getPawns() {
	return this->m_pieces[Utils::enumPieces::pawn];
}

U64  Board::getBishops() {
	return this->m_pieces[Utils::enumPieces::bishop];
}

U64 Board::getRooks() {
	return this->m_pieces[Utils::enumPieces::rook];
}

U64 Board::getQueen() {
	return this->m_pieces[Utils::enumPieces::queen];
}

U64 Board::getKing() {
	return this->m_pieces[Utils::enumPieces::king];
}

void Board::updateBoardOfAGivenPlayer(Utils::Color color, U64 newBoard) {
	if(Utils::Color::whitePLayer == color) {
		this->m_pieces[Utils::enumPieces::white] = newBoard;
	} else {
		this->m_pieces[Utils::enumPieces::black] = newBoard;
	}
}

void Board::updateBoard(Utils::enumPieces pt, Utils::Color color, U64 newBoard) {
	U64 allPlayerPieces{getALlPiecesOfAGivenPlayer(color)};
	U64 playerPtPieces{getPieceSetOfAGivenPlayer(pt, color)};
	U64 playerPtPiecesOfTheOtherPlayer{this->m_pieces[pt] ^ playerPtPieces};

	U64 newPtBoard{playerPtPiecesOfTheOtherPlayer | newBoard};
	// Update the board of the specific piece
	this->m_pieces[pt] = newPtBoard;

	// Delete original pt pieces from the color board
	U64 newPieceBoard{allPlayerPieces ^ playerPtPieces};
	newPieceBoard = newPieceBoard | newBoard;
	updateBoardOfAGivenPlayer(color, newPieceBoard);
}
