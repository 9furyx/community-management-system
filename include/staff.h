#ifndef __STAFF_H__
#define __STAFF_H__

#define MAX_STAFF_NAME_LEN 64  // maximum staff name length
#define MAX_STAFF_NUM 256      // maximum staff number

typedef struct Staff {
    int id;
    int target_id;
    char name[MAX_STAFF_NAME_LEN];

} staff_t, *staff_ptr;

#endif
