OUT=bin/wsh
CC=gcc
CFLAGS=-Wall -g
_OBJS = parser.o
_ROBJS = wsh.o
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))
ROBJS = $(patsubst %,$(OBJDIR)/%,$(_ROBJS))
SRCDIR = src
OBJDIR = objs
TESTDIR = test
TESTBIN = test/bin
TESTS = parsetest

-include $(OBJS:.o=.d) $(ROBJS:.o=.d)

$(OUT): $(OBJS) $(ROBJS)
	@echo [Compile]: $@
	@$(CC) $(CFLAGS) $(OBJS) $(ROBJS) -o $(OUT) -lreadline

$(ROBJS): EXTRAFLAGS = -lreadline

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo [Compile]: $< \> $@ 
	@$(CC) $(CFLAGS) -c -o $@ $< $(EXTRAFLAGS)
	@$(CC) -MM $(CFLAGS) $< > $(OBJDIR)/$*.d 

test: $(TESTS)

.PHONY: parsetest
parsetest: test/parsetest.c src/parser.c src/parser.h
	@echo [Compile]: $< \> $@
	@$(CC) $(CFLAGS) -o $@ @<
	@test/bin/parsetest
	@echo [Passed] parsetest

.PHONY: clean
clean:
	@rm -f $(OBJDIR)/*.o $(OUT) $(OBJDIR)/*.d
