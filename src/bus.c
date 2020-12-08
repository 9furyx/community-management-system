#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bus.h"
#include "member.h"
#include "defs.h"

struct Location loc[MAX_LOC_NUM];

int dis[MAX_LOC_NUM][MAX_LOC_NUM];
int locn = 0;

int read_location(FILE *fp) {
    locn = 0;
    char buf[MAX_LOC_NAME_LEN];
    double dirx, diry;
    while (fscanf(fp, "%s%lf%lf", buf, &dirx, &diry) != EOF) {
        if (locn >= MAX_LOC_NUM)
            return 0;
        memcpy(loc[++locn].name, buf, sizeof(buf));
        loc[locn].x = dirx, loc[locn].y = diry;
    }
    return 0;
}

void print_main_menu() {
    printf("*********************\n");
    printf("班车管理系统\n");
    printf("*********************\n");
    printf("1.班车预约\n");
    printf("2.路线规划\n");
    printf("0.退出\n");
}

void print_rsv_menu() {
    printf("**********\n");
    printf("班车预约\n");
    printf("**********\n");
    printf("1.会员预约\n");
    printf("2.取消预约\n");
    printf("0.返回\n");
}

// list all currunt locations
void list_location() {
    printf("*********************\n");
    printf("当前可选地点:\n");
    for (int i = 1; i <= locn; ++i)
        printf("%d: %s\n", i, loc[i].name);
}

void add_rsv_member() {
    clear_sh();
    list_member();
    puts("\n");
    list_location();
    puts("\n");
    printf("请输入预约会员编号和地点编号,按0结束输入:\n");
    int mem_id = -1;
    int loc_id = -1;
    while (1) {
        mem_id = get_int();
        if (mem_id == 0) break;
        loc_id = get_int();
        if (loc_id == 0) break;
        if (mem_id > get_member_num() || loc_id > locn || mem_id == -1 || loc_id == -1) {
            printf("请输入合法的会员编号和地点编号.\n");
        } else {
            printf("会员:%d  地点%d\n", mem_id, loc_id);
            //do somthing ...
        }
    }
}
void cancle_bus_rsv() {
    clear_sh();
    list_member();
    puts("\n");
    printf("请输入需要取消的会员编号,按0结束输入:\n");
    int mem_id = -1;
    while (1) {
        mem_id = get_int();
        if (mem_id == 0) break;
        if (mem_id > get_member_num() || mem_id == -1) {
            printf("请输入合法的会员编号.\n");
        } else {
            printf("会员:%d  的班车预约已取消\n", mem_id);
            //do somthing ...
        }
    }
}

void bus_route_man() {
}

void bus_rsv_man() {
    int choice = 0;
    do {
        clear_sh();
        print_rsv_menu();
        printf("请选择:\n");
        choice = get_int();
        switch (choice) {
            case 1:
                add_rsv_member();
                break;
            case 2:
                cancle_bus_rsv();
                break;
            case 0:
                break;
            default:
                printf("invalid number.\n");
                break;
        }
    } while (choice != 0);
}

void bus_ui() {
    int choice = 0;
    do {
        clear_sh();
        print_main_menu();
        printf("请选择:\n");
        choice = get_int();
        switch (choice) {
            case 1:
                bus_rsv_man();
                break;
            case 2:
                bus_route_man();
                break;
            case 0:
                break;
            default:
                printf("invalid number.\n");
                break;
        }
    } while (choice != 0);
}

int main() {
    FILE *fp = fopen("/home/yzh/Documents/Workspace/CMS/data/location.dat", "r");
    char buf[32];
    fscanf(fp, "%s", buf);
    read_location(fp);
    bus_ui();
}