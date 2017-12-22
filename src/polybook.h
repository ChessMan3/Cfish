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

/* polybook.h from BrainFish, Copyright (C) 2016-2017 Thomas Zipproth */

#ifndef POLYBOOK_H_INCLUDED
#define POLYBOOK_H_INCLUDED

#include "bitboard.h"
#include "position.h"

void pb_init(const char *bookfile);
void pb_set_best_book_move(int best_book_move);
void pb_set_book_depth(int book_depth);

Move pb_probe(Pos *pos);

#endif

