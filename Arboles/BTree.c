#include <stdlib.h>
#include <stdio.h>
#include "BTree.h"

BTree btree_create(int data, BTree left, BTree right)
{
	BTree newNode = malloc(sizeof(BTNode));
	btree_data(newNode) = data;
	btree_left(newNode) = left;
	btree_right(newNode) = right;
	return newNode;
}
BTree createfib(int num){
	BTree newNode = malloc(sizeof(BTNode));
	btree_data(newNode) = num;
	if(num==1 || num==0){
		btree_left(newNode)=NULL;
		btree_right(newNode)=NULL;
	}else{	
		btree_left(newNode) = createfib(num-1);
		btree_right(newNode) = createfib(num-1);
	}
	return newNode;
}
void  btree_destroy(BTree node)
{
	if (node != NULL) {
		btree_destroy(btree_left(node));
		btree_destroy(btree_right(node));
		free(node);
	}
}

void  btree_foreach(BTree node, VisitorFuncInt visit, BTreeTraversalOrder rec, void *extra_data)
{
	switch (rec){
	   case BTREE_TRAVERSAL_ORDER_PRE: 
	        if (node != NULL) {
		        visit(btree_data(node), extra_data);
		        btree_foreach(btree_left(node), visit, rec, extra_data);
		        btree_foreach(btree_right(node), visit, rec, extra_data);

	        }
	        break;
	   case BTREE_TRAVERSAL_ORDER_POST:
	        if (node != NULL) {
		        btree_foreach(btree_left(node), visit, rec, extra_data);
		        btree_foreach(btree_right(node), visit, rec, extra_data);
		        visit(btree_data(node), extra_data);

	        }
	        break;
        case BTREE_TRAVERSAL_ORDER_IN:
            if (node != NULL) {
	            btree_foreach(btree_left(node), visit, rec, extra_data); 
	            visit(btree_data(node), extra_data);
	            btree_foreach(btree_right(node), visit, rec, extra_data);

            }
            break;
	}
}
void btree_min(BTree node, VisitorFuncInt visit, void *extra_data){

	if (node != NULL) {
		        if(btree_data(node)>btree_data(btree_left(node))){
		        	btree_data(node)=btree_data(btree_left(node));
		        	visit(btree_data(node), extra_data);
		        	btree_min(btree_left(node), visit, extra_data);
		        	*(int *)extra_data=btree_data(node);

		        }else if(btree_data(node)>btree_data(btree_right(node))){
		        	if(btree_right(node)!=NULL)
		        		visit(btree_data(btree_right(node)), extra_data);
		        	
		        	btree_data(node)=*(int *)extra_data;
		        	btree_min(btree_right(node), visit, extra_data);
		        	btree_min(btree_left(node), visit, extra_data);

		    	}
	        }
}


