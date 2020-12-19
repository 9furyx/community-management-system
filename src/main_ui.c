// main user interface of the program

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"
#include "path.h"

static char* mainui_subpath[] = {"",         "会员管理", "班车管理",
                                 "房屋管理", "入住管理", "员工管理"};
void print_main_menu() {
    printf("*********************\n");
    printf("长者社区管理系统\n");
    printf("*********************\n");
    printf("1.%s\n", mainui_subpath[1]);
    printf("2.%s\n", mainui_subpath[2]);
    printf("3.%s\n", mainui_subpath[3]);
    printf("4.%s\n", mainui_subpath[4]);
    printf("5.%s\n", mainui_subpath[5]);
    printf("0.退出并保存\n");
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
                break;
            case 2:
                cd_ch(mainui_subpath[2]);
                bus_ui();
                break;
            case 3:
                cd_ch(mainui_subpath[3]);
                room_ui();
                break;
            case 4:
                cd_ch(mainui_subpath[4]);
                checkin_ui();
                break;
            case 5:
                cd_ch(mainui_subpath[5]);
                staff_ui();
                break;
            case 0:
                clear_sh();
                break;
            default:
                printf("invalid number.\n");
                break;
        }
        cd_fa();
    } while (choice != 0);
}