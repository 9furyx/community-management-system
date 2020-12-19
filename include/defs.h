#ifndef __DEFS_H__
#define __DEFS_H__


struct Link_Node;
struct Member;
typedef int cmp_t(const void *, const void *);

// init.c
int init(int, char *[]);

// util.c
int get_int(void);
int my_getline(FILE *, char *);
void clear_sh(void);
void swap(int *, int *);

// bus.c
void bus_ui(void);
int read_location(FILE *);
int write_location(FILE *);
int read_bus(FILE *);
int write_bus(FILE *);
void recycle_bus(void);

// member.c
void mem_ui(void);
int get_member_num(void);
void list_member(void);
int read_member(FILE *);
int write_member(FILE *);
void recycle_member(void);
struct Member *find_member(int);

// room.c
int read_room(FILE *);
int write_room(FILE *);
void room_ui();
int buy_room(int);
void list_empty_room(void);

// staff.c
void staff_ui(void);
int read_staff(FILE *);
int write_staff(FILE *);
void recycle_staff(void);

// linked_list.c
int l_add(struct Link_Node **, const void *);
int l_delete(struct Link_Node **, void *, cmp_t);
struct Link_Node *l_find(struct Link_Node **, const void *, cmp_t);
void l_recycle(struct Link_Node **);

// main_ui.c
void main_ui(void);

// path.c
void print_curr_path(void);
void cd_ch(char *);
void cd_fa(void);

// checkin.c
int checkin_ui(void);

// qsort.c
void quick_sort(void *const, size_t, size_t, cmp_t cmp);


#endif