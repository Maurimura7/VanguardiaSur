#ifndef __BSORT_H__
#define __BSORT_H__
#include "SList.h"

typedef int (*CmpFunc)(void *, void *);

void bsort(int [], int);
void ssort(int [], int);
SList ssortl(SList l);
SList isortl(SList l);
void ssortr(int [],int, int);
#endif /* __BSORT_H__ */
