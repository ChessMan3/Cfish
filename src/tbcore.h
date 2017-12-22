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

/*
  tbcore.h Copyright (c) 2011-2017 Ronald de Man
*/

#ifndef TBCORE_H
#define TBCORE_H

#include <stdatomic.h>

#ifndef _WIN32
#include <pthread.h>
#define SEP_CHAR ':'
#define FD int
#define FD_ERR -1
#else
#include <windows.h>
#define SEP_CHAR ';'
#define FD HANDLE
#define FD_ERR INVALID_HANDLE_VALUE
#endif

#ifndef _WIN32
#define LOCK_T pthread_mutex_t
#define LOCK_INIT(x) pthread_mutex_init(&(x), NULL)
#define LOCK_DESTROY(x) pthread_mutex_destroy(&(x))
#define LOCK(x) pthread_mutex_lock(&(x))
#define UNLOCK(x) pthread_mutex_unlock(&(x))
#else
#define LOCK_T HANDLE
#define LOCK_INIT(x) do { x = CreateMutex(NULL, FALSE, NULL); } while (0)
#define LOCK_DESTROY(x) CloseHandle(x)
#define LOCK(x) WaitForSingleObject(x, INFINITE)
#define UNLOCK(x) ReleaseMutex(x)
#endif

#ifndef _MSC_VER
#define BSWAP32(v) __builtin_bswap32(v)
#define BSWAP64(v) __builtin_bswap64(v)
#else
#define BSWAP32(v) _byteswap_ulong(v)
#define BSWAP64(v) _byteswap_uint64(v)
#endif

#define WDLSUFFIX ".rtbw"
#define DTZSUFFIX ".rtbz"
#define DTMSUFFIX ".rtbm"
#define TBPIECES 6

const uint32_t WDL_MAGIC = 0x5d23e871;
const uint32_t DTZ_MAGIC = 0xa50c66d7;
const uint32_t DTM_MAGIC = 0x88ac504b;

#define TBHASHBITS 10

struct TBHashEntry;

typedef uint64_t base_t;

struct PairsData {
  uint8_t *indextable;
  uint16_t *sizetable;
  uint8_t *data;
  uint16_t *offset;
  uint8_t *symlen;
  uint8_t *sympat;
  uint32_t blocksize;
  uint32_t idxbits;
  uint8_t min_len;
  uint8_t const_val[2];
  base_t base[]; // must be base[1] in C++
};

struct TBEntry {
  uint8_t *data;
  Key key;
  uint64_t mapping;
  atomic_uchar ready;
  uint8_t num;
  uint8_t symmetric;
  uint8_t has_pawns;
  uint8_t loss_only;
}
#ifndef _WIN32
__attribute__((__may_alias__))
#endif
;

struct TBEntry_piece {
  uint8_t *data;
  Key key;
  uint64_t mapping;
  atomic_uchar ready;
  uint8_t num;
  uint8_t symmetric;
  uint8_t has_pawns;
  uint8_t loss_only;
  uint8_t enc_type;
  struct PairsData *precomp[2];
  int factor[2][TBPIECES];
  uint8_t pieces[2][TBPIECES];
  uint8_t norm[2][TBPIECES];
};

struct TBEntry_pawn {
  uint8_t *data;
  Key key;
  uint64_t mapping;
  atomic_uchar ready;
  uint8_t num;
  uint8_t symmetric;
  uint8_t has_pawns;
  uint8_t loss_only;
  uint8_t pawns[2];
  struct {
    struct PairsData *precomp[2];
    int factor[2][TBPIECES];
    uint8_t pieces[2][TBPIECES];
    uint8_t norm[2][TBPIECES];
  } file[4];
};

struct TBEntry_pawn2 {
  uint8_t *data;
  Key key;
  uint64_t mapping;
  atomic_uchar ready;
  uint8_t num;
  uint8_t symmetric;
  uint8_t has_pawns;
  uint8_t loss_only;
  uint8_t pawns[2];
  struct {
    struct PairsData *precomp[2];
    int factor[2][TBPIECES];
    uint8_t pieces[2][TBPIECES];
    uint8_t norm[2][TBPIECES];
  } rank[6];
};

struct DTZEntry_piece {
  uint8_t *data;
  Key key;
  uint64_t mapping;
  atomic_uchar ready;
  uint8_t num;
  uint8_t symmetric;
  uint8_t has_pawns;
  uint8_t loss_only;
  uint8_t enc_type;
  struct PairsData *precomp;
  int factor[TBPIECES];
  uint8_t pieces[TBPIECES];
  uint8_t norm[TBPIECES];
  uint8_t flags; // accurate, mapped, side
  uint16_t map_idx[4];
  uint8_t *map;
};

struct DTZEntry_pawn {
  uint8_t *data;
  Key key;
  uint64_t mapping;
  atomic_uchar ready;
  uint8_t num;
  uint8_t symmetric;
  uint8_t has_pawns;
  uint8_t loss_only;
  uint8_t pawns[2];
  struct {
    struct PairsData *precomp;
    int factor[TBPIECES];
    uint8_t pieces[TBPIECES];
    uint8_t norm[TBPIECES];
  } file[4];
  uint8_t flags[4];
  uint16_t map_idx[4][4];
  uint8_t *map;
};

struct DTMEntry_piece {
  uint8_t *data;
  Key key;
  uint64_t mapping;
  atomic_uchar ready;
  uint8_t num;
  uint8_t symmetric;
  uint8_t has_pawns;
  uint8_t loss_only;
  uint8_t enc_type;
  struct PairsData *precomp[2];
  int factor[2][TBPIECES];
  uint8_t pieces[2][TBPIECES];
  uint8_t norm[2][TBPIECES];
  uint16_t map_idx[2][2];
  uint16_t *map;
};

struct DTMEntry_pawn {
  uint8_t *data;
  Key key;
  uint64_t mapping;
  atomic_uchar ready;
  uint8_t num;
  uint8_t symmetric;
  uint8_t has_pawns;
  uint8_t loss_only;
  uint8_t pawns[2];
  struct {
    struct PairsData *precomp[2];
    int factor[2][TBPIECES];
    uint8_t pieces[2][TBPIECES];
    uint8_t norm[2][TBPIECES];
  } rank[6];
  uint16_t map_idx[6][2][2];
  uint16_t *map;
};

struct TBHashEntry {
  Key key;
  struct TBEntry *ptr;
  struct TBEntry *dtm_ptr;
};

struct DTZTableEntry {
  Key key1;
  Key key2;
  struct TBEntry *entry;
};

#endif

