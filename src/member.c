#include <stdio.h>
#include "utils.h"
#include "defs.h"
int memn = 12;

int get_member_num() {
    return memn;
}

// list all currunt members
void list_member() {
    printf("*********************\n");
    printf("当前所有会员:\n");
    printf("1.John\n");
    printf("2.Tom\n");

}