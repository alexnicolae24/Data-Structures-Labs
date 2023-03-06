/*
*	Created by Nan Mihai on 28.03.2021
*	Copyright (c) 2021 Nan Mihai. All rights reserved.
*	Laborator 5 - Structuri de date
*	Facultatea de Automatica si Calculatoare
*	Anul Universitar 2020-2021, Seria CD
*/
#include "tree.h"

/*
*	Funcție care creează un arbore cu un singur nod
*/
Tree createTree(Item value) {
	Tree root = malloc(sizeof(TreeNode));
	root->value = value;
	root->left = NULL;
	root->right = NULL;
	return root;
}

/*
*	Funcție care inițializează un nod de arbore
*		- îi alocă memorie
*		- îi setează câmpul valoare
*		- setează left și right să pointeze către NULL
*/
void init(Tree *root, Item value) {
	// TODO 1
	*root =(TreeNode*)malloc(sizeof(TreeNode));
	(*root) -> value = value;
	(*root) -> left = NULL;
	(*root) -> right = NULL;
}

/*
*	Funcție care inserează o valoare într-un arbore binar, respectând
* proprietățile unui arbore binar de căutare
*/
Tree insert(Tree root, Item value) {
	// TODO 2
	if(root == NULL){
		init(&root, value);
		return root;
	}
	else if(root -> value == value)
	       return root;
	    else{
			if(root -> value > value){
				if(root -> left == NULL){
					init(&(root -> left), value);
					return root;
				}
				else{
					root -> left = insert(root -> left, value);
					return root;
				}
			}	
			else{
				if(root -> right == NULL){
					init(&(root -> right), value);
					return root;
				}
				else{
					root -> right = insert(root -> right, value);
					return root;
				}
			}
	    }
}

/*
*	Funcție care afișează nodurile folosind parcurgerea în postordine
*/
void printPostorder(Tree root) {
	// TODO 3
	if(root != NULL){
       printPostorder(root -> left);
       printPostorder(root -> right);
       printf("%d ",root -> value);
	}
}

/*
*	Funcție care afișează nodurile folosind parcurgerea în preordine
*/
void printPreorder(Tree root) {
	// TODO 4
	if(root != NULL){
	   printf("%d ",root -> value);
       printPreorder(root -> left);
       printPreorder(root -> right);
	}
}

/*
*	Funcție care afișează nodurile folosind parcurgerea în inordine
*/
void printInorder(Tree root) {
	// TODO 5
	if(root != NULL){
       printInorder(root -> left);
	   printf("%d ",root -> value);
       printInorder(root -> right);
	}

}

/*
*	Funcție care dealocă întreaga memorie alocată pentru un arbore binar
*		- root va pointa către NULL după ce se va apela funcția
*/
void freeTree(Tree *root) {
	// TODO 6
	 if((*root) == NULL)
	    return;
	 freeTree(&((*root) -> left));
	 freeTree(&((*root) -> right));
	 (*root) = NULL;
	 free((*root));
}


/*
*	Funcție care determină numărul de noduri dintr-un arbore binar
*/
int size(Tree root) {
	// TODO 7
	if(root == NULL) 
        return 0;
    else     
        return(size(root -> left) + 1 + size(root -> right));
}

/*
*	Funcție care returnează adâncimea maximă a arborelui
*/
int maxDepth(Tree root) {
	// TODO 8
	if(root == NULL)
       return -1;
    else{
      int left = maxDepth(root -> left);
      int right = maxDepth(root -> right);
      if(left >= right){
	       left = left + 1 ;
           return left ;
	    }
      else{
		   right = right + 1 ; 
            return right ;
	    }
    }
}

/*
*	Funcție care construiește oglinditul unui arbore binar
*/
void mirror(Tree root) {
	// TODO 9
	if (root==NULL) 
    	return;  
    else{
		Tree temp;
		mirror(root -> left);
		mirror(root -> right);
		temp = root -> left;
		root -> left  = root -> right;
		root -> right = temp;
    }
}

/*
*	Funcție care verifică dacă doi arbori binari sunt identici
*/
int sameTree(Tree root1, Tree root2) {
	// TODO 10
	if ((root1 == NULL) && (root2 == NULL))
        return 1;
    if((root1 != NULL) && (root2 != NULL))
    {
        if((root1 -> value == root2 -> value) && sameTree(root1 -> left, root2 -> left) && sameTree(root1 -> right, root2 -> right))
		    return 1;
		else
			return 0;	
    }
    return 0;
}
