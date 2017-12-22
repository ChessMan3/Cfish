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

#include "numa.h"
#include "search.h"
#include "settings.h"
#include "thread.h"
#include "tt.h"
#include "types.h"

struct settings settings, delayed_settings;

// Process Hash, Threads, NUMA and LargePages settings.

void process_delayed_settings(void)
{
  int tt_change = delayed_settings.tt_size != settings.tt_size;
  int lp_change = delayed_settings.large_pages != settings.large_pages;
  int numa_change =   (settings.numa_enabled != delayed_settings.numa_enabled)
                   || (   settings.numa_enabled
                       && !masks_equal(settings.mask, delayed_settings.mask));
  int ls_change = delayed_settings.limit_strength_enabled != settings.limit_strength_enabled;
  int elo_change = delayed_settings.elo_level != settings.elo_level;

#ifdef NUMA
  if (numa_change) {
    threads_set_number(0);
    settings.num_threads = 0;
#ifndef __WIN32__
    if ((settings.numa_enabled = delayed_settings.numa_enabled))
      copy_bitmask_to_bitmask(delayed_settings.mask, settings.mask);
#endif
    settings.numa_enabled = delayed_settings.numa_enabled;
  }
#endif

  if (settings.num_threads != delayed_settings.num_threads) {
    settings.num_threads = delayed_settings.num_threads;
    threads_set_number(settings.num_threads);
  }

  if (numa_change || tt_change || lp_change || ls_change || elo_change ) {
    tt_free();
    settings.large_pages = delayed_settings.large_pages;
    settings.tt_size = delayed_settings.tt_size;
    tt_allocate(settings.tt_size);
	settings.limit_strength_enabled = delayed_settings.limit_strength_enabled;
	settings.elo_level = delayed_settings.elo_level;
  }

  if (delayed_settings.clear) {
    delayed_settings.clear = 0;
    search_clear();
  }
}

