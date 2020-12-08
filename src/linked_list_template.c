#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

int l_add(lnode_ptr *head, const void *element) {
    lnode_ptr new_node = (lnode_ptr)malloc(sizeof(lnode_t));
    if (new_node == NULL)
        return -1;
    new_node->next = *head;
    new_node->t_ptr = element;
    *head = new_node;
    return 0;
}

int l_delete(lnode_ptr *head, void *element, int (*cmp)(const void *, const void *)) {
    while (*head != NULL) {
        if (cmp(element, (*head)->t_ptr)) {
            lnode_ptr entry = *head;
            *head = entry->next;
            free(entry);
            return 0;
        } else
            head = &(*head)->next;
    }
    return -1;
}

lnode_ptr l_find(lnode_ptr *head, const void *element, int (*cmp)(const void *,const void *)) {
    lnode_ptr curr = *head;
    while (curr != NULL) {
        if (cmp(element, curr->t_ptr)) {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

void l_recycle(lnode_ptr *head) {
    while (*head) {
        lnode_ptr entry = *head;
        *head = (*head)->next;
        free(entry);
    }
}