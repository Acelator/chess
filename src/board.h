#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <array>
#include <iostream>

#include "utils/utils.h"

// Denser board
class Board{
	// The first arrays will represent all the white pieces 
	// while the second the black ones 
	// From there, the array will represent each color independent pieces bitboards
	std::array<U64, 8> m_pieces{};

public:
	Board() {
		// Set up starting pieces position
		m_pieces[Utils::enumPieces::white]  =  0xffff;
		m_pieces[Utils::enumPieces::black]  =  0xffff000000000000;

		m_pieces[Utils::enumPieces::pawn]   =  0x00ff00000000ff00;
		m_pieces[Utils::enumPieces::bishop] =  0x2400000000000024;
		m_pieces[Utils::enumPieces::knight] =  0x4200000000000042;
		m_pieces[Utils::enumPieces::rook]   =  0x8100000000000081;

		// m_pieces[Utils::enumPieces::king]  =   0x0800000000000010;
		// m_pieces[Utils::enumPieces::queen] =   0x1000000000000008;

		// Reversed
		m_pieces[Utils::enumPieces::queen] =   0x0800000000000010;
		m_pieces[Utils::enumPieces::king]  =   0x1000000000000008;
	}

	U64 getCompleteBoard();
	U64 getPieceSet(Utils::enumPieces pt);
	U64 getPieceSetOfAGivenPlayer(Utils::enumPieces pt, Utils::Color color);
	U64 getALlPiecesOfAGivenPlayer(Utils::Color color);

	U64 getPawns();
	U64 getBishops();
	U64 getKnights();
	U64 getRooks();
	U64 getQueen();
	U64 getKing();

	// Returns the updatedBoard
	void updateBoard(Utils::enumPieces pt, Utils::Color color, U64 newBoard);
	void updateBoardOfAGivenPlayer(Utils::Color color, U64 newBoard);
};


#endif
