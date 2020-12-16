#include <stdio.h>
#include <string.h>
#include "path.h"

char *curr_path[MAX_DEPTH] = {"主界面"};
int path_dep = 1;

// print current location that user reached
void print_curr_path() {
    printf("当前位置:\n");
    for (int i = 0; i < path_dep; ++i) {
        if (i > 0)
            for (int j = 0; j < i; ++j) printf("    ");
        printf("┣━━ ");
        //for (int j = 0; j < i; ++j) printf("-");
        printf("%s\n", curr_path[i]);
    }
    printf("\n");
}

// add current names to path
void cd_ch(char *str) {
    curr_path[path_dep++] = str;
    return;
}

// go back
void cd_fa() {
    --path_dep;
}