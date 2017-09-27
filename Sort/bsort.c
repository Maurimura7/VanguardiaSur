#include "SList.h"
#include "bsort.h"
#include <stdio.h>
#include <stdlib.h>
void swap(int *p, int *q) {
  int t = *p;
  *p = *q;
  *q = t;
}

void bsort(int data[], int sz) {
  int sorted, i;

  do {
    sorted = 1;
    for (i = 0; i < sz - 1; i++)
      if (data[i] > data[i+1]) {
	sorted = 0;
	swap(&data[i], &data[i+1]);
      }
  } while (sorted != 1);
}

void ssort(int data[], int sz){
  int i, j, min;
  for(i=0; i < sz; i++){
     min = i;
     for(j = i + 1; j < sz; j++){
        if(data[j] < data[min]){
	   min = j;
	 }
     }
	swap(&data[i], &data[min]);
 }
}
void ssortr(int data[], int sz, int ini){
   if(ini<=sz){	
	int min = ini;
	int j;
	for(j = ini +1; j<sz; j++){
		if(data[j]<data[min])
			min = j;
	}
	swap(&data[ini],&data[min]);
	ssortr(data,sz,ini+1);
   }
}	

SList ssortl(SList list) {
  SList new = NULL;
  SList walker;
  int min;
  int index;
  int count;

  while (list != NULL) {
    walker = list;
    min = list->data;
    index = count = 0;

    while (walker != NULL) {
      if (walker->data < min) {
        min = walker->data;
        index = count;
      } 
      count++;
      walker = walker->next;
    }

    new = slist_append(new, min);
    list = slist_remove(list, index);
  }
  return new;
}

void isort(int data[], int sz){
	int i;
	int j;
	int min;
	int aux;
	for (i=1;i<=sz-1;i++){
		for(j = i-1; j>=0; j--){
			if(data[j+1]<data[j]){
				swap(&data[j],&data[j+1]);	
			}
				
		}	
	} 
}
SList isortl(SList l){
	if(l == NULL || slist_next(l)==NULL)
		return l;
	SList head = NULL; // Lista ordenada resultante
	while(l != NULL){	
		SList current = l;
		l = slist_next(l);
			if (head == NULL || slist_data(current)<slist_data(head)){
				slist_next(current)=head;
				head = current;
			}else{
				SList aux = head;
				while (slist_next(aux)!=NULL){
					if(slist_data(current)<slist_data(slist_next(aux))){
						slist_next(current)=slist_next(aux);
						slist_next(aux)=current;
            break;
					}
					aux=slist_next(aux);
				}
        if(slist_next(aux) == NULL && slist_data(current)>=slist_data(aux)){
              slist_next(current)=slist_next(aux);
              slist_next(aux)=current;
        }	
			}
			printf("Head: %d \t Current: %d \n",slist_data(head),slist_data(current));
			if(slist_next(head)!=NULL)
			printf("Headnext: %d \n",slist_data(slist_next(head)));
	}
	return head;
}
/*
void bsortg(int data[], int sz, CmpFunc compare){
	int stored = 0;
	while(stored != 1){
		
	}
}*/

