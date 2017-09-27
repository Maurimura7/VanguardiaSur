#ifndef __SLIST_H__
#define __SLIST_H__

typedef void (*VisitorFuncInt) (int data, void *extra_data);

/**
 * Los campos son privados, y no deberian ser accedidos
 * desde el código cliente.
 */
typedef struct _SNode {
        int    data;
        struct _SNode *next;
} SNode;

typedef SNode *SList;

#define slist_data(l)       (l)->data
#define slist_next(l)       (l)->next
#define slist_nil()         NULL

/**
 * Agrega un elemento al final de la lista, en complejidad O(n).
 *
 * Nota: una lista vacia se representa con un (SList *) NULL.
 */
SList slist_append(SList list, int data);

/**
 * Agrega un elemento al inicio de la lista, en complejidad O(1).
 *
 * Nota: una lista vacia se representa con un (SList *) NULL.
 */
SList slist_prepend(SList list, int data);

/**
 * Destruccion de la lista.
 */
void  slist_destroy(SList list);

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void  slist_foreach(SList list, VisitorFuncInt visit, void *extra_data);

/**
* Verifica si un nodo tiene un siguiente elemento
*/
void slist_has_next(SList list);
/**
* Devuelve la longitud de la lista
*/
void slist_length(SList list);
/**
*Concatena 2 listas dadas. Devuelve una lista nueva
*las originales no se modifican
*/
SList slist_concat(SList list, SList list1);
/**
*Inserta un dato en una posicion arbitraria de la lista
*/
SList slist_insert(SList lista, int data, int lugar);

SList slist_remove(SList l, int n);
/** ANTES DE HACER EL EJERCICIO 3 DECLARAR LA LISTA DE LA SIGUIENTE MANERA
typedef stryct _GNode{
	void * data; Puntero void a los datos, que todavia no se que son (En los otros ej eran Int)
	struct _GNode *next;
}GNode;
typedef GNode *GList
*/

#endif /* __SLIST_H__ */
