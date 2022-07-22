#ifndef CHESS_BOARD_H
#define CHESS_BOARD_H

#include <iostream>

#include "utils/utils.h"
#include "move.h"
#include "player.h"

// Denser board
class Board{
	// The array represents each color independent pieces bitboards
	std::array<U64, 6> m_pieces{};
	std::array<U64, 2> m_playerSet{};

	std::uint_fast8_t enPassantAllowedFile{0};
	U64 mirrorHorizontal (U64 x);

public:
	Board() {
		// Little-Endian Rank File (LERF) Mapping
		// Set up starting pieces position
		m_playerSet[Utils::Color::whitePLayer]  =  0xffff;
		m_playerSet[Utils::Color::blackPlayer]  =  0xffff000000000000;

		m_pieces[Utils::enumPieces::pawn]   =  0x00ff00000000ff00;
		m_pieces[Utils::enumPieces::bishop] =  0x2400000000000024;
		m_pieces[Utils::enumPieces::knight] =  0x4200000000000042;
		m_pieces[Utils::enumPieces::rook]   =  0x8100000000000081;
		m_pieces[Utils::enumPieces::queen] =   0x0800000000000010;
		m_pieces[Utils::enumPieces::king]  =   0x1000000000000008;
	}

	U64 getCompleteBoard();
	U64 getPieceSet(Utils::enumPieces pt);
	U64 getPieceSetOfAGivenPlayer(Utils::enumPieces pt, Player &pj);
	U64 getAllPiecesOfAGivenPlayer(Player &pj);

	void updateBoard(Move& move, Player& currentPlayer, Player& nextPlayer);

	std::uint_fast8_t getEnPassantAllowedFiles();
	void newEnPassantOportunity(int file);
	void restartEnPassant();

	friend std::ostream& operator<<(std::ostream &os, Board& board); 
};


#endif
