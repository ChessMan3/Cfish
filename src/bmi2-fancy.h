/*
 McBrain, a UCI chess playing engine derived from Stockfish and Glaurung 2.1
 Copyright (C) 2004-2008 Tord Romstad (Glaurung author)
 Copyright (C) 2008-2015 Marco Costalba, Joona Kiiski, Tord Romstad (Stockfish Authors)
 Copyright (C) 2015-2016 Marco Costalba, Joona Kiiski, Gary Linscott, Tord Romstad (Stockfish Authors)
 Copyright (C) 2017 Michael Byrne, Marco Costalba, Joona Kiiski, Gary Linscott, Tord Romstad (McBrain Authors)
 
 Other significant contributors through their Stockfish forks:
 Ronald De Man - SF/Cfish and Syzygy tablebase author
 Ivan Ivec - SF/Corchess author
 Thomas Zipproth - SF/Brainfish author (Book author)
 
 McBrain is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 McBrain is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <immintrin.h>

extern Bitboard RookMasks[64], RookMasks2[64];
extern Bitboard BishopMasks[64], BishopMasks2[64];
extern uint16_t *RookAttacks[64];
extern uint16_t *BishopAttacks[64];

INLINE unsigned bmi2_index_bishop(Square s, Bitboard occupied)
{
  return (unsigned)_pext_u64(occupied, BishopMasks[s]);
}

INLINE unsigned bmi2_index_rook(Square s, Bitboard occupied)
{
  return (unsigned)_pext_u64(occupied, RookMasks[s]);
}

INLINE Bitboard attacks_bb_bishop(Square s, Bitboard occupied)
{
  return _pdep_u64(BishopAttacks[s][bmi2_index_bishop(s, occupied)],
                   BishopMasks2[s]);
}

INLINE Bitboard attacks_bb_rook(Square s, Bitboard occupied)
{
  return _pdep_u64(RookAttacks[s][bmi2_index_rook(s, occupied)],
                   RookMasks2[s]);
}

