#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "staff.h"
#include "linked_list.h"
#include "defs.h"
#include "member.h"

lnode_ptr staff_head = NULL;
int staffn = 0;

static int cmp(const void *id, const void *node) {
    return *(int *)id == ((staff_ptr)node)->id;
}

int add_staff(int id, int target_id, char *name) {
    staff_ptr t = (staff_ptr)malloc(sizeof(staff_t));
    t->id = id;
    t->target_id = target_id;
    strcpy(t->name, name);
    return l_add(&staff_head, t);
}

int del_staff(int id) { return l_delete(&staff_head, &id, cmp); }

staff_ptr find_staff(int id) {
    return (staff_ptr)(l_find(&staff_head, &id, cmp)->t_ptr);
}

int read_staff(FILE *fp) {
    staffn = 0;
    char buf[MAX_STAFF_NUM];
    int staff_id = 0;
    int target_id = 0;
    while (fscanf(fp, "%d%d ", &staff_id, &target_id) != EOF &&
           my_getline(fp, buf) != -1) {
        if (++staffn > MAX_STAFF_NUM) return 0;
        add_staff(staff_id, target_id, buf);
    }
}

int write_staff(FILE *fp) {
    char buf[MAX_STAFF_NUM];
    int staff_id = 0;
    lnode_ptr curr = staff_head;
    fprintf(fp, "staff-id target_id staff_name\n");
    while (curr != NULL) {
        staff_ptr entry = (staff_ptr)(curr->t_ptr);
        if (entry != NULL)
            fprintf(fp, "%d %d %s\n", entry->id, entry->target_id, entry->name);
        curr = curr->next;
    }
    return 0;
}

void list_staff() {
    printf("*********************\n");
    printf("当前所有员工:\n");
    lnode_ptr curr = staff_head;
    while (curr != NULL) {
        staff_ptr entry = (staff_ptr)(curr->t_ptr);
        member_ptr mem = find_member(entry->target_id);
        char *mem_name = NULL;
        if (mem != NULL) mem_name = mem->name;
        printf("id:%d    %-10s    服务对象: %d  %s\n", entry->id, entry->name,
               entry->target_id, mem_name);

        curr = curr->next;
    }
}

void add_staff_ui() {
    clear_sh();
    print_curr_path();
    getchar();
    while (1) {
        char buf[MAX_STAFF_NAME_LEN];
        printf("请输入员工名称, 输入#结束:\n");
        my_getline(stdin, buf);
        if (buf[0] == '#') break;
        if (++staffn > MAX_STAFF_NUM) {
            printf("已达最大员工数量, 按任意键返回\n");
            getchar();
            break;
        }
        add_staff(staffn, 0, buf);
        printf("已加入员工: %s\n", buf);
    }
}

void del_staff_ui() {
    clear_sh();
    print_curr_path();
    int staff_id = 0;
    list_staff();
    printf("\n请输入要删除的员工编号, 输入0结束:\n");
    while (1) {
        staff_id = get_int();
        if (staff_id == 0) break;
        if (del_staff(staff_id) == -1) {
            printf("该员工不存在\n");
        } else {
            printf("已删除员工: %d\n", staff_id);
            staffn--;
        }
    }
}

void manage_staff_ui() {
    clear_sh();
    print_curr_path();
    list_member();
    list_staff();

    int staff_id, mem_id;
    printf("请输入员工和服务会员编号, 输入0结束:\n");
    staff_id = get_int();
    if (staff_id == 0) return;
    mem_id = get_int();
    if (mem_id == 0) return;
    while (staff_id == -1 || mem_id == -1) {
        printf("请输入合法的id:\n");
        staff_id = get_int();
        if (staff_id == 0) return;
        mem_id = get_int();
        if (mem_id == 0) return;
    }
    staff_ptr stf = find_staff(staff_id);
    if (stf->target_id == mem_id) {
        printf("当前员工已经服务该会员\n");
        goto wait;
    }
    if (stf->target_id != 0) {
        printf("当前员工已经服务了: %d号会员, 是否继续 1/0\n", stf->target_id);
        int choice = get_int();
        if (choice == 1) {
            stf->target_id = mem_id;
            printf("员工: %d,  会员: %d\n", staff_id, mem_id);
        }
    } else {
        stf->target_id = mem_id;
        printf("员工: %d,  会员: %d\n", staff_id, mem_id);
    }

wait:;
    printf("输入任意键返回\n");
    getchar();
    getchar();
}

void staff_list() {
    clear_sh();
    print_curr_path();
    list_staff();
    printf("\n输入任意键返回\n");
    getchar();
    getchar();
}

static char *staff_subp[] = {"", "查看员工列表", "添加员工", "删除员工",
                             "管理员工"};
void print_staff_menu() {
    printf("*********************\n");
    printf("员工管理系统\n");
    printf("*********************\n");
    printf("1.%s\n", staff_subp[1]);
    printf("2.%s\n", staff_subp[2]);
    printf("3.%s\n", staff_subp[3]);
    printf("4.%s\n", staff_subp[4]);
    printf("0.返回\n");
}

void staff_ui() {
    int choice = 0;
    do {
        clear_sh();
        print_curr_path();
        print_staff_menu();
        printf("请选择:\n");
        choice = get_int();
        switch (choice) {
            case 1:
                cd_ch(staff_subp[1]);
                staff_list();
                break;
            case 2:
                cd_ch(staff_subp[2]);
                add_staff_ui();
                break;
            case 3:
                cd_ch(staff_subp[3]);
                del_staff_ui();
                break;
            case 4:
                cd_ch(staff_subp[4]);
                manage_staff_ui();
                break;
            case 0:
                break;
            default:
                printf("invalid number.\n");
                break;
        }
        cd_fa();
    } while (choice != 0);
}