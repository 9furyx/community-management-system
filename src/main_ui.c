#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"
#include "path.h"

static char* mainui_subpath[] = {"", "会员管理", "班车管理"};
void print_main_menu() {
    printf("*********************\n");
    printf("长者社区管理系统\n");
    printf("*********************\n");
    printf("1.%s\n", mainui_subpath[1]);
    printf("2.%s\n", mainui_subpath[2]);
    printf("0.退出\n");
}

void main_ui() {
    int choice = 0;
    do {
        clear_sh();
        print_curr_path();
        print_main_menu();
        printf("请选择:\n");
        choice = get_int();
        switch (choice) {
            case 1:
                cd_ch(mainui_subpath[1]);
                mem_ui();
                cd_fa();
                break;
            case 2:
                cd_ch(mainui_subpath[2]);
                bus_ui();
                cd_fa();
                break;
            case 0:
                clear_sh();
                break;
            default:
                printf("invalid number.\n");
                break;
        }
    } while (choice != 0);
}