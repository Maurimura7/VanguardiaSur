#include <stdio.h>
#include <stdlib.h>
#include "BTree.h"

static void print_int (int data, void *extra_data)
{
	printf("%d ", data);
}
static void suma_int (int data, void *extra_data)//Uso de extra_data (puntero que uso para almacenar la suma)
{
  //Como el puntero es tipo void *, lo casteo *(int *)
    *(int *)extra_data += data;
}

static void suman_int (int data, void *extra_data)
{
	*(int *)extra_data +=1;
}

static void set_min (int data, void *extra_data)
{
  printf("Entro a set_min\n");
  *(int *)extra_data = data;
  printf("%d\n",data);
}

int main(int argc, char *argv[])
{
  int x=5;
  BTree root = createfib(5);
  printf("%d\n",btree_data(btree_left(root)));
  btree_foreach(root, print_int, BTREE_TRAVERSAL_ORDER_PRE, NULL);
  btree_destroy(root);

  return 0;
}

