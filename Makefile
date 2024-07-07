CC = cc
CFLAGS = -Wall -Wextra -pedantic -std=c99 -Iinclude
SRC = source
INCLUDE_DIR = include
BUILD_DIR = build
TARGET = $(BUILD_DIR)/jedit

all:$(TARGET)

$(TARGET): main.o prep_terminal.o $(BUILD_DIR)
	$(CC) $(BUILD_DIR)/main.o $(BUILD_DIR)/prep_terminal.o -o $(TARGET) $(CFLAGS)

main.o: $(SRC)/main.c $(INCLUDE_DIR)/prep_terminal.h $(SRC)/prep_terminal.c
	$(CC) -c $(SRC)/main.c -o $(BUILD_DIR)/main.o $(CFLAGS)

prep_terminal.o: $(SRC)/prep_terminal.c $(INCLUDE_DIR)/prep_terminal.h
	$(CC) -c $(SRC)/prep_terminal.c -o $(BUILD_DIR)/prep_terminal.o $(CFLAGS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -f $(BUILD_DIR)/*.o

# #What we want to build -> jedit
# main.c is what is required to build it
# $(CC) is a variable make extends to cc by default
# -Wall stands for All Warnings
# -Wextra and -pedantic makes the compiler even more sensible to warnings
# -std=99 defines the exact C version
# C99 allows us to declare variables anywhere within a function, ANSI C requires the
# all variables to be declared at the top of the function or block.