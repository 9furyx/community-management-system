#ifndef __DEFS_H__
#define __DEFS_H__

struct Link_Node;

// init.c
int init(int, char *[]);


// util.c
int get_int(void);
void clear_sh(void);


// bus.c
void bus_ui(void);
void bus_rsv_man(void);
void bus_route_man(void);
void list_location(void);
int read_location(FILE *);
int read_bus(FILE *);
void add_bus_rsv_member(void);
int add_bus_mem_to_link(int, int);


// member.c
void mem_ui(void);
int get_member_num(void);
void list_member(void);
int read_member(FILE *);


// linked_list.c
int l_add(struct Link_Node **, const void *);
int l_delete(struct Link_Node **, void *, int (*)(const void *, const void *), void (*)(const void *));
struct Link_Node *l_find(struct Link_Node **, const void *, int (*)(const void *, const void *));
void l_recycle(struct Link_Node **, void (*)(const void *));


// main_ui.c
void main_ui(void);


// path.c
void print_curr_path(void);
void cd_ch(char *);
void cd_fa(void);

#endif