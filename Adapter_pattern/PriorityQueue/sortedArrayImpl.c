#include "PriorityQueue/PQHandler.h"

/***************Repr-start***********/
typedef struct PQ{

  PQRtti rtti;
  List *array;
}PQ;
/****************Repr-end************/

/*************Usage-start **********/
bool sortedArrayForPQCanHandle(PQImplType implType){
  if(implType == PQ_USING_SORTED_ARRAY){
    return true;
  }
  return false;
}

PQ * createSortedArrayForPQ(void){

  PQ *pq = malloc(sizeof(PQ));
  pq->array = createList(ARRAY_IMPL);
  (pq->rtti).handler = &sortedArrayHandlerForPQ;
  return pq;
}

void freeSortedArrayForPQ(PQ *pq){
  if(pq != NULL){
    freeList(pq->array);
    free(pq);
  }
}

int isEmptySortedArrayForPQ(PQ *pq){

  if(pq == NULL){

    fprintf(stderr, "isEmptySortedArrayForPQ() - NULL is passed\n");
    return -1;
  }
  if(getSize(pq->array) == 0){
    return 1;
  }
  return 0;
}

void insertSortedArrayItemForPQ(PQ *pq, void *item, compareTo compare){

  if(pq == NULL){
    fprintf(stderr, "insertPQElement() - NULL is passed\n");
  }
  pq->array = sortInsertItem(pq->array, item, compare);
}

void *delSortedItemForPQ(PQ *pq, isLess less){

  if(pq == NULL){

    fprintf(stderr, "delMaxPQ() - NULL PQ is passed\n");
    return NULL;
  }

  void *maxElement = (void *)sortDeleteMax(pq->array);
  if(maxElement == NULL){
    fprintf(stdout, "PQ is empty\n");
    return NULL;
  }
  return maxElement;
}
/*****************Usage-end ************/

PQImplHandler sortedArrayHandlerForPQ = {
  sortedArrayForPQCanHandle,
  createSortedArrayForPQ,
  freeSortedArrayForPQ,
  isEmptySortedArrayForPQ,
  NULL,
  insertSortedArrayItemForPQ,
  delSortedItemForPQ,
  NULL
};