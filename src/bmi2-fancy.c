/*
 McBrain, a UCI chess playing engine derived from Stockfish and Glaurung 2.1
 Copyright (C) 2004-2008 Tord Romstad (Glaurung author)
 Copyright (C) 2008-2015 Marco Costalba, Joona Kiiski, Tord Romstad (Stockfish Authors)
 Copyright (C) 2015-2017 Marco Costalba, Joona Kiiski, Gary Linscott, Tord Romstad (Stockfish Authors)
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

Bitboard RookMasks[64], RookMasks2[64];
uint16_t *RookAttacks[64];

Bitboard BishopMasks[64], BishopMasks2[64];
uint16_t *BishopAttacks[64];

static uint16_t BishopTable[5248];
static uint16_t RookTable[102400];

typedef unsigned (Fn)(Square, Bitboard);

static void init_bmi2(uint16_t table[], uint16_t *attacks[], Bitboard masks[],
                      Bitboard masks2[], int deltas[], Fn index)
{
  Bitboard edges, b;

  for (int s = 0; s < 64; s++) {
    attacks[s] = table;

    // Board edges are not considered in the relevant occupancies
    edges = ((Rank1BB | Rank8BB) & ~rank_bb_s(s)) | ((FileABB | FileHBB) & ~file_bb_s(s));

    masks2[s] = sliding_attack(deltas, s, 0);
    masks[s] = masks2[s] & ~edges;

    // Use Carry-Rippler trick to enumerate all subsets of masks[s] and
    // fill the attacks table.
    b = 0;
    do {
      attacks[s][index(s, b)] = _pext_u64(sliding_attack(deltas, s, b), masks2[s]);
      b = (b - masks[s]) & masks[s];
      table++;
    } while (b);
  }
}

static void init_sliding_attacks(void)
{
  init_bmi2(RookTable, RookAttacks, RookMasks, RookMasks2,
            RookDeltas, bmi2_index_rook);
  init_bmi2(BishopTable, BishopAttacks, BishopMasks, BishopMasks2,
            BishopDeltas, bmi2_index_bishop);
}

