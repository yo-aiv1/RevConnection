#include "../include/main.h"
#include "../include/utils.h"


unsigned long HashStrA(const unsigned short *str) {
    unsigned long   result  = 0;
    int             idx     = 0;
    char            CurrentChar;

    while (*str != 0) {
        idx++;

        CurrentChar = *str;

        if (CurrentChar >= 0x6C) {
            CurrentChar -= 0x19;
        }

        result = ((CurrentChar * K2) / K1) + (idx * result);
        *str++;

    }
    
    return (result >> 1);
}

unsigned long HashStrB(const char *str) {
    unsigned long   result  = 0;
    int             idx     = 0;
    char            CurrentChar;

    while (*str != 0) {
        idx++;

        CurrentChar = *str;

        if (CurrentChar >= 0x6C) {
            CurrentChar -= 0x19;
        }

        result = ((CurrentChar * K2) / K1) + (idx * result);
        *str++;

    }
    
    return (result >> 1);
}

void GetOriginalStr(const char *str, wchar_t *OriginalStr) {
    int     idx = 0;
    char    CurrentChar;

    while (*str != '\0') {
        CurrentChar = *str;
        if (CurrentChar >= 0x5a) {
            CurrentChar -= 0x4;
        } else {
            CurrentChar -= 0x20;
        }

        OriginalStr[idx] = (wchar_t)CurrentChar;
        *str++;
        idx++;
    }
    OriginalStr[idx] = L'\0';

    return OriginalStr;
}