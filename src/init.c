#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fflag.h"
#include "defs.h"

static int fflag[FLAGN];
static int fn = 0;

// read file functions
static int (*rfflags[])() = {
    //[F_FACILITY] Read_Facility,
    [F_LOCATION] read_location,
    [F_MEMBER] read_member,
    [F_BUS] read_bus,
    [F_ROOM] read_room,
    //[F_STAFF] Read_Staff,
};

// write file functions
static int (*wfflags[])() = {
    [F_LOCATION] write_location,
    [F_MEMBER] write_member,
    [F_BUS] write_bus,
    [F_ROOM] write_room,
};

// check if the file format is correct
int check_file_validity(FILE *fp) {
    char flag_id[16];
    fscanf(fp, "%s", flag_id);
    char c;
    do {
        c = getc(fp);
    } while (c != '\n');
    if (strlen(flag_id) != 3)
        return -1;
    if (flag_id[0] == '[' && flag_id[2] == ']')
        if (flag_id[1] >= '0' && flag_id[1] <= '9')
            return flag_id[1] - '0';
    return -1;
}

// help messages
void print_help() {
    printf("Usage: ersvs [OPTIONS]... [FILE]...\n\n");
    printf("  -f [FILE 1] [FILE 2]... ,   lanuch and read from specific files\n");
    printf("  -h ,                        display this help\n");
    printf("  -v ,                        output version info\n\n");
    printf("Full documentation: <https://github.com/9furyx/community-management-system>\n");
}

// initialize files
int file_init(int F_NUM, char *path[]) {
    FILE *fp;
    for (int i = 1; i < F_NUM; ++i) {
        fp = fopen(path[i], "r");
        if (fp == NULL) {
            printf("Error when opening file: %s\n", path[i]);
            return -1;
        }
        //printf("%s\n", path[i]);
        int target = check_file_validity(fp);
        if (target < 0) {
            printf("bad file format: %s\n", path[i]);
            return -1;
        }
        rfflags[target](fp);
        fflag[++fn] = target;
        fclose(fp);
    }
    return 0;
}

// save file changes
int save_file(int F_NUM, char *path[]) {
    FILE *fp;
    for (int i = 1; i < F_NUM; ++i) {
        fp = fopen(path[i], "w");
        if (fp == NULL) {
            printf("Error when opening file: %s\n", path[i]);
            return -1;
        }
        int target = fflag[i];
        fprintf(fp, "[%d] ", target);
        wfflags[target](fp);
        fclose(fp);
    }
    return 0;
}

void print_version() {
    printf("长者社区管理系统 v1.0\n");
}

int init(int argc, char *argv[]) {
    int p = 0;
    int start = 0;
    while (++p < argc && argv[p][0] == '-' && argv[p][1] >= 'a' && argv[p][1] <= 'z') {
        if (argv[p][1] == 'f')
            start = 1;
        if (argv[p][1] == 'h')
            print_help();
        if (argv[p][1] == 'v')
            print_version();
    }
    if (start == 1 && file_init(argc - p + 1, argv + p - 1) != -1) {
        main_ui();
        save_file(argc - p + 1, argv + p - 1);
    } else if (p == 1)
        print_help();
}