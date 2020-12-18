#include <stdio.h>
#include "room.h"
#include "defs.h"
#include "member.h"

room_t room[MAX_ROOM_NUM];
int roomn;

int read_room(FILE *fp) {
    roomn = 0;
    int room_id, owner_mem_id, rent_mem_id, price;
    while (fscanf(fp, "%d%d%d%d", &room_id, &owner_mem_id, &rent_mem_id,
                  &price) != EOF) {
        if (roomn >= MAX_ROOM_NUM) return 0;
        room[++roomn].room_id = room_id;
        room[roomn].owner_mem_id = owner_mem_id;
        room[roomn].rent_mem_id = rent_mem_id;
        room[roomn].price = price;
    }
    return 0;
}

int write_room(FILE *fp) {
    fprintf(fp, "room-id owner-id renter-id price\n");
    for (int i = 1; i <= roomn; ++i) {
        fprintf(fp, "%d %d %d %d\n", room[i].room_id, room[i].owner_mem_id,
                room[i].rent_mem_id, room[i].price);
    }
    return 0;
}

void list_empty_room() {
    printf("当前空置房屋:\n");
    for (int i = 1; i <= roomn; ++i) {
        if (!room[i].rent_mem_id) printf("roomid: %d\n", room[i].room_id);
    }
}
void list_ub_room(int l, int r) {
    printf("当前未购买的房屋:\n");
    for (int i = l; i <= r; ++i) {
        if (!room[i].owner_mem_id)
            printf("roomid: %d    price: $%d\n", room[i].room_id,
                   room[i].price);
    }
}
void list_room_owner() {
    clear_sh();
    print_curr_path();
    for (int i = 1; i <= roomn; ++i) {
        if (room[i].owner_mem_id != 0)
            printf("room_id: %d owner: %s\n", room[i].room_id,
                   find_member(room[i].owner_mem_id)->name);
        else
            printf("room_id: %d owner: \n", room[i].room_id);
    }
    printf("输入任意键结束\n");
    getchar();
    getchar();
}

// find room price lager or equal
int find_room_le(int val) {
    int l = 1, r = roomn;
    while (l < r) {
        int mid = (l + r) >> 1;
        if (room[mid].price >= val) {
            r = mid;
        } else
            l = mid + 1;
    }
    return l;
}
// find room price smaller or equal
int find_room_se(int val) {
    int l = 1, r = roomn;
    while (l < r) {
        int mid = (l + r + 1) >> 1;
        if (room[mid].price <= val) {
            l = mid;
        } else
            r = mid - 1;
    }
    return l;
}
int filter_room() {
    clear_sh();
    print_curr_path();
    printf("%d", 3 > 1);
    int lo, hi;
    printf("请输入房屋价格区间:\n");
    lo = get_int();
    hi = get_int();
    while (lo < 0 || hi < 0 || lo > hi) {
        printf("请输入合法的区间:\n");
        lo = get_int();
        hi = get_int();
    }
    int l = find_room_le(lo);
    int r = find_room_se(hi);
    list_ub_room(l, r);
    return 0;
}

int buy_room(int input_mem_id) {
    clear_sh();
    print_curr_path();
    filter_room();
    // list_ub_room(l, r);
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
            if (mem_id > get_member_num() || room_id > roomn || mem_id == -1 ||
                room_id == -1 || room[room_id].owner_mem_id) {
                printf("请输入合法的房屋id和会员id.\n");
            } else {
                room[room_id].owner_mem_id = mem_id;
                printf("房屋:%d  会员%d\n", room_id, mem_id);
            }
        } else {
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
    return 0;
}

int room_price_cmp(const void *a, const void *b) {
    return ((room_ptr)a)->price - ((room_ptr)b)->price;
}
int add_new_room() {
    clear_sh();
    print_curr_path();
    printf("输入新建房屋的数目:\n");
    int num;
    num = get_int();
    while (num == -1 || roomn + num > MAX_ROOM_NUM) {
        printf("输入错误或已达最大房屋上限,请重新输入");
        num = get_int();
    }
    printf("输入每间房屋的价格:\n");

    for (int i = roomn + 1; i <= roomn + num; ++i) {
        int price = get_int();
        while (price == -1) {
            printf("请输入正确的数字:\n");
            price = get_int();
        }
        room[i].room_id = i;
        room[i].price = price;
        room[i].owner_mem_id = 0;
        room[i].rent_mem_id = 0;
    }
    roomn += num;
    quick_sort(room, roomn + 1, sizeof(room_t), room_price_cmp);
    printf("输入任意键返回\n");
    getchar();
    getchar();
    return 0;
}

static char *room_menu_subp[] = {"", "添加房屋", "购买房屋", "查看房屋所有者"};

void print_room_menu() {
    printf("**********\n");
    printf("班车预约\n");
    printf("**********\n");
    printf("1.%s\n", room_menu_subp[1]);
    printf("2.%s\n", room_menu_subp[2]);
    printf("3.%s\n", room_menu_subp[3]);
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
                break;
            case 2:
                cd_ch(room_menu_subp[2]);
                buy_room(0);
                break;
            case 3:
                cd_ch(room_menu_subp[3]);
                list_room_owner();
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