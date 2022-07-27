#ifndef CHESS_UTILS_H
#define CHESS_UTILS_H

#include <iostream>
#include <array>
#include <cstdint>
#include <cmath>
#include <string>

using U64 = std::uint_fast64_t;

namespace Utils {
    namespace Constants {
        // From first rank to eighth
        inline constexpr std::array<U64, 8> ranks{0xff, 0xff00, 0xff0000, 0xff000000, 0xff00000000, 0xff0000000000, 0xff000000000000,
                                                  0xff00000000000000};

        // Bitmasks for files from a to  H
        inline constexpr std::array<U64, 8> files{0x101010101010101, 0x202020202020202, 0x404040404040404, 0x808080808080808, 0x1010101010101010,
                                                  0x2020202020202020, 0x4040404040404040, 0x8080808080808080};
    }

    enum enumSquare {
        a1, b1, c1, d1, e1, f1, g1, h1,
        a2, b2, c2, d2, e2, f2, g2, h2,
        a3, b3, c3, d3, e3, f3, g3, h3,
        a4, b4, c4, d4, e4, f4, g4, h4,
        a5, b5, c5, d5, e5, f5, g5, h5,
        a6, b6, c6, d6, e6, f6, g6, h6,
        a7, b7, c7, d7, e7, f7, g7, h7,
        a8, b8, c8, d8, e8, f8, g8, h8
    };

    enum Color {
        whitePLayer,
        blackPlayer
    };

    enum enumPieces {
        pawn,
        bishop,
        knight,
        rook,
        queen,
        king
    };
};

#endif
