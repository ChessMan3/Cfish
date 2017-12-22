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

/*
 tbprobe.h Copyright (c) 2011-2017 Ronald de Man
*/

#ifndef TBPROBE_H
#define TBPROBE_H

#include "movegen.h"

extern int TB_MaxCardinality;
extern int TB_MaxCardinalityDTM;

void TB_init(char *path);
void TB_free(void);
int TB_probe_wdl(Pos *pos, int *success);
int TB_probe_dtz(Pos *pos, int *success);
Value TB_probe_dtm(Pos *pos, int wdl, int *success);
int TB_root_probe_wdl(Pos *pos, RootMoves *rm);
int TB_root_probe_dtz(Pos *pos, RootMoves *rm);
int TB_root_probe_dtm(Pos *pos, RootMoves *rm);
void TB_expand_mate(Pos *pos, RootMove *move);

#endif

