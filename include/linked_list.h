typedef struct Link_Node {
    void *t_ptr;
    struct Link_Node *next;
} lnode_t, *lnode_ptr;