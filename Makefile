CC = gcc
CFLAGS = -Wall -g
SRC = src
OBJ = obj
OBJS = $(patsubst $(SRC)/%.c,$(OBJ)/%.o,$(wildcard $(SRC)/*.c))

.PHONY: test clean all

all: bin/wsh

bin/wsh: $(OBJS)
	@mkdir -p bin
	@echo [Compile]'\t'$@
	@$(CC) $(CFLAGS) $(OBJS) -o $@ -lreadline

$(OBJ)/%.o: $(SRC)/%.c $(wildcard $(SRC)/*.h)
	@mkdir -p $(OBJ)
	@echo [Compile]'\t'$< \> $@ 
	@$(CC) $(CFLAGS) -c -o $@ $<

test:
	@cd test; make $(MFLAGS)

clean:
	@rm -rf $(OBJ) bin/wsh
	@cd test; make $(MFLAGS) clean
