#include <stdio.h>

#define K1 21
#define K2 5421


unsigned long hashstr(char *str) {
    unsigned long result = 0;
    char CurrentChar;
    int idx = 0;

    while (1) {
        idx++;
        if (*str == '\0') {
            break;
        }
        CurrentChar = *str;
        if (CurrentChar >= 0x6C) {
            CurrentChar -= 0x19;
        }
        result = ((CurrentChar * K2) / K1) + (idx * result);
        *str++;
    }
    
    return (result >> 1);
}


int main(int argc, char *argv[]) {
    unsigned long hash = hashstr(argv[1]);
    printf("0x%lx\n", hash);
}