#ifndef __MEMBER_H__
#define __MEMBER_H__

#define MAX_MEMBER_NAME_LEN 64 // maximum member name length
#define MAX_MAMBER_NUM 256  // maximum member number

struct Member {
    int id;
    int room_id;
    char name[MAX_MEMBER_NAME_LEN];
    struct Member *next;
};

#endif