OUT=bin/wsh
CC=gcc
CFLAGS=-Wall -g
_OBJS = parser.o
_ROBJS = wsh.o
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))
ROBJS = $(patsubst %,$(OBJDIR)/%,$(_ROBJS))
SRCDIR = src
OBJDIR = objs

$(OUT): $(OBJS) $(ROBJS)
	@echo [Compile]: $@
	@$(CC) $(CFLAGS) $(OBJS) $(ROBJS) -o $(OUT) -lreadline

$(ROBJS): EXTRAFLAGS = -lreadline

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo [Compile]: $< \> $@ 
	@$(CC) $(CFLAGS) -c -o $@ $< $(EXTRAFLAGS)


.PHONY: clean
clean:
	@rm -f $(OBJDIR)/*.o $(OUT)
