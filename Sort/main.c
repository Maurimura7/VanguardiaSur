#include <stdio.h>
#include "bsort.h"
#include "SList.h"

#define NELEMS(a) (sizeof((a))/sizeof(int))


static void print_int (int data, void *extra_data)
{
  printf("%d ", data);
}


static void minl (int data, void *extra_data)
{
  if(data < *(int *)extra_data)
	*(int *)extra_data = data;
}

int main(void) {
  int arr[] = { 8, 4, 1, 3, 7, 8, 6 };
  int i;
  int arr2[] = { 7, 8, 3, 9, 0, 8, 6 };
  SList l = NULL;
  l = slist_append(l, 4);
  l = slist_append(l, 1);
  l = slist_append(l, 7);
  l = slist_append(l, 9);
  l = slist_append(l, 2);
  for (i  = 0; i < NELEMS(arr); i++)
    printf("%d ", arr[i]);

  puts("");
  ssortr(arr, NELEMS(arr), 0);
   for (i  = 0; i < NELEMS(arr); i++)
    printf("%d ", arr[i]);
puts("");
  slist_foreach(l, print_int, NULL);
  l= isortl(l);
  printf("Acá se tendria que ordenar\n");
  slist_foreach(l, print_int, NULL);

  return 0;
}
