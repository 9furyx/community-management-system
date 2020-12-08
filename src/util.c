#include <stdio.h>
#include <string.h>
#include "member.h"

// safely get an integer from stdin
int get_int() {
    static char buf[16];
    int input_id = 0;
    scanf("%s", buf);
    if (strlen(buf) > 9) // limit number length to avoid overflow
        return -1;
    for (int i = 0; i < strlen(buf); ++i) {
        if (buf[i] >= '0' && buf[i] <= '9') // make sure inputs are numbers
            input_id = input_id * 10 + buf[i] - '0';
        else
            return -1;
    }
    return input_id;
}