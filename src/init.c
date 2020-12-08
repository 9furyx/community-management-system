#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fflag.h"
#include "defs.h"

static int (*fflags[])() = {
    [F_FACILITY] Read_Facility,
    [F_LOCATION] read_location,
    [F_MEMBER] Read_Member,
    [F_ROOM] Read_Room,
    [F_STAFF] Read_Staff,
};

int check_file_validity(FILE *fp) {
    char flag_id[16];
    fscanf(fp, "%s", flag_id);
    if (strlen(flag_id) > 3)
        return -1;
    if (flag_id[0] == '[' && flag_id[2] == ']')
        if (flag_id[1] >= '0' && flag_id[1] <= '9')
            return flag_id[1] - '0';
    return -1;
}

int file_init(int F_NUM, char *path[]) {
    FILE *fp;
    for (int i = 0; i < F_NUM; ++i) {
        fp = fopen(path[i], "r");
        int target = Check_File_Validity(fp);
        if (target < 0) {
            printf("bad file format.\n");
            return -1;
        }
        fflags[target](fp);
    }
}