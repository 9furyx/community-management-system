#include <stdio.h>
#include "room.h"
#include "utils.h"
#include "defs.h"

struct Room room[MAX_ROOM_NUM];
int roomn;

int read_room(FILE *fp) {
    roomn = 0;
    int room_id, owner_mem_id, rent_mem_id;
    while (fscanf(fp, "%d%d%d", &room_id, &owner_mem_id, &rent_mem_id) != EOF) {
        if (roomn >= MAX_ROOM_NUM)
            return 0;
        room[++roomn].room_id = room_id;
        room[roomn].owner_mem_id = owner_mem_id;
        room[roomn].rent_mem_id = rent_mem_id;
    }
    return 0;
}

void list_empty_room() {
    printf("当前空置房屋:\n");
    for (int i = 1; i <= roomn; ++i) {
        if (!room[i].rent_mem_id)
            printf("roomid: %d\n", room[i].room_id);
    }
}
void list_ub_room() {
    printf("当前未购买的房屋:\n");
    for (int i = 1; i <= roomn; ++i) {
        if (!room[i].owner_mem_id)
            printf("roomid: %d\n", room[i].room_id);
    }
}

int buy_room(int input_mem_id) {
    clear_sh();
    print_curr_path();
    list_ub_room();
    if (!input_mem_id) {
        list_member();
        printf("\n请输入房屋id和会员id,按0结束输入:\n");
    } else {

        printf("\n请输入要购买的房屋id:\n");
    }
    int mem_id = -1;
    int room_id = -1;
    while (1) {
        room_id = get_int();
        if (!input_mem_id) {
            if (room_id == 0) break;
            mem_id = get_int();
            if (mem_id == 0) break;
            if (mem_id > get_member_num() || room_id > roomn || mem_id == -1 || room_id == -1 || room[room_id].owner_mem_id) {
                printf("请输入合法的房屋id和会员id.\n");
            } else {
                room[room_id].owner_mem_id = mem_id;
                printf("房屋:%d  会员%d\n", room_id, mem_id);
            }
        }
        else{
            if (room_id > roomn || room[room_id].owner_mem_id) {
                printf("请输入合法的房屋id\n");
            } else {
                room[room_id].owner_mem_id = input_mem_id;
                printf("输入任意键结束\n");
                getchar();
                getchar();
                break;
            }
        }
    }
}

int add_new_room() {
    clear_sh();
    printf("输入新建房屋的数目:\n");
    int num;
    num = get_int();
    if (roomn + num > MAX_ROOM_NUM) {
        printf("已达最大房屋上限\n");
    } else {
        for (int i = roomn + 1; i <= roomn + num; ++i) {
            room[i].room_id = i;
            room[i].owner_mem_id = 0;
            room[i].rent_mem_id = 0;
        }
        roomn += num;
    }
    printf("输入任意键返回\n");
    getchar();
    getchar();
}

static char *room_menu_subp[] = {
    "",
    "添加房屋",
    "购买房屋"};

void print_room_menu() {
    printf("**********\n");
    printf("班车预约\n");
    printf("**********\n");
    printf("1.%s\n", room_menu_subp[1]);
    printf("2.%s\n", room_menu_subp[2]);
    printf("0.返回\n");
}

void room_ui() {
    int choice = 0;
    do {
        clear_sh();
        print_curr_path();
        print_room_menu();
        printf("请选择:\n");
        choice = get_int();
        switch (choice) {
            case 1:
                cd_ch(room_menu_subp[1]);
                add_new_room();
                cd_fa();
                break;
            case 2:
                cd_ch(room_menu_subp[2]);
                buy_room(0);
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