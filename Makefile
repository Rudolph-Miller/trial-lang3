CC = gcc
CFLAGS= -Wall -I ./include
BUILD_DIR=build
_OBJS=lex.o
OBJS=$(addprefix $(BUILD_DIR)/,$(_OBJS))

trial-lang3: $(BUILD_DIR)/main.o $(OBJS)
	$(CC) $(CFLAGS) -o bin/trial-lang3 $(BUILD_DIR)/main.o $(OBJS)

$(BUILD_DIR)/%.o: src/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(BUILD_DIR)/* bin/*
