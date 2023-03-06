#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "heap.h"

typedef int TCost;

typedef struct node
{
	int v;
	TCost c;
	struct node *next;
} TNode, *ATNode;

typedef struct
{
	int nn;
	ATNode *adl;
}	TGraphL;


void alloc_list(TGraphL * G, int n)
{
    int i;
    G->nn = n;
	G->adl = (ATNode*) malloc((n+1)*sizeof(ATNode));
	for(i = 0; i < n; i++)
		G->adl[i] = NULL;

}

void free_list(TGraphL *G)
{
    int i;
    ATNode it;
    for(i = 1; i < G->nn; i++){
		it = G->adl[i];
		while(it != NULL){
			ATNode aux = it;
			it = it->next;
			free(aux);
		}
		G->adl[i] = NULL;
	}
	G->nn = 0;
}

void insert_edge_list(TGraphL *G, int v1, int v2, int c)
{
 TNode *t;
 t=(ATNode)malloc(sizeof(TNode));
 t->v = v2; t->c=c; t->next = G->adl[v1]; G->adl[v1]=t;
 t=(ATNode)malloc(sizeof(TNode));
 t->v = v1;  t->c=c; t->next = G->adl[v2]; G->adl[v2]=t;
}

void print1(int dist[], int n)
{   printf("\nPentru functia dijkstra :\n");
    for (int i = 0; i < n; ++i)
        printf("%d \t\t %d\n", i, dist[i]);
}

void print2(int dist[], int n)
{   printf("\nPentru functia Prim :\n");
    for (int i = 1; i < n; ++i)
        printf("%d \t\t %d\n", dist[i], i);
}

void dijkstra(TGraphL G, int s)
{   int size = G.nn;
    int dist[size];    
    MinHeap* minHeap = newQueue(size);
    for (int i = 0; i < size; ++i)
    {
        dist[i] = INT_MAX;
        minHeap->elem[i] = newNode(i,dist[i]);
        minHeap->pos[i] = i;
    }
    minHeap->elem[s] = newNode(s, dist[s]);
    minHeap->pos[s] = s;
    dist[s] = 0;
    SiftUp(minHeap, s, dist[s]);
    minHeap->size = size;
    while (!isEmpty(minHeap))
    {
        MinHeapNode* minHeapNode = removeMin(minHeap);
        int u = minHeapNode->v;
        TNode* p = G.adl[u];
        while (p != NULL)
        {
            int x = p->v;
            if (isInMinHeap(minHeap, x) && dist[u] != INT_MAX && p->c + dist[u] < dist[x])
            {
                dist[x] = dist[u] + p->c;
                SiftUp(minHeap, x, dist[x]);
            }
            p = p->next;
        }
    }
    print1(dist, size);
}

void Prim(TGraphL G)
{   int size = G.nn;
    int par[size]; 
    int dist[size]; 
    MinHeap* minHeap = newQueue(size);
    for (int i = 1; i < size; ++i) {
        par[i] = -1;
        dist[i] = INT_MAX;
        minHeap->elem[i] = newNode(i, dist[i]);
        minHeap->pos[i] = i;
    }
    dist[0] = 0;
    minHeap->elem[0] = newNode(0, dist[0]);
    minHeap->pos[0] = 0;
    minHeap->size = size;
    while (!isEmpty(minHeap)) {
        MinHeapNode* minHeapNode = removeMin(minHeap);
        int u = minHeapNode->v; 
        TNode* p = G.adl[u];
        while (p != NULL) {
            int x = p->v;
            if (isInMinHeap(minHeap, x) && p->c < dist[x]) {
                dist[x] = p->c;
                par[x] = u;
                SiftUp(minHeap, x, dist[x]);
            }
            p = p->next;
        }
    }
    print2(par, size);
}


int main()
{
    int i,v1,v2,c;
	int V,E;
	TGraphL G;
	ATNode t;
	freopen ("graph.in", "r", stdin);
	scanf ("%d %d", &V, &E);
	alloc_list(&G, V);

	for (i=1; i<=E; i++)
	{
		scanf("%d %d %d", &v1, &v2, &c);
	    insert_edge_list(&G, v1,v2, c);
	}

	for(i=0;i<G.nn;i++)
	{
    	printf("%d : ", i);
    	for(t = G.adl[i]; t != NULL; t = t->next)
   			 printf("%d ",t->v);
    		 printf("\n");
	}
	dijkstra(G,0);
	Prim(G);

	return 0;
}