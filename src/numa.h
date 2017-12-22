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

#ifndef NUMA_H
#define NUMA_H
#include "types.h"

#ifdef NUMA
#ifndef __WIN32__
#include <numa.h>
#else
#include <windows.h>
#endif

int numa_avail;
void numa_init(void);
void numa_exit(void);
void read_numa_nodes(char *str);
struct bitmask *numa_thread_to_node(int idx);
int bind_thread_to_numa_node(int idx);

#ifndef __WIN32__
typedef struct bitmask *NodeMask;
#define masks_equal numa_bitmask_equal
#else
typedef int NodeMask;
#define masks_equal(a,b) 1
void *numa_alloc(size_t size);
void numa_free(void *ptr, size_t size);
void numa_interleave_memory(void *ptr, size_t size, ULONGLONG mask);
#endif

#else

typedef int NodeMask;
#define masks_equal(a,b) 1
#define numa_alloc(size) calloc(size, 1)
#define numa_interleave_memory(a, b, c) do {} while (0)
#define numa_free(ptr, size) free(ptr)
#define bind_thread_to_numa_node(a) 0

#endif

#endif

