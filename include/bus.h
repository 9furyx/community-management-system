#ifndef __LOCATION_H__
#define __LOCATION_H__

#define MAX_LOC_NAME_LEN 128  // maximum length of location name
#define MAX_LOC_NUM 32  // maximum number of locations

#define COMM_X 27.3  // community's coordinate x
#define COMM_Y 118.5 // community's coordinate y

struct Location {
    char name[MAX_LOC_NAME_LEN];
    double x, y;
    int num;
};

typedef struct Bus {
    int mem_id;
    int loc_id;
}bus_t, *bus_ptr;

#endif