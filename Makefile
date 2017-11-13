SRC = $(wildcard src/*.c)
OBJ = ${SRC:.c=.o}

CC = clang
PREFIX = /usr/local
CFLAGS = -std=c99 -g -O0 -Wno-parentheses -Wno-switch-enum -Wno-unused-value
CFLAGS += -Wno-switch
CFLAGS += -I deps
LDFLAGS += -lm

TEST_SRC = $(shell find src/*.c test/*.c | sed '/16bitc/d')
TEST_OBJ = ${TEST_SRC:.c=.o}

CFLAGS += -I src

OUT = 16bitc

$(OUT): $(OBJ)
	$(CC) $^ $(LDFLAGS) -o $@

%.o: %.c
	@$(CC) -c $(CFLAGS) $< -o $@
	@printf "\e[36mCC\e[90m %s\e[0m\n" $@

test: test_runner
	@./$<

test_runner: $(TEST_OBJ)
	$(CC) $^ $(LDFLAGS) -o $@

install: 16bitc
	install 16bitc $(PREFIX)/bin

uninstall:
	rm $(PREFIX)/bin/16bitc

clean:
	rm -f 16bitc test_runner $(OBJ) $(TEST_OBJ)

.PHONY: clean test install uninstall
