CC=gcc
CFLAGS=-Wall -g
_OBJS = parser.o
_ROBJS = wsh.o
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))
ROBJS = $(patsubst %,$(OBJDIR)/%,$(_ROBJS))
SRCDIR = ../src
OBJDIR = ../objs
TESTDIR = .
TESTBIN = bin
RTESTS = ptest
TESTS = 

test: $(TESTS) $(RTESTS)

.PHONY: parsetest
ptest: bin/parsetest
	@bin/parsetest
	@echo [Passed]'\t'parsetest

bin/parsetest: parsetest.c $(SRCDIR)/parser.c $(SRCDIR)/parser.h $(SRCDIR)/debug.h
	@echo [Compile]'\t'$< \> $@
	@$(CC) $(CFLAGS) -o $@ parsetest.c $(SRCDIR)/parser.c

.PHONY: clean
clean:
	@rm -f bin/*