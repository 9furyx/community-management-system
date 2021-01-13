#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

typedef const int *cmp_t(const void *, const void *);

// create a new node add an element to node
int l_add(lnode_ptr *head, void *elem) {
    lnode_ptr new_node = (lnode_ptr)malloc(sizeof(lnode_t));
    if (new_node == NULL) return -1;
    new_node->next = *head;
    new_node->t_ptr = elem;
    *head = new_node;
    return 0;
}

// delete a node, using cmp to perform the comparisons
int l_delete(lnode_ptr *head, void *elem, cmp_t cmp) {
    while (*head != NULL) {
        if (cmp(elem, (*head)->t_ptr)) {
            lnode_ptr entry = *head;
            *head = entry->next;
            free(entry->t_ptr);
            free(entry);
            return 0;
        } else
            head = &(*head)->next;
    }
    return -1;
}

// find a node, using cmp to perform the comparisons
lnode_ptr l_find(lnode_ptr *head, void *elem, cmp_t cmp) {
    while (*head != NULL) {
        if (cmp(elem, (*head)->t_ptr)) return *head;
        head = &(*head)->next;
    }
    return NULL;
}

// recycle all node memory
void l_recycle(lnode_ptr *head) {
    while (*head) {
        lnode_ptr entry = *head;
        *head = (*head)->next;
        free(entry->t_ptr);
        free(entry);
    }
}