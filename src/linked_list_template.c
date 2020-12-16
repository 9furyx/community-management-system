#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"


typedef const int *cmp_t(const void *, const void *);

// add a new link node
int l_add(struct Link_Node** head,  void *element) {
    lnode_ptr new_node = (lnode_ptr)malloc(sizeof(lnode_t));
    if (new_node == NULL)
        return -1;
    new_node->next = *head;
    new_node->t_ptr = element;
    *head = new_node;
    return 0;
}

// delete a node and node data using a specific comparision function and data free function
int l_delete(lnode_ptr *head, void *element, cmp_t cmp, const void (*free_data)(const void *)) {
    while (*head != NULL) {
        if (cmp(element, (*head)->t_ptr)) {
            lnode_ptr entry = *head;
            *head = entry->next;
            free_data(entry->t_ptr);
            free(entry);
            return 0;
        } else
            head = &(*head)->next;
    }
    return -1;
}

// find a node using a specific comparision function
lnode_ptr l_find(lnode_ptr *head, const void *element, cmp_t cmp) {
    lnode_ptr curr = *head;
    while (curr != NULL) {
        if (cmp(element, curr->t_ptr)) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

// recycle all node memory
void l_recycle(lnode_ptr *head, void (*free_data)(const void *)) {
    while (*head) {
        lnode_ptr entry = *head;
        *head = (*head)->next;
        free(entry);
    }
}