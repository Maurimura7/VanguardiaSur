#include <stdlib.h>
#include <stdio.h>
#include "BStree.h"

BSTree bstree_create(int data)
{
	BSTree newNode = malloc(sizeof(BSTNode));
	bstree_data(newNode) = data;
	bstree_left(newNode) = bstree_right(newNode) = NULL;

	return newNode;
}

BSTree bstree_insert(BSTree root, int data){
	if(root == NULL)
		root = bstree_create(data);
	else if(data<=bstree_data(root))
		bstree_left(root)=bstree_insert(bstree_left(root),data);
	else
		bstree_right(root)=bstree_insert(bstree_right(root),data);

	return root;

}

void  bstree_destroy(BSTree node)
{
	if (node != NULL) {
		bstree_destroy(bstree_left(node));
		bstree_destroy(bstree_right(node));
		free(node);
	}
}

void bstree_contain(BSTree root, int data){
	if(bstree_data(root)==data)
		printf("El elemneto %d esta en el arbol\n", data);
	else if(data<=bstree_data(root) && bstree_left(root) != NULL)
		bstree_contain(bstree_left(root),data);
	else if(data>bstree_data(root) && bstree_right(root) != NULL)
		bstree_contain(bstree_right(root),data);
	else if(bstree_data(root) != data)
		printf("El elemneto %d no se encuentra en el arbol\n",data);
}

void  bstree_foreach(BSTree node, VisitorFuncInt visit, BTreeTraversalOrder rec, void *extra_data)
{
	switch (rec){
	   case BTREE_TRAVERSAL_ORDER_PRE: 
	        if (node != NULL) {
		        visit(bstree_data(node), extra_data);
		        bstree_foreach(bstree_left(node), visit, rec, extra_data);
		        bstree_foreach(bstree_right(node), visit, rec, extra_data);

	        }
	        break;
	   case BTREE_TRAVERSAL_ORDER_POST:
	        if (node != NULL) {
		        bstree_foreach(bstree_left(node), visit, rec, extra_data);
		        bstree_foreach(bstree_right(node), visit, rec, extra_data);
		        visit(bstree_data(node), extra_data);

	        }
	        break;
        case BTREE_TRAVERSAL_ORDER_IN:
            if (node != NULL) {
	            bstree_foreach(bstree_left(node), visit, rec, extra_data); 
	            visit(bstree_data(node), extra_data);
	            bstree_foreach(bstree_right(node), visit, rec, extra_data);

            }
            break;
	}
}

void bstree_nelements(BSTree root, VisitorFuncInt visit, void *extra_data){
	 if (root != NULL) {
	            bstree_nelements(bstree_left(root), visit, extra_data); 
	            visit(bstree_data(root), extra_data);
	            bstree_nelements(bstree_right(root), visit, extra_data);
            }
}

int bstree_height(BSTree root){
		if(root != NULL){
			int left = bstree_height(bstree_left(root));
			int rigth = bstree_height(bstree_right(root));
				if(left > rigth)
			        return left + 1;
			    else
			        return rigth +1;

		}else
			return -1;
}