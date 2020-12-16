#ifndef __ROOM_H__
#define __ROOM_H__


#define MAX_ROOM_NUM 64

typedef struct Room {
    int room_id;
    int price;
    int owner_mem_id;
    int rent_mem_id;
} room_t,*room_ptr;


#endif