#include"list/list.h"

#ifndef PQ_H
#define PQ_H

typedef enum{PQ_USING_HEAP, PQ_USING_ARRAY, PQ_USING_SORTED_ARRAY}PQImplType;


/**************Usage-start ******************/
typedef struct PQ PQ;


PQ *createPQ(PQImplType);
void freePQ(PQ *);
 int isEmptyPQ(PQ *);
void insertItemInPQ(PQ *, void *, isLess);
void insertSortedItemInPQ(PQ *, void *, compareTo);
void*deleteItemInPQ(PQ *, isLess);
PQ*heapSort(PQ *, isLess);
/**************Usage-end ******************/
#endif