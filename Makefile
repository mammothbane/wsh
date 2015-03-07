CC=gcc
CFLAGS=-Wall -g
OUT=bin/wsh
_OBJS = parser.o
_ROBJS = wsh.o
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))
ROBJS = $(patsubst %,$(OBJDIR)/%,$(_ROBJS))
SRCDIR = src
OBJDIR = objs
TESTDIR = test
TESTBIN = test/bin
TESTS = parsetest

$(OUT): $(OBJS) $(ROBJS)
	@echo [Compile]'\t'$@
	@$(CC) $(CFLAGS) $(OBJS) $(ROBJS) -o $(OUT) -lreadline

$(ROBJS): EXTRAFLAGS = -lreadline

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo [Compile]'\t'$< \> $@ 
	@$(CC) $(CFLAGS) -c -o $@ $< $(EXTRAFLAGS)
	@$(CC) -MM $(CFLAGS) $< > $(OBJDIR)/$*.d 

.PHONY: test
test:
	@cd $(TESTDIR); make $(MFLAGS)

.PHONY: clean
clean:
	@rm -f $(OBJDIR)/*.o $(OUT) $(OBJDIR)/*.d

-include $(OBJS:.o=.d) $(ROBJS:.o=.d)
