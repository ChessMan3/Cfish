### ==========================================================================
### Copyright Notice and License Information
### ==========================================================================
#   McBrain, a UCI chess playing engine derived from Stockfish and Glaurung 2.1
#   Copyright (C) 2004-2008 Tord Romstad (Glaurung Author)
#   Copyright (C) 2008-2015 Marco Costalba, Joona Kiiski, Tord Romstad (Stockfish Authors)
#   Copyright (C) 2015-2016 Marco Costalba, Joona Kiiski, Gary Linscott, Tord Romstad (Stockfish Authors)
#   Copyright (C) 2017 Michael Byrne, Marco Costalba, Joona Kiiski, Gary Linscott, Tord Romstad (McBrain Authors)
#   Other significant contributitors through their Stockfish forks:
#   	Ronald De Man - SF/Cfish and Syzygy tablebase author
#		Ivan Ivec - SF/Corchess author
#       Thomas Zipproth - SF/Brainfish author (Book author)
#
#   McBrain is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.

#   McBrain is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see <http://www.gnu.org/licenses/>.
#   Aristides is McBrain in c, 10% faster for macOS - no support for Windows or Linux
### ==========================================================================
### Section 1. General Configuration
### ==========================================================================

mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
current_dir := $(notdir $(patsubst %/,%,$(dir $(mkfile_path))))
EXE= $(current_dir:.d=)
#EXE=Aristides v3.0
CC=clang
LDFLAGS=
STRIP=strip

default:
	$(MAKE) -j quick
help:
	@echo "type make"
	@echo ""

clang:
	@/opt/local/libexec/llvm-3.9/bin/llvm-profdata merge -output=engine.profdata *.profraw
	$(MAKE) -j target=UNIX \
	CC=clang \
	opt='-DUNIX -DUSE_POPCNT -DPEDANTIC -DNDEBUG -DIS_64BIT -DAPPLE -Wno-missing-field-initializers' \
	CFLAGS='-Wall -m64 -arch x86_64 -mmacosx-version-min=10.9 -pthread -std=c11 -mtune=native \
	-pedantic -Wextra -Wshadow -Os -Ot -Ofast -O2 -mdynamic-no-pic \
     -mssse3 -mpopcnt -fprofile-instr-use=engine.profdata' \
	LDFLAGS='$(LDFLAGS) -fprofile-instr-use=engine.profdata' \
	cfish-make

quick:
	$(MAKE) -j target=UNIX \
	CC=clang \
	opt='-DUNIX  -DUSE_POPCNT -DPEDANTIC  -DNDEBUG -DIS_64BIT -DAPPLE -Wno-missing-field-initializers' \
	CFLAGS='-Wall -m64 -arch x86_64 -mmacosx-version-min=10.9 -pthread -std=c11 -mtune=native \
	-pedantic -Wextra -Wshadow -Os -Ot -Ofast -O2 -mdynamic-no-pic \
	-mssse3 -mpopcnt ' \
	LDFLAGS='$(LDFLAGS) ' \
	cfish-make

clang-profile:
	$(MAKE) -j target=x86_64 \
	CC=clang \
	opt='-DUNIX -DUSE_POPCNT -DPEDANTIC  -DNDEBUG -DIS_64BIT -DAPPLE -Wno-missing-field-initializers' \
	CFLAGS='-Wall -m64 -arch x86_64 -mmacosx-version-min=10.9 -pthread -std=c11 -mtune=native \
	-pedantic -Wextra -Wshadow -Os -Ot -Ofast -O2 -mdynamic-no-pic \
	-msse3 -mpopcnt -fprofile-instr-generate ' \
	LDFLAGS='$(LDFLAGS)  -fprofile-instr-generate  ' \
	cfish-make

cpro:
	@rm -rf *.o
	@rm -rf log.*
	@rm -rf game.*
	@rm -rf prof
	@rm -rf *.profraw
	@rm -rf *.profdata
	@rm -rf $(EXE)
	@mkdir prof
	@touch *.c  *.h
	$(MAKE) -j clang-profile
	@echo "#!/bin/csh" > runprof
	@echo "./$(EXE) <<EOF" >>runprof
	@echo "bench 16 1 13" >>runprof
	@echo "quit" >>runprof
	@echo "EOF" >>runprof
	@chmod +x runprof
	@./runprof
	@rm runprof
	@touch *.c *.h
	$(MAKE) -j clang
	$(STRIP) $(EXE)
	cp $(EXE) /Users/michaelbyrne/cluster.mfb/$(EXE)

objects =  search.o bitboard.o evaluate.o movegen.o  bitbase.o movepick.o benchmark.o \
endgame.o  main.o material.o misc.o  pawns.o position.o psqt.o tbprobe.o thread.o \
timeman.o tt.o uci.o ucioption.o numa.o settings.o polybook.o

# Do not change anything below this line

opts = $(opt) -D$(target)

#	@$(MAKE) -j opt='$(opt)'  CFLAGS='$(CFLAGS)' $(EXE)
cfish-make:
	@$(MAKE) opt='$(opt)'  CFLAGS='$(CFLAGS)' $(EXE)

cfish.o: *.c *.h

$(EXE):	$(objects)
	$(CC) $(LDFLAGS) -o $(EXE) $(objects) -lm  $(LIBS)

clean:
	-rm -f *.o $(EXE)

$(objects):

.c.o:
	$(CC) $(CFLAGS) $(opts) -c $*.c

