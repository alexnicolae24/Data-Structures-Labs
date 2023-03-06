
#ifndef AVLTREE_H_
#define AVLTREE_H_

#include<stdlib.h>

// An AVL tree node
typedef struct AVLNode{
	Item elem;
	int height;
	struct AVLNode *l;
	struct AVLNode *r;
	struct AVLNode *p;

}AVLNode;

typedef struct AVLTree{
	long size;
	AVLNode* root;
	AVLNode* nil;
	int (*comp)(Item a, Item b);
}AVLTree;

AVLTree* avlCreateTree(int (*comp) (Item1,Item1))
{
	AVLTree* newTree = (AVLTree*) malloc(sizeof(AVLTree));
	newTree->comp = comp;
	newTree->nil = (AVLNode*) malloc(sizeof(AVLNode));
	newTree->nil->p = newTree->nil->l = newTree->nil->r = newTree->nil;
	newTree->nil->height = 0;
	newTree->root = (AVLNode*) malloc(sizeof(AVLNode));
	newTree->root->p = newTree->root->l = newTree->root->r = newTree->nil;
	newTree->root->height = 0;
	newTree->size = 0;

	return newTree;
}

int avlIsEmpty(AVLTree* tree){
	return (tree->root->l == tree->nil);
}

AVLNode* avlNewNode(AVLTree* tree){
	AVLNode* newNode = (AVLNode*) malloc(sizeof(AVLNode));
	// Initialize the new node to be used in the tree
	newNode->p = newNode->r = newNode->l = tree->nil;
	newNode->height = 1;

	return newNode;
}



// A utility function to get maximum of two integers
int max(int a, int b){
	return (a > b)? a : b;
}

// A utility function to right rotate subtree rooted with y
void avlRightRotate(AVLTree *tree,  AVLNode *y){
	AVLNode *x= y->l;
    y->l = x->r;
    if(x->r != tree->nil) {
       x->r->p = y;
    }
    x->p = y->p;
   if(y->p == tree->nil){ 
      tree->root = x;
    }
   else if(y == y->p->r){ 
           y->p->r = x;
        }
        else{
            y->p->l = x;
        }
    x->r = y;
    y->p = x;
    y->height = 1 + max(y->l->height,y->r->height);
    x->height = 1 + max(x->l->height,x->r->height);
}

// A utility function to left rotate subtree rooted with x
void avlLeftRotate(AVLTree *tree, AVLNode *x){
	AVLNode *y = x->r;
    x->r = y->l;
    if(y->l != tree->nil){
       y->l->p = x;
    }
    y->p = x->p;
    if(x->p == tree->nil) { 
       tree->root = y;
    }
   else if(x == x->p->l) { 
           x->p->l = y;
        }
        else{ 
             x->p->r = y;
        }
    y->l = x;
    x->p = y;
	y->height = 1 + max(y->l->height,y->r->height);
    x->height = 1 + max(x->l->height,x->r->height);
}

// Get Balance factor of node x
int avlGetBalance(AVLNode *x){
	if (x == NULL)
		return 0;
	return x->l->height - x->r->height;
}

AVLNode * avlMinimum(AVLTree* tree, AVLNode* x){
	while (x->l != tree->nil)
		x = x->l;
	return x;
}

AVLNode* avlMaximum(AVLTree* tree, AVLNode* x){
	while(x->r != tree->nil){
		x = x->r;
	}
	return x;
}



void avlInsert(struct AVLTree* tree, Item elem){
    AVLNode* a = tree->root->l;
	AVLNode* b = tree->root;
	while(a != tree->nil){
		b = a;
		if(tree->comp(a->elem, elem) == 1)
			a = a->l;
		else 
		    if(tree->comp(a->elem, elem) == -1)
			   a = a->r;
	}
	AVLNode *c = avlNewNode(tree);
	c->elem = elem;
	c->p = b;
	if((b == tree->root) || (tree->comp(b->elem, c->elem) == 1))
		b->l = c;
	else
		b->r = c;
	tree->size = tree -> size + 1;
	while(b != tree->root){
	  b->height = max(b->l->height, b->r->height) + 1;
	  if(avlGetBalance(b) > 1 && (tree->comp(elem, b->l->elem) == -1))
		avlRightRotate(tree, b);
	  if(avlGetBalance(b) < -1 && (tree->comp(elem, b->r->elem) == 1))
		avlLeftRotate(tree, b);
	  if(avlGetBalance(b) > 1 && (tree->comp(elem, b->l->elem)) == 1){
		avlLeftRotate(tree, b->l);
		avlRightRotate(tree, b);
	  }
	  if(avlGetBalance(b) < -1 && (tree->comp(elem, b->r->elem)) == -1){
		avlRightRotate(tree, b->l);
		avlLeftRotate(tree, b);
	  }
	  b = b->p;
    }
}

void avlDeleteNode(AVLTree *tree, AVLNode* node){
	destroyElem(node->elem);
	free(node);
}


void avlDestroyTreeHelper(AVLTree* tree, AVLNode* x) {
	if (x != tree->nil) {
		avlDestroyTreeHelper(tree,x->l);
		avlDestroyTreeHelper(tree,x->r);
		avlDeleteNode(tree,x);
	}
}

void avlDestroyTree(AVLTree* tree){
	avlDestroyTreeHelper(tree, tree->root->l);
	free(tree->root);
	free(tree->nil);
	free(tree);
}

#endif /* AVLTREE_H_ */