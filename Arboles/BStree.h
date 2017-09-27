#ifndef __BTREE_H__
#define __BTREE_H__

typedef void (*VisitorFuncInt) (int data, void *extra_data);

typedef enum {
	BTREE_TRAVERSAL_ORDER_IN,
	BTREE_TRAVERSAL_ORDER_PRE,
	BTREE_TRAVERSAL_ORDER_POST
} BTreeTraversalOrder;

/**
 * Los campos son privados, y no deberian ser accedidos
 * desde el código cliente.
 */
typedef struct _BSTNode {
	int    data;
	struct _BSTNode *left;
	struct _BSTNode *right;
} BSTNode;

typedef BSTNode *BSTree;

#define bstree_data(l)       (l)->data
#define bstree_left(l)       (l)->left
#define bstree_right(l)      (l)->right
#define bstree_empty()       NULL

/**
 * Crea un nuevo nodo, en complejidad O(1).
 *
 * Nota: el árbol vacio se representa con un (BSTree *) NULL.
 */

BSTree bstree_create(int data);

/**
 * Inserta un nodo en el arbol.
 */

BSTree bstree_insert(BSTree root, int data);

/**
 * Indica si un elemento se encuentra en el arbol
 */
void bstree_contain(BSTree root, int data);

/**
 * Destruccion del árbol.
 */
void  bstree_destroy(BSTree root);

/**
 * Recorrido del árbol, utilizando la funcion pasada.
 */
void  bstree_foreach(BSTree list, VisitorFuncInt visit, BTreeTraversalOrder rec, void *extra_data);

/**
 * Devuelve la cantidad de elementos que hay en el arbol
 */
void bstree_nelements(BSTree root, VisitorFuncInt visit, void *extra_data);

#endif /* __BTREE_H__ */

