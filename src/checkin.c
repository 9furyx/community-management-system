// Written by MXH

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#include "member.h"
#include "linked_list.h"

int check_in(int mem_id, int room_id) {
    member_ptr result = find_member(mem_id);
    if (result != NULL) {
        result->room_id = room_id;
        return 0;
    }
    return -1;
}

int rent(int c1) {
    clear_sh();
    print_curr_path();
    list_empty_room();
    printf("请选择:");
    int c4;
    scanf("%d", &c4);
    check_in(c1, c4);
    return 0;
}

static char* checkinui_subpath[] = {
    "",
    "选择入住",
    "申请娱乐设施",
};

static char* checkinui_buy_rent_subpath[] = {
    "",
    "购房",
    "租房",
};

int checkin_ui() {
    clear_sh();
    print_curr_path();
    list_member();
    printf("\n选择入住人id:");
    int c1;
    c1 = get_int();
    while (c1 > get_member_num()||c1==-1) {
        printf("invalid number.\n");
        printf(":");
        c1 = get_int();
    }
    printf("选择服务:\n1.选择入住\n2.申请娱乐设施\n");
    int c3;
    c3 = get_int();
    if (c3 == 1) {
        while (1) {
            cd_ch(checkinui_subpath[1]);
            clear_sh();
            printf("1.购房\n2.租房\n请选择:");
            int c2;
            c2 = get_int();
            if (c2 == 1) {
                cd_ch(checkinui_buy_rent_subpath[1]);
                buy_room(c1);  //购房
                cd_fa();
                break;
            }
            if (c2 == 2) {
                cd_ch(checkinui_buy_rent_subpath[2]);
                rent(c1);  //租房
                cd_fa();
                break;

            } else
                printf("选择错误");
        }
        cd_fa();
    }
    if (c3 == 2) {
        (c1);  //选择设施
    }
    return 0;
}