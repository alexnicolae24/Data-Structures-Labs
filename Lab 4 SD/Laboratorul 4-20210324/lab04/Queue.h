#ifndef QUEUE_H_
#define QUEUE_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct QueueNode{
	Item elem;
	struct QueueNode *next;
}QueueNode;

typedef QueueNode TcelQ;
typedef QueueNode *ACelQ;

typedef struct Queue{
	QueueNode *front;
	QueueNode *rear;
	long size;
}Queue;

typedef Queue TCoada;
typedef Queue *AQ;


Queue* createQueue(void){
	// TODO: Cerinta 2
	Queue *q = (Queue*)malloc(sizeof(Queue));
	q -> front = NULL;
	q -> rear = NULL;
	q -> size = 0;
	return q;
} 

int isQueueEmpty(Queue *q){
	if(q -> front == NULL)
	   return 1;
	else
	   return 0;
}

void enqueue(Queue *q, Item elem){
	// TODO: Cerinta 2
	QueueNode *newNode = NULL;

    // Check queue out of capacity error
    if (q -> size > 100)
    {
        return ;
    }
    newNode = (QueueNode *) malloc (sizeof(QueueNode));
    newNode -> elem = elem;
    newNode->next = NULL; 
    if (q -> rear)
    {
        q -> rear -> next = newNode;
    }
    q -> rear = newNode;
    if ( !( q -> front) )
    {
        q -> front = q -> rear;
    }
    q -> size++;
    return ;
}

Item front(Queue* q){
	// TODO: Cerinta 2
	return q -> front -> elem;
}

void dequeue(Queue* q){
	// TODO: Cerinta 2
    if( q -> front == NULL)
         exit(1);
    else
    {
		Item el = q -> front -> elem;
        if(q -> front == q -> rear){
		    free(q -> front);
            q -> front = NULL;
			q -> rear = NULL;
			q -> size--;
		}
		else
		{
			QueueNode *ptr = q -> front;
            q -> front = q -> front -> next;
			free(ptr);
			q -> size--;
		}
    }
}

void destroyQueue(Queue *q){
	// TODO: Cerinta 2
	QueueNode *temp = q -> front;
    while (temp){
    q -> front = temp->next;
    free(temp);
    temp = q -> front;
    }
	free(q);
}

#endif
