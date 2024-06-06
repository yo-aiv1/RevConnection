CC = gcc
CCX64 = x86_64-w64-mingw32-gcc

INCLUDE_DIR = -Iinclude
CFLAGS = -Os -fno-asynchronous-unwind-tables -nostdlib -fno-ident -fpack-struct=8 -falign-functions=1 -s -ffunction-sections -falign-jumps=1 -w -falign-labels=1 -fPIC -masm=intel -fpermissive -mrdrnd -Wl,-s,--no-seh,--enable-stdcall-fixup

SRC = src/main.c src/loaders.c src/utils.c
OBJ = $(SRC:.c=.o)

TARGET = bin/main.exe


all: argscheck edit compile link clean

argscheck:
        @if [ -z "$(ip)" ]; then \
                echo "Error: 'ip' argument is required."; \
                exit 1; \
        fi
        @if [ -z "$(port)" ]; then \
                echo "Error: 'port' argument is required."; \
                exit 1; \
        fi


edit:
        @ echo "PARSING\c"
        @ $(CC) utils/tobytes.c -o utils/convert
        @ python3 utils/edit.py $(port) $(ip)
        @ echo "... DONE"
        @ echo "COMPILING\c"

compile: $(OBJ)
        @ nasm -f win64 src/peb.asm -o src/peb.o
%.o: %.c
        @ $(CCX64) $(CFLAGS) $(INCLUDE_DIR) -c $< -o $@

link:
        @ $(CCX64) $(OBJ) src/peb.o $(CFLAGS) -o $(TARGET)
        @ echo "... DONE"

clean:
        @ echo "CLEANING\c"
        @ rm -f utils/convert
        @ rm -f $(OBJ)
        @ rm -f src/peb.o
        @ python3 utils/edit.py back
        @ echo "... DONE\n"
        @ echo "THE EXECUTABLE IS LOCATED AT: $(TARGET)"
