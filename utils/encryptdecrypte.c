#include <stdio.h>



void EncryptAndDecrypte(const char *str, char type, wchar_t *result) {
    char CurrentChar;
    int idx = 0;

    while (*str != '\0') {
        if (type == 'e') {
            CurrentChar = *str;

            if (CurrentChar >= 90 ) {
                CurrentChar += 4;
            } else {
                CurrentChar += 32;
            }
        } else {
            CurrentChar = *str;
            if (CurrentChar >= 90) {
                CurrentChar -= 4;
            } else {
                CurrentChar -= 32;
            }
        }

        result[idx] = (wchar_t)CurrentChar;
        *str++;
        idx++;
    }
    result[idx] = L'\0';

}
int main(int argc, char *argv[]) {
    wchar_t arg[100] = {0};

    if (*argv[1] == 'e') {
        EncryptAndDecrypte(argv[2], 'e', arg);
    } else {
        EncryptAndDecrypte(argv[2], 'd', arg);
    }

    printf("%S\n", arg);
}