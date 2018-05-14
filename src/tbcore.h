/*
  Copyright (c) 2011-2018 Ronald de Man
*/

#ifndef TBCORE_H
#define TBCORE_H

#include <stdatomic.h>

#ifndef _WIN32
#include <pthread.h>
#define SEP_CHAR ':'
#else
#include <windows.h>
#define SEP_CHAR ';'
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
#define TBPIECES 7

const uint32_t WDL_MAGIC = 0x5d23e871;
const uint32_t DTZ_MAGIC = 0xa50c66d7;
const uint32_t DTM_MAGIC = 0x88ac504b;

#define TBHASHBITS 10

struct TBHashEntry;

typedef uint64_t base_t;

#ifdef _WIN32
typedef HANDLE map_t;
#else
typedef size_t map_t;
#endif

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
  map_t mapping;
  atomic_bool ready;
  uint8_t num;
  bool symmetric;
  bool has_pawns;
  bool loss_only;
}
#ifndef _WIN32
__attribute__((__may_alias__))
#endif
;

struct TBEntry_piece {
  uint8_t *data;
  Key key;
  map_t mapping;
  atomic_bool ready;
  uint8_t num;
  bool symmetric;
  bool has_pawns;
  bool loss_only;
  bool kk_enc;
  struct PairsData *precomp[2];
  size_t factor[2][TBPIECES];
  uint8_t pieces[2][TBPIECES];
  uint8_t norm[2][TBPIECES];
};

struct TBEntry_pawn {
  uint8_t *data;
  Key key;
  map_t mapping;
  atomic_bool ready;
  uint8_t num;
  bool symmetric;
  bool has_pawns;
  bool loss_only;
  uint8_t pawns[2];
  struct {
    struct PairsData *precomp[2];
    size_t factor[2][TBPIECES];
    uint8_t pieces[2][TBPIECES];
    uint8_t norm[2][TBPIECES];
  } file[4];
};

struct TBEntry_pawn2 {
  uint8_t *data;
  Key key;
  map_t mapping;
  atomic_bool ready;
  uint8_t num;
  bool symmetric;
  bool has_pawns;
  bool loss_only;
  uint8_t pawns[2];
  struct {
    struct PairsData *precomp[2];
    size_t factor[2][TBPIECES];
    uint8_t pieces[2][TBPIECES];
    uint8_t norm[2][TBPIECES];
  } rank[6];
};

struct DTZEntry_piece {
  uint8_t *data;
  Key key;
  map_t mapping;
  atomic_bool ready;
  uint8_t num;
  bool symmetric;
  bool has_pawns;
  bool loss_only;
  bool kk_enc;
  struct PairsData *precomp;
  size_t factor[TBPIECES];
  uint8_t pieces[TBPIECES];
  uint8_t norm[TBPIECES];
  uint8_t flags; // accurate, mapped, side
  uint16_t map_idx[4];
  uint8_t *map;
};

struct DTZEntry_pawn {
  uint8_t *data;
  Key key;
  map_t mapping;
  atomic_bool ready;
  uint8_t num;
  bool symmetric;
  bool has_pawns;
  bool loss_only;
  uint8_t pawns[2];
  struct {
    struct PairsData *precomp;
    size_t factor[TBPIECES];
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
  map_t mapping;
  atomic_bool ready;
  uint8_t num;
  bool symmetric;
  bool has_pawns;
  bool loss_only;
  bool kk_enc;
  struct PairsData *precomp[2];
  size_t factor[2][TBPIECES];
  uint8_t pieces[2][TBPIECES];
  uint8_t norm[2][TBPIECES];
  uint16_t map_idx[2][2];
  uint16_t *map;
};

struct DTMEntry_pawn {
  uint8_t *data;
  Key key;
  map_t mapping;
  atomic_bool ready;
  uint8_t num;
  bool symmetric;
  bool has_pawns;
  bool loss_only;
  uint8_t pawns[2];
  struct {
    struct PairsData *precomp[2];
    size_t factor[2][TBPIECES];
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
