#ifndef __QUEUE_H__
#define __QUEUE_H__


#define QElemType int

typedef struct QNode {
    QElemType data;
    struct QNode *next;
} qnode_t, *qnode_ptr;

typedef struct Queue
{
    qnode_ptr front;
    qnode_ptr back;
    int size;
} queue, *queue_ptr;


#endif