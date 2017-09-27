#include <stdio.h>
#include <stdlib.h>
#include "BStree.h"

static void print_int (int data, void *extra_data)
{
  printf("%d ", data);
}

static void count (int data, void *extra_data)
{
  *(int *)extra_data+=1;
}

int main(int argc, char *argv[])
{

  BSTree root = NULL;
  void *p;
  int suma=0;
  p=&suma;
  root = bstree_insert(root, 25);
  root = bstree_insert(root, 5);
  root = bstree_insert(root, 15);
  root = bstree_insert(root, 2);
  root = bstree_insert(root, 3);
  root = bstree_insert(root, 49);
  root = bstree_insert(root, 77);
  root = bstree_insert(root, 55);
  root = bstree_insert(root, 100);
  root = bstree_insert(root, 7);

  bstree_contain(root,1000);
  bstree_foreach(root, print_int, BTREE_TRAVERSAL_ORDER_POST, bstree_empty());
  //bstree_nelements(root, count, p);
  suma = bstree_height(root);
  puts("");
  printf("La cantidad de niveles es %d\n", suma);
  bstree_destroy(root);

  return 0;
}

