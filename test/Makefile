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
TESTS = jtest

test: $(TESTS) $(RTESTS)

ptest: bin/parsetest
	@bin/parsetest
	@echo [Passed]'\t'parsetest

jtest: bin/jobtest
	@bin/jobtest
	@echo [Passed]'\t'jobtest

.PHONY: parsetest
parsetest: bin/parsetest

bin/parsetest: parsetest.c $(SRCDIR)/parser.c $(SRCDIR)/parser.h $(SRCDIR)/debug.h
	@echo [Compile]'\t'$< \> $@
	@$(CC) $(CFLAGS) -o $@ parsetest.c $(SRCDIR)/parser.c

.PHONY: jobtest
jobtest: bin/jobtest

bin/jobtest: jobtest.c $(SRCDIR)/job.c $(SRCDIR)/job.h
	@echo [Compile]'\t'$< \> $@
	@$(CC) $(CFLAGS) -o $@ jobtest.c $(SRCDIR)/job.c


.PHONY: clean
clean:
	@rm -f bin/*