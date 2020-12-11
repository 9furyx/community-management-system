#ifndef __ROOM_H__
#define __ROOM_H__

#define MAX_ROOM_NUM 64

struct Room {
    int room_id;
    int owner_mem_id;
    int rent_mem_id;
};

#endif