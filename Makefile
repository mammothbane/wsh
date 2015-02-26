OUT=bin/wsh
CC=gcc
CFLAGS=-Wall -g
_OBJS = parser.o wsh.o
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))
SRCDIR = src
OBJDIR = objs

$(OUT): $(OBJS)
	@echo [Compile]: $@
	@$(CC) $(CFLAGS) $(OBJS) -o $(OUT)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo [Compile]: $< \> $@
	@$(CC) $(CFLAGS) $(EXTRAFLAGS) -c -o $@ $<

.PHONY: clean
clean:
	@rm -f $(OBJDIR)/*.o $(OUT)
