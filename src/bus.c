#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "defs.h"
#include "bus.h"
#include "member.h"
#include "path.h"
#include "linked_list.h"

lnode_ptr bus_head = NULL;
struct Location loc[MAX_LOC_NUM];
int locn = 0;  // tot location number

int read_location(FILE *fp) {
    locn = 0;
    char buf[MAX_LOC_NAME_LEN];
    double dirx, diry;
    while (fscanf(fp, "%lf%lf ", &dirx, &diry) != EOF &&
           my_getline(fp, buf) != -1) {
        if (locn >= MAX_LOC_NUM) return 0;
        memcpy(loc[++locn].name, buf, sizeof(buf));
        loc[locn].x = dirx, loc[locn].y = diry;
    }
    return 0;
}

int write_location(FILE *fp) {
    fprintf(fp, "location-name location-dirx location-diry\n");
    for (int i = 1; i <= locn; ++i)
        fprintf(fp, "%lf %lf %s\n", loc[i].x, loc[i].y, loc[i].name);
    return 0;
}

// main utils

// specific comparision funcion used in linked list template
static int cmp(const void *id, const void *node) {
    return *(int *)id == ((bus_ptr)node)->mem_id;
}

int add_bus_mem_to_link(int mem_id, int loc_id) {
    bus_ptr t = (bus_ptr)malloc(sizeof(bus_t));
    t->mem_id = mem_id;
    t->loc_id = loc_id;
    loc[loc_id].num++;
    return l_add(&bus_head, t);
}

int del_bus_mem_from_link(int id) { return l_delete(&bus_head, &id, cmp); }

bus_ptr find_bus_member(int id) {
    lnode_ptr result = l_find(&bus_head, &id, cmp);
    if (result == NULL) return NULL;
    return result->t_ptr;
}

void list_bus_rsv_member() {
    printf("*********************\n");
    printf("当前预约会员及选择的目的地:\n");
    lnode_ptr curr = mem_head;
    while (curr != NULL) {
        if (curr->t_ptr != NULL) {
            member_ptr entry = (member_ptr)(curr->t_ptr);
            bus_ptr f_mem = find_bus_member(entry->id);
            if (f_mem != NULL && f_mem->loc_id != 0)
                printf("会员id:%d    %-10s    地点id: %d\n", entry->id,
                       entry->name, f_mem->loc_id);
        }
        curr = curr->next;
    }
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

void recycle_bus() { l_recycle(&bus_head); }

static char *bus_menu_subp[] = {"", "班车预约", "路线规划", "增加地点",
                                "删除地点"};
void print_bus_menu() {
    printf("*********************\n");
    printf("班车管理系统\n");
    printf("*********************\n");
    printf("1.%s\n", bus_menu_subp[1]);
    printf("2.%s\n", bus_menu_subp[2]);
    printf("3.%s\n", bus_menu_subp[3]);
    printf("4.%s\n", bus_menu_subp[4]);
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
    for (int i = 1; i <= locn; ++i) printf("%d: %s\n", i, loc[i].name);
}

void add_bus_rsv_member() {
    clear_sh();
    print_curr_path();
    list_member();
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
        if (mem_id > get_member_num() || loc_id > locn || mem_id == -1 ||
            loc_id == -1 || find_bus_member(mem_id) != NULL) {
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
            // add_bus_mem_to_link(mem_id, 0);
            printf("会员:%d  的班车预约已取消\n", mem_id);
        }
    }
}

int add_location() {
    clear_sh();
    print_curr_path();
    getchar();
    char buf[MAX_LOC_NAME_LEN];
    double dirx = 0, diry = 0;
    if (locn >= MAX_LOC_NUM) {
        printf("已达最大上限\n");
        return -1;
    }
    printf("请输入新增地点名称\n");
    my_getline(stdin, buf);
    printf("请输入新增地点座标x, y\n");
    scanf("%lf%lf", &dirx, &diry);
    memcpy(loc[++locn].name, buf, sizeof(loc[locn].name));
    loc[locn].x = dirx, loc[locn].y = diry;
    printf("已增加地点: %s\n", loc[locn].name);
    printf("输入任意键返回\n");
    getchar();
    getchar();
    return 0;
}

int del_location() {
    clear_sh();
    print_curr_path();
    list_location();
    printf("请输入删除地点id, 输入0返回\n");
    int loc_id = get_int();
    while (loc_id == -1 || loc_id > locn) {
        printf("请输入合法的id:\n");
        loc_id = get_int();
    }
    if (loc_id == 0) return 0;
    for (int i = loc_id; i < locn; ++i) {
        loc[i] = loc[i + 1];
    }
    locn--;
    printf("已删除地点 id: %d\n", loc_id);
    printf("输入任意键返回\n");
    getchar();
    getchar();
    return 0;
}

// use simulated annealing to calculate approximate TSP
int *tsp_sa(double dis[][MAX_LOC_NUM], int r_locn, const int *ori_rout) {
    static const double INI_T = 1000000, esp = 1e-10, dlt = 0.998, INF = 1e10;
    static int ans_r[MAX_LOC_NUM];

    int curr_rout[MAX_LOC_NUM];
    double now = INF;
    double ans = INF;
    memcpy(curr_rout, ori_rout, sizeof(curr_rout));
    memcpy(ans_r, curr_rout, sizeof(ans_r));
    srand(time(0));

    for (double T = INI_T; T > esp; T *= dlt) {
        int x = 0, y = 0;
        while (x == y) x = rand() % r_locn + 1, y = rand() % r_locn + 1;
        // make sure x and y are different
        swap(&curr_rout[x], &curr_rout[y]);

        double nxt = 0;
        for (int i = 1; i <= r_locn; ++i)
            nxt += dis[curr_rout[i - 1]][curr_rout[i]] *
                   loc[curr_rout[i]].num;  // calculate time cost

        if (nxt < now) {
            now = nxt;
            if (nxt < ans) {
                ans = nxt;
                memcpy(ans_r, curr_rout, sizeof(ans_r));
            }
            continue;
        }
        if (exp((now - nxt) / T) * RAND_MAX < rand()) {
            now = nxt;
            continue;
        }
        swap(&curr_rout[x], &curr_rout[y]);
    }
    return ans_r;
}

void bus_route_man() {
    clear_sh();
    print_curr_path();

    int now[MAX_LOC_NUM], p = 0;
    double dis[MAX_LOC_NUM][MAX_LOC_NUM];
    now[0] = 0;
    int tot_num = 0;  // all members number
    for (int i = 1; i <= locn; ++i)
        if (loc[i].num > 0) {
            now[++p] = i;
            tot_num += loc[i].num;
            dis[i][0] = dis[0][i] =
                fabs(COMM_X - loc[i].x) +
                fabs(COMM_Y - loc[i].y);  // community to others' distance
        }
    for (int i = 1; i <= p; ++i) {
        for (int j = 1; j < i; ++j) {
            double x1 = loc[now[i]].x;
            double y1 = loc[now[i]].y;
            double x2 = loc[now[j]].x;
            double y2 = loc[now[j]].y;
            dis[now[j]][now[i]] = dis[now[i]][now[j]] =
                fabs(x1 - x2) +
                fabs(y1 - y2);  // as all road lies perpendicular to each
                                // other, we use the sum of delta x and
                                // delta y to represent total distance
        }
    }
    int *ans_route = NULL;
    if (p > 1) ans_route = tsp_sa(dis, p, now);

    printf("当前规划路线:\n");
    printf("社区 -> ");
    if (ans_route != NULL)
        for (int i = 1; i <= p; ++i) printf("%s -> ", loc[ans_route[i]].name);
    printf("社区\n");
    printf("\n按任意键返回\n");
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
                break;
            case 2:
                cd_ch(bus_rsv_subp[2]);
                cancle_bus_rsv();
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
                break;
            case 2:
                cd_ch(bus_menu_subp[2]);
                bus_route_man();
                break;
            case 3:
                cd_ch(bus_menu_subp[3]);
                add_location();
                break;
            case 4:
                cd_ch(bus_menu_subp[4]);
                del_location();
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
