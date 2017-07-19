#include "PriorityQueue/PQHandler.h"


/***************Repr-start***********/
typedef struct PQ{

  PQRtti rtti;
  List *array;
}PQ;
/****************Repr-end************/

/*************Usage-start **********/

bool arrayForPQCanHandle(PQImplType implType){

  if(implType == PQ_USING_ARRAY){
    return true;
  }
  return false;
}


PQ * createArrayForPQ(void){

  PQ *pq = malloc(sizeof(PQ));
  pq->array = createList(ARRAY_IMPL);
  (pq->rtti).handler = &arrayHandlerForPQ;
  return pq;
}


void freeArrayForPQ(PQ *pq){

  if(pq != NULL){

    freeList(pq->array);
    free((pq->rtti).handler);
    free(pq);
  }
}


int isEmptyArrayForPQ(PQ *pq){

  if(pq == NULL){
    fprintf(stderr, "isEmptyArrayForPQ() - NULL is passed\n");
    return -1;
  }
  if(getSize(pq->array) == 0){
    return 1;
  }
  return 0;
}

void insertArrayItemForPQ(PQ *pq, void *item, isLess less){

  if(pq == NULL){
    fprintf(stderr, "insertArrayItemForPQ() - NULL is passed\n");
    return;
  }
  insertItem(pq->array, item);
}


void* delMaxArrayItemForPQ(PQ *pq, isLess less){

  if(pq == NULL){
    fprintf(stderr, "delMaxArrayItemForPQ() - NULL PQ is passed\n");
    return NULL;
  }
  void *maxElement = (void *)deleteMax(pq->array, less);

  if(maxElement == NULL){
    fprintf(stdout, "PQ is empty\n");
    return NULL;
  }
  return maxElement;
}
/*****************Usage-end ************/


PQImplHandler arrayHandlerForPQ={
  arrayForPQCanHandle,
  createArrayForPQ,
  freeArrayForPQ,
  isEmptyArrayForPQ,
  insertArrayItemForPQ,
  NULL,
  delMaxArrayItemForPQ,
  NULL
};