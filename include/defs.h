#ifndef __DEFS_H__
#define __DEFS_H__

// init.c
int file_init(int, char *[]);

// util.c
int get_int(void);


// bus.c
void bus_ui(void);
void bus_rsv_man(void);
void bus_route_man(void);
void add_rsv_member(void);
void list_location(void);
int read_location(FILE *fp);
void list_location(void);

// member.c
int get_member_num(void);
void list_member(void);

//clearsh
void clear_sh(void);


// mainui.c




#endif