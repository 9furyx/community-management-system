// utilities that being used frequently

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "member.h"

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
// safely get an integer from stdin
int get_int() {
    static char buf[16];
    int input_id = 0;
    scanf("%s", buf);
    if (strlen(buf) > 9)  // limit number length to avoid overflow
        return -1;
    for (int i = 0; i < strlen(buf); ++i) {
        if (buf[i] >= '0' && buf[i] <= '9')  // make sure inputs are numbers
            input_id = input_id * 10 + buf[i] - '0';
        else
            return -1;
    }
    return input_id;
}

int my_getline(FILE *stream, char *string) {
    int p = 0;
    char c = fgetc(stream);
    while (c != '\n' && c != EOF) {
        string[p++] = c;
        c = fgetc(stream);
    }
    if (c == EOF) return -1;
    string[p] = '\0';
    return 0;
}

// clear shell content
void clear_sh() {
    system("clear || cls");  // compatible with both POSIX and WIN32 api
}