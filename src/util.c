// utilities that being used frequently

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "member.h"

// swap two integer
void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// safely get an integer from stdin
int get_int() {
    const long long MAXI = 0x7fffffff;
    static char buf[16];
    long long input_id = 0;
    scanf("%s", buf);
    for (int i = 0; i < (int)strlen(buf); ++i) {
        if (buf[i] >= '0' && buf[i] <= '9')  // make sure inputs are valid
            input_id = input_id * 10 + buf[i] - '0';
        else
            return -1;
    }
    if (input_id > MAXI) return -1;
    return (int)input_id;
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