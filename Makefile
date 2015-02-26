OUT=bin/wsh
CC=gcc
CFLAGS=-Wall -g
_OBJS = parser.o
_ROBJS = wsh.o
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))
ROBJS = $(patsubst %,$(OBJDIR)/%,$(_ROBJS))
SRCDIR = src
OBJDIR = objs

$(OUT): $(OBJS)
	$(CC) $(CFLAGS) 

$(ROBJS):
	EXTRAFLAGS += -lreadline

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(EXTRAFLAGS) -c -o $@ $<


.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o $(OUT)