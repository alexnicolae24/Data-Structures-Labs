#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Util.h"
#include "Graph.h"

TGraphL* createGraphAdjList(int numberOfNodes) {
	//TODO: 1
	int i;
    TGraphL *G = malloc(sizeof *G);
    G->nn = numberOfNodes;
    G->adl = malloc(numberOfNodes * sizeof(ATNode));
    for (i = 0; i < numberOfNodes; i++) 
	     G->adl[i] = NULL;
    return G; 
}

TNode *createNode(int v) {
    TNode *temp = (TNode*) malloc(sizeof(TNode));
    temp->v = v;
    temp->next = NULL;
    return temp;
} 

void addEdgeList(TGraphL* graph, int v1, int v2) {
	//TODO: 1
	TNode *aux = createNode(v2);
    aux->next = graph->adl[v1];
    graph->adl[v1]=aux;
    aux = createNode(v1);
    aux->next = graph->adl[v2];
    graph->adl[v2] = aux;
}

List* dfsIterative(TGraphL* graph, int s) {
	//TODO: 2
	int* visited = (int*)malloc(graph->nn*sizeof(int));
	Stack *st = createStack();
	List *l = createList();
	int p = -1; 
	push(st, s);
	visited[s] = 1;
	while(!isStackEmpty(st)) {
		p = top(st);
		pop(st);
		enqueue(l, p);
		ATNode tmp = graph->adl[p];
		while(tmp != NULL) {
			if(visited[tmp->v] == 0) {
				push(st, tmp->v);
				visited[tmp->v] = 1;
			}
			tmp = tmp->next;
		}
	}

	free(visited);
	destroyStack(st);
	return l;
}

void dfsRecHelper(TGraphL* graph, int* visited, List* path, int s) {
	//TODO: 3
	visited[s] = 1;
	enqueue(path,s);
	TNode *p = graph->adl[s];
	while(p != 0) {
		if(visited[p->v] == 0) {
			dfsRecHelper(graph,visited,path,p->v);
		}
		p = p->next;
	}
}

List* dfsRecursive(TGraphL* graph, int s) {
	// TODO 3
	List* path = createList();
	int* visited = malloc(graph->nn*sizeof(int));
	dfsRecHelper(graph,visited,path,s);
	return path;
}

List* bfs(TGraphL* graph, int s){
	// TODO: 4
	Queue* q = createQueue();
	int *visited = (int*)malloc(graph->nn*sizeof(int));
    visited[s] = 1;
    enqueue(q, s);
    while (!isQueueEmpty(q)) {
    int currentVertex = front(q);
    TNode* temp = graph->adl[currentVertex];
    while (temp) {
      int adjVertex = temp->v;
      if (visited[adjVertex] == 0) {
        visited[adjVertex] = 1;
        enqueue(q, adjVertex);
      }
      temp = temp->next;
    }
  }
  return q;
}


void destroyGraphAdjList(TGraphL* graph){
	// TODO: 5
	if(graph != NULL)
    {
        if(graph->adl != NULL)
        {
            int vert;
            for(vert = 0; vert < graph->nn; vert++)
            {
                TNode *listIterator = graph->adl[vert];
                while(listIterator != NULL)
                {
                    TNode *tmp = listIterator;
                    listIterator = listIterator->next;
                    free(tmp);
                }
            }

            free(graph->adl);
        }
        free(graph);
    }
}

void removeEdgeList(TGraphL* graph, int v1, int v2){
	TNode* it = graph->adl[v1];
	TNode* prev = NULL;
	while(it != NULL && it->v != v2){
		prev = it;
		it = it->next;
	}

	if(it == NULL)return;

	if(prev != NULL)
		prev->next = it->next;
	else
		graph->adl[v1] = it->next;
	free(it);

	it = graph->adl[v2];
	prev = NULL;
	while(it != NULL && it->v != v1){
		prev = it;
		it = it->next;
	}
	if(it == NULL) return;
	if(prev != NULL)
		prev->next = it->next;
	else
		graph->adl[v2] = it->next;

	free(it);
}

void removeNodeList(TGraphL* graph, int v){
	for(int i = 0; i < graph->nn;i++){
		removeEdgeList(graph,v,i);
	}
}
