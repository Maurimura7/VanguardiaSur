#include <stdio.h>
#include <stdlib.h>
#include "SList.h"

SList slist_append(SList list, int data)
{
      SList newNode = malloc(sizeof(SNode));
      SList node;
      slist_data(newNode) = data;
      slist_next(newNode) = NULL;
      if (list == slist_nil()) {
         return newNode;
      }
      node = list;
      while (slist_next(node) != slist_nil()) {
            node = slist_next(node);
      }
      /* ahora 'node' apunta al ultimo nodo en la lista */
      slist_next(node) = newNode;
      return list;
}

SList slist_prepend(SList list, int data)
{
      SList newNode = malloc(sizeof(SNode));
      slist_next(newNode) = list;
      slist_data(newNode) = data;
      return newNode;
}

void  slist_destroy(SList list)
{
      SList nodeToDelete;

      while (list != slist_nil()) {
            nodeToDelete = list;
            list = slist_next(list);
            free(nodeToDelete);
      }
}

void  slist_foreach(SList list, VisitorFuncInt visit, void *extra_data)
{
      SList node = list;

      while (node != slist_nil()) {
            visit(slist_data(node), extra_data);
            node = slist_next(node);
      }
}

void slist_has_next(SList list){
	SList node = list;
	SList aux;
		  while (node != slist_nil()) {
            aux = node;
            node = slist_next(node);
            	if(node == slist_nil())
            		printf("El nodo %d es el ultimo elemento de la lista\n",slist_data(aux));
            	else
            		printf("El nodo %d tiene un siguiente elemnto\n",slist_data(aux));
            
      }
}
void slist_length(SList list){
	int cont=0;
	while (list != slist_nil()) {
			cont++;
            list = slist_next(list);
      }
    printf("La longitud de la lista es %d\n", cont);
}

SList slist_concat(SList list, SList list1){
	SList listcon = slist_nil();
	SList node = list;
	SList node1 = list1;
		while (node != slist_nil()) {
			listcon = slist_append(listcon, slist_data(node));
			node = slist_next(node);			
		}
		while (node1 != slist_nil()) {
			listcon = slist_append(listcon, slist_data(node1));
			node1 = slist_next(node1);			
		}
	return listcon;
}
SList slist_insert(SList lista, int data, int lugar){
	SList node = lista;
	SList aux = slist_nil();
	int i;
	while (node != slist_nil()) {
				for(i=0;i<lugar;i++){
					aux = slist_append(node, slist_data(node));
					node = slist_next(node);
				}
			aux = slist_append(node, slist_data(node));
			node = slist_next(node);			
		}
		return aux;
}


SList slist_remove(SList list1, int n) {
	SList first = list1;
	SList temp = slist_next(list1);
	if (n == 0) {
		slist_next(list1) = NULL;
		return temp; }

	while (n > 0) {
		temp = list1;
		list1 = slist_next(list1);
		n--;
	}

	slist_next(temp) = slist_next(list1);
	slist_next(list1) = NULL;
	slist_destroy(list1);
	return first;
}
unsigned int slist_index(SList list, const int data) {
	if (list == NULL) return -1;
	int i = 0;
	while (slist_next(list) != NULL) {
		if (slist_data(list) == data)
			return i;
		list = slist_next(list);
		i++;
	}
	if (slist_data(list) == data) return i;
	return -1;	
}
