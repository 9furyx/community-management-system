#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "linked_list.h"
#include "defs.h"
#include "member.h"
#include "path.h"

lnode_ptr mem_head = NULL;
int memn = 0;

// specific funcion used in linked list template
static int cmp(const void *id, const void *node) {
    return *(int *)id == ((member_ptr)node)->id;
}
static void free_data(const void *mem) {
    free(((member_ptr)mem));
}

// main utils

int add_member(int id, int room_id, char *name) {
    member_ptr t = (member_ptr)malloc(sizeof(member_t));
    t->id = id;
    t->room_id = room_id;
    strcpy(t->name, name);
    return l_add(&mem_head, t);
}

int del_member(int id) {
    return l_delete(&mem_head, &id, cmp, free_data);
}

member_ptr find_member(int id) {
    return (member_ptr)(l_find(&mem_head, &id, cmp)->t_ptr);
}

int read_member(FILE *fp) {
    memn = 0;
    char buf[MAX_MEMBER_NAME_LEN];
    int room_id = 0;
    int mem_id = 0;
    while (fscanf(fp, "%d%s%d", &mem_id, buf, &room_id) != EOF) {
        if (++memn > MAX_MAMBER_NUM)
            return 0;
        add_member(mem_id, room_id, buf);
    }
}

int get_member_num() {
    return memn;
}
void list_member() {
    printf("*********************\n");
    printf("当前所有会员:\n");
    lnode_ptr curr = mem_head;
    while (curr != NULL) {
        member_ptr entry = (member_ptr)(curr->t_ptr);
        printf("id:%d %s\n", entry->id, entry->name);
        curr = curr->next;
    }
}

// User Interface
static char *mem_subp[] = {"", "查看会员列表", "添加会员", "删除会员"};
void print_mem_menu() {
    printf("*********************\n");
    printf("会员管理系统\n");
    printf("*********************\n");
    printf("1.%s\n", mem_subp[1]);
    printf("2.%s\n", mem_subp[2]);
    printf("3.%s\n", mem_subp[3]);
    printf("0.返回\n");
}

void add_member_ui() {
    clear_sh();
    print_curr_path();
    char buf[MAX_MEMBER_NAME_LEN];
    printf("请输入会员名, 输入#结束:\n");
    while (1) {
        scanf("%s", buf);
        if (buf[0] == '#')
            break;
        if (++memn > MAX_MAMBER_NUM) {
            printf("已达最大会员数量, 按任意键返回\n");
            getchar();
            break;
        }
        add_member(memn, 0, buf);
        printf("已加入会员: %s\n", buf);
    }
}

void del_member_ui() {
    clear_sh();
    print_curr_path();
    int mem_id = 0;
    list_member();
    printf("\n请输入要删除的会员编号, 输入0结束:\n");
    while (1) {
        mem_id = get_int();
        if (mem_id == 0)
            break;
        if (del_member(mem_id) == -1) {
            printf("该会员不存在\n");
        } else
            printf("已删除会员: %d\n", mem_id);
    }
}

void member_list() {
    clear_sh();
    print_curr_path();
    list_member();
    printf("\n输入任意键返回\n");
    getchar();
    getchar();
}

void mem_ui() {
    int choice = 0;
    do {
        clear_sh();
        print_curr_path();
        print_mem_menu();
        printf("请选择:\n");
        choice = get_int();
        switch (choice) {
            case 1:
                cd_ch(mem_subp[1]);
                member_list();
                cd_fa();
                break;
            case 2:
                cd_ch(mem_subp[2]);
                add_member_ui();
                cd_fa();
                break;
            case 3:
                cd_ch(mem_subp[3]);
                del_member_ui();
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