#ifndef __HEAP_H__
#define __HEAP_H__

#include <stdlib.h>
#include <math.h>

/* We assume there is a defined primitive type Item. */
typedef struct {
	int prior; // Item priority
	Item data; // Item d
}ItemType;

typedef struct heap{
	long maxHeapSize; // capacity
	long size; // number of elements
	ItemType *elem; // array of elements
} PriQueue, *APriQueue;

PriQueue* makeQueue(int maxHeapSize){
	PriQueue *q = malloc(sizeof(PriQueue));
	q -> elem = (ItemType*)malloc(maxHeapSize * sizeof(ItemType));
    q -> maxHeapSize = maxHeapSize;
	q -> size = 0;
	return q;
}

int getLeftChild(int i){
	return 2 * i + 1;
}

int getRightChild(int i) {
	return 2 * i + 2;
}

int getParent(int i) {
	return (i - 1) / 2;
}

ItemType getMax(APriQueue h) {
	return h -> elem[0];
}

void siftUp(APriQueue h, int idx) {
	while (idx >= 0  && h -> elem[idx].prior > h -> elem[getParent(idx)].prior) {
		ItemType aux = h -> elem[getParent(idx)];
		h -> elem[getParent(idx)] = h -> elem[idx];
		h -> elem[idx] = aux;
        idx = getParent(idx);
    }
}


void insert(PriQueue *h, ItemType x) {
	if(h -> size == h -> maxHeapSize) {
       h -> maxHeapSize = h -> maxHeapSize * 2;
       h -> elem = (ItemType*)realloc(h -> elem,h -> maxHeapSize * sizeof(ItemType));
    }
    h -> elem[h -> size] = x;
    siftUp(h,h -> size);
    h -> size ++; 
}

void siftDown(APriQueue h, int idx){
    int l = getLeftChild(idx);
    int r = getRightChild(idx);
    int maxidx = idx;
    if (l < h -> size && h -> elem[l].prior > h -> elem[maxidx].prior) {
        maxidx = l;
    }
    if (r < h -> size && h -> elem[r].prior > h -> elem[maxidx].prior) {
        maxidx = r;
    }
    if (maxidx != idx) {
        ItemType aux = h -> elem[maxidx];
        h -> elem[maxidx] = h -> elem[idx];
        h -> elem[idx] = aux;
        siftDown(h,maxidx);
    }
}

void removeMax(APriQueue h) {
	h -> elem[0] = h -> elem[h -> size - 1];
    h -> size --;
    siftDown(h,0);
}

void freeQueue(APriQueue h){
	h -> size = 0;
    h -> maxHeapSize = 0;
    free(h -> elem);
    free(h);

}

#endif
