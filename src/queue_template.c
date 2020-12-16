#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#include "member.h"
#include "queue.h"

int q_init(queue_ptr *q) {
    (*q)->front = (*q)->back = (qnode_ptr)malloc(sizeof(qnode_t));
    if ((*q)->front == NULL)
        return -1;
    (*q)->front->next = NULL;
    (*q)->size = 0;
    return 0;
}
int q_push(queue_ptr *q, QElemType element) {
    qnode_ptr New_Node = (qnode_ptr)malloc(sizeof(qnode_t));
    if (New_Node == NULL)
        return -1;
    (*q)->back->next = New_Node;
    (*q)->back = New_Node;
    New_Node->next = NULL;
    New_Node->data = element;
    (*q)->size++;
    return 0;
}
int q_pop(queue_ptr *q) {
    if ((*q)->front->next == NULL)
        return -1;
    qnode_ptr t = (*q)->front;
    (*q) = t->next;
    (*q)->size--;
    free(t);
    return 0;
}
