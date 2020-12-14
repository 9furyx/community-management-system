#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"
#include "bus.h"
#include "member.h"
#include "path.h"
#include "linked_list.h"

lnode_ptr bus_head = NULL;
struct Location loc[MAX_LOC_NUM];
int locn = 0;
int dis[MAX_LOC_NUM][MAX_LOC_NUM];

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

int write_location(FILE *fp) {
    fprintf(fp, "location-name location-dirx location-diry\n");
    for (int i = 1; i <= locn; ++i)
        fprintf(fp, "%s %lf %lf\n", loc[i].name, loc[i].x, loc[i].y);
    return 0;
}

int read_bus(FILE *fp) {
    int mem_id, loc_id;
    while (fscanf(fp, "%d%d", &mem_id, &loc_id) != EOF)
        add_bus_mem_to_link(mem_id, loc_id);
    return 0;
}

int write_bus(FILE *fp) {
    lnode_ptr curr = bus_head;
    fprintf(fp, "member-id location_id\n");
    while (curr != NULL) {
        int loc_id = ((bus_ptr)(curr->t_ptr))->loc_id;
        int mem_id = ((bus_ptr)(curr->t_ptr))->mem_id;
        fprintf(fp, "%d %d\n", mem_id, loc_id);
        curr = curr->next;
    }
    return 0;
}

static char *bus_menu_subp[] = {"", "班车预约", "路线规划", "增加地点"};
void print_bus_menu() {
    printf("*********************\n");
    printf("班车管理系统\n");
    printf("*********************\n");
    printf("1.%s\n", bus_menu_subp[1]);
    printf("2.%s\n", bus_menu_subp[2]);
    printf("3.%s\n", bus_menu_subp[3]);
    printf("0.返回\n");
}

static char *bus_rsv_subp[] = {"", "会员预约", "取消预约"};
void print_bus_rsv_menu() {
    printf("**********\n");
    printf("班车预约\n");
    printf("**********\n");
    printf("1.%s\n", bus_rsv_subp[1]);
    printf("2.%s\n", bus_rsv_subp[2]);
    printf("0.返回\n");
}

// list all currunt locations
void list_location() {
    printf("*********************\n");
    printf("当前可选地点:\n");
    for (int i = 1; i <= locn; ++i)
        printf("%d: %s\n", i, loc[i].name);
}

// specific funcion used in linked list template
static int cmp(const void *id, const void *node) {
    return *(int *)id == ((bus_ptr)node)->mem_id;
}
static void free_data(const void *bus) {
    free(((bus_ptr)bus));
}

// main utils

int add_bus_mem_to_link(int mem_id, int loc_id) {
    bus_ptr t = (bus_ptr)malloc(sizeof(bus_t));
    t->mem_id = mem_id;
    t->loc_id = loc_id;
    loc[loc_id].num++;
    return l_add(&bus_head, t);
}

int del_bus_mem_from_link(int id) {
    return l_delete(&bus_head, &id, cmp, free_data);
}

bus_ptr find_bus_member(int id) {
    lnode_ptr result = l_find(&bus_head, &id, cmp);
    if (result == NULL)
        return NULL;
    return result->t_ptr;
}

void list_bus_rsv_member() {
    printf("*********************\n");
    printf("当前所有会员及选择的目的地:\n");
    lnode_ptr curr = mem_head;
    while (curr != NULL) {
        if (curr->t_ptr != NULL) {
            member_ptr entry = (member_ptr)(curr->t_ptr);
            bus_ptr f_mem = find_bus_member(entry->id);
            if (f_mem != NULL)
                printf("id:%d %s loc_id: %d\n", entry->id, entry->name, f_mem->loc_id);
        }
        curr = curr->next;
    }
}
void add_bus_rsv_member() {
    clear_sh();
    print_curr_path();
    list_bus_rsv_member();
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
            add_bus_mem_to_link(mem_id, loc_id);
            printf("会员:%d  地点%d\n", mem_id, loc_id);
        }
    }
}
void cancle_bus_rsv() {
    clear_sh();
    print_curr_path();
    list_bus_rsv_member();
    puts("\n");
    printf("请输入需要取消的会员编号,按0结束输入:\n");
    int mem_id = -1;
    while (1) {
        mem_id = get_int();
        if (mem_id == 0) break;
        if (mem_id > get_member_num() || mem_id == -1) {
            printf("请输入合法的会员编号.\n");
        } else {
            del_bus_mem_from_link(mem_id);
            add_bus_mem_to_link(mem_id, 0);
            printf("会员:%d  的班车预约已取消\n", mem_id);
        }
    }
}

int add_location() {
    clear_sh();
    print_curr_path();
    char buf[MAX_LOC_NAME_LEN];
    double dirx, diry;
    if (locn >= MAX_LOC_NUM) {
        printf("已达最大上限\n");
        return -1;
    }
    printf("请输入新增地点名称, 座标x, 座标y:\n");
    scanf("%s%lf%lf", buf, &dirx, &diry);
    memcpy(loc[++locn].name, buf, sizeof(buf));
    loc[locn].x = dirx, loc[locn].y = diry;
    printf("已增加地点: %s\n", loc[locn].name);
    printf("输入任意键返回\n");
    getchar();
    getchar();
    return 0;
}

void bus_route_man() {
    clear_sh();
    print_curr_path();
    printf("当前规划路线:\n");
    for (int i = 1; i <= locn; ++i) {
        if (loc[i].num > 0) {
            printf("%s", loc[i].name);
            if (i != locn) printf(" -> ");
        }
    }
    printf("\n\n按任意键返回\n");
    getchar();
    getchar();
}

void bus_rsv_man() {
    int choice = 0;
    do {
        clear_sh();
        print_curr_path();
        print_bus_rsv_menu();
        printf("请选择:\n");
        choice = get_int();
        switch (choice) {
            case 1:
                cd_ch(bus_rsv_subp[1]);
                add_bus_rsv_member();
                cd_fa();
                break;

            case 2:
                cd_ch(bus_rsv_subp[2]);
                cancle_bus_rsv();
                cd_fa();
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
        print_curr_path();
        print_bus_menu();
        printf("请选择:\n");
        choice = get_int();
        switch (choice) {
            case 1:
                cd_ch(bus_menu_subp[1]);
                bus_rsv_man();
                cd_fa();
                break;
            case 2:
                cd_ch(bus_menu_subp[2]);
                bus_route_man();
                cd_fa();
                break;
            case 3:
                cd_ch(bus_menu_subp[3]);
                add_location();
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
